#include "event.h"

void odbevent::Accept(){
    event_accepted = true;
}

QString odbevent::getName(){
    return QString::fromStdString(event_name);
}

QDateTime odbevent::getDate(){
    return event_date;
}

int odbevent::getId(){
    return event_id;
}

bool odbevent::isAccepted()
{
    return event_accepted;
}
