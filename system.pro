QT += widgets
QT += gui
QT += opengl
LIBS += -lopengl32
HEADERS += \
    CSSCity.h \
    CSSIndex.h \
    CSSNameIndex.h \
    CSSNameIndexNode.h \
    CSSSpatialIndex.h \
    CSSSpatialIndexNode.h \
    CHPolygon.h \
    CFile.h \
    CHLayer.h \
    CHMap.h \
    CHObject.h \
    CHPoint.h \
    MainWindow.h \
    CHPolyline.h \
    MyOpenGLWidget.h

SOURCES += \
    main.cpp \
    CSSCity.cpp \
    CSSIndex.cpp \
    CSSNameIndex.cpp \
    CSSNameIndexNode.cpp \
    CSSSpatialIndex.cpp \
    CSSSpatialIndexNode.cpp \
    CHPolygon.cpp \
    CFile.cpp \
    CHLayer.cpp \
    CHMap.cpp \
    CHObject.cpp \
    CHPoint.cpp \
    MainWindow.cpp \
    CHPolyline.cpp \
    MyOpenGLWidget.cpp

FORMS += \
    mainwindow.ui

RESOURCES += \
    src/src.qrc
