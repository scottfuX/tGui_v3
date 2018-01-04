#ifndef _TTEXTEDITOR_H_
#define _TTEXTEDITOR_H_

#include "tObject/tTextEdit.h"
#include "tObject/tAbstractScrollArea.h"

class tTextEditor :
	public tAbstractScrollArea
{
public:
	tTextEditor(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj);
	virtual~tTextEditor();
	virtual void show();

	virtual void touchPressEvent(tTouchEvent *) ;
	virtual void touchReleaseEvent(tTouchEvent *) ;
	virtual void touchClickEvent(tTouchEvent *) ;
	virtual void touchMoveEvent(tTouchEvent *) ;
};


#endif  //!_TTEXTEDITOR_H_
