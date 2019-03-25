#include <iostream>
#include <odb/transaction.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>
#include <memory>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

/*#include "event.h"
#include "event-odb.hxx"
#include "image.h"
#include "image-odb.hxx"
#include "user.h"
#include "user-odb.hxx"*/
#include "tardis.h"
#include "tardis-odb.hxx"
#include "track.h"
#include "track-odb.hxx"




int main()
{
	std::auto_ptr<odb::core::database> db(new odb::mysql::database("root", "", "runner"));
	odb::session s;
	//user user1("ati703", "testPW", "Attila", "Lebbenszki", "lebbenszkiattilagmailcom");
	//user user2("patrikkocsis", "testPW", "Patrik", "Patrik", "patrikkocsisgmailcom");
	//event event1("Próbafutás",1);
	std::tr1::shared_ptr<track> e1(new track(1,1));
	std::tr1::shared_ptr<track> e2(new track(2, 1));
	std::tr1::shared_ptr<tardis> t1(new tardis(e1, 1,1,  "199612312312"));
	std::tr1::shared_ptr<tardis> t2(new tardis(e1, 2, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t3(new tardis(e1, 3, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t4(new tardis(e1, 4, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t5(new tardis(e2, 1, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t6(new tardis(e2, 2, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t7(new tardis(e2, 3, 1, "199612312312"));
	std::tr1::shared_ptr<tardis> t8(new tardis(e2, 4, 1, "199612312312"));
	odb::core::transaction t(db->begin());
	db->persist(e1);
	db->persist(e2);
	db->persist(t1);
	db->persist(t2);
	db->persist(t3);
	db->persist(t4);
	db->persist(t5);
	db->persist(t6);
	db->persist(t7);
	db->persist(t8);
	t.commit();

    return 0;
}
