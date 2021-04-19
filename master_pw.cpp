#include "master_pw.h"

#include <QDebug>
#include <QMouseEvent>

Master_PW::Master_PW(QObject* parent) : Master_Graphic(parent) {
    connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
}

void Master_PW::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_pw:: ev coordinates:" << mev->x() << "," << mev->y();
    return;
}
