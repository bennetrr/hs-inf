#ifndef _WIN32
#include <cgclib/contrib/tigr/tigr.h>
#include <cgclib/sys/CGWindow.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Tigr* screen;
} TigrContext;

int32_t CreateCGWindow(CGWindow* window, int32_t width, int32_t height, const char* windowTitle,
                       RenderSceneCallback renderSceneCallback)

{
    if (window == NULL)
    {
        return 0;
    }

    window->context = malloc(sizeof(TigrContext));
    if (window->context == NULL)
    {
        return 0;
    }
    TigrContext* tigrContex = (TigrContext*)window->context;

    window->renderSceneCallback = renderSceneCallback;
    CreatePixelBuffer(&window->pixelBuffer, width, height, false);

    tigrContex->screen = tigrWindow(width, height, windowTitle, TIGR_FIXED);
    if (tigrContex->screen == NULL)
    {
        free(tigrContex);
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

    TigrContext* tigrContex = (TigrContext*)window->context;
    if (tigrContex == NULL)
    {
        return;
    }

    window->pixelBuffer.pixels = (uint32_t*)(tigrContex->screen->pix);

    tigrFree(tigrContex->screen);
    free(window->context);
}

int32_t RunCGWindow(CGWindow* window)
{
    if (window == NULL)
    {
        return 0;
    }

    TigrContext* tigrContex = (TigrContext*)window->context;

    int32_t       frames               = 0;
    const int32_t measureFrameInterval = 32;
    double        previousTime         = 0.0;

    while (!tigrClosed(tigrContex->screen))
    {
        if (window->renderSceneCallback != NULL)
        {
            window->pixelBuffer.time += 1000.0f * tigrTime();
            window->pixelBuffer.pixels = (uint32_t*)(tigrContex->screen->pix);
            window->renderSceneCallback(window->pixelBuffer);
        }
        tigrUpdate(tigrContex->screen);
        frames++;
        if (frames % measureFrameInterval == 0)
        {
            double currentTime = window->pixelBuffer.time;
            fprintf(stderr, "%f\r", (currentTime - previousTime) / measureFrameInterval);
            previousTime = currentTime;
        }
    }
    return 1;
}
#endif
