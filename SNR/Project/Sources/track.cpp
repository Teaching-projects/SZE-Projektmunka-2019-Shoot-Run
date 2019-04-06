#include "track.h"

track::track(QLazySharedPointer<event_type> event_id, QLazySharedPointer<user_type> user_id) :
	event_id(event_id),user_id(user_id){}