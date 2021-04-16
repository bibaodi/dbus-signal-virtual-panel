#include "kbdev.h"
#include <QDebug>

#include "backend.h"
#include "mouse_manager.h"
KbdEv::KbdEv(QObject* parent) : QObject(parent) {}

void KbdEv::key_ev_slot(const QString& keyname, const QString& actname) {
    qDebug() << "key_ev_slot message:" << keyname << actname;
    MouseMgr_CursorShapeArea* cur = MouseMgr_CursorShapeArea::get_instance();
    int cursorshape = actname.toInt();
    cur->set_CursorShape(cursorshape);
    return;
}
