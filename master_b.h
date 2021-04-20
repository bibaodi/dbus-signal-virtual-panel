#ifndef MASTER_B_H
#define MASTER_B_H

//#include <QObject>

#include "mouse_manager_module.h"

class QMouseEvent;
class Master_B : public Master_Graphic {
    Q_OBJECT
  public:
    explicit Master_B(QObject* parent = nullptr);

  signals:
    void sig_mouse_event(QMouseEvent*);
  public slots:
    void slot_mouse_event(QMouseEvent*) override;

  public:
    Mouse_Control_Type m_mouse_ctrl_category = Mouse_Control_Type_graphic_B;

  private:
    const Mouse_Control_Type m_mouse_ctrl_type = Mouse_Control_Type_graphic;
};

#endif // MASTER_B_H
