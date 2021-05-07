#ifndef MASTER_PW_H
#define MASTER_PW_H
#include "mouse_mgr_interface.h"

class QMouseEvent;
class Master_PW : public Mouse_Mgr_Interface {
    Q_OBJECT
  public:
    explicit Master_PW(QObject* parent = nullptr);

  public slots:
    void slot_mouse_event(QMouseEvent* mev) override;
};

class Master_BOX_MOVE : public Mouse_Mgr_Interface {
    Q_OBJECT
  public:
    explicit Master_BOX_MOVE(QObject* parent = nullptr);

  public slots:
    void slot_mouse_event(QMouseEvent* mev) override;
};

class Master_BDMK : public Mouse_Mgr_Interface {
    Q_OBJECT
  public:
    explicit Master_BDMK(QObject* parent = nullptr);

  public slots:
    void slot_mouse_event(QMouseEvent* mev) override;
};

#endif // MASTER_PW_H
