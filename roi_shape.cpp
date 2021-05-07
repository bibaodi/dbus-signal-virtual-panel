#include "roi_shape.h"
#include "master_b.h"
#include "mouse_ctrl_event_filter.h"
#include <QPainter>
ROI_Shape::ROI_Shape(QQuickItem* parent) : QQuickPaintedItem(parent) {
    local_mb = new Master_B();
    connect(local_mb, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    connect(local_mb, SIGNAL(sig_wheel_event(QWheelEvent*)), this, SLOT(slot_wheel_event(QWheelEvent*)));
    Mouse_Mgr_Main::get_instance()->get_mouse_control(local_mb, 1001);
}

QString ROI_Shape::name() const { return m_name; }

void ROI_Shape::setName(const QString& name) { m_name = name; }

QColor ROI_Shape::color() const { return m_color; }

void ROI_Shape::setColor(const QColor& color) { m_color = color; }

//![1]
void ROI_Shape::paint(QPainter* painter) {
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawChord(boundingRect().adjusted(1, 1, -1, -1), x * 16, y * 16);
}
void ROI_Shape::clearChart() {
    setColor(QColor(Qt::red));
    update();
    emit chartCleared();
}

void ROI_Shape::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "ROI_Shape:: ev coordinates:" << mev->x() << "," << mev->y();
    setColor(QColor(mev->x() % 255, mev->y() % 255, mev->x() % 255));
    update();
    return;
}
void ROI_Shape::slot_wheel_event(QWheelEvent* wev) {
    QPoint numDegree = wev->angleDelta() / 8;
    if (numDegree.y() > 0) {
        x += 10;
        y += 10;
    } else if (numDegree.y() < 0) {
        x -= 10;
        y -= 10;
    }
    qDebug() << "x*16/16:" << x << "y*16/16" << y;
    update();
}
