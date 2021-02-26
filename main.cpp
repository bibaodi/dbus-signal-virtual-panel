#include "backend.h"
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
/*qxtglobalshortcut begin*/
#include <QTextStream>
#include <qxtglobalshortcut.h>
/*qxtglobalshortcut--end*/
//#include <QApplication>
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
  QString glog_file_name("google-glog:");
  const char *slash = strrchr(argv[0], '/');
  const char *argv0 = slash ? slash + 1 : argv[0];
  glog_file_name.append(argv0);
  DLOG(INFO) << "glog name:" << glog_file_name.toStdString();
  QByteArray br_glog_file_name = glog_file_name.toUtf8();
  google::InitGoogleLogging(br_glog_file_name);
  LOG(WARNING) << "Glog TEST- finish init glog Instance";
  DLOG(WARNING) << "Glog TEST- finish init glog Instance";
  FLAGS_max_log_size = 1;
  DLOG(INFO) << "Google Debug logging export class to qml finished";
  /*grab-key.begin*/
  QTextStream out(stdout);
  QTextStream err(stderr);

  const QKeySequence shortcut("alt+y");
  const QKeySequence shortcut2("ctrl+shift+f3");
  const QxtGlobalShortcut globalShortcut(shortcut);
  const QxtGlobalShortcut globalShortcut2(shortcut2);

  if (!globalShortcut.isValid() || !globalShortcut2.isValid()) {
    err << QString("Error: Failed to set shortcut %1 || %2")
               .arg(shortcut.toString(), shortcut2.toString())
        << Qt::endl;
    return 1;
  }

  out << QString("Press shortcut %1 ||%2 (or CTRL+C to exit)")
             .arg(shortcut.toString(), shortcut2.toString())
      << Qt::endl;

  QObject::connect(
      &globalShortcut, &QxtGlobalShortcut::activated, &globalShortcut,
      [&] { out << QLatin1String("Shortcut pressed!") << Qt::endl; });

  QObject::connect(
      &globalShortcut2, &QxtGlobalShortcut::activated, &globalShortcut2,
      [&] { out << QLatin1String("Shortcut2 pressed!") << Qt::endl; });
  DLOG(INFO) << "finish create grab key";
  /*grab-key.end*/

  return app.exec();
}

// unregister_and_ungrab_key(dpy, wd_root);
