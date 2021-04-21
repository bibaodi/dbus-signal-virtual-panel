#include "mouse_manager.h"

#include <QCursor>

MouseMgr_CursorShapeArea* MouseMgr_CursorShapeArea::get_instance() {
    static MouseMgr_CursorShapeArea instance;
    return &instance;
}
MouseMgr_CursorShapeArea::MouseMgr_CursorShapeArea(QQuickItem* parent) : QQuickItem(parent), m_currentShape(-1) {}

void MouseMgr_CursorShapeArea::set_CursorShape(int cursorShape) {
    if (m_currentShape == cursorShape)
        return;

    setCursor(QCursor((Qt::CursorShape)cursorShape));
    qDebug() << ">>>>>set cursor" << cursorShape;
    emit cursorShapeChanged();
    m_currentShape = cursorShape;
}

int MouseMgr_CursorShapeArea::cursor_Shape() const { return m_currentShape; }

Mouse_Manager::Mouse_Manager() {}

#include "master_b.h"
#include "master_pw.h"
#include "mouse_ctrl_event_filter.h"
Master_B* global_mb = new Master_B();
Master_PW* global_mpw = new Master_PW();
Master_BDMK* global_bdmk = new Master_BDMK();
Master_BOX_MOVE* global_box_move = new Master_BOX_MOVE();

QString MouseMgr_CursorShapeArea::messageSlot(const QString& a, const QString& b) {
    qDebug() << "MouseMgr_CursorShapeArea message slot:: a=" << a << "; b=" << b;

    if (a == QString("1")) {
        set_CursorShape(1);
    } else if (a == QString("2")) {
        set_CursorShape(2);
    } else if (a == QString("cursor")) {
        qDebug() << "inter cursor branch";
        set_CursorShape(b.toInt());
    } else if (a == "get") {
        qDebug() << "inter mode-get branch";
        if (b == QString("b")) {
            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_mb, 1000);
        } else if (b == QString("pw")) {

            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_mpw, 1010);
        }
    } else if (a == "release") {
        qDebug() << "inter mode-release branch";
        if (b == QString("b")) {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_mb, 1000);
        } else if (b == QString("pw")) {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_mpw, 1010);
        }
    }
    return a;
}

void SingletonTypeExample::messageSlot(const QString& a, const QString& b) {
    qDebug() << "SingletonTypeExample message slot:: a=" << a << "; b=" << b;
    emit somePropertyChanged(b.toInt());
    if (a == "get") {
        qDebug() << "inter mode-get branch";
        if (b == QString("b")) {
            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_mb, 1001);
        } else if (b == QString("pw")) {
            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_mpw, 1002);
        } else if (b == "bdmk") {
            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_bdmk, 2002);
        } else if (b == "boxm") {
            Mouse_Mgr_Event_Filter::get_instance()->get_mouse_control(global_box_move, 1003);
        } else if (b == "all") {
            Mouse_Mgr_Event_Filter::get_instance()->get_all_available_status();
        }
    } else if (a == "release") {
        qDebug() << "inter mode-release branch";
        if (b == QString("b")) {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_mb, 1001);
        } else if (b == QString("pw")) {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_mpw, 1002);
        } else if (b == "bdmk") {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_bdmk, 2002);
        } else if (b == "boxm") {
            Mouse_Mgr_Event_Filter::get_instance()->release_mouse_control(global_box_move, 1003);
        }
    }
    return;
}
