#include "backend.h"
#include <X11/XKBlib.h>

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
  qDebug() << "init BackEnd Instance";
  // MyXcbEventFilter tmp(43, this);
  evfilter = new MyXcbEventFilter(43, this);
  qDebug() << "finish create BackEnd and EvFilter";
}

BackEnd::~BackEnd() { delete evfilter; }

QString BackEnd::userName() { return m_userName; }

void BackEnd::setUserName(const QString &userName) {
  if (userName == m_userName)
    return;

  m_userName = userName;
  emit userNameChanged();
}

const QString BackEnd::keySym() const { return m_keysym; }

void BackEnd::setKeySym(const QString ks) {
  m_keysym = ks;
  emit keySymChanged(ks);
}

MyXcbEventFilter::MyXcbEventFilter(int a, void *p)
    : be_p(static_cast<BackEnd *>(p)) {
  qDebug() << "starting EventFilter, a=" << a;
  QAbstractEventDispatcher::instance()->installNativeEventFilter(this);
  qDebug() << "finish install native event filter;";
}

bool MyXcbEventFilter::nativeEventFilter(const QByteArray &eventType,
                                         void *message, long *result) {
  //--begin
  Q_UNUSED(result);

  xcb_key_press_event_t *kev = nullptr;
  if (eventType == "xcb_generic_event_t") {
    xcb_generic_event_t *ev = static_cast<xcb_generic_event_t *>(message);
    if ((ev->response_type & 127) == XCB_KEY_PRESS)
      kev = static_cast<xcb_key_press_event_t *>(message);
  }

  if (kev != nullptr) {
    unsigned int keycode = kev->detail;
    unsigned int keystate = 0;
    if (kev->state & XCB_MOD_MASK_1)
      keystate |= Mod1Mask;
    if (kev->state & XCB_MOD_MASK_CONTROL)
      keystate |= ControlMask;
    if (kev->state & XCB_MOD_MASK_4)
      keystate |= Mod4Mask;
    if (kev->state & XCB_MOD_MASK_SHIFT)
      keystate |= ShiftMask;
    qDebug() << "KeyCode:" << keycode << ";keystate:" << keystate;
    Display *xdisplay;
    QPlatformNativeInterface *native = qApp->platformNativeInterface();
    void *display = native->nativeResourceForScreen(
        QByteArray("display"), QGuiApplication::primaryScreen());
    xdisplay = reinterpret_cast<Display *>(display);
    /*p0=disp;p1=keycode;p2=index
     * KeySym keysym = XKeycodeToKeysym(xdisplay, keycode,0);
     *XkeycodeToKeysym is deprecated
     */
    /* which declares:
         KeySym XkbKeycodeToKeysym(Display *dpy, KeyCode kc,
                                   unsigned int group, unsigned int level); */
    KeySym keysym =
        XkbKeycodeToKeysym(xdisplay, keycode, 0, keystate & ShiftMask ? 1 : 0);
    qDebug() << "keysym:" << XKeysymToString(keysym) << "(" << keysym << ")";
    be_p->setKeySym(XKeysymToString(keysym));
    // emit notify_keysym(keysym);
  }
  //--end
  return false;
}
