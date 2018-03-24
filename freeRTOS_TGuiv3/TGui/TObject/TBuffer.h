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


class TBuffer
{
private:
    uint8* buf;
    uint32 bufW;
    uint32 bufH;
public:
    TBuffer(uint8* pre_addr,uint32 pre_w,uint32 w,uint32 h);
    ~TBuffer();
    uint8* getBufAddr(){return buf;};
    uint32  getBufW(){return bufW;}
    uint32  getBufH(){return bufH;}

    uint32 readPoint(int32 x,int32 y);
    void writePoint(int32 x,int32 y,uint32 color);

};


#endif //_TBUFFER_H_
