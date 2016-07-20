QT += qml quick location positioning quickcontrols2

CONFIG += c++11

SOURCES += main.cpp \
    gpstrack.cpp \
    gpstrackstat.cpp \
    storagemodel.cpp \
    filesystemmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    gpstrack.h \
    gpstrackstat.h \
    storagemodel.h \
    filesystemmodel.h

DISTFILES +=
