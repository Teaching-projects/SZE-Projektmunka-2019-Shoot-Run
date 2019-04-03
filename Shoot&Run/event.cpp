#include "event.h"
#include <algorithm>


bool comp(image* a, image* b)
{
    return a->getDate().durationinseconds() < b->getDate().durationinseconds();
}

vector<image *> event::getImages() const
{
    return images;
}

vector<Track> event::getTracks() const
{
    return tracks;
}

event::event(string name, unsigned int y,unsigned int m,unsigned int d):name(name),date(y,m,d)
{

}

void event::imageAdd(image i)
{
    images.push_back(&i);
}

void event::trackAdd(Track t)
{
    tracks.push_back(t);
}


void event::sortt(){
    sort(images.begin(),images.end(),comp);
}

void event::print()
{
    for(auto i:images)
        i->print();
}

