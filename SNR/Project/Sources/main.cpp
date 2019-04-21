#include <iostream>
#include <memory>
#include <iomanip>

#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include <odb/qt/lazy-ptr.hxx>
#include <QApplication>
//#include <QCryptographicHash>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>

#include <QMessageBox> //TODO

#include "event.h"
#include "event-odb.hxx"
#include "image.h"
#include "image-odb.hxx"
//#include "user.h"
//#include "user-odb.hxx"
#include "tardis.h"
#include "tardis-odb.hxx"
#include "track.h"
#include "track-odb.hxx"
#include "database.h"
#include "gui.h"
#include "exif.h"
#include "qdownloader.h"

#include <windows.h>
#include <stdio.h>


#define earthRadiusKm 6371.0 //TODO
#define M_PI 3.14159265358979323846 //TODO

/*

int Track_upload(QString Name_PATH, QSharedPointer<event> event_id, QSharedPointer<user> user_id, QSharedPointer<track> track_id) {
	QSharedPointer<odb::core::database> db = create_database();


	QFile file(Name_PATH);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "File open error:" << file.errorString();
		return 1;
	}
	QXmlStreamReader inputStream(&file);
	while (!inputStream.atEnd() && !inputStream.hasError())
	{
		odb::core::transaction t(db->begin());

		inputStream.readNext();
		double lat, lon;
		if (inputStream.isStartElement()) {
			QString name = inputStream.name().toString();
			if (name == "wpt") {
				lat = inputStream.attributes().value("lat").toDouble();
				lon = inputStream.attributes().value("lon").toDouble();
			}
			if (name == "time") {
				QSharedPointer<tardis> filler(new tardis(track_id, lon, lat, (QDateTime::fromString(inputStream.readElementText(), "yyyy-MM-ddThh:mm:ssZ"))));
				filler->track(track_id);
				track_id->tardises().push_back(filler);
				db->update(track_id);
				db->persist(filler);
				t.commit();

			}
		}
	}
	std::cout << "Testing";
	return 1;
}



double deg2rad(double deg) {
	return (deg * M_PI / 180);
}
double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}
double distance(image image, tardis tardis) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(tardis.getLatitude());
	lon1r = deg2rad(tardis.getLongitude());
	lat2r = deg2rad(image.getLatitude());
	lon2r = deg2rad(image.getLongitude());
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)) * 1000;
}

void load(std::string path) {
	char *cstr = new char[path.length() + 1];
	strcpy(cstr, path.c_str());
	FILE *fp = fopen(cstr, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned long fsize = ftell(fp);
	rewind(fp);
	unsigned char *buf = new unsigned char[fsize];
	if (fread(buf, 1, fsize, fp) != fsize) {
		printf("Can't read file.\n");
		delete[] buf;
	}
	fclose(fp);
	easyexif::EXIFInfo result;
	int code = result.parseFrom(buf, fsize);
	delete[] buf;
	if (code) {
		printf("Error parsing EXIF: code %d\n", code);
	}
	std::cout << result.GeoLocation.Longitude <<"\t"<<
				 result.GeoLocation.Latitude  <<"\t"<<
				 result.DateTime.c_str()      <<"\n";
}

*/




int main(int argc, char *argv[])
{/*
	/*
	user	---					user_name	 password		first_name		last_name	 email			registration_date
	event	---					name
	image	-event-user-		PATH		 event          user            datetime     longitude		latitude
	track	-event-user-		event		 user
	tardis	-track-				track		 longitude		latitude		time
	*/

	FreeConsole();
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
	freopen("CON", "r", stdin);

	
		/*DB TODO;
		QSharedPointer<odb::core::database> db = TODO.create_database();
		odb::core::transaction t(db->begin());

		QDateTime now = QDateTime::currentDateTime();
		QSharedPointer<user> user1(new user("ati703", "testPW", "Attila", "Lebbenszki", "lebbenszkiattilagmailcom", now));
		QSharedPointer<event> event1(new event("first_event", now));
		QSharedPointer<event> event2(new event("second_event", now));
		QSharedPointer<event> event3(new event("third_event", now));

		event1->user(user1); 	event2->user(user1); 	event3->user(user1);
		db->persist(user1);
		db->persist(event1);	db->persist(event2);	db->persist(event3);
		t.commit();*/



	//QDownloader imagedownload;
	//imagedownload.setFile("https://dl.dropboxusercontent.com/s/nw6wd1msc7ifuou/blue.png");
	//https://dl.dropboxusercontent.com/s/x65l1cu3eoin9kt/green.png
	//https://dl.dropboxusercontent.com/s/cs2bnp80frxttpe/red.png

	QApplication a(argc, argv);
    gui gui;
    gui.show();
	return a.exec();
}

