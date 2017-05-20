TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    imageeditor.cpp \
    qds.cpp

HEADERS += \
    imageeditor.h \
    qds.h

LIBS += -L/usr/lib/ -lSDL -lSDL_image -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video  -lopencv_calib3d \
        -L/usr/local/lib/ -ljpeg -lopencv_calib3d -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc\

INCLUDEPATH += /usr/include/

