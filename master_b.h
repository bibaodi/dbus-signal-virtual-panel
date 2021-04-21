#ifndef MASTER_B_H
#define MASTER_B_H

//#include <QObject>

#include "mouse_manager_module.h"

class QMouseEvent;
class Master_B : public Mouse_Master {
    Q_OBJECT
  public:
    explicit Master_B(QObject* parent = nullptr);

    // signals:
    //  void sig_mouse_event(QMouseEvent*);
  public slots:
    void slot_mouse_event(QMouseEvent*) override;
};

#endif // MASTER_B_H
