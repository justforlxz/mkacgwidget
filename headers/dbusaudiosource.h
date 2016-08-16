#ifndef DBUSAUDIOSOURCE_H
#define DBUSAUDIOSOURCE_H
#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

struct SourcePortStruct {
    QString id;
    QString name;
    uchar index;
};

typedef QList<SourcePortStruct> SourcePortList;

Q_DECLARE_METATYPE(SourcePortStruct)
Q_DECLARE_METATYPE(SourcePortList)

QDBusArgument &operator<<(QDBusArgument &argument, const SourcePortStruct &port);
const QDBusArgument &operator>>(const QDBusArgument &argument, SourcePortStruct &port);

/*
 * Proxy class for interface com.deepin.daemon.Audio.Source
 */
class DBusAudioSource: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage &msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count()) {
            return;
        }
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "com.deepin.daemon.Audio.Source") {
            return;
        }
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString & prop, keys) {
            const QMetaObject *self = metaObject();
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
                    Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
    }
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.daemon.Audio.Source"; }
    static inline const char *staticServerPath()
    { return "com.deepin.daemon.Audio"; }

public:
    DBusAudioSource(const QString &path, QObject *parent = 0);

    ~DBusAudioSource();

    Q_PROPERTY(SourcePortStruct ActivePort READ activePort NOTIFY ActivePortChanged)
    inline SourcePortStruct activePort() const
    { return qvariant_cast< SourcePortStruct >(property("ActivePort")); }

    Q_PROPERTY(double Balance READ balance NOTIFY BalanceChanged)
    inline double balance() const
    { return qvariant_cast< double >(property("Balance")); }

    Q_PROPERTY(double BaseVolume READ baseVolume NOTIFY BaseVolumeChanged)
    inline double baseVolume() const
    { return qvariant_cast< double >(property("BaseVolume")); }

    Q_PROPERTY(QString Description READ description NOTIFY DescriptionChanged)
    inline QString description() const
    { return qvariant_cast< QString >(property("Description")); }

    Q_PROPERTY(double Fade READ fade NOTIFY FadeChanged)
    inline double fade() const
    { return qvariant_cast< double >(property("Fade")); }

    Q_PROPERTY(bool Mute READ mute NOTIFY MuteChanged)
    inline bool mute() const
    { return qvariant_cast< bool >(property("Mute")); }

    Q_PROPERTY(QString Name READ name NOTIFY NameChanged)
    inline QString name() const
    { return qvariant_cast< QString >(property("Name")); }

    Q_PROPERTY(SourcePortList Ports READ ports NOTIFY PortsChanged)
    inline SourcePortList ports() const
    { return qvariant_cast< SourcePortList >(property("Ports")); }

    Q_PROPERTY(bool SupportBalance READ supportBalance NOTIFY SupportBalanceChanged)
    inline bool supportBalance() const
    { return qvariant_cast< bool >(property("SupportBalance")); }

    Q_PROPERTY(bool SupportFade READ supportFade NOTIFY SupportFadeChanged)
    inline bool supportFade() const
    { return qvariant_cast< bool >(property("SupportFade")); }

    Q_PROPERTY(double Volume READ volume NOTIFY VolumeChanged)
    inline double volume() const
    { return qvariant_cast< double >(property("Volume")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusObjectPath> GetMeter()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetMeter"), argumentList);
    }

    inline QDBusPendingReply<> SetBalance(double in0, bool in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QStringLiteral("SetBalance"), argumentList);
    }

    inline QDBusPendingReply<> SetFade(double in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("SetFade"), argumentList);
    }

    inline QDBusPendingReply<> SetMute(bool in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("SetMute"), argumentList);
    }

    inline QDBusPendingReply<> SetPort(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("SetPort"), argumentList);
    }

    inline QDBusPendingReply<> SetVolume(double in0, bool in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QStringLiteral("SetVolume"), argumentList);
    }

Q_SIGNALS: // SIGNALS
// begin property changed signals
    void ActivePortChanged();
    void BalanceChanged();
    void BaseVolumeChanged();
    void DescriptionChanged();
    void FadeChanged();
    void MuteChanged();
    void NameChanged();
    void PortsChanged();
    void SupportBalanceChanged();
    void SupportFadeChanged();
    void VolumeChanged();
};

namespace com
{
namespace deepin
{
namespace daemon
{
namespace Audio
{
typedef ::DBusAudioSource Source;
}
}
}
}
#endif // DBUSAUDIOSOURCE_H
