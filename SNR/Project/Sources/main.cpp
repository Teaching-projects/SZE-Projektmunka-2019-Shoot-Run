#include <iostream>
#include <memory>
#include <iomanip>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <QApplication>
#include <QCryptographicHash>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>

#include <QMessageBox> //TODO

#include "event.h"
#include "event-odb.hxx"
#include "image.h"
#include "image-odb.hxx"
#include "user.h"
#include "user-odb.hxx"
#include "tardis.h"
#include "tardis-odb.hxx"
#include "track.h"
#include "track-odb.hxx"
#include "database.h"
#include "gui.h"
#include "exif.h"


#include <windows.h>
#include <stdio.h>


#define earthRadiusKm 6371.0 //TODO
#define M_PI 3.14159265358979323846 //TODO


double ran(double const range_min, double const range_max)
{
	static unsigned long long const mant_mask53(9007199254740991);
	static double const i_to_d53(1.0 / 9007199254740992.0);
	unsigned long long const r((unsigned long long(rand()) | (unsigned long long(rand()) << 15) | (unsigned long long(rand()) << 30) | (unsigned long long(rand()) << 45)) & mant_mask53);
	return range_min + i_to_d53 * double(r)*(range_max - range_min);
}

void password_hash(std::string &password, QDateTime current_date) {
	QString Q_date = current_date.toString();
	QString Q_password = QString::fromStdString(password);

	QCryptographicHash::Algorithm algo = QCryptographicHash::Sha512;
	const int rounds = 1000;
	QByteArray hash = (Q_date + Q_password).toUtf8();
	for (int i = 0; i < rounds; ++i) {
		hash = QCryptographicHash::hash(hash, algo);
	}
	QString hashedPass = QString(hash.toBase64());
	password = hashedPass.toUtf8().constData();
}

int user_exist(std::string user_name, std::string email) {
	typedef odb::query<user> query;
	QSharedPointer<odb::core::database> db = create_database();
	QSharedPointer<user> exists = db->query_one<user>(query::user_name == user_name || query::email == email);
	if (exists.get() == 0)
		return 0;
	return 1;
}

int user_correct(std::string user_name, std::string password) {
	typedef odb::query<user> query;
	QSharedPointer<odb::core::database> db = create_database();
	QSharedPointer<user> exists_name = db->query_one<user>(query::user_name == user_name);
	if (exists_name.get() != 0) {
		password_hash(password, exists_name->getRegistretionDate());
		QSharedPointer<user> exists_password = db->query_one<user>(query::user_name == user_name && query::password == password);
		if (exists_password.get() != 0)
			return 1;
	}
	return 0;
}

int registration(std::string user_name, std::string password, std::string first_name, std::string last_name, std::string email)
{
	QSharedPointer<odb::core::database> db = create_database();
	odb::session s;
	odb::core::transaction t(db->begin());

	if (!user_exist(user_name, email)){
		QDateTime registration_date = QDateTime::currentDateTime();
		password_hash(password, registration_date);
		QSharedPointer<user> user_new(new user(user_name, password , first_name, last_name, email, registration_date));
		db->persist(user_new);
		t.commit();
		std::cout << "\nUser registered" << std::endl;
		return 1;
	}
	std::cout << "\nUser name or email address already taken!" << std::endl;
	return 0;
};

int login(std::string user_name, std::string password) {
	QSharedPointer<odb::core::database> db = create_database();
	odb::session s;
	odb::core::transaction t(db->begin());
	if (user_correct(user_name, password)) {
		std::cout << "\nValid name and password!" << std::endl;
		return 1;
	}
	std::cout << "\nWrong name or password!" << std::endl;
	return 0;
}

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

	{
		/*QSharedPointer<odb::core::database> db = create_database();
		odb::core::transaction t(db->begin());

		QDateTime now = QDateTime::currentDateTime();

		QSharedPointer<user> user1(new user("ati703", "testPW", "Attila", "Lebbenszki", "lebbenszkiattilagmailcom", now));
		QSharedPointer<user> user2(new user("patrikkocsis", "testPW", "Patrik", "Patrik", "patrikkocsisgmailcom", now));
		QSharedPointer<event> event1(new event("first"));
		QSharedPointer<event> event2(new event("second"));
		QSharedPointer<event> event3(new event("third"));
		QSharedPointer<image> image1(new image("/randompath", event1, user1, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<image> image2(new image("/randompath", event1, user1, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<image> image3(new image("/randompath", event1, user1, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<image> image4(new image("/randompath", event2, user2, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<image> image5(new image("/randompath", event2, user2, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<image> image6(new image("/randompath", event3, user2, now, ran(0.0, 100.0), ran(0.0, 100.0)));
		QSharedPointer<track> track1(new track(event1, user1));
		QSharedPointer<track> track2(new track(event2, user2));
		QSharedPointer<track> track3(new track(event3, user2));

		QSharedPointer<tardis> t1(new tardis(track1, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t2(new tardis(track1, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t3(new tardis(track1, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t4(new tardis(track2, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t5(new tardis(track2, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t6(new tardis(track3, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t7(new tardis(track3, ran(0.0, 100.0), ran(0.0, 100.0), now));
		QSharedPointer<tardis> t8(new tardis(track3, ran(0.0, 100.0), ran(0.0, 100.0), now));

		image1->event(event1);	image2->event(event1);	image3->event(event1);	image4->event(event2);	image5->event(event2);	 image6->event(event3);
		event1->images().push_back(image1);		event1->images().push_back(image2);	event1->images().push_back(image3);
		event2->images().push_back(image4);		event2->images().push_back(image5);
		event3->images().push_back(image6);
		event1->user(user1); 	event2->user(user1); 	event3->user(user2);

		image1->user(user1);	image2->user(user1);	image3->user(user1);	image4->user(user2);	image5->user(user2);	 image6->user(user2);
		user1->images().push_back(image1);	user1->images().push_back(image2);	user1->images().push_back(image3);
		user2->images().push_back(image4);	user2->images().push_back(image5);	user2->images().push_back(image6);

		track1->event(event1);	track2->event(event2);  track3->event(event3);
		track1->user(user1);	track2->user(user2);	track3->user(user2);
		t1->track(track1);		t2->track(track1);		t3->track(track1);		t4->track(track2);		t5->track(track2);		t6->track(track3);		t7->track(track3);		t8->track(track3);
		track1->tardises().push_back(t1);	track1->tardises().push_back(t2);	track1->tardises().push_back(t3);
		track2->tardises().push_back(t4);	track2->tardises().push_back(t5);
		track3->tardises().push_back(t6);	track3->tardises().push_back(t7);	track3->tardises().push_back(t8);


		db->persist(user1);		db->persist(user2);
		db->persist(event1);	db->persist(event2); 	db->persist(event3);
		db->persist(image1);	db->persist(image2);	db->persist(image3);	db->persist(image4);	db->persist(image5);	db->persist(image6);
		db->persist(track1);	db->persist(track2);	db->persist(track3);
		db->persist(t1);		db->persist(t2);		db->persist(t3);		db->persist(t4);		db->persist(t5);		db->persist(t6);		db->persist(t7);		db->persist(t8);

		t.commit();
		Track_upload("Files/track.gpx", event1, user1, track1);
		//std::cout << (image1, t1);
		//registration("ati7031", "password", "Attila", "Lebbenszki", "ati703@gmail.com1");
		//login("ati703", "password");*/
	}

	//load("Files/android.jpg");

	user user = user.guest_init();
	//user.getImages(

	QApplication a(argc, argv);
    gui gui;
    gui.show();
	return a.exec();
}

