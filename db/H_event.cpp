#include "H_event.h"


std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

H_event::H_event(std::string event_name, unsigned int submitter_id) : event_name(event_name), submitter_id(submitter_id) {
	submit_date = currentDateTime();
}

