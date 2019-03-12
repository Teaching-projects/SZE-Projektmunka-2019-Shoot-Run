#include "eventcontroller.h"

EventController::EventController(Event *event, QObject *parent) :
    QObject(parent),
    m_event( event )
{
    /*
     * Via Q_ASSERT we ensure that we got valid pointers. It is good practise to make as much
     * use of these asserts as possible to find issues early in development.
     */
    Q_ASSERT( event != nullptr );
}
EventEntry* EventController::createEntry()
{
    auto result = m_event->createEntry();
    if ( result ) {
        result->setName( tr( "New entry" ) );
    }
    return result;
}
bool EventController::deleteEntry(EventEntry *entry)
{
    return m_event->deleteEntry( entry );
}

