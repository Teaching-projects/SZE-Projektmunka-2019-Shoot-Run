#include "gui.h"
#include <QtWidgets>

gui::gui(QWidget *parent) : QWidget(parent)
{
    QLabel *unameLabel=new QLabel(tr("Username:"));
    unameLine=new QLineEdit;
    QLabel *passLabel = new QLabel(tr("Password:"));
    passLine = new QLineEdit;
    passLine->setEchoMode(QLineEdit::Password);
    regButton = new QPushButton(tr("&Register"));
    regButton->setEnabled(true);
    logButton = new QPushButton(tr("&Login"));
    logButton->setEnabled(true);
    regdialog=new Reg(this);
    logdialog=new login(this);
     connect(regButton, SIGNAL(clicked()), this, SLOT(regUser()));
	 connect(logButton, SIGNAL(clicked()), this, SLOT(logUser()));
     QVBoxLayout *buttonLayout1 = new QVBoxLayout;
     buttonLayout1->addWidget(regButton);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(unameLabel, 0, 0);
    mainLayout->addWidget(unameLine, 0, 1);
    mainLayout->addWidget(passLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(passLine, 1, 1);
    mainLayout->addWidget(logButton, 0, 2);
    mainLayout->addWidget(regButton, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Shoot&Run"));
}

void gui::logUser()
{
	if(!user_login(unameLine->text().toStdString(), passLine->text().toStdString()))
		QMessageBox::information(this, tr("Error"), tr("Please enter a valid data."));
	else
    logdialog->show();
}

void gui::regUser()
{
    regdialog->show();
}

void gui::password_hash(std::string &password, QDateTime current_date) {
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

int gui::user_exist(std::string user_name, std::string email) {
	typedef odb::query<user> query;
	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
	QSharedPointer<user> exists = db->query_one<user>(query::user_name == user_name || query::email == email);
	if (exists.get() == 0)
		return 0;
	return 1;
}

int gui::user_correct(std::string user_name, std::string password) {
	typedef odb::query<user> query;
	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
	QSharedPointer<user> exists_name = db->query_one<user>(query::user_name == user_name);
	if (exists_name.get() != 0) {
		password_hash(password, exists_name->getRegistretionDate());
		QSharedPointer<user> exists_password = db->query_one<user>(query::user_name == user_name && query::password == password);
		if (exists_password.get() != 0) {
			return 1;
		}
	}
	return 0;
}

int gui::user_registration(std::string user_name, std::string password, std::string first_name, std::string last_name, std::string email)
{
	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
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

int gui::user_login(std::string user_name, std::string password) {
	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
	odb::session s;
	odb::core::transaction t(db->begin());
	if (user_correct(user_name, password)) {
		std::cout << "\nValid name and password!" << std::endl;
		return 1;
	}
	std::cout << "\nWrong name or password!" << std::endl;
	return 0;
}


