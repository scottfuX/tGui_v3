#ifndef _TPUSHBUTTON_H_
#define _TPUSHBUTTON_H_

#include "tObject/tAbstractButton.h"
#include "tPainter/tPainter.h"

class tPushButton :public tAbstractButton
{
public:
	tPushButton(int32 x, int32 y, int32 w, int32 h, const char* name, tWidget* obj );
	virtual ~tPushButton() {};

	virtual void	show();
	virtual void	sig_depress(int32 d1, int32 d2);
	virtual void	sig_release(int32 d1, int32 d2);
	virtual void	release(); //只响应，不发送signal
	

private:
	
	
};

#endif // !_TPUSHBUTTON_H_
