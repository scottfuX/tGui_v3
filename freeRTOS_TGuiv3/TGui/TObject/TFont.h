#ifndef _TFONT_H_
#define _TFONT_H_


#include "TGlobal.h"



//#define T_GBK        1
#define T_GB2312     2
#define T_UTF_8      3

typedef struct T_Ascii_Font
{    
    uint8* table;
    uint16 Width;
    uint16 Height;
    
} T_ASCII_FONT;

// extern const unsigned char asc2_1206[95][12];
// extern const unsigned char asc2_1608[95][16];
// extern const unsigned char asc2_2412[95][36];
// extern const unsigned char asc2_3216[95][128];

extern T_ASCII_FONT Font12x12;
extern T_ASCII_FONT Font16x16;
extern T_ASCII_FONT Font24x24;
extern T_ASCII_FONT Font32x32;


//目前只支持 *.FON 格式
class TFont
{
public:
    TFont(const char *filename,uint16 width,uint16 height,uint8 codetype = T_GB2312);
    virtual ~TFont();

    uint16 fontW(){return width;}
    uint16 fontH(){return height;}
    uint8  fontType(){return type;} 
    uint8* getWordCode(uint32 c);
private:
    uint16 width;
    uint16 height;
    uint8  type;
    uint8* fontTable;
    const char *fontFile;
};



#endif //!_TFONT_H_

