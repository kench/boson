#include <cstdlib>
#include <cstring>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#if __has_include(<SDL3/SDL_openxr.h>)
#include <SDL3/SDL_openxr.h>
#endif
#include <SDL3/SDL_main.h>

#if __has_include(<SDL3/SDL_openxr.h>)
const bool kSDLHasOpenXRSupport = true;
#else
const bool kSDLHasOpenXRSupport = false;
#endif
const char* kDummySDLVideoDriver = "dummy";

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
/* These will be populated by SDL */
XrInstance xr_instance = XR_NULL_HANDLE;
XrSystemId xr_system_id = 0;

SDL_PropertiesID getGPUDeviceProperties() {
    SDL_PropertiesID properties = SDL_CreateProperties();
    #if __has_include(<SDL3/SDL_openxr.h>)
    SDL_SetBooleanProperty(properties, SDL_PROP_GPU_DEVICE_CREATE_XR_ENABLE_BOOLEAN, true);
    SDL_SetPointerProperty(properties, SDL_PROP_GPU_DEVICE_CREATE_XR_INSTANCE_POINTER, &xr_instance);
    SDL_SetPointerProperty(properties, SDL_PROP_GPU_DEVICE_CREATE_XR_SYSTEM_ID_POINTER, &xr_system_id);
    #endif
    return properties;
}

SDL_WindowFlags getSDLWindowFlags() {
    const char* env_sdl_video_driver = std::getenv("SDL_VIDEO_DRIVER");
    if (env_sdl_video_driver == nullptr) {
        return SDL_WINDOW_RESIZABLE;
    } else if (std::strcmp(env_sdl_video_driver, kDummySDLVideoDriver)) {
        #if defined(__APPLE__)
        return SDL_WINDOW_METAL;
        #elif defined(_WIN32)
        return SDL_WINDOW_RESIZABLE;
        #else
        return SDL_WINDOW_VULKAN;
        #endif
    } else {
        // Disable hardware acceleration when dummy video driver is used.
        return SDL_WINDOW_RESIZABLE;
    }
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Boson", "1.0", "tv.kenley.boson.Boson");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_PropertiesID gpuDeviceProperties = getGPUDeviceProperties();
    SDL_GPUDevice *device = SDL_CreateGPUDeviceWithProperties(gpuDeviceProperties);
    if (device == NULL) {
        SDL_Log("Failed to create GPU device: %s", SDL_GetError());
    }
    SDL_DestroyProperties(gpuDeviceProperties);

    if (!kSDLHasOpenXRSupport) {
        SDL_Log("SDL3 library does not have OpenXR support");
    } else if (xr_instance == XR_NULL_HANDLE) {
        SDL_Log("XR instance unavailable");
    } else {
        SDL_Log("XR instance initialized");
    }

    if (!SDL_CreateWindowAndRenderer("Boson", 1280, 720, getSDLWindowFlags(), &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type != SDL_EVENT_MOUSE_MOTION) {
        SDL_Log("Event received: %d", static_cast<int>(event->type));
    }
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}

int SDLCALL app_callback(int argc, char *argv[])
{
    SDL_Log("Hello, SDL!");
    return SDL_EnterAppMainCallbacks(
        argc, argv,
        SDL_AppInit, SDL_AppIterate, SDL_AppEvent, SDL_AppQuit
    );
}