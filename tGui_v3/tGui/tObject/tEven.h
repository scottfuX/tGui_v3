#ifndef _TEVENT_H_
#define _TEVENT_H_

#include "tGlobal.h"
#include "tPoint.h"
#include "tSize.h"
#include "tRect.h"



#define Event_None					0		// invalid event
#define Event_Timer					1		// timer event
#define Event_TouchPress			2		// touch pressed
#define Event_TouchRelese			3		// touch released
#define Event_TouchClick			4		// touch click
#define Event_TouchMove				5		// touch move
#define Event_MousePress			6		// mouse pressed
#define Event_MouseRelease			7		// mouse released
#define Event_MouseClick			8		// mouse click
#define Event_MouseDblClick			9		// mouse double click
#define Event_MouseMove				10		// mouse move
#define Event_KeyPress				11		// key pressed
#define Event_KeyRelease			12		// key released
#define Event_KeyClick				13		// key click
#define Event_FocusIn				14		// keyboard focus received
#define Event_FocusOut				15		// keyboard focus lost
#define Event_Enter					16		// mouse enters widget
#define Event_Leave					17		// mouse leaves widget
#define Event_Paint					18		// paint widget
#define Event_Move					19		// move widget
#define Event_Resize				20		// resize widget
#define Event_Create				21		// after object creation
#define Event_Destroy				22		// during object destruction
#define Event_Show					23		// widget is shown
#define Event_Hide					24		// widget is hidden
#define Event_Close					25		// request to close widget

#define Event_User					1001	// first user event id

//#define Event_tuit				20		// request to quit application
//#define Event_Accel				30		// accelerator event
//#define Event_Clipboard			40		// internal clipboard event
//#define Event_SockAct				50		// socket activation
//#define Event_DragEnter			60		// drag moves into widget
//#define Event_DragMove			61		// drag moves in widget
//#define Event_DragLeave			62		// drag leaves or is cancelled
//#define Event_Drop				63		// actual drop
//#define Event_DragResponse		64		// drag accepted/rejected
//#define Event_ChildInserted		70		// new child widget
//#define Event_ChildRemoved		71		// deleted child widget
//#define Event_LayoutHint			72		// child min/max size changed



class  tEvent					// event base class
{
public:
	tEvent(int32 type)
		: t(type), posted(false) {}
	~tEvent() { if (posted) peErrMsg(); }
	int32	  type()	const { return t; }
protected:
	int32	  t;
	bool  posted;
private:
	void  peErrMsg();
};


class  tTimerEvent : public tEvent		// timer event
{
public:
	tTimerEvent(int32 timerId)
		: tEvent(Event_Timer), id(timerId) {}
	int32	  timerId()	const { return id; }
protected:
	int32	  id;
};

#define t_TIMER_EVENT(x)	((tTimerEvent*)x)

class tTouchEvent :public tEvent
{
public:
	tTouchEvent(int32 type, const tPoint &pos, int32 state)
		: tEvent(type), p(pos), s((uint16)state) {}
	const tPoint &pos() const { return p; }
	int32	   x()		const { return p.x(); }
	int32	   y()		const { return p.y(); }
	int32	   state()	const { return s; }
private:
	tPoint p;
	uint16 s;
};


enum ButtonState {				// mouse/keyboard state values
	NoButton = 0x00,
	LeftButton = 0x01,
	RightButton = 0x02,
	MidButton = 0x04,
	MouseButtonMask = 0x07,
	ShiftButton = 0x08,
	ControlButton = 0x10,
	AltButton = 0x20,
	KeyButtonMask = 0x38
};

class  tMouseEvent : public tEvent		// mouse event
{
public:
	tMouseEvent(int32 type, const tPoint &pos, int32 button, int32 state)
		: tEvent(type), p(pos), b(button), s((uint16)state) {}
	tMouseEvent(int32 type, const tPoint &pos, const tPoint&globalPos, int32 button, int32 state)
		: tEvent(type), p(pos), b(button), s((uint16)state) {
		g = globalPos;
	}
	const tPoint &pos() const { return p; }
	const tPoint &globalPos() const { return g; }
	int32	   x()		const { return p.x(); }
	int32	   y()		const { return p.y(); }
	int32	   globalX()		const { return g.x(); }
	int32	   globalY()		const { return g.y(); }
	int32	   button()	const { return b; }
	int32	   state()	const { return s; }

protected:
	tPoint p;
	static tPoint g; // ### is non-static in 2.0
	int32  b;
	uint16 s;
};

