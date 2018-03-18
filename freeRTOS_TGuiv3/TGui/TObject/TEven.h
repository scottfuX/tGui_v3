#ifndef _TEVENT_H_
#define _TEVENT_H_

#include "TGlobal.h"
#include "TObject/TPoint.h"
#include "TObject/TSize.h"
#include "TObject/TRect.h"



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


class  TEvent					// event base class
{
public:
	TEvent(int32 type)
		: t(type), posted(false) {}
	virtual ~TEvent() { if (posted) peErrMsg(); }
	int32	  type()	const { return t; }
protected:
	int32	  t;
	bool  posted;
private:
	void  peErrMsg();
};


class  TTimerEvent : public TEvent		// timer event
{
public:
	TTimerEvent(int32 timerId)
		: TEvent(Event_Timer), id(timerId) {}
	int32	  timerId()	const { return id; }
protected:
	int32	  id;
};

#define T_TIMER_EVENT(x)	((TTimerEvent*)x)

class TTouchEvent :public TEvent
{
public:
	TTouchEvent(int32 type, const TPoint &pos)
		: TEvent(type) { p = new TPoint(pos);}
	virtual ~TTouchEvent() { delete p; };
	const TPoint *pos() const { return p; }
	int32	   x()		const { return p->x(); }
	int32	   y()		const { return p->y(); }
private:
	TPoint* p;
};
#define T_THOUCH_EVENT(x)	((TTouchEvent*)x)

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

class  TMouseEvent : public TEvent		// mouse event
{
public:
	TMouseEvent(int32 type, const TPoint &pos, int32 button, int32 state)
		: TEvent(type), p(pos), b(button), s((uint16)state) {}
	TMouseEvent(int32 type, const TPoint &pos, const TPoint&globalPos, int32 button, int32 state)
		: TEvent(type), p(pos), b(button), s((uint16)state) {
		g = globalPos;
	}
	const TPoint &pos() const { return p; }
	const TPoint &globalPos() const { return g; }
	int32	   x()		const { return p.x(); }
	int32	   y()		const { return p.y(); }
	int32	   globalX()		const { return g.x(); }
	int32	   globalY()		const { return g.y(); }
	int32	   button()	const { return b; }
	int32	   state()	const { return s; }

protected:
	TPoint p;
	static TPoint g; // ### is non-static in 2.0
	int32  b;
	uint16 s;
};

#define T_MOUSE_EVENT(x)	((TMouseEvent*)x)


class  TKeyEvent : public TEvent			// keyboard event
{
public:
	TKeyEvent(int32 type, int32 key, int32 ascii, int32 state)
		: TEvent(type), k((uint16)key), s((uint16)state), a((char)ascii),
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

#define T_KEY_EVENT(x)		((TKeyEvent*)x)


class  TFocusEvent : public TEvent		// widget focus event
{
public:
	TFocusEvent(int32 type)
		: TEvent(type) {}
	bool   gotFocus()	const { return type() == Event_FocusIn; }
	bool   lostFocus()	const { return type() == Event_FocusOut; }
};

#define T_FOCUS_EVENT(x)	((TFocusEvent*)x)


class  TPainTEvent : public TEvent		// widget paint event
{
public:
	TPainTEvent(const TRect &paintRect)
		: TEvent(Event_Paint), r(paintRect) {}
	const TRect &rect() const { return r; }
protected:
	TRect r;
};

#define T_PAINT_EVENT(x)	((TPainTEvent*)x)


class  TMoveEvent : public TEvent		// widget move event
{
public:
	TMoveEvent(const TPoint &pos, const TPoint &oldPos)
		: TEvent(Event_Move), p(pos), oldp(oldPos) {}
	const TPoint &pos()	  const { return p; }
	const TPoint &oldPos()const { return oldp; }
protected:
	TPoint p, oldp;
};

#define T_MOVE_EVENT(x)		((TMoveEvent*)x)


class  TResizeEvent : public TEvent		// widget resize event
{
public:
	TResizeEvent(const TSize &size, const TSize &oldSize)
		: TEvent(Event_Resize), s(size), olds(oldSize) {}
	const TSize &size()	  const { return s; }
	const TSize &oldSize()const { return olds; }
protected:
	TSize s, olds;
};

#define T_RESIZE_EVENT(x)	((TResizeEvent*)x)


class  TCloseEvent : public TEvent		// widget close event
{
public:
	TCloseEvent()
		: TEvent(Event_Close), accpt(false) {}
	bool   isAccepted() const { return accpt; }
	void   accept() { accpt = true; }
	void   ignore() { accpt = false; }
protected:
	bool   accpt;
};

#define T_CLOSE_EVENT(x)	((TCloseEvent*)x)


class  TShowEvent : public TEvent		// widget show event
{
public:
	TShowEvent(bool spontaneous)
		: TEvent(Event_Show), spont(spontaneous) {}
	bool spontaneous() const { return spont; }
protected:
	bool spont;
};

#define T_SHOW_EVENT(x)		((TShowEvent*)x)


class  THideEvent : public TEvent		// widget hide event
{
public:
	THideEvent(bool spontaneous)
		: TEvent(Event_Hide), spont(spontaneous) {}
	bool spontaneous() const { return spont; }
protected:
	bool spont;
};

#define T_HIDE_EVENT(x)		((THideEvent*)x)



class  TCustomEvent : public TEvent		// user-defined event
{
public:
	TCustomEvent(int32 type, void *data)
		: TEvent(type), d(data) {}
	void       *data()	const { return d; }
private:
	void       *d;
};

#define T_CUSTOM_EVENT(x)	((TCustomEvent*)x);

#endif // !_TEVENT_H_
