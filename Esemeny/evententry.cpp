#include "evententry.h"

EventEntry::EventEntry(QObject *parent) : QObject(parent)
{

}

QString EventEntry::name() const
{
    return m_name;
}

void EventEntry::setName(const QString &name)
{

    if ( m_name != name ) {
        m_name = name;
        emit nameChanged();
    }
}

QStringList EventEntry::photoes() const
{
    return m_photoes;
}

void EventEntry::setPhotoes(const QStringList &photoes)
{
    if ( m_photoes != photoes ) {
        m_photoes = photoes;
        emit photoesChanged();
    }
}

QDate EventEntry::date() const
{
    return m_date;
}

void EventEntry::setDate(const QDate &date)
{
    if ( m_date != date ) {
        m_date = date;
        emit dateChanged();
    }
}

