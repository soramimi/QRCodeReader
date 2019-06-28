

CONFIG(release,debug|release):TARGET = zbar
CONFIG(debug,debug|release):TARGET = zbard
TEMPLATE = lib
QT += core gui widgets
CONFIG += staticlib c++11

DESTDIR = $$PWD/_bin

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/zbar-0.10/zbar
INCLUDEPATH += $$PWD/zbar-0.10/include

win32:INCLUDEPATH += $$PWD/win/libiconv/include


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
    zbar-0.10/zbar/img.c

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

