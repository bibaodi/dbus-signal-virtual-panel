#include "event_filter.h"

#include <QVector>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <xcb/xcb.h>

Event_filter::Event_filter(QAbstractNativeEventFilter *parent) {
  QAbstractEventDispatcher::instance()->installNativeEventFilter(this);
}

bool Event_filter::nativeEventFilter(const QByteArray &eventType, void *message,
                                     long *result) {
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

    activateShortcut(keycode,
                     // Mod1Mask == Alt, Mod4Mask == Meta
                     keystate &
                         (ShiftMask | ControlMask | Mod1Mask | Mod4Mask));
  }
  return false;
}

QHash<QPair<quint32, quint32>, Event_filter *> Event_filter::shortcuts;

void Event_filter::activateShortcut(quint32 nativeKey, quint32 nativeMods) {
  Event_filter *shortcut = shortcuts.value(qMakePair(nativeKey, nativeMods));
  if (shortcut && shortcut->isEnabled())
    emit shortcut->activated(shortcut);
}
