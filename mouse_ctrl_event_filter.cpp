#include "mouse_ctrl_event_filter.h"
#include <QDebug>
#include <QMouseEvent>

#include "master_b.h"
#include "master_pw.h"

Mouse_Mgr_Main* Mouse_Mgr_Main::get_instance() {
    static Mouse_Mgr_Main obj;
    return &obj;
}

bool Mouse_Mgr_Main::eventFilter(QObject* obj, QEvent* ev) {
    Q_UNUSED(obj)
    if (cursor() != Qt::BlankCursor) {
        return false;
    }
    if (QEvent::MouseMove == ev->type()) {
        QMouseEvent* mev = static_cast<QMouseEvent*>(ev);
        // qDebug() << "Mouse_Mgr_Main:: mouse event move<" << mev->x() << "," << mev->y() << ">;";
        if (m_iter != m_master_home.end()) {
            qDebug() << "before emit signal";
            emit m_iter->obj->sig_mouse_event(mev);
        }
        return true;
    }
    return false;
}

void Mouse_Mgr_Main::listenTo(QObject* object) {
    if (object) {
        qDebug() << "listenTo called with obj:" << object->objectName();
        object->installEventFilter(this);
    }
}

void Mouse_Mgr_Main::set_cursor(int cur) {
    qDebug() << "cur=" << cur;
    if (cur >= 0) {
        m_cursor = cur;
    }
}

int Mouse_Mgr_Main::cursor() { return m_cursor; }

///
/// \brief Mouse_Mgr_Main::is_have_same_type
/// \param mm_ptr
/// \return -1 if not find same type; else return the index of the first occur;
///
int Mouse_Mgr_Main::is_have_same_type(Mouse_Mgr_Interface* mm_ptr) {
    if (m_master_home.isEmpty()) {
        return -1;
    }
    for (int i = 0; i < m_master_home.size(); i++) {
        qDebug() << "size=" << m_master_home.size() << "; i=" << i;
        if (m_master_home.at(i).obj->get_type() == mm_ptr->get_type()) {
            qDebug() << "got same type: mmptr=" << mm_ptr->get_type()
                     << "home's=" << m_master_home.at(i).obj->get_type() << "i=" << i;
            return i;
        }
    }
    return -1;
}
///
/// \brief Mouse_Mgr_Main::get_mouse_control
/// this function will preempt the mouse from old obj to mg,
/// if old-obj is app then just pop else save it.
/// \param mm_ptr
/// \param save_option
/// \return
///

int Mouse_Mgr_Main::get_mouse_control(Mouse_Mgr_Interface* mm_ptr, int save_option) {
    emit cursorShapeChanged(Qt::BlankCursor);
    // m_current_obj = get_sub_class_ptr(mm_ptr, type);
    qDebug() << "save option is::" << save_option << "type=" << mm_ptr->get_type();
    // 01-judge previous obj type and do something.
    if (m_master_home.end() != m_iter) { // not the first one
        if (m_iter->obj->is_application()) {
            qDebug() << "application: default not save it when it lost mouse";
            // m_master_home.removeFirst();
            remove_master_obj_from_list(m_iter->obj);
        } else if (m_iter->obj->get_type() < MMT_Application) {
            qDebug() << "graphics: default will save it when it lost mouse";
        } else {
            qDebug() << "cursor: ignore";
        }
        emit m_iter->obj->sig_loss_mouse(MLMR_Preempted);
    }

    int ret = -1;
    while ((ret = is_have_same_type(mm_ptr)) >= 0) { // fool-prof measures
        qDebug() << "remove all same type obj" << ret;
        m_master_home.removeAt(ret);
    }
    // 02-change 2 current
    Master_Info mi = {mm_ptr, save_option};
    m_master_home.prepend(mi);
    m_iter = m_master_home.begin();
    return 0;
}

////
/// \brief Mouse_Mgr_Main::release_mouse_control
/// retrive the mouse control privilege and give it to the next obj which saved in master_home, send notify to the
/// obj which will loss mouse. \param mm_ptr: the obj which current has mouse control privilege \param
/// release_option: reserved param \return int: 0 is success.
///

int Mouse_Mgr_Main::release_mouse_control(Mouse_Mgr_Interface* mm_ptr, int release_option) {
    qDebug() << "release mouse control called: release_option=" << release_option;
    remove_master_obj_from_list(mm_ptr);
    emit mm_ptr->sig_loss_mouse(MLMR_Releasing);
    make_iter_safe();
    return 0;
}

///
/// \brief Mouse_Mgr_Main::remove_master_obj_from_list
/// \param mm_ptr
/// \return
///
int Mouse_Mgr_Main::remove_master_obj_from_list(Mouse_Mgr_Interface* mm_ptr) {
    if (m_master_home.isEmpty()) {
        qDebug() << "list is null return -1;";
        return 0;
    }
    if (m_master_home.begin()->obj == mm_ptr) {
        qDebug() << "remove first";
        m_master_home.removeFirst();
        return 1;

    } else if (m_master_home.rbegin()->obj == mm_ptr) {
        qDebug() << "remove last";
        m_master_home.removeLast();
        return 1;
    } else {
        for (int i = 0; i < m_master_home.size(); i++) {
            qDebug() << "size=" << m_master_home.size() << "; i=" << i;
            if (m_master_home.at(i).obj == mm_ptr) {
                qDebug() << "got it in home and remove in middle";
                m_master_home.removeAt(i);
                return 1;
            } else {
                qDebug() << "not find obj , remove null";
            }
        }
        return 0;
    }
}

