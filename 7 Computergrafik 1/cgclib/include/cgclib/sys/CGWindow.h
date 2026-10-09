#ifndef CG_WINDOW_H
#define CG_WINDOW_H
#include <cgclib/sys/PixelBuffer.h>
#include <stdint.h>

/**
 * @brief Callback function type for rendering a scene.
 *
 * @param pixelBuffer The pixel buffer to render into.
 * @return int32_t Status code (e.g., 0 for success).
 */
typedef int32_t (*RenderSceneCallback)(PixelBuffer pixelBuffer);

/**
 * @brief Represents a CG window with rendering capabilities.
 */
typedef struct CGWindow
{
    PixelBuffer         pixelBuffer;         /**< The pixel buffer used for rendering */
    RenderSceneCallback renderSceneCallback; /**< Callback function for rendering the scene */
    void*               context;             /**< Windows-specific rendering context */
} CGWindow;

/**
 * @brief Creates a CG window and initializes its rendering context.
 *
 * @param window Pointer to the CGWindow structure to initialize.
 * @param width Width of the window in pixels.
 * @param height Height of the window in pixels.
 * @param windowTitle Title of the window.
 * @param renderSceneCallback Callback function for rendering the scene.
 * @return int32_t Status code (0 for success, non-zero for failure).
 */
int32_t CreateCGWindow(CGWindow* window, int32_t width, int32_t height, const char* windowTitle,
                       RenderSceneCallback renderSceneCallback);

/**
 * @brief Destroys the CG window and releases associated resources.
 *
 * @param window Pointer to the CGWindow structure to destroy.
 */
void DestroyCGWindow(CGWindow* window);

/**
 * @brief Runs the CG window's main loop, handling rendering and events.
 *
 * @param window Pointer to the CGWindow structure.
 * @return int32_t Status code (0 for success, non-zero for failure).
 *
 */
int32_t RunCGWindow(CGWindow* window);

#endif
