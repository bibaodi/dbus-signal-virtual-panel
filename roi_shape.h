#ifndef ROI_SHAPE_H
#define ROI_SHAPE_H

#include "mouse_mgr_interface.h"
#include <QColor>
#include <QtQuick/QQuickPaintedItem>
class QMouseEvent;
class Master_B;
class ROI_Shape : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    QML_ELEMENT
  public:
    ROI_Shape(QQuickItem* parent = 0);

    QString name() const;
    void setName(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    void paint(QPainter* painter);
    Q_INVOKABLE void clearChart();

  signals:
    void chartCleared();
  public slots:
    void slot_mouse_event(QMouseEvent* mev);
    void slot_wheel_event(QWheelEvent*);

  private:
    QString m_name;
    QColor m_color;
    Master_B* local_mb;
    qreal x = 80, y = 90;
};

#endif // ROI_SHAPE_H
