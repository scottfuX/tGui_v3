#ifndef _TBUFFER_H_
#define _TBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#ifdef __cplusplus
}
#endif

#include "TGlobal.h"
#include "TObject/TRect.h"
//#include "TObject/TImage.h"
#include "TObject/TSize.h"
#include "TObject/TRect.h"

// typedef struct T_BUF
// {
//     uint8* addr;
//     uint16 bufW;
//     uint16 bufH;
    
// }TBufDef;


class TBuffer
{
private:
    int  contextType;
    uint8* addr;
    uint16 bufW;
    uint16 bufH;
    
public:
    TBuffer(uint32 w,uint32 h);
    ~TBuffer();

    uint8*  getBufAddr(){return addr;}
    uint32  getBufW(){return bufW;}
    uint32  getBufH(){return bufH;}

    void obPareBack(uint8* pre_addr,uint32 pre_w,int32 x = 0,int32 y = 0,uint16 w = 0,uint16 h = 0);
    void transform(int32 x,int32 y,TRect* srcRect);//输送一部分内容到显存
    uint32 readPoint(int32 x,int32 y);
    void writePoint(int32 x,int32 y,uint32 color);

};


#endif //_TBUFFER_H_
