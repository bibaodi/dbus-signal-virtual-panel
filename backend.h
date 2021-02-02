#ifndef BACKEND_H
#define BACKEND_H

#include <qqml.h>

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QString>

#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qpa/qplatformnativeinterface.h>
#include <xcb/xcb.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <QVector>
class MyXcbEventFilter;
class BackEndData;

class BackEnd : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
  Q_PROPERTY(QString keySym READ keySym WRITE setKeySym NOTIFY keySymChanged)

public:
  explicit BackEnd(QObject *parent = nullptr);
  ~BackEnd();
  QString userName();
  void setUserName(const QString &userName);

  const QString keySym() const;
  void setKeySym(const QString &ks);

signals:
  void userNameChanged();
  void keySymChanged(const QString ks);

private:
  QString m_userName;
  QString m_keysym;
  MyXcbEventFilter *evfilter;
};

class MyXcbEventFilter : public QAbstractNativeEventFilter {

public:
  bool nativeEventFilter(const QByteArray &eventType, void *message,
                         long *) override;

  MyXcbEventFilter(int a, void *p);

private:
  BackEnd *be_p;
};

#endif // BACKEND_H
