QT += xml

SOURCES += \
    main.cpp \
    rs232.cpp \
    enttecdmxusb.cpp \
    colorwheel.cpp \
    gestiondmx.cpp \
    fenetreprincipale.cpp \
    fenetreparametres.cpp \
    gestionxml.cpp \
    fenetregererappareils.cpp

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
    fenetregererappareils.h

FORMS += \
    fenetreprincipale.ui \
    fenetreparametres.ui \
    fenetregererappareils.ui
