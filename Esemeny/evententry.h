#ifndef EVENTENTRY_H
#define EVENTENTRY_H

#include <QDate>
#include <QObject>


class EventEntry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList photoes READ photoes WRITE setPhotoes NOTIFY photoesChanged)
    Q_PROPERTY(QDate date READ birthday WRITE setDate NOTIFY dateChanged)
public:
    explicit EventEntry(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QStringList photoes() const;
    void setPhotoes(const QStringList &photoes);

    QDate date() const;
    void setDate(const QDate &date);

signals:

    void nameChanged();
    void photoesChanged();
    void dateChanged();

public slots:

private:
    QString m_name;
    QStringList m_photoes;
    QDate m_date;
};

#endif
