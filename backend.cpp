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

//////////////////////////
