#include "TWidget/TTextEditor.h"


TTextEditor::TTextEditor(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj)
	:TAbstractScrollArea(x,y,w,h,n,obj)
{
	text = new TTextEdit();
}


TTextEditor::~TTextEditor()
{

}

void TTextEditor::show()
{
	TPainter p;
	p.setTextColor(WHITE);
	p.drawFullRect(x(), y(), width(), height());
	showScroll(width(), height(), 20, true, true);
}

void TTextEditor::touchPressEvent(tTouchEvent *e)
{
	
}

void TTextEditor::touchReleaseEvent(tTouchEvent *e)
{

}

void TTextEditor::touchClickEvent(tTouchEvent *e)
{

}

void TTextEditor::touchMoveEvent(tTouchEvent *e)
{

}
