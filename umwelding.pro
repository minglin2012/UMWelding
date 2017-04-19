QT += widgets

HEADERS     = umwelding.h \
              pages.h \
    curveview.h \
    umweldingparams.h \
    myellipseitem.h
SOURCES     = umwelding.cpp \
              main.cpp \
              pages.cpp \
    curveview.cpp \
    umweldingparams.cpp \
    myellipseitem.cpp
RESOURCES   += umwelding.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/dialogs/umwelding
INSTALLS += target

##win32 {
#LIBS += -L"C:\Users\wang\Documents\GitHub\umwelding\modbus\lib" -lmodbus-5
#INCLUDEPATH += C:\Users\wang\Documents\GitHub\umwelding\modbus\include
##}
unix:!macx {
#LIBS += -L$$PWD/ -lXXXXX
CONFIG += link_pkgconfig
PKGCONFIG += libmodbus
}



#wince50standard-x86-msvc2005: LIBS += libcmt.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib commctrl.lib coredll.lib winsock.lib ws2.lib


win32: LIBS += -L$$PWD/modbus/lib/ -lmodbus

INCLUDEPATH += $$PWD/modbus/include
DEPENDPATH += $$PWD/modbus/include
