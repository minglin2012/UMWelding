QT += widgets

HEADERS     = umwelding.h \
              pages.h
SOURCES     = umwelding.cpp \
              main.cpp \
              pages.cpp
RESOURCES   += umwelding.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/dialogs/UMWelding
INSTALLS += target

wince50standard-x86-msvc2005: LIBS += libcmt.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib commctrl.lib coredll.lib winsock.lib ws2.lib

CONFIG += link_pkgconfig
PKGCONFIG += libmodbus
