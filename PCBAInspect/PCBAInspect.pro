TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

INCLUDEPATH += C:\openCV343\release\install\include

LIBS+= C:\openCV343\release\bin\libopencv_core343.dll
LIBS+= C:\openCV343\release\bin\libopencv_highgui343.dll
LIBS+= C:\openCV343\release\bin\libopencv_imgcodecs343.dll
LIBS+= C:\openCV343\release\bin\libopencv_imgproc343.dll
LIBS+= C:\openCV343\release\bin\libopencv_calib3d343.dll
LIBS+= C:\openCV343\release\bin\libopencv_videoio343.dll
LIBS+= C:\openCV343\release\bin\libopencv_objdetect343.dll
LIBS+= C:\openCV343\release\bin\libopencv_features2d343.dll
LIBS+= C:\openCV343\release\bin\libopencv_photo343.dll


SOURCES += \
    detectdifference.cpp\
    identifyfaults.cpp \
    imagecapture.cpp \
    main.cpp \
    realign.cpp \
    selectcomponents.cpp \

HEADERS += \
    detectdifference.h \
    identifyfaults.h \
    imagecapture.h \
    realign.h \
    selectcomponents.h \
    shared_include.h \
