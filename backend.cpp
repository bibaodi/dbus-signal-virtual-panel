#include "backend.h"
//#include <X11/XKBlib.h>
#include <glog/logging.h>
#include <string>

BackEnd::BackEnd(QObject* parent) : QObject(parent) {
    DLOG(INFO) << "init BackEnd Instance";
    DLOG(INFO) << "finish create BackEnd and EvFilter";
}

BackEnd::~BackEnd() {
    // delete evfilter;
}

QString BackEnd::userName() { return m_userName; }

void BackEnd::setUserName(const QString& userName) {
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

const QString BackEnd::keySym() const { return m_keysym; }

void BackEnd::setKeySym(const QString& p_keysym) {
    /*为了简单方便，这里使用字符串，后续要改为int，然后判断函数在cpp中实现，导入到qml中，决定哪一个button被激活*/
    m_keysym = p_keysym;
    emit keySymChanged(p_keysym);
}

void BackEnd::slot_receive(QString* sc) { DLOG(INFO) << "sc->shortcut().toString().toStdString():" << sc; }

ShortcutListener* ShortcutListener::get_instance() {
    static ShortcutListener obj;
    return &obj;
}

bool ShortcutListener::eventFilter(QObject* obj, QEvent* ev) {
    // qDebug() << "eventfilter: obj-name=" << obj->objectName();
    if (QEvent::MouseMove == ev->type()) {
        QMouseEvent* mev = static_cast<QMouseEvent*>(ev);
        qDebug() << "mouse event move<" << mev->x() << "," << mev->y() << ">;";
        return true;
    }
    return false;
}

void ShortcutListener::listenTo(QObject* object) {
    if (object) {
        qDebug() << "listenTo called with obj:" << object->objectName();
        object->installEventFilter(this);
    }
}

void ShortcutListener::set_cursor(int condition) {
    if (condition > 0) {
        m_cursor = true;
    } else {
        m_cursor = false;
    }
}

bool ShortcutListener::cursor() { return m_cursor; }

//////////////////////////

QsltCursorShapeArea::QsltCursorShapeArea(QQuickItem* parent) : QQuickItem(parent), m_currentShape(-1) {}
//#include <Qt>
#include <QCursor>
void QsltCursorShapeArea::set_CursorShape(int cursorShape) {
    if (m_currentShape == cursorShape)
        return;

    // setCursor(cursorShape);
    emit cursorShapeChanged();
    m_currentShape = cursorShape;
}

int QsltCursorShapeArea::cursor_Shape() const { return m_currentShape; }
