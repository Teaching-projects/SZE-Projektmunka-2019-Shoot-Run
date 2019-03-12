#include "event.h"

Event::Event(QObject *parent) : QObject(parent)
{

}
Event::Entries Event::entries() const
{
    return m_entries;
}
EventEntry *Event::createEntry()
{
    EventEntry *result = new EventEntry( this );
    if ( result ) {
        m_entries.append( result );
        emit entryAdded( result );
    }
    return result;
}
bool Event::deleteEntry(EventEntry *entry)
{
    if ( m_entries.contains( entry ) ) {
        emit entryRemoved( entry );
        m_entries.removeAll( entry );
        entry->deleteLater();
        return true;
    }
    return false;
}
