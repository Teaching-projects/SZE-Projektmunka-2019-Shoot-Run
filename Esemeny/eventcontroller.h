#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include "event.h"

#include <QObject>

class EventController : public QObject
{
    Q_OBJECT
public:
    explicit EventController(Event *event, QObject *parent = 0);
    EventEntry *createEntry();
    bool deleteEntry( EventEntry *entry );

private:
    Event *m_event;
};

#endif
