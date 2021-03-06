/*************************************************************
 Abstract GUI toolkit
 Copyright by L.Berti (c) 2007
 *************************************************************/

#ifndef LWTKDEFS_H_INCLUDED
#define LWTKDEFS_H_INCLUDED

#include "video/videodef.h"
#include "video/graphics.h"


/**Informazioni sulla versione dell'applicazione*/
typedef struct {

    int major;
    int minor;
    int revision;
    char info[64];
}
VERSION_INFO;

/**Valori restituiti da MsgBox*/

const int     MSG_NONE=0;
const int     MSG_YESNO=1;
const int     MSG_OKCANCEL=2;
const int     MSG_OK=4;
const int     MSG_YESNOCANCEL=8;
const int     MSG_ICO_NONE=32;
const int     MSG_ICO_INFORMATION=64;
const int     MSG_ICO_EXCLAMATION=128;
const int     MSG_ICO_QUESTION=256;
const int     MSG_ICO_STOP=1024;

/**Risultati di un message box*/
enum MSG_BOX_RESULT {
    MSG_RET_NONE=0,
    MSG_RET_OK=1,
    MSG_RET_NO=2,
    MSG_RET_CANCEL=4,
    MSG_RET_YES=8
};



/**Allineamento testo*/
enum TEXT_ALIGN
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};

enum BORDER_TYPE
{
    BORDER_NONE=0x0,
    BORDER_SOLID,
    BORDER_ETCHED,
    BORDER_RAISED,
    BORDER_BUMP,
    BORDER_SUNKEN
};

enum TEXT_FIELD_TYPE
{
    TEXT_NORMAL=0x0,
    TEXT_UPPERCASE=0x1,
    TEXT_LOWERCASE=0x2,
    TEXT_NUMERIC_FLOAT=0x4,
    TEXT_NUMERIC_UNSIGNED_INT=0x5,
    TEXT_NUMERIC_INT=0x6,
};

enum LIST_SELECTION_MODE
{
    SINGLE_SELECTION=0x0,
    MULTI_SELECTION=0x1,
    NO_SELECTION=0x2,
};

enum SCROLL_BAR_TYPE
{
    SCROLL_HORIZ=0x0,
    SCROLL_VERT=0x1,
};

enum COMBOBOX_STYLE
{
    DROPDOWN_READ_ONLY=0x0,
    LIST_EDITABLE=0x1,
    DROPDOWN_EDITABLE=0x2,
};

/**Identificatori delle posizione z-order dei componenti*/
enum ZORDER_POS
{
    ZORDER_TOP=0x1,
    ZORDER_BOTTOM=0x0,
};

/**Font di sistema che devono essere sempre implementati*/
enum LWTK_FONTS
{
    FONT_NONE=0x0,
    DEFAULT_FONT=0x1, //font default
    FIXED_FONT=0x2, //font a spaziatura fissa
    SERIF_FONT=0x4,
    SANS_SERIF_FONT=0x5,
};







#define TEXT_STYLE_NORMAL 0x0
#define TEXT_STYLE_MULTILINE 0x1
#define TEXT_STYLE_HSCROLL 0x2
#define TEXT_STYLE_VSCROLL 0x4

#endif // LWTKDEFS_H_INCLUDED
