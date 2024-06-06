QT += widgets network

TEMPLATE = app
CONFIG += c++17
CONFIG += qt quick gui

# For automatic handling of UIC, MOC, and RCC
QT += uitools

# Sources
SOURCES += main.cpp \
           mainwindow.cpp \
           registrationform.cpp \
           citychooseform.cpp \
           user.cpp \
           weatherform.cpp \
           loginform.cpp

# Headers
HEADERS += mainwindow.h \
           registrationform.h \
           citychooseform.h \
           user.h \
           weatherform.h \
           loginform.h

# Forms
FORMS += mainwindow.ui \
         registrationform.ui \
         citychooseform.ui \
         weatherform.ui \
         loginform.ui

# Bundle identifier and version for macOS
macx {
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_BUNDLE = 1
    QMAKE_BUNDLE_ID = com.example.WeatherApp
    VERSION = 0.1
    QMAKE_TARGET_BUNDLE_VERSION = $$VERSION
    QMAKE_TARGET_BUNDLE_SHORT_VERSION_STRING = 0.1
}

# Windows executable properties
win32 {
    CONFIG += console
    CONFIG += windows
}

# Installation directories
unix:!mac {
    target.path = $$[QT_INSTALL_BINS]
    INSTALLS += target
}
