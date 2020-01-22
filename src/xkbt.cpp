#include "xkbt.h"

void XKBt::run()
{

    XEvent e;
    Display *d;

    if (!(d = XOpenDisplay(NULL))) {
        /* qDebug()  << " QXKB:cannot open display"; */
    }

    XKeysymToKeycode(d, XK_F1);

    int xkbEventType;
    XkbQueryExtension(d, 0, &xkbEventType, 0, 0, 0);
    XkbSelectEvents(d, XkbUseCoreKbd, XkbAllEventsMask, XkbAllEventsMask);

    XSync(d, False);

    while (1) {
        XNextEvent(d, &e);
        emit xkbSignal(&e);
    }
}

/* void XKBt::xkbSignal(void) */
/* { */
/*     qDebug() << " QXKB:group is changed"; */

/* } */

