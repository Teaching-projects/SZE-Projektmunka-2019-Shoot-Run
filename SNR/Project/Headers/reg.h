#ifndef REG_H
#define REG_H

#include <QDialog>
#include "database.h"
#include "user.h"
#include "user-odb.hxx"
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <QCryptographicHash>

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

int user_registration(std::string user_name, std::string password, std::string first_name, std::string last_name, std::string email)
{
	QSharedPointer<odb::core::database> db = create_database();
	odb::session s;
	odb::core::transaction t(db->begin());
	if (!user_exist(user_name, email)) {
		QDateTime registration_date = QDateTime::currentDateTime();
		password_hash(password, registration_date);
		QSharedPointer<user> user_new(new user(user_name, password, first_name, last_name, email, registration_date));
		db->persist(user_new);
		t.commit();
		std::cout << "\nUser registered" << std::endl;
		return 1;
	}
	std::cout << "\nUser name or email address already taken!" << std::endl;
	return 0;
};

int user_login(std::string user_name, std::string password) {
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


class QPushButton;
class QLineEdit;

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);

private slots:
	void regClicked();
    void cancel();
private:
    QPushButton *regButton;
    QPushButton *cancelButton;
    QLineEdit *nameEdit;
    QLineEdit *passEdit;
    QLineEdit *mailEdit;
	QLineEdit *fnameEdit;
	QLineEdit *lnameEdit;

};

#endif // REG_H
