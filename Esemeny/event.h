#ifndef EVENT_H
#define EVENT_H

#include "evententry.h"

#include <QList>
#include <QObject>

class Event : public QObject
{
    Q_OBJECT
public:
    typedef QList<EventEntry*> Entries;
    explicit Event(QObject *parent = 0);
    Entries entries() const;
    EventEntry *createEntry();
    bool deleteEntry( EventEntry *entry );

signals:
    void entryAdded( EventEntry *entry );
    void entryRemoved( EventEntry *entry );

public slots:

private:

    Entries m_entries;

};

#endif
