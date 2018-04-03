#ifndef _TIMAGE_H_
#define _TIMAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "libraries/picture_lib/piclib.h"	

#ifdef __cplusplus
}
#endif

#include "libraries/picture_lib/lodepng.h"
#include "TGlobal.h"
#include "TObject/TBuffer.h"
#include "TObject/TSize.h"
#include "TObject/TRect.h"


#define 	T_JPG		0x0f
#define 	T_JPEG	    0x1f
#define 	T_PNG		0x2f
#define  	T_BMP   	0x3f
#define 	T_GIF		0x4f

class TImage
{
public:
    TImage(const char* filename);
    TImage(uint8* addr,uint16 w,uint16 h,const char* filename) ;
   
    ~TImage();
    int32	imgW()	const	{ return width; }
    int32	imgH()	const	{ return height; }
    uint8*  imgBuf() const  {return imgBufAddr;}
    uint8   getImgType()    {return imgType;}

    void Decode();
    
    void imgLoad(uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect = NULL);
    void blendPoint(uint32 argb_color,uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect = NULL);
    void doubleBlendPoint(uint32 argb_color,uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect = NULL);
    uint8 doubleBlendFunc(uint8 af,uint8 cf,uint8 ab,uint8 cb);
    uint8 ObFileType(const char *fname);
						
private:
    uint16	width;				// image width
	uint16	height;				// image height

    const char* filename;
    uint8* imgBufAddr;
    uint8  imgType;
};

#endif //_TIMAGE_H_
