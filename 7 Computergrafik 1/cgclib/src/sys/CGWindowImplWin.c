#ifdef _WIN32
#include <cgclib/sys/CGWindow.h>
#include <stdio.h>
#include <windows.h>
/**
 * @brief Stores timing-related data for performance measurements.
 */
typedef struct TimingData
{
    int64_t startTime;          /**< Start time in ticks */
    float   ticksToMillisecond; /**< Conversion factor from ticks to milliseconds */
} TimingData;

/**
 * @brief Represents the Windows-specific device context used for rendering.
 */
typedef struct WindowsDeviceContext
{
    HWND       hwnd;       /**< Handle to the window */
    HDC        hdc;        /**< Handle to the device context */
    HDC        memDC;      /**< Handle to the memory device context */
    HBITMAP    hBitmap;    /**< Bitmap used for off-screen rendering */
    TimingData timingData; /**< Timing data for frame timing or profiling */
} WindowsDeviceContext;

int CreateTimingData(TimingData* const result)
{
    if (result == NULL)
    {
        return 0;
    }
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    result->startTime          = startTime.QuadPart;
    result->ticksToMillisecond = 1e3f / frequency.QuadPart;
    return 1;
}

float GetTimeSinceStart(TimingData const* const timingData)
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    return (endTime.QuadPart - timingData->startTime) * timingData->ticksToMillisecond;
}

static void ReleasePixelBuffer(PixelBuffer* result, WindowsDeviceContext* windowsDeviceContext)
{
    if (result->pixels != 0)
    {
        DeleteObject(windowsDeviceContext->hBitmap);
        DeleteDC(windowsDeviceContext->memDC);
        ReleaseDC(windowsDeviceContext->hwnd, windowsDeviceContext->hdc);
        result->pixels = NULL;
    }
}

static int32_t AcquirePixelBuffer(PixelBuffer* pixelBuffer, WindowsDeviceContext* windowsDeviceContext)
{
    if (pixelBuffer->width == 0 || pixelBuffer->height == 0)
    {
        return 0;
    }

    windowsDeviceContext->hdc   = GetDC(windowsDeviceContext->hwnd);
    windowsDeviceContext->memDC = CreateCompatibleDC(windowsDeviceContext->hdc);
    if (windowsDeviceContext->memDC == 0)
    {
        return 0;
    }
    BITMAPINFO bmi              = { 0 };
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = pixelBuffer->width;
    bmi.bmiHeader.biHeight      = pixelBuffer->height;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    windowsDeviceContext->hBitmap =
        CreateDIBSection(windowsDeviceContext->memDC, &bmi, DIB_RGB_COLORS, &pixelBuffer->pixels, NULL, 0);
    if (pixelBuffer->pixels == 0)
    {
        return 0;
    }
    if (windowsDeviceContext->hBitmap == 0)
    {
        return 0;
    }
    else
    {
        SelectObject(windowsDeviceContext->memDC, windowsDeviceContext->hBitmap);
    }
    return 1;
}

static void BlitPixelBuffer(CGWindow* window)
{
    if (window == NULL)
    {
        perror("CGWindow is NULL!");
    }

    BitBlt((*(WindowsDeviceContext*)(window->context)).hdc, 0, 0, window->pixelBuffer.width, window->pixelBuffer.height,
           (*(WindowsDeviceContext*)(window->context)).memDC, 0, 0, SRCCOPY);
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
        {
            CGWindow* window = (CGWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (window != NULL)
            {
                int width  = LOWORD(lParam);
                int height = HIWORD(lParam);
                if (width != 0 && height != 0)
                {
                    ReleasePixelBuffer(&window->pixelBuffer, &(*(WindowsDeviceContext*)(window->context)));
                    DestroyPixelBuffer(&window->pixelBuffer, false);
                    CreatePixelBuffer(&window->pixelBuffer, width, height, false);
                    if (AcquirePixelBuffer(&window->pixelBuffer, &(*(WindowsDeviceContext*)(window->context))) == 0)
                    {
                        return 0;
                    }
                }
            }
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int32_t CreateCGWindow(CGWindow* window, int32_t width, int32_t height, const char* windowTitle,
                       RenderSceneCallback renderSceneCallback)
{
    if (window == NULL)
    {
        return 0;
    }

    window->renderSceneCallback = renderSceneCallback;

    window->context = malloc(sizeof(WindowsDeviceContext));

    CreateTimingData(&(*(WindowsDeviceContext*)(window->context)).timingData);

    const char CLASS_NAME[] = "ComputerGraphicsRasterizer";
    WNDCLASS   wc           = { 0 };
    wc.lpfnWndProc          = WindowProc;
    wc.hInstance            = GetModuleHandle(NULL);
    wc.lpszClassName        = CLASS_NAME;

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    RegisterClass(&wc);

    (*(WindowsDeviceContext*)(window->context)).hwnd =
        CreateWindowEx(0, wc.lpszClassName, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                       rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, wc.hInstance, NULL);

    if ((*(WindowsDeviceContext*)(window->context)).hwnd == NULL)
    {
        return 0;
    }
    ShowWindow((*(WindowsDeviceContext*)(window->context)).hwnd, SW_SHOW);
    SetWindowLongPtr((*(WindowsDeviceContext*)(window->context)).hwnd, GWLP_USERDATA, (LONG_PTR)&window->pixelBuffer);
    CreatePixelBuffer(&window->pixelBuffer, width, height, false);
    if (AcquirePixelBuffer(&window->pixelBuffer, &(*(WindowsDeviceContext*)(window->context))) == 0)
    {
        return 0;
    }
    return 1;
}

void DestroyCGWindow(CGWindow* window)
{
    if (window == NULL)
    {
        return;
    }
    ReleasePixelBuffer(&window->pixelBuffer, &(*(WindowsDeviceContext*)(window->context)));
    DestroyPixelBuffer(&window->pixelBuffer, false);
    free(window->context);
}

int32_t RunCGWindow(CGWindow* window)
{
    MSG           msg                  = { 0 };
    double        previousTime         = GetTimeSinceStart(&(*(WindowsDeviceContext*)(window->context)).timingData);
    int32_t       frames               = 0;
    const int32_t measureFrameInterval = 256;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            window->pixelBuffer.time = GetTimeSinceStart(&(*(WindowsDeviceContext*)(window->context)).timingData);
            if (window->renderSceneCallback)
            {
                window->renderSceneCallback(window->pixelBuffer);
                BlitPixelBuffer(window);
                frames++;
                if (frames % measureFrameInterval == 0)
                {
                    double currentTime = window->pixelBuffer.time;
                    printf("%f\r", (currentTime - previousTime) / measureFrameInterval);
                    previousTime = currentTime;
                }
            }
        }
    }
    return 1;
}
#endif
