#ifndef MOUSE_CTRL_EVENT_FILTER_H
#define MOUSE_CTRL_EVENT_FILTER_H

#include "mouse_manager_module.h"
#include <QObject>

class QMouseEvent;

class Mouse_Ctrl_Event_Filter : public QObject {
    Q_OBJECT
  public:
    explicit Mouse_Ctrl_Event_Filter(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void listenTo(QObject* object);
    Q_INVOKABLE bool cursor();
    Q_INVOKABLE void set_cursor(int);
    bool eventFilter(QObject* object, QEvent* ev) override;
    static Mouse_Ctrl_Event_Filter* get_instance();
    int get_mouse_control(
        Master_Graphic*); // need to provide a abstract class to normalize the members and signal receiver function;

  private:
    int m_cursor;
    Master_Graphic* m_current_obj = nullptr;
    void (*m_current_fun)(QMouseEvent*);
};
#endif // MOUSE_CTRL_EVENT_FILTER_H