///
/// \brief Mouse_Mgr_Main::emit_current_subclass_signal
/// !!!must specify the sub-class otherwise base-class's signal emitted
/// \param mev mouse event
///
/*
void Mouse_Mgr_Main::emit_current_subclass_signal(QMouseEvent* mev) {
    auto base_obj = m_current_obj;

    if (MMT_SV == base_obj->get_type()) {
        qDebug() << "PW mode obj";
        Master_PW* obj = static_cast<Master_PW*>(base_obj);
        emit obj->sig_mouse_event(mev);
    } else if (MMT_Null == base_obj->get_type()) {
        qDebug() << "B mode obj";
        Master_B* obj = static_cast<Master_B*>(base_obj);
        emit obj->sig_mouse_event(mev);
    } else if (MMT_Annotation == base_obj->get_type()) {
        qDebug() << "annotation obj";
    } else if (MMT_BodyMark == base_obj->get_type()) {
        qDebug() << "bodymark obj";
    } else if (MMT_Box_Move == base_obj->get_type()) {
        qDebug() << "box move obj";
    } else if (MMT_Box_Size == base_obj->get_type()) {
        qDebug() << "box size obj";
    }
    return;
}*/

///
/// \brief Mouse_Mgr_Main::make_iter_safe
/// assume list is not empty; if m_iter is not available then assign the last to it.
void Mouse_Mgr_Main::make_iter_safe() {
    if (m_master_home.isEmpty()) {
        m_iter = m_master_home.end();
        emit cursorShapeChanged(Qt::ArrowCursor);
        return;
    }
    QList<Master_Info>::Iterator tmp = m_master_home.begin();
    for (; tmp != m_master_home.end(); tmp++) {
        if (tmp == m_iter) {
            return;
        }
    }
    m_iter = m_master_home.begin();
    qDebug() << "after [get] begin type is:" << m_iter->obj->get_type();
}

int Mouse_Mgr_Main::cursor_switch() {
    if (cursor() == Qt::BlankCursor) {
        m_iter = m_master_home.end();
    } else if (cursor() != Qt::BlankCursor) {
        m_iter = m_master_home.begin();
    }
    emit cursorShapeChanged(-1);
    return 0;
}

int Mouse_Mgr_Main::switch_to_next(int direction) {
    if (m_iter == m_master_home.end()) {
        return -1;
    }
    if (MMT_Null == m_iter->obj->get_type()) {
        // todo: does current is cursor then hide it
        emit cursorShapeChanged(Qt::BlankCursor);
        qDebug() << "hide cursor";
    }
    if (!direction) {
        m_iter++;
    } else {
        m_iter--;
    }
    if (m_master_home.end() == m_iter) {
        m_iter = m_master_home.begin();
    } else if (m_master_home.begin() - 1 == m_iter) {
        m_iter = m_master_home.end() - 1;
    }
    if (MMT_Null == m_iter->obj->get_type()) {
        // todo: equal to cursor show
        emit cursorShapeChanged(Qt::ArrowCursor);
        qDebug() << "show cursor";
    } else {
        emit cursorShapeChanged(Qt::BlankCursor);
    }
    make_iter_safe();
    // m_current_obj = m_iter->obj;
    return 0;
}

QList<Mouse_Master_Type> Mouse_Mgr_Main::get_all_available_status() {
    QList<Master_Info>::reverse_iterator tmp = m_master_home.rbegin();
    QList<Mouse_Master_Type> list;
    while (tmp != m_master_home.rend()) {
        qDebug() << "Type:::" << tmp->obj->get_type();
        list.append(tmp->obj->get_type());
        tmp++;
    }
    return list;
}

#include "master_b.h"
#include "master_pw.h"
#include "mouse_ctrl_event_filter.h"
Master_B* global_mb = new Master_B();
Master_PW* global_mpw = new Master_PW();
Master_BDMK* global_bdmk = new Master_BDMK();
Master_BOX_MOVE* global_box_move = new Master_BOX_MOVE();

void Mouse_Mgr_Main::messageSlot(const QString& a, const QString& b) {
    qDebug() << "Mouse_Mgr_Main message slot:: a=" << a << "; b=" << b;
    // emit cursorShapeChanged(b.toInt());
    if (a == "get") {
        qDebug() << "inter mode-get branch";
        if (b == QString("b")) {
            get_mouse_control(global_mb, 1001);
        } else if (b == QString("pw")) {
            get_mouse_control(global_mpw, 1002);
        } else if (b == "bdmk") {
            get_mouse_control(global_bdmk, 2002);
        } else if (b == "boxm") {
            get_mouse_control(global_box_move, 1003);
        } else if (b == "all") {
            get_all_available_status();
        } else if (b == "s0") {
            switch_to_next(0);
        } else if (b == "s1") {
            switch_to_next(1);
        } else if (b == "sc") {
            cursor_switch();
        }
    } else if (a == "release") {
        qDebug() << "inter mode-release branch";
        if (b == QString("b")) {
            release_mouse_control(global_mb, 1001);
        } else if (b == QString("pw")) {
            release_mouse_control(global_mpw, 1002);
        } else if (b == "bdmk") {
            release_mouse_control(global_bdmk, 2002);
        } else if (b == "boxm") {
            release_mouse_control(global_box_move, 1003);
        }
    }
    return;
}
