QT       += core gui
QT += core gui widgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/Controller.cpp \
    Media/AbstractMedia.cpp \
    Media/Book.cpp \
    Media/Converter/Json.cpp \
    Media/Converter/JsonReader.cpp \
    Media/Converter/JsonVisitor.cpp \
    Media/DataMapper/JsonFile.cpp \
    Media/Film.cpp \
    Media/Repository/JsonRepository.cpp \
    Media/Song.cpp \
    View/EditWidget.cpp \
    View/Grid.cpp \
    View/ItemEditor/AbstractItemEditor.cpp \
    View/ItemEditor/BookEditor.cpp \
    View/ItemEditor/FilmEditor.cpp \
    View/ItemEditor/MediaInjector.cpp \
    View/ItemEditor/SongEditor.cpp \
    View/MainWindow.cpp \
    View/MediaRender/FilterRender.cpp \
    View/MediaRender/Card.cpp \
    View/MediaRender/Full.cpp \
    View/TypeSelector.cpp \
    main.cpp

HEADERS += \
    Controller/Controller.h \
    Media/AbstractMedia.h \
    Media/Book.h \
    Media/ConstVisitor.h \
    Media/Converter/Json.h \
    Media/Converter/JsonReader.h \
    Media/Converter/JsonVisitor.h \
    Media/Converter/MReader.h \
    Media/DataMapper/JsonFile.h \
    Media/Film.h \
    Media/Repository/JsonRepository.h \
    Media/Repository/MRepository.h \
    Media/Song.h \
    Media/Visitor.h \
    View/EditWidget.h \
    View/Grid.h \
    View/ItemEditor/AbstractItemEditor.h \
    View/ItemEditor/BookEditor.h \
    View/ItemEditor/FilmEditor.h \
    View/ItemEditor/MediaInjector.h \
    View/ItemEditor/SongEditor.h \
    View/MainWindow.h \
    View/MediaRender/Card.h \
    View/MediaRender/FilterRender.h \
    View/MediaRender/Full.h \
    View/MediaRender/IMediaRender.h \
    View/TypeSelector.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
