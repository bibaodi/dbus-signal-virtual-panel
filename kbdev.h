#ifndef KBDEV_H
#define KBDEV_H

#include <QObject>

#define KBD_EV_IFACE_NAME "com.esi.kbdev"

class KbdEv : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", KBD_EV_IFACE_NAME)
  public:
    explicit KbdEv(QObject* parent = nullptr);

  Q_SIGNALS:
    Q_SCRIPTABLE void key_ev_sig(const QString& keyname,
                                 const QString& actname);
  public Q_SLOTS:
    Q_SCRIPTABLE void key_ev_slot(const QString& keyname,
                                  const QString& actname);
};

#endif // KBDEV_H
