#include "mouse_ctrl_event_filter.h"
#include <QDebug>
#include <QMouseEvent>

Mouse_Ctrl_Event_Filter* Mouse_Ctrl_Event_Filter::get_instance() {
    static Mouse_Ctrl_Event_Filter obj;
    return &obj;
}

bool Mouse_Ctrl_Event_Filter::eventFilter(QObject* obj, QEvent* ev) {
    // qDebug() << "eventfilter: obj-name=" << obj->objectName();
    if (QEvent::MouseMove == ev->type()) {
        QMouseEvent* mev = static_cast<QMouseEvent*>(ev);
        qDebug() << "Mouse_Ctrl_Event_Filter:: mouse event move<" << mev->x() << "," << mev->y() << ">;";
        if (m_current_obj) {
            emit m_current_obj->sig_mouse_event(mev);
        }
        return true;
    }
    return false;
}

void Mouse_Ctrl_Event_Filter::listenTo(QObject* object) {
    if (object) {
        qDebug() << "listenTo called with obj:" << object->objectName();
        object->installEventFilter(this);
    }
}

void Mouse_Ctrl_Event_Filter::set_cursor(int condition) {
    if (condition > 0) {
        m_cursor = true;
    } else {
        m_cursor = false;
    }
}

bool Mouse_Ctrl_Event_Filter::cursor() { return m_cursor; }

#include "master_b.h"
int Mouse_Ctrl_Event_Filter::get_mouse_control(Master_Graphic* mg) {
    m_current_obj = mg;
    if (Mouse_Control_Type_graphic_B == mg->m_mouse_ctrl_category) {
        qDebug() << "B mode obj";
        Master_B* mb = static_cast<Master_B*>(mg);
    }
    return 0;
}
