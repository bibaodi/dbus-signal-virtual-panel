#include "backend.h"
#include <X11/XKBlib.h>
#include <glog/logging.h>
#include <string>

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
  DLOG(INFO) << "init BackEnd Instance";
  evfilter = new MyXcbEventFilter(43, this);
  DLOG(INFO) << "finish create BackEnd and EvFilter";
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

void BackEnd::setKeySym(const QString &p_keysym) {
  /*为了简单方便，这里使用字符串，后续要改为int，然后判断函数在cpp中实现，导入到qml中，决定哪一个button被激活*/
  m_keysym = p_keysym;
  emit keySymChanged(p_keysym);
}

MyXcbEventFilter::MyXcbEventFilter(int a, void *p)
    : be_p(static_cast<BackEnd *>(p)) {
  DLOG(INFO) << "starting EventFilter, a=" << a;
  QAbstractEventDispatcher::instance()->installNativeEventFilter(this);
  DLOG(INFO) << "finish install native event filter;";
}

bool MyXcbEventFilter::nativeEventFilter(const QByteArray &eventType,
                                         void *message, long *result) {

  Q_UNUSED(result);

  xcb_key_press_event_t *kev = nullptr;
  if (eventType == "xcb_generic_event_t") {
    xcb_generic_event_t *ev = static_cast<xcb_generic_event_t *>(message);
    if ((ev->response_type & 127) == XCB_KEY_PRESS)
      kev = static_cast<xcb_key_press_event_t *>(message);
  }

  QString key_modifier;
  if (kev != nullptr) {
    unsigned int keycode = kev->detail;
    unsigned int keystate = 0;
    if (kev->state & XCB_MOD_MASK_1) {
      keystate |= Mod1Mask;
      key_modifier += "alt;";
    }
    if (kev->state & XCB_MOD_MASK_CONTROL) {
      keystate |= ControlMask;
      key_modifier += "ctrl;";
    }
    if (kev->state & XCB_MOD_MASK_4) {
      keystate |= Mod4Mask;
      key_modifier += "mod4;";
    }
    if (kev->state & XCB_MOD_MASK_SHIFT) {
      keystate |= ShiftMask;
      key_modifier += "shift;";
    }
    DLOG(INFO) << "KeyCode:" << keycode
               << ";keystate:" << key_modifier.toStdString();

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
                                   unsigned int group, unsigned int level);
    */
    KeySym keysym =
        XkbKeycodeToKeysym(xdisplay, keycode, 0, keystate & ShiftMask ? 1 : 0);
    QString s_keysym(XKeysymToString(keysym));
    DLOG(INFO) << "keysym:" << s_keysym.toStdString() << "(" << keysym << ")";
    LOG(INFO) << "TEST-init BackEnd Instance" << s_keysym.toStdString();
    LOG(WARNING) << "TEST-init BackEnd Instance" << s_keysym.toStdString();
    LOG(ERROR) << "TEST-init BackEnd Instance" << s_keysym.toStdString();
    /*LOG(FATAL) << "TEST-init BackEnd Instance" << s_keysym.toStdString();
     *this will end the process, be carefule to use it.
     * */
    QString combine_keystring = key_modifier + "+" + s_keysym;
    int idx_comma = combine_keystring.indexOf(';');
    if (idx_comma > 0) {
      DLOG(INFO) << "combine" << combine_keystring.left(idx_comma).toStdString()
                 << idx_comma;
    } else {
      int n = combine_keystring.indexOf('+');
      int len = combine_keystring.length();
      DLOG(INFO) << "no-modifier"
                 << combine_keystring.right(len - n - 1).toStdString() << len
                 << n;
    }
    be_p->setKeySym(combine_keystring);
  }

  return false;
}
