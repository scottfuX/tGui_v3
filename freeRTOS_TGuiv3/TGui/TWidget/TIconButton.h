#ifndef _TICONBUTTON_H_
#define _TICONBUTTON_H_

#include "TWidget/TAbstractButton.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TImage.h"

class TIconButton :public TAbstractButton
{
public:
	TIconButton(int32 x, int32 y, TImage* norImg ,TImage* selImg, const char* name, TWidget* obj );
	
	virtual ~TIconButton() ;

	virtual void	show();
	virtual void	sig_depress(int32 d1, int32 d2);
	virtual void	sig_release(int32 d1, int32 d2);
	virtual void	release(); //只响应，不发送signal
	

private:
	
};

#endif // !_TICONBUTTON_H_
