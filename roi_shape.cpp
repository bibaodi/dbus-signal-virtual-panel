#include "roi_shape.h"
#include <QPainter>
// ROI_Shape::ROI_Shape(QQuickItem* parent) : QQuickPaintedItem(parent) {}

QString ROI_Shape::name() const { return m_name; }

void ROI_Shape::setName(const QString& name) { m_name = name; }

QColor ROI_Shape::color() const { return m_color; }

void ROI_Shape::setColor(const QColor& color) { m_color = color; }

//![1]
void ROI_Shape::paint(QPainter* painter) {
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}
void ROI_Shape::clearChart() {
    setColor(QColor(Qt::red));
    update();

    emit chartCleared();
}
///
#include <QDebug>
#include <QMouseEvent>
ROI_Shape::ROI_Shape(QQuickItem* parent) : Mouse_Mgr_Interface(parent) {
    QObject::connect(this, SIGNAL(sig_mouse_event(QMouseEvent*)), this, SLOT(slot_mouse_event(QMouseEvent*)));
    m_mouse_ctrl_type = MMT_Null;
}

void ROI_Shape::slot_mouse_event(QMouseEvent* mev) {
    qDebug() << "Master_b:: ev coordinates:" << mev->x() << "," << mev->y();

    return;
}
