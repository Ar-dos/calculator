QT       += core gui charts  widgets

#QMAKE_CXXFLAGS += -std=c++0x

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/controller.cpp \
    ../Model/parser.cpp \
    calc.cpp \
    main.cpp \

HEADERS += \
    ../Controller/controller.h \
    ../Model/parser.h \
    calc.h \

FORMS += \
    calc.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
