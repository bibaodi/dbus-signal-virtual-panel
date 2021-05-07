#ifndef MOUSE_CTRL_EVENT_FILTER_H
#define MOUSE_CTRL_EVENT_FILTER_H

#include "mouse_mgr_interface.h"
#include <QDebug>
#include <QObject>

class QMouseEvent;

struct Master_Info {
    Mouse_Mgr_Interface* obj;
    //  Mouse_Master_Type type;
    int obj_option;
};

enum Mouse_Master_Option { MMO_None = 100, MMO_Save = 101, MMO_Temp = 102, MMO_Notify = 103, MMO_Other = 104 };
enum Master_Loss_Mouse_Reason { MLMR_None = 100, MLMR_Releasing, MLMR_Preempted, MLMR_Other };

#include "master_b.h"
#include "master_pw.h"

class Mouse_Mgr_Main : public QObject {
    Q_OBJECT
  public:
    explicit Mouse_Mgr_Main(QObject* parent = nullptr) : QObject(parent), m_iter(m_master_home.end()) {}

    Q_INVOKABLE void listenTo(QObject* object);
    Q_INVOKABLE int cursor();
    Q_INVOKABLE void set_cursor(int);
    bool eventFilter(QObject* object, QEvent* ev) override;
    static Mouse_Mgr_Main* get_instance();
    // need to provide a abstract class to normalize the members and signal receiver function;
    int get_mouse_control(Mouse_Mgr_Interface*, int);
    int release_mouse_control(Mouse_Mgr_Interface*, int);
    int switch_to_next(int direction = 0);
    int cursor_switch();
    QList<Mouse_Master_Type> get_all_available_status();
  signals:
    void cursorShapeChanged(
        int new_cursor_shape); // if new_cursor_shape is minus zero then just switch between arrow and blank
  public slots:
    void messageSlot(const QString& a, const QString& b);

  private:
    QList<Master_Info> m_master_home;
    QList<Master_Info>::iterator m_iter;
    // QList<Master_Info>::reverse_iterator m_riter;
    // void emit_current_subclass_signal(QMouseEvent*);
    int remove_master_obj_from_list(Mouse_Mgr_Interface*);
    int is_have_same_type(Mouse_Mgr_Interface*);
    void make_iter_safe();
    //
    int m_cursor = 10;
    // Mouse_Mgr_Interface* m_current_obj = nullptr;
};
#endif // MOUSE_CTRL_EVENT_FILTER_H
