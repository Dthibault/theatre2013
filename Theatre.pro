QT += xml network

SOURCES += \
    main.cpp \
    rs232.cpp \
    enttecdmxusb.cpp \
    colorwheel.cpp \
    gestiondmx.cpp \
    fenetreprincipale.cpp \
    fenetreparametres.cpp \
    gestionxml.cpp \
    fenetregererappareils.cpp \
    gestionconsole.cpp \
    fenetrecontroledistance.cpp \
    fenetreajoutlyre.cpp \
    widgetcanalsuppl.cpp \
    fenetreajoutpar.cpp \
    fenetrescannerled.cpp \
    fenetreajoutautre.cpp \
    widgetgestionscenes.cpp \
    sceneparled.cpp \
    scenelyre.cpp \
    scenescanner.cpp \
    sceneautres.cpp

HEADERS += \
    types.h \
    rs232.h \
    enttecdmxusb.h \
    colorwheel.h \
    errcode.h \
    gestiondmx.h \
    fenetreprincipale.h \
    fenetreparametres.h \
    gestionxml.h \
    fenetregererappareils.h \
    gestionconsole.h \
    fenetrecontroledistance.h \
    fenetreajoutlyre.h \
    widgetcanalsuppl.h \
    fenetreajoutpar.h \
    fenetrescannerled.h \
    fenetreajoutautre.h \
    widgetgestionscenes.h \
    sceneparled.h \
    scenelyre.h \
    scenescanner.h \
    sceneautres.h

FORMS += \
    fenetreprincipale.ui \
    fenetreparametres.ui \
    fenetregererappareils.ui \
    fenetrecontroledistance.ui \
    fenetreajoutlyre.ui \
    widgetcanalsuppl.ui \
    fenetreajoutpar.ui \
    fenetrescannerled.ui \
    fenetreajoutautre.ui \
    widgetgestionscenes.ui \
    sceneparled.ui \
    scenelyre.ui \
    scenescanner.ui \
    sceneautres.ui

RESOURCES += \
    ressources.qrc
