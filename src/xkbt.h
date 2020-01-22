#include "defs.h"

class XKBt : public QObject,  public QRunnable
{
    Q_OBJECT
public:
    void run();
signals:
    void xkbSignal(XEvent *ev);
};
