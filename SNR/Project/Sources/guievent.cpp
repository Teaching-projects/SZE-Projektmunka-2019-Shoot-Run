#include "guievent.h"
#include <QtWidgets>
#include <QFileDialog>
#include "exif.h"


GuiEvent::GuiEvent(QWidget *parent) :
    QDialog(parent)
{
    uploadButton = new QPushButton(tr("&Upload pictures"));
    uploadButton->setEnabled(true);
    backButton = new QPushButton(tr("&Back"));
    backButton->setEnabled(true);
    trackButton = new QPushButton(tr("&Track upload"));
    trackButton->setEnabled(true);
    infotrackButton = new QPushButton(tr("&Track info"));
    infotrackButton->setEnabled(true);
    okButton = new QPushButton(tr("&List pictures"));
    okButton->setEnabled(true);
    dloadButton = new QPushButton(tr("&Download pictures"));
    dloadButton->setEnabled(true);

    m_listeWidget=new QListWidget(this);
    m_listeWidget->setViewMode(QListWidget::IconMode);
    m_listeWidget->setIconSize(QSize(200,200));
    m_listeWidget->setResizeMode(QListWidget::Adjust);

	m_listeWidget->addItem(new QListWidgetItem(QIcon("images_server/red.png"), ""));
	m_listeWidget->addItem(new QListWidgetItem(QIcon("images_server/green.png"), ""));
	m_listeWidget->addItem(new QListWidgetItem(QIcon("images_server/blue.png"), ""));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(uploadButton, 1,0);
    layout->addWidget(infotrackButton, 3,0);
    layout->addWidget(dloadButton, 2,0);
    layout->addWidget(trackButton, 1,1);
    layout->addWidget(okButton, 2,1);
    layout->addWidget(backButton, 3,1);
    layout->addWidget(m_listeWidget, 0,0,1,0);

    setLayout(layout);
    setWindowTitle(tr("Event"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.64);

    filtereddialog=new FilteredDialog(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(filterPictures()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
	connect(uploadButton, SIGNAL(clicked()), this, SLOT(filewindow()  ));
}

void GuiEvent::filewindow() {
	QString file_name;
	QStringList file_names = QFileDialog::getOpenFileNames(this,"Select the picture", QDir::homePath());
	for (int i = 0; i < file_names.size(); ++i)
		load(file_names.at(i));
}

void GuiEvent::load(QString path_Q) {
	std::string path = path_Q.toStdString();
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
	QDateTime date = QDateTime::fromString(QString::fromStdString(result.DateTime),"yyyy:MM:dd HH:mm:ss");


	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
	odb::session s;
	odb::core::transaction t(db->begin());

	typedef odb::query<user> u_query;
	typedef odb::query<::event> e_query;

	QSharedPointer<user> current_user = db->query_one<user>(u_query::user_name == "admin");
	QSharedPointer<::event> current_event = db->query_one<::event>(e_query::event_name == "first_event");
	
	QSharedPointer<image> new_image(new image(path, current_event, current_user, date , result.GeoLocation.Longitude, result.GeoLocation.Latitude));
	db->persist(new_image);
	new_image->user(current_user); new_image->event(current_event);
	current_user->images().push_back(new_image);
	current_event->images().push_back(new_image);
	db->update(current_event); db->update(current_user);
	t.commit();
}

void GuiEvent::back(){
   GuiEvent::close();
}

void GuiEvent::filterPictures(){
    filtereddialog->show();
}
