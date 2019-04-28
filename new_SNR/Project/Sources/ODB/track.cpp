#include "track.h"

track::track(QLazySharedPointer<odbevent_type> event_id, QLazySharedPointer<user_type> user_id) :
    event_id(event_id),user_id(user_id){}

int track::getID(){
    return track_id;
}
