#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#define DEBUG printf

/* typedef VkResult (*genSurface)
(VkInstance,
 VkXlibSurfaceCreateInfoKHR*,
 VkAllocationCallbacks*,
 VkSurfaceKHR*);
genSurface surface_khr = (genSurface) vkCreateXlibSurfaceKHR;
*/

VkResult create_surface(VkInstance instance, SDL_Window* w,
			VkAllocationCallbacks* allocators,
			VkSurfaceKHR* surface) {

  DEBUG("Start create_surface\n");
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_bool b = SDL_GetWindowWMInfo(w, &info);
  DEBUG("Window information acquired \n");

  if(b && info.subsystem == SDL_SYSWM_X11) {
    DEBUG("X11 subsystem identified \n");

    VkXlibSurfaceCreateInfoKHR vkInfo;
    vkInfo.sType=VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    vkInfo.pNext = NULL;
    vkInfo.flags = 0;
    vkInfo.dpy = info.info.x11.display;
    vkInfo.window = info.info.x11.window;

    /*  if (surface_khr == NULL ) {
      DEBUG("Acquiring vkCreateXlibSurfaceKHR pointer\n");
      surface_khr =(genSurface)
	vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR");
      printf("Pointer acquired:%x\n", surface_khr);
      if (surface_khr == NULL) {
	return (-7);;
      }
      } */
    return vkCreateXlibSurfaceKHR(instance,&vkInfo,allocators,surface);

  }
  else {

    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
		 "Unsupported system: %s", SDL_GetError());
  }
    /*    const char *subsystem = "an unknown system!";
    switch(info.subsystem) {
      case SDL_SYSWM_UNKNOWN:   break;
      case SDL_SYSWM_WINDOWS:
	subsystem = "Microsoft Windows(TM)";  break;
      case SDL_SYSWM_X11:
	subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
      case SDL_SYSWM_WINRT:
	subsystem = "WinRT";                  break;
#endif
      case SDL_SYSWM_DIRECTFB:
	subsystem = "DirectFB";               break;
      case SDL_SYSWM_COCOA:
	subsystem = "Apple OS X";             break;
      case SDL_SYSWM_UIKIT:
	subsystem = "UIKit";                  break;

#if SDL_VERSION_ATLEAST(2, 0, 2)
      case SDL_SYSWM_WAYLAND:
	subsystem = "Wayland";                break;
      case SDL_SYSWM_MIR:
	subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
      case SDL_SYSWM_ANDROID:
	subsystem = "Android";                break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
      case SDL_SYSWM_VIVANTE:
	subsystem = "Vivante";                break;
#endif
    }
    */
}
