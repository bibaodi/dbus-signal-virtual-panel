#include "master_pw.h"

#include <QDebug>
#include <QMouseEvent>

Master_PW::Master_PW(QObject* parent) : Mouse_Mgr_Interface(parent) {
    connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    m_mouse_ctrl_type = MMT_SV;
}

void Master_PW::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_pw:: ev coordinates:" << mev->x() << "," << mev->y();
    return;
}

Mouse_Master_Type Mouse_Mgr_Interface::get_type() { return m_mouse_ctrl_type; }

Master_BOX_MOVE::Master_BOX_MOVE(QObject* p) : Mouse_Mgr_Interface(p) {
    connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    m_mouse_ctrl_type = MMT_Box_Move;
}

void Master_BOX_MOVE::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_BOX_MOVE:: ev coordinates:" << mev->x() << "," << mev->y();
    return;
}

Master_BDMK::Master_BDMK(QObject* p) : Mouse_Mgr_Interface(p) {
    connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    m_mouse_ctrl_type = MMT_BodyMark;
}

void Master_BDMK::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_BDMK:: ev coordinates:" << mev->x() << "," << mev->y();
    return;
}
