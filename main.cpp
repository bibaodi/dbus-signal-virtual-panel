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

int register_and_grab_key(Display *dpy0, Window root) {

  int shortcuts[10] = {0};

  // Get the root window -- so keys will be global
  Display *dpy = XOpenDisplay(0);
  root = DefaultRootWindow(dpy);
  DLOG(INFO) << "wd_rood=" << root;
  shortcuts[0] = XKeysymToKeycode(dpy, XStringToKeysym("F2"));
  if (NoSymbol == shortcuts[0]) {
    LOG(ERROR) << "Xkeysym not exist" << shortcuts[0];
  }
  XGrabKey(dpy, shortcuts[0], ControlMask, root, True, GrabModeAsync,
           GrabModeAsync);
  XGrabKey(dpy, shortcuts[0], 0, root, True, GrabModeAsync, GrabModeAsync);
  DLOG(INFO) << "register GrabKey finish: keycode=" << shortcuts[0];
  return 0;
}

int unregister_and_ungrab_key(Display *dpy, Window root) {
  int shortcuts[10] = {0};

  shortcuts[0] = XKeysymToKeycode(dpy, XStringToKeysym("F2"));
  XUngrabKey(dpy, shortcuts[0], 0, root);
  return 0;
}

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
  Display *dpy = XOpenDisplay(0);
  if (!dpy) {
    DLOG(INFO) << "no dpy available.%p" << dpy;
    return 0;
  }
  DLOG(INFO) << "dpy (0) available.%p" << dpy;
  Window wd_root = 0;
  register_and_grab_key(dpy, wd_root);
  DLOG(INFO) << "finish create grab key";
  /*grab-key.end*/

  return app.exec();
}

// unregister_and_ungrab_key(dpy, wd_root);
