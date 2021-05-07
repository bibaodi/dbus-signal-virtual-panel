#ifndef ROI_SHAPE_H
#define ROI_SHAPE_H

#include "mouse_mgr_interface.h"
#include <QColor>
#include <QtQuick/QQuickPaintedItem>
class QMouseEvent;
class ROI_Shape : public Mouse_Mgr_Interface {
  public:
    ROI_Shape(QQuickItem* parent = 0);

    QString name() const;
    void setName(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    void paint(QPainter* painter);
    Q_INVOKABLE void clearChart() override;

  signals:
    void chartCleared();
  public slots:
    void slot_mouse_event(QMouseEvent*) override;

  private:
    QString m_name;
    QColor m_color;
};

#endif // ROI_SHAPE_H
