#ifndef MOUSE_MANAGER_MODULE_H
#define MOUSE_MANAGER_MODULE_H
#include <QObject>
enum Mouse_Master_Type {
    MMT_Graphic = 1000,
    MMT_Null = 1001,
    MMT_SV = 1002,
    MMT_Box_Move = 1003,
    MMT_Box_Size = 1004,
    MMT_Cine = 1100,
    MMT_Cine_Img = 1101,
    MMT_Cine_Pw = 1102,
    MMT_Pan = 1200,
    MMT_Application = 2000,
    MMT_BodyMark = 2001,
    MMT_Annotation = 2002,
    MMT_Measures = 2003,
    MMT_Cursor = 3000,
};
class QMouseEvent;
class QWheelEvent;
#include <QDBusConnection>
class Mouse_Mgr_Interface : public QObject {
    Q_OBJECT
  public:
    explicit Mouse_Mgr_Interface(QObject* parent = nullptr) : QObject(parent) {
        QDBusConnection sess = QDBusConnection::sessionBus();
        sess.connect(QString(), QString(), "org.example.chat", "message", this, SLOT(messageSlot(QString, QString)));
    }
    Mouse_Master_Type get_type();
    bool is_application() {
        if (m_mouse_ctrl_type > MMT_Application && m_mouse_ctrl_type < MMT_Cursor)
            return true;
        else
            return false;
    }

  protected:
    Mouse_Master_Type m_mouse_ctrl_type = MMT_Null;
  signals:
    void sig_mouse_event(QMouseEvent*);
    void sig_wheel_event(QWheelEvent*);
    void sig_loss_mouse(int);

  public:
    virtual void slot_mouse_event(QMouseEvent* ev0) = 0;
    // virtual void slot_wheel_event(QWheelEvent*) = 0;
    // public slots:
    //  virtual void messageSlot(const QString& a, const QString& b) = 0;
};
#endif // MOUSE_MANAGER_MODULE_H
