QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
QMAKE_CFLAGS += -std=c99 -Wno-unused-variable -Wno-unused-parameter -Wno-type-limits -Wno-sign-compare -Wno-old-style-declaration

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  $$PWD/../../../ext/gumbo/src/ \
                $$PWD/../../html/ \
                $$PWD/../../data/ \
                $$PWD/../../net/

SOURCES += \
    ../../../ext/gumbo/src/attribute.c \
    ../../../ext/gumbo/src/char_ref.c \
    ../../../ext/gumbo/src/error.c \
    ../../../ext/gumbo/src/parser.c \
    ../../../ext/gumbo/src/string_buffer.c \
    ../../../ext/gumbo/src/string_piece.c \
    ../../../ext/gumbo/src/tag.c \
    ../../../ext/gumbo/src/tokenizer.c \
    ../../../ext/gumbo/src/utf8.c \
    ../../../ext/gumbo/src/util.c \
    ../../../ext/gumbo/src/vector.c \
    ../../html/HtmlNode.cpp \
    ../../html/HtmlAttribute.cpp \
    ../../html/HtmlDocument.cpp \
    ../../data/DataItem.cpp \
    ../../data/DataItemGallery.cpp \
    ../../data/DataItemImage.cpp \
    ../../data/DataItemPager.cpp \
    ../../data/DataItemText.cpp \
    ../../data/DataItemVideo.cpp \
    ../../net/ParsingResult.cpp \
    ../../net/NetworkDataSource.cpp \
    tst_html.cpp


HEADERS += \
    ../../../ext/gumbo/src/gumbo.h \
    ../../html/HtmlNode.h \
    ../../html/HtmlAttribute.h \
    ../../html/HtmlDocument.h \
    ../../data/DataItem.h \
    ../../data/DataItemGallery.h \
    ../../data/DataItemImage.h \
    ../../data/DataItemPager.h \
    ../../data/DataItemText.h \
    ../../data/DataItemVideo.h \
    ../../net/ParsingResult.h \
    ../../net/AbstractDataSource.h \
    ../../net/NetworkDataSource.h \
    util.h

