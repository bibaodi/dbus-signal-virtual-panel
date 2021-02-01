#include "backend.h"
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <glog/logging.h>
#include <qpa/qplatformnativeinterface.h>
#include <xcb/xcb.h>

#include <QVector>

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

  DLOG(INFO) << "Google Debug logging export class to qml finished";

  return app.exec();
}
