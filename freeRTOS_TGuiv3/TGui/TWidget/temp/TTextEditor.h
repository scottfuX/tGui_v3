#ifndef _TTEXTEDITOR_H_
#define _TTEXTEDITOR_H_

#include "TWidget/TTextEdit.h"
#include "TWidget/TAbstractScrollArea.h"

class TTextEditor :
	public TAbstractScrollArea
{
public:
	TTextEditor(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj);
	virtual~TTextEditor();
	virtual void show();

	virtual void touchPressEvent(tTouchEvent *) ;
	virtual void touchReleaseEvent(tTouchEvent *) ;
	virtual void touchClickEvent(tTouchEvent *) ;
	virtual void touchMoveEvent(tTouchEvent *) ;
private:
	TTextEdit* text;
};


#endif  //!_TTEXTEDITOR_H_
