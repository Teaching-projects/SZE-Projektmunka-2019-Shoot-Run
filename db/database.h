#ifndef DATABASE_HXX
#define DATABASE_HXX

//#include <string>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>

std::auto_ptr<odb::core::database> create_database()
{
	std::auto_ptr<odb::core::database> db(new odb::mysql::database("root", "", "runner"));
	return db;
}

#endif