#define t_MOUSE_EVENT(x)	((tMouseEvent*)x)


class  tKeyEvent : public tEvent			// keyboard event
{
public:
	tKeyEvent(int32 type, int32 key, int32 ascii, int32 state)
		: tEvent(type), k((uint16)key), s((uint16)state), a((char)ascii),
		accpt(true) {}
	int32	   key()	const { return k; }
	int32	   ascii()	const { return a; }
	int32	   state()	const { return s; }
	bool   isAccepted() const { return accpt; }
	void   accept() { accpt = true; }
	void   ignore() { accpt = false; }
protected:
	uint16 k, s;
	char  a;
	char   accpt;				// ### tt 2.0: bool
};

#define t_KEY_EVENT(x)		((tKeyEvent*)x)


class  tFocusEvent : public tEvent		// widget focus event
{
public:
	tFocusEvent(int32 type)
		: tEvent(type) {}
	bool   gotFocus()	const { return type() == Event_FocusIn; }
	bool   lostFocus()	const { return type() == Event_FocusOut; }
};

#define t_FOCUS_EVENT(x)	((tFocusEvent*)x)


class  tPaintEvent : public tEvent		// widget paint event
{
public:
	tPaintEvent(const tRect &paintRect)
		: tEvent(Event_Paint), r(paintRect) {}
	const tRect &rect() const { return r; }
protected:
	tRect r;
};

#define t_PAINT_EVENT(x)	((tPaintEvent*)x)


class  tMoveEvent : public tEvent		// widget move event
{
public:
	tMoveEvent(const tPoint &pos, const tPoint &oldPos)
		: tEvent(Event_Move), p(pos), oldp(oldPos) {}
	const tPoint &pos()	  const { return p; }
	const tPoint &oldPos()const { return oldp; }
protected:
	tPoint p, oldp;
};

#define t_MOVE_EVENT(x)		((tMoveEvent*)x)


class  tResizeEvent : public tEvent		// widget resize event
{
public:
	tResizeEvent(const tSize &size, const tSize &oldSize)
		: tEvent(Event_Resize), s(size), olds(oldSize) {}
	const tSize &size()	  const { return s; }
	const tSize &oldSize()const { return olds; }
protected:
	tSize s, olds;
};

#define t_RESIZE_EVENT(x)	((tResizeEvent*)x)


class  tCloseEvent : public tEvent		// widget close event
{
public:
	tCloseEvent()
		: tEvent(Event_Close), accpt(false) {}
	bool   isAccepted() const { return accpt; }
	void   accept() { accpt = true; }
	void   ignore() { accpt = false; }
protected:
	bool   accpt;
};

#define t_CLOSE_EVENT(x)	((tCloseEvent*)x)


class  tShowEvent : public tEvent		// widget show event
{
public:
	tShowEvent(bool spontaneous)
		: tEvent(Event_Show), spont(spontaneous) {}
	bool spontaneous() const { return spont; }
protected:
	bool spont;
};

#define t_SHOW_EVENT(x)		((tShowEvent*)x)


class  tHideEvent : public tEvent		// widget hide event
{
public:
	tHideEvent(bool spontaneous)
		: tEvent(Event_Hide), spont(spontaneous) {}
	bool spontaneous() const { return spont; }
protected:
	bool spont;
};

#define t_HIDE_EVENT(x)		((tHideEvent*)x)



class  tCustomEvent : public tEvent		// user-defined event
{
public:
	tCustomEvent(int32 type, void *data)
		: tEvent(type), d(data) {}
	void       *data()	const { return d; }
private:
	void       *d;
};


#define t_CUSTOM_EVENT(x)	((tCustomEvent*)x)



#endif // !_TEVENT_H_
