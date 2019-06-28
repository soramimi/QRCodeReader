
TARGET = QRCodeReader
TEMPLATE = app
QT += core gui widgets
CONFIG += c++11

DESTDIR = $$PWD/_bin

INCLUDEPATH += $$PWD/src

# opencv

linux:LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc

win32 {
	# recommended: opencv-4.1.0-vc14_vc15.exe
	INCLUDEPATH += C:/opencv/build/include
	CONFIG(release,debug|release):LIBS += -LC:/opencv/build/x64/vc15/lib -lopencv_world410
	CONFIG(debug,debug|release):LIBS += -LC:/opencv/build/x64/vc15/lib -lopencv_world410d
}


# libiconv for windows: https://github.com/pffang/libiconv-for-Windows

win32 {
	INCLUDEPATH += $$PWD/win/libiconv/include
	LIBS += -L$$PWD/win/libiconv/lib64 -llibiconvStatic
}


# zbar: https://github.com/ZBar/ZBar

INCLUDEPATH += $$PWD/zbar-0.10/zbar
INCLUDEPATH += $$PWD/zbar-0.10/include
#CONFIG(release,debug|release):LIBS += -L$$PWD/_bin -lzbar
#CONFIG(debug,debug|release):LIBS += -L$$PWD/_bin -lzbard

SOURCES += \
	zbar-0.10/zbar/config.c \
	zbar-0.10/zbar/decoder.c \
	zbar-0.10/zbar/decoder/qr_finder.c \
	zbar-0.10/zbar/error.c \
	zbar-0.10/zbar/img_scanner.c \
	zbar-0.10/zbar/qrcode/bch15_5.c \
	zbar-0.10/zbar/qrcode/binarize.c \
	zbar-0.10/zbar/qrcode/isaac.c \
	zbar-0.10/zbar/qrcode/qrdec.c \
	zbar-0.10/zbar/qrcode/qrdectxt.c \
	zbar-0.10/zbar/qrcode/rs.c \
	zbar-0.10/zbar/qrcode/util.c \
	zbar-0.10/zbar/refcnt.c \
	zbar-0.10/zbar/scanner.c \
	zbar-0.10/zbar/symbol.c \
	zbar-0.10/zbar/img.c \
    src/ImageWidget.cpp

HEADERS += \
	config.h \
	zbar-0.10/include/zbar.h \
	zbar-0.10/zbar/debug.h \
	zbar-0.10/zbar/decoder.h \
	zbar-0.10/zbar/decoder/qr_finder.h \
	zbar-0.10/zbar/error.h \
	zbar-0.10/zbar/img_scanner.h \
	zbar-0.10/zbar/libzbar.rc \
	zbar-0.10/zbar/qrcode.h \
	zbar-0.10/zbar/qrcode/bch15_5.h \
	zbar-0.10/zbar/qrcode/binarize.h \
	zbar-0.10/zbar/qrcode/isaac.h \
	zbar-0.10/zbar/qrcode/qrdec.h \
	zbar-0.10/zbar/qrcode/rs.h \
	zbar-0.10/zbar/qrcode/util.h \
	zbar-0.10/zbar/refcnt.h \
	zbar-0.10/zbar/symbol.h \
	zbar-0.10/zbar/img.h


# application

SOURCES += \
	src/MainWindow.cpp \
	src/main.cpp

HEADERS += \
	src/ImageWidget.h \
	src/MainWindow.h

FORMS += \
	src/MainWindow.ui

