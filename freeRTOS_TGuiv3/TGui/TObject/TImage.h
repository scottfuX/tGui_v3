#ifndef _TIMAGE_H_
#define _TIMAGE_H_

#include "TGlobal.h"
#include "TObject/TSize.h"
#include "TObject/TRect.h"


class TImage
{
public:
    TImage();

    int		width()		const	{ return w; }
    int		height()	const	{ return h; }
    TSize	size()		const	{ return TSize(w,h); }
    TRect	rect()		const	{ return TRect(0,0,w,h); }
private:
    uint32	w;				// image width
	uint32	h;				// image height

};

#endif //_TIMAGE_H_
