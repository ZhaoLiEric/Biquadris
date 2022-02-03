#include "window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Xwindow::Xwindow(int width, int height) {
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix =
      XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0, (XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[11][10] = {"white",     "black",     "Crimson",  "Lime",
                             "Dark Blue", "Goldenrod", "Indigo",   "Coral",
                             "Web Gray",  "Sienna",    "Deep Pink"};

  cmap = DefaultColormap(d, DefaultScreen(d));
  for (int i = 0; i < 11; ++i) {
    XParseColor(d, cmap, color_vals[i], &xcolour);
    XAllocColor(d, cmap, &xcolour);
    colours[i] = xcolour.pixel;
  }

  XSetForeground(d, gc, colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height =
      height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d, True);

  XSelectInput(d, w, ExposureMask);
  XFlush(d);
  XNextEvent(d, &event);  // Hang until the window is ready.
  XSelectInput(d, w, 0);
  /* select kind of events we are interested in */
  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  // XFontStruct* ft = XLoadQueryFont(d, "*-helvetica-*-18-*");

  // // XSetForeground(d, gc, get_color(col));

  // XSetFont(d, gc, ft->fid);
  // XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  // char* name = "-*-dejavu sans-bold-r-*-*-*-220-100-100-*-*-iso8859-1";
  // XFontStruct* fs = XLoadQueryFont(d, "*-helvetica-*-18-*");
  Font font =
      XLoadFont(d, "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-9");
  // XSetFont(d, gc, fs->fid);
  char *char_arr;
  char_arr = &msg[0];
  XTextItem items[] = {char_arr, int(msg.length()), 0, font};
  XDrawText(d, w, DefaultGC(d, s), x, y, items,
            sizeof(items) / (sizeof((items)[0])));

  // XTextItem* tItem =
  //     new XTextItem{(char*)msg.c_str(), int(msg.length()), 1, font->fid};
  // XDrawText(d, w, DefaultGC(d, s), x, y, tItem, 1);
  // XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

int Xwindow::getEvent() {
  XSelectInput(d, w, KeyPressMask);
  XNextEvent(d, &event);
  /* keyboard events */
  if (event.type == KeyPress) {
    // cout << event.xkey.keycode << endl;
    return event.xkey.keycode;
  }
  XFlush(d);
  return 0x09;  // escape
}
