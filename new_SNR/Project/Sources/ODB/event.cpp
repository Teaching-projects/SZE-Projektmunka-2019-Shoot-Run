#include "event.h"

void odbevent::Accept(){
    event_accepted = true;
}

QString odbevent::getname(){
    return QString::fromStdString(event_name);
}

QDateTime odbevent::getdate(){
    return event_date;
}

int odbevent::getid(){
    return event_id;
}
