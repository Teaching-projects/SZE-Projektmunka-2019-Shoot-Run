#include "track.h"

track::track(QLazySharedPointer<event_type> event_track_, QLazySharedPointer<user_type> user_track_) :
	event_track_(event_track_),user_track_(user_track_){}