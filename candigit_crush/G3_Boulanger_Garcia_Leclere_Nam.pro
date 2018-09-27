TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MAC_SDK = macosx10.13

LIBS += -static
LIBS += -static-libstdc++ -pthread

SOURCES += main.cpp \
    G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/nsutil.cpp \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/game.cpp \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/gridmanagement.cpp \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/timer.cpp

HEADERS += \
    G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/nsutil.h \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/game.h \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/gridmanagement.h \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/params.h \
    G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/type.h \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/type.h \
    G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/timer.h
