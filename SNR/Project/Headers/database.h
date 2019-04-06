#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <odb/database.hxx>
#include <odb/mysql/database.hxx>

QSharedPointer<odb::core::database> create_database()
{
	QSharedPointer<odb::core::database> db(new odb::mysql::database("root", "", "runner"));
	return db;
}

#endif DATABASE_HXX
