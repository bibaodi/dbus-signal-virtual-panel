#include "master_b.h"
#include <QDebug>
#include <QMouseEvent>
Master_B::Master_B(QObject* parent) : Mouse_Master(parent) {
    connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    m_mouse_ctrl_type = MMT_Null;
}

void Master_B::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_b:: ev coordinates:" << mev->x() << "," << mev->y();

    return;
}
