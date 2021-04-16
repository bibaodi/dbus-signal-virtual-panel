#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QString>
#include <qqml.h>
//#include <qxtglobalshortcut.h>

#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qpa/qplatformnativeinterface.h>
//

//#include <X11/Xlib.h>
//#include <X11/keysym.h>

#include <QEvent>
#include <QVector>
class MyXcbEventFilter;
class BackEndData;

class BackEnd : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString keySym READ keySym WRITE setKeySym NOTIFY keySymChanged)

  public:
    explicit BackEnd(QObject* parent = nullptr);
    ~BackEnd();
    QString userName();
    void setUserName(const QString& userName);

    const QString keySym() const;
    void setKeySym(const QString& ks);

  signals:
    void userNameChanged();
    void keySymChanged(const QString ks);
    void globalShotcut(const QString gskeys);
  public slots:
    void slot_receive(QString*);

  private:
    QString m_userName;
    QString m_keysym;
    // MyXcbEventFilter *evfilter;
};

class MyXcbEventFilter : public QAbstractNativeEventFilter {

  public:
    bool nativeEventFilter(const QByteArray& eventType, void* message, long*) override;

    MyXcbEventFilter(int a, void* p);

  private:
    BackEnd* be_p;
};

class ShortcutListener : public QObject {
    Q_OBJECT
  public:
    ShortcutListener(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void listenTo(QObject* object);
    Q_INVOKABLE bool cursor();
    Q_INVOKABLE void set_cursor(int);
    bool eventFilter(QObject* object, QEvent* ev) override;
    static ShortcutListener* get_instance();

  private:
    int m_cursor;
};

#endif // BACKEND_H
