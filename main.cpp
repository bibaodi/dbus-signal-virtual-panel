#include "backend.h"
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
/*qxtglobalshortcut begin*/
#include <QTextStream>
//#include <qxtglobalshortcut.h>
/*qxtglobalshortcut--end*/
//#include <QApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVector>
//#include <X11/Xlib.h>
//#include <X11/keysym.h>
#include "mouse_manager.h"
#include <glog/logging.h>
#include <qpa/qplatformnativeinterface.h>
//#include <xcb/xcb.h>

#define KBD_EV_SERVICE_NAME "com.esi.mouse"
#define KBD_EV_OBJECT_NAME "/obj"

int init_glog(char* argv[]) {
    QString glog_file_name("google-glog:");
    const char* slash = strrchr(argv[0], '/');
    const char* argv0 = slash ? slash + 1 : argv[0];
    glog_file_name.append(argv0);
    DLOG(INFO) << "glog name:" << glog_file_name.toStdString();
    QByteArray br_glog_file_name = glog_file_name.toUtf8();
    google::InitGoogleLogging(br_glog_file_name);
    LOG(WARNING) << "Glog TEST- finish init glog Instance";
    DLOG(WARNING) << "Glog TEST- finish init glog Instance";
    FLAGS_max_log_size = 1;
    DLOG(INFO) << "Google Debug logging export class to qml finished";
    return 0;
}
#include "KbdEvAdaptor.h"
#include "KbdEvInterface.h"
#include "kbdev.h"
#include <QCoreApplication>

int init_dbus() {
    KbdEv ke;
    KbdEv* p_kbdev = new KbdEv(nullptr);
    KbdevAdaptor* p_adaptor = new KbdevAdaptor(p_kbdev);
    QDBusConnection sess_bus = QDBusConnection::sessionBus();

    if (!sess_bus.registerService(QString(KBD_EV_SERVICE_NAME))) {
        qFatal("Could not register service!");
        return -1;
    }

    if (!sess_bus.registerObject(KBD_EV_OBJECT_NAME, p_kbdev, QDBusConnection::ExportScriptableContents)) {
        qFatal("Could not register Chat object!");
        return -1;
    }
    com::esi::kbdev kbdiface(KBD_EV_SERVICE_NAME, KBD_EV_OBJECT_NAME, sess_bus);
    QObject::connect(&kbdiface, SIGNAL(key_ev_sig(QString, QString)), p_kbdev, SLOT(key_ev_slot(QString, QString)));
    return 0;
}

int main(int argc, char* argv[]) {
    init_glog(argv);
    init_dbus();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    /*register class defined in cpp to qml, just class no instace*/
    qmlRegisterType<BackEnd>("EsiModule", 1, 0, "BackEnd");
    qmlRegisterType<MouseMgr_CursorShapeArea>("EsiModule", 1, 0, "CursorShapeArea");
    // qmlRegisterSingletonInstance<MouseMgr_CursorShapeArea>("EsiModule", 1, 0, "CursorShapeArea",
    //                                                       MouseMgr_CursorShapeArea::get_instance());
    qmlRegisterSingletonInstance<ShortcutListener>("EvFilter", 1, 0, "EvFilter", ShortcutListener::get_instance());
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    /*grab-key.begin
    QTextStream out(stdout);
    QTextStream err(stderr);

    const QKeySequence shortcut("alt+y");
    const QKeySequence shortcut2("meta+t");
    QList<QKeySequence> shortcuts;
    shortcuts << shortcut << shortcut2;
    const QxtGlobalShortcut globalShortcut(shortcuts);

    if (!globalShortcut.isValid()) {
      err << QString("Error: Failed to set shortcut %1 || %2")
                 .arg(shortcut.toString(), shortcut2.toString())
          << endl;
      return 1;
    }

    out << QString("Press shortcut %1 ||%2 (or CTRL+C to exit)")
               .arg(shortcut.toString(), shortcut2.toString())
        << endl;
    QObject::connect(&globalShortcut, &QxtGlobalShortcut::activated,
                     &globalShortcut, [&](QString activated_keys) {
                       out << activated_keys << endl;
                       // backend->setKeySym(activated_keys);
                     });

    DLOG(INFO) << "finish create grab key";
    grab-key.end*/

    return app.exec();
}

// unregister_and_ungrab_key(dpy, wd_root);
