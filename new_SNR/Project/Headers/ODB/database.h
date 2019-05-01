#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>
#include <memory>
#include <iomanip>
#include <QSharedPointer>

class DB {
public:
    DB() {}
   static QSharedPointer<odb::core::database> create_database() {
        //QSharedPointer<odb::core::database> db(new odb::mysql::database("ZNUNonRurv", "ys7Yj0Rpjp", "ZNUNonRurv", "remotemysql.com", 3306));
        QSharedPointer<odb::core::database> db(new odb::mysql::database("root", "", "inorder"));
        return db;
    }
};

#endif //DATABASE_HXX
