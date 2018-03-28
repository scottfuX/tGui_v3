#ifndef _TPUSHBUTTON_H_
#define _TPUSHBUTTON_H_

#include "TWidget/TAbstractButton.h"
#include "TPainter/TBufPainter.h"
#include "TPainter/TPainter.h"
#include "TObject/TImage.h"

class TPushButton :public TAbstractButton
{
public:
	TPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj );
	TPushButton(int32 x, int32 y, TImage norImg ,TImage selImg, const char* name, TWidget* obj );
	
	virtual ~TPushButton() ;

	virtual void	show();
	virtual void	sig_depress(int32 d1, int32 d2);
	virtual void	sig_release(int32 d1, int32 d2);
	virtual void	release(); //只响应，不发送signal
	

private:
	
};

#endif // !_TPUSHBUTTON_H_
