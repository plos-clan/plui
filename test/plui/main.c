#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <X11/keysym.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <type.h>

u32 screen_width  = 800;
u32 screen_height = 600;

Display *display;
int      screen;
Window   window;

static void init_xlib() {
  display     = XOpenDisplay(NULL);
  screen      = DefaultScreen(display);
  Window root = RootWindow(display, screen);
  window      = XCreateSimpleWindow(display, root, 0, 0, screen_width, screen_height, 1,
                                    BlackPixel(display, screen), WhitePixel(display, screen));
  XSelectInput(display, window,
               ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask |
                   ButtonReleaseMask | ButtonMotionMask | EnterWindowMask | LeaveWindowMask |
                   StructureNotifyMask);
  XMapWindow(display, window);
  XFlush(display);

  { // 隐藏鼠标指针
    // XColor  black   = {};
    // uint8_t data[8] = {};
    // Pixmap  bitmap  = XCreateBitmapFromData(display, root, data, 8, 8);
    // Cursor  cursor  = XCreatePixmapCursor(display, bitmap, bitmap, &black, &black, 0, 0);
    // XDefineCursor(display, window, cursor);
    // XFreeCursor(display, cursor);
    // XFreePixmap(display, bitmap);
  }
}

XShmSegmentInfo shm_info;
XImage         *image;

void create_img(int32_t width, int32_t height) {
  if (image) {
    XShmDetach(display, &shm_info);
    shmfree(shm_info.shmaddr);
    XDestroyImage(image);
  }

  image            = XShmCreateImage(display, NULL, 24, ZPixmap, 0, &shm_info, width, height);
  shm_info.shmaddr = image->data = shmalloc(width * height * 4, &shm_info.shmid);
  shm_info.readOnly              = false;
  XShmAttach(display, &shm_info);
}

void main_loop() {
  XEvent event;
  while (1) {
    XNextEvent(display, &event);

    if (image && pdds_flush()) {
      memcpy(image->data, pdds_pixels(), screen_width * screen_height * 4);
      XShmPutImage(display, window, DefaultGC(display, screen), image, 0, 0, 0, 0, screen_width,
                   screen_height, true);
    }
  }

quit:
  return;
}

int main() {
  init_xlib();

  main_loop();

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
