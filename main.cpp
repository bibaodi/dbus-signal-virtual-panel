#include "backend.h"
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qpa/qplatformnativeinterface.h>
//#include <QtGui/5.12.8/QtGui/qpa/qplatformnativeinterface.h>
#include <xcb/xcb.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <QVector>

//#include "xcbkeyboard.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  /*register class defined in cpp to qml, just class no instace*/
  qmlRegisterType<BackEnd>("EsiModule", 1, 0, "BackEnd");

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
  /*#for cpp map to qml*/
  qmlRegisterType<BackEnd>("EsiModule", 1, 0, "ScreenAdapter");
  // qmlRegisterType<MyXcbEventFilter>("EsiModule", 1, 0, "MyEventFilter");
  qDebug() << "qdebug logging";
  /*for evfilter*/
  // BackEnd be;
  // MyXcbEventFilter evfilter(43, (void *)&be);
  /*qml must have same instance so use this way to export to qml*/
  // engine.rootContext()->setContextProperty("screenAdapter", evfilter);
  return app.exec();
}
