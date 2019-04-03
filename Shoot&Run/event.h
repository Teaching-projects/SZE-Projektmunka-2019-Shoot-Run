#ifndef EVENT_H
#define EVENT_H
#include "image.h"
#include "track.h"
#include "date.h"


class event
{
private:
    string name;
    date date;
    vector<image*> images;
    vector<Track> tracks;
public:
    event(string,unsigned int, unsigned int, unsigned int);
    void imageAdd(image);
    void trackAdd(Track);
    void sortt();
    void print();


    vector<image *> getImages() const;
    vector<Track> getTracks() const;
};





#endif // EVENT_H
