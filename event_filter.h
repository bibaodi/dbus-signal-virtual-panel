#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QHash>
#include <QObject>

class QKeySequence;

class Event_filter : public QAbstractNativeEventFilter {

public:
  explicit Event_filter(QAbstractNativeEventFilter *parent = nullptr);
  ~Event_filter();

  bool enabled;
  Qt::Key key;
  Qt::KeyboardModifiers mods;
  quint32 nativeKey;
  quint32 nativeMods;
  bool registered;
  bool isEnabled() const;

  bool setShortcut(const QKeySequence &shortcut);
  bool unsetShortcut();
  bool nativeEventFilter(const QByteArray &eventType, void *message,
                         long *result) override;
  static void activateShortcut(quint32 nativeKey, quint32 nativeMods);

private:
  static quint32 nativeKeycode(Qt::Key keycode);
  static quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);

  static bool registerShortcut(quint32 nativeKey, quint32 nativeMods);
  static bool unregisterShortcut(quint32 nativeKey, quint32 nativeMods);

  static QHash<QPair<quint32, quint32>, Event_filter *> shortcuts;
signals:
  void activated(Event_filter *self);
};

#endif // EVENT_FILTER_H
