#include "track.h"

track::track(odb::tr1::lazy_weak_ptr<event_type> event_track_, odb::tr1::lazy_shared_ptr<user_type> user_track_):
	event_track_(event_track_), user_track_(user_track_)
{}