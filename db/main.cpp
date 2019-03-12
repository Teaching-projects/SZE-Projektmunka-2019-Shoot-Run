#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <iostream>
#include <odb/transaction.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>
#include <memory>
#include <odb/session.hxx>//mégnemkell
#include <odb/transaction.hxx>

/*#include "event.h"
#include "event-odb.hxx"
#include "image.h"
#include "image-odb.hxx"*/
#include "tardis.h"
#include "tardis-odb.hxx"
/*#include "track.h"
#include "track-odb.hxx"
#include "user.h"
#include "user-odb.hxx"*/



int main()
{
	std::auto_ptr<odb::core::database> db(new odb::mysql::database("root", "", "runner"));

	//user user1("ati703", "testPW", "Attila", "Lebbenszki", "lebbenszkiattilagmailcom");
	//user user2("patrikkocsis", "testPW", "Patrik", "Patrik", "patrikkocsisgmailcom");
	//event event1("Próbafutás",1);
	tardis td(12, 41.02, 41.44, "1996-09-01 12:32:32");
	td.ki();
	odb::core::transaction t(db->begin());
	db->persist(td);
	//db->persist(user1);
	//db->persist(user2);
	//db->persist(event1);
	t.commit();

    return 0;
}
