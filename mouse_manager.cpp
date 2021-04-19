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

QString MouseMgr_CursorShapeArea::messageSlot(const QString& a, const QString& b) {
    qDebug() << "MouseMgr_CursorShapeArea message slot:: a=" << a << "; b=" << b;

    if (a == QString("1")) {
        set_CursorShape(1);
    } else if (a == QString("2")) {
        set_CursorShape(2);
    } else {
        set_CursorShape(b.toInt());
    }
    return a;
}

void SingletonTypeExample::messageSlot(const QString& a, const QString& b) {
    qDebug() << "SingletonTypeExample message slot:: a=" << a << "; b=" << b;
    emit somePropertyChanged(b.toInt());
    return;
}
