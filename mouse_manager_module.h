#ifndef MOUSE_MANAGER_MODULE_H
#define MOUSE_MANAGER_MODULE_H
#include <QObject>
enum Mouse_Control_Type {
    Mouse_Control_Type_graphic = 1000,
    Mouse_Control_Type_non_graphic = 2000,
    Mouse_Control_Type_graphic_B = 1001
};
class QMouseEvent;

class Master_Graphic : public QObject {
    Q_OBJECT
  public:
    explicit Master_Graphic(QObject* parent = nullptr) : QObject(parent) {}

  protected:
    const Mouse_Control_Type m_mouse_ctrl_type = Mouse_Control_Type_graphic;

  public:
    Mouse_Control_Type m_mouse_ctrl_category;
  signals:
    void sig_mouse_event(QMouseEvent*);

  public:
    virtual void slot_mouse_event(QMouseEvent* ev0) = 0;
};
#endif // MOUSE_MANAGER_MODULE_H
