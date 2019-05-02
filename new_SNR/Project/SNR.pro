QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = SNR
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += \
    $$PWD/Sources/main.cpp \
    $$PWD/Sources/exif.cpp \
    $$PWD/Sources/GUI/mainwindow.cpp \
    $$PWD/Sources/GUI/eventwindow.cpp \
    $$PWD/Sources/GUI/addeventdialog.cpp \
    $$PWD/Sources/GUI/adminwindow.cpp \
    $$PWD/Sources/GUI/picturelist.cpp \
    $$PWD/Sources/ODB/event.cpp \
    $$PWD/Sources/ODB/image.cpp \
    $$PWD/Sources/ODB/tardis.cpp \
    $$PWD/Sources/ODB/track.cpp \
    $$PWD/Sources/ODB/user.cpp \
    $$PWD/ODB-cxx/event-odb.cxx \
    $$PWD/ODB-cxx/image-odb.cxx \
    $$PWD/ODB-cxx/tardis-odb.cxx \
    $$PWD/ODB-cxx/track-odb.cxx \
    $$PWD/ODB-cxx/user-odb.cxx \
    $$PWD/Sources/GUI/userwindow.cpp


HEADERS += \
    $$PWD/Headers/exif.h \
    $$PWD/Headers/GUI/mainwindow.h \
    $$PWD/Headers/GUI/eventwindow.h \
    $$PWD/Headers/GUI/addeventdialog.h \
    $$PWD/Headers/GUI/adminwindow.h \
    $$PWD/Headers/GUI/picturelist.h \
    $$PWD/Headers/ODB/database.h \
    $$PWD/Headers/ODB/event.h \
    $$PWD/Headers/ODB/image.h \
    $$PWD/Headers/ODB/tardis.h \
    $$PWD/Headers/ODB/track.h \
    $$PWD/Headers/ODB/user.h \
    $$PWD/ODB-hxx/event-odb.hxx \
    $$PWD/ODB-hxx/image-odb.hxx \
    $$PWD/ODB-hxx/tardis-odb.hxx \
    $$PWD/ODB-hxx/track-odb.hxx \
    $$PWD/ODB-hxx/user-odb.hxx \
    $$PWD/Headers/GUI/userwindow.h

FORMS += \
    $$PWD/UI/mainwindow.ui \
    $$PWD/UI/eventwindow.ui \
    $$PWD/UI/addeventdialog.ui \
    $$PWD/UI/adminwindow.ui \
    $$PWD/UI/picturelist.ui \
    $$PWD/UI/userwindow.ui


LIBS += \
    -L$$PWD/Libraries/libodb/lib64/ -lodb \
    -L$$PWD/Libraries/libodb/lib64/ -lodb-d \
    -L$$PWD/Libraries/libodb-mysql/lib64/ -lodb-mysql \
    -L$$PWD/Libraries/libodb-mysql/lib64/ -lodb-mysql-d \
    -L$$PWD/Libraries/libodb-qt/lib64/ -lodb-qt \
    -L$$PWD/Libraries/libodb-qt/lib64/ -lodb-qt-d \
    -L$$PWD/Libraries/mysql/lib/ -llibmysql \
    -L$$PWD/Libraries/mysql/lib/ -llibmysqld

INCLUDEPATH += \
    $$PWD/Libraries/libodb/lib64/ \
    $$PWD/Libraries/libodb/ \
    $$PWD/Libraries/mysql/lib/ \
    $$PWD/Libraries/mysql/include/ \
    $$PWD/Libraries/libodb-qt/lib64/ \
    $$PWD/Libraries/libodb-qt/ \
    $$PWD/Libraries/libodb-mysql/lib64/ \
    $$PWD/Libraries/libodb-mysql/ \
    $$PWD/ODB-hxx/ \
    $$PWD/ODB-ixx/ \
    $$PWD/ODB-cxx/ \
    $$PWD/Sources/ \
    $$PWD/Sources/GUI/ \
    $$PWD/Sources/ODB/ \
    $$PWD/Headers/ \
    $$PWD/Headers/GUI/ \
    $$PWD/Headers/ODB/ \
    $$PWD/UI/

DEPENDPATH += \
    $$PWD/Libraries/libodb/lib64/ \
    $$PWD/Libraries/libodb/ \
    $$PWD/Libraries/mysql/lib/ \
    $$PWD/Libraries/mysql/include/ \
    $$PWD/Libraries/libodb-qt/lib64/ \
    $$PWD/Libraries/libodb-qt/ \
    $$PWD/Libraries/libodb-mysql/lib64/ \
    $$PWD/Libraries/libodb-mysql/ \
    $$PWD/ODB-hxx/ \
    $$PWD/ODB-ixx/ \
    $$PWD/ODB-cxx/ \
    $$PWD/Sources/ \
    $$PWD/Sources/GUI/ \
    $$PWD/Sources/ODB/ \
    $$PWD/Headers/ \
    $$PWD/Headers/GUI/ \
    $$PWD/Headers/ODB/ \
    $$PWD/UI/

PRE_TARGETDEPS += \
    $$PWD/Libraries/libodb/lib64/odb.lib \
    $$PWD/Libraries/libodb/lib64/odb-d.lib \
    $$PWD/Libraries/libodb-mysql/lib64/odb-mysql.lib \
    $$PWD/Libraries/libodb-mysql/lib64/odb-mysql-d.lib \
    $$PWD/Libraries/libodb-qt/lib64/odb-qt.lib \
    $$PWD/Libraries/libodb-qt/lib64/odb-qt-d.lib \
    $$PWD/Libraries/mysql/lib/libmysql.lib \
    $$PWD/Libraries/mysql/lib/libmysqld.lib

DISTFILES += \
    $$PWD/ODB-sql/event.sql \
    $$PWD/ODB-sql/image.sql \
    $$PWD/ODB-sql/tardis.sql \
    $$PWD/ODB-sql/track.sql \
    $$PWD/ODB-sql/user.sql \
    $$PWD/ODB-ixx/event-odb.ixx \
    $$PWD/ODB-ixx/image-odb.ixx \
    $$PWD/ODB-ixx/tardis-odb.ixx \
    $$PWD/ODB-ixx/track-odb.ixx \
    $$PWD/ODB-ixx/user-odb.ixx \
    $$PWD/Files/track.gpx \
    $$PWD/Files/android.jpg

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
