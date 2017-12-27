#include "tObject/tWidget.h"

tWidget::tWidget(const char* n, tObject* obj) :tObject(n, obj)
{
	point = new tPoint();
	size = new tSize();
	setX(0);
	setY(0);
	setW(0);
	setH(0);
	backColor = WHITE;
};

tWidget::tWidget(int32 x, int32 y, int32 w, int32 h, const char* n,tObject* obj):tObject(n,obj)
{
	point = new tPoint();
	size = new tSize();
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	backColor = WHITE;
}

bool tWidget::isArea(int32 xt,int32 yt)
{
	if (xt >= x() && yt >= y() && xt < (x() + width()) && yt < (y() + height()))
		return true;
	return false;
}


void tWidget::showAll(tWidget* obj)
{
	obj->show();
	tObjList* list = obj->getChildList();
	tObject* temp;
	if (list)
	{
		showAll((tWidget*)list->getFirst());
		while (temp = list->getNext())
			showAll((tWidget*)temp);
	}
}

void tWidget::eventFilter(tEvent* e)
{
	switch (e->type())
	{
		case  Event_None: {}break;
		case  Event_Timer: {}break;
		case  Event_TouchPress:{touchPressEvent((tTouchEvent *)e) ;}break;
		case  Event_TouchRelese: {touchReleaseEvent((tTouchEvent *)e);}break;
		case  Event_TouchClick: {touchClickEvent((tTouchEvent *)e);}break;
		case  Event_TouchMove: {touchMoveEvent((tTouchEvent *)e);}break;
		case  Event_MousePress: {mousePressEvent((tMouseEvent *)e);}break;
		case  Event_MouseRelease: {mouseReleaseEvent((tMouseEvent *)e);}break;
		case  Event_MouseClick: {mouseDoubleClickEvent((tMouseEvent *)e);}break;
		case  Event_MouseDblClick: {mouseClickEvent((tMouseEvent *)e);}break;
		case  Event_MouseMove: {mouseMoveEvent((tMouseEvent *)e);}break;
		case  Event_KeyPress: {keyPressEvent((tKeyEvent *)e);}break;
		case  Event_KeyRelease: {keyReleaseEvent((tKeyEvent *)e);}break;
		case  Event_KeyClick: {	}break;
		case  Event_FocusIn: {focusInEvent((tFocusEvent *)e); }break;
		case  Event_FocusOut: {focusOutEvent((tFocusEvent *)e);}break;
		case  Event_Enter: {enterEvent(e);}break;
		case  Event_Leave: {leaveEvent(e);}break;
		case  Event_Paint: {paintEvent((tPaintEvent *)e);}break;
		case  Event_Move: {moveEvent((tMoveEvent *)e);}break;
		case  Event_Resize: {resizeEvent((tResizeEvent *)e);}break;
		case  Event_Create: {closeEvent((tCloseEvent *)e); }break;
		case  Event_Destroy: {}break;
		case  Event_Show: {}break;
		case  Event_Hide: {}break;
		case  Event_Close: {}break;
		case  Event_User: {}break;
		default:
			break;
	}
}