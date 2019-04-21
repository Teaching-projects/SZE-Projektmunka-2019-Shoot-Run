#ifndef GUI_H
#define GUI_H

#include <QMap>
#include <QWidget>
#include <string>


#include "reg.h"
#include "login.h"
#include "user-odb.hxx"
#include "database.h"

class user;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;

class gui : public QWidget, public DB
{
    Q_OBJECT
public:
    explicit gui(QWidget *parent = nullptr);
	static void password_hash(std::string &password, QDateTime current_date);
	static int user_exist(std::string user_name, std::string email);
	static int user_registration(std::string user_name, std::string password, std::string first_name, std::string last_name, std::string email);
	static int user_correct(std::string user_name, std::string password);
	static int user_login(std::string user_name, std::string password);
private:
    QPushButton *logButton;
    QPushButton *regButton;
    QPushButton *cancelButton;
    QLineEdit *unameLine;
    QLineEdit *passLine;
    Reg *regdialog;
    login *logdialog;
signals:

public slots:
	void regUser();
	void logUser();
};





#endif // GUI_H
