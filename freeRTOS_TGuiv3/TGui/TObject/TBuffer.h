#ifndef _TBUFFER_H_
#define _TBUFFER_H_


#include "TGlobal.h"


class TBuffer
{
private:
    uint32* buf;
    uint32 bufW;
    uint32 bufH;
public:
    TBuffer(uint32* pre_addr,uint32 pre_w,uint32 w,uint32 h);
    ~TBuffer();
    uint32* getBufAddr(){return buf;};
    //
    void transform();

};


#endif //_TBUFFER_H_
