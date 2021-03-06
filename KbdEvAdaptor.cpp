/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp kbd_event.xml -a KbdEvAdaptor
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "KbdEvAdaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class KbdevAdaptor
 */

KbdevAdaptor::KbdevAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

KbdevAdaptor::~KbdevAdaptor()
{
    // destructor
}

void KbdevAdaptor::key_ev_slot(const QString &keyname, const QString &actname)
{
    // handle method call com.esi.kbdev.key_ev_slot
    QMetaObject::invokeMethod(parent(), "key_ev_slot", Q_ARG(QString, keyname), Q_ARG(QString, actname));
}

