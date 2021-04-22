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
