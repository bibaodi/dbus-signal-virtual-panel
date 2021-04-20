#ifndef MASTER_PW_H
#define MASTER_PW_H
#include "mouse_manager_module.h"

class QMouseEvent;
class Master_PW : public Master_Graphic {
    Q_OBJECT
  public:
    explicit Master_PW(QObject* parent = nullptr);

  signals:
    void sig_mouse_event(QMouseEvent*);

  public slots:
    void slot_mouse_event(QMouseEvent* mev) override;

  private:
    const Mouse_Control_Type m_mouse_ctrl_type = Mouse_Control_Type_graphic;
};

#endif // MASTER_PW_H
