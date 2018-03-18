#ifndef _TRECT_H_
#define _TRECT_H_

#include "TGlobal.h"
#include "TObject/TSize.h"


class  TRect					// rectangle class
{
public:
	TRect() { x1 = y1 = 0; x2 = y2 = -1; }
	TRect(const TPoint &topleft, const TPoint &bottomright);
	TRect(const TPoint &topleft, const TSize &size);
	TRect(int left, int top, int width, int height);

	bool   isNull()	const;
	bool   isEmpty()	const;
	bool   isValid()	const;
	bool   isValidStrict()	const; //如果是直线也是无效的
	TRect  normalize()	const;

	int	   left()	const;
	int	   top()	const;
	int	   right()	const;
	int	   bottom()	const;
	int	   x()		const;
	int	   y()		const;
	void   setLeft(int pos);
	void   setTop(int pos);
	void   setRight(int pos);
	void   setBottom(int pos);
	void   setX(int x);
	void   setY(int y);

	TPoint topLeft()	 const;
	TPoint bottomRight() const;
	TPoint topRight()	 const;
	TPoint bottomLeft()	 const;
	TPoint center()	 const;

	void   rect(int *x, int *y, int *w, int *h) const;
	void   coords(int *x1, int *y1, int *x2, int *y2) const;

	void   moveTopLeft(const TPoint &p);
	void   moveTopLeft(int32 xt, int32 yt);
	void   moveBottomRight(const TPoint &p);
	void   moveTopRight(const TPoint &p);
	void   moveBottomLeft(const TPoint &p);
	void   moveCenter(const TPoint &p);
	void   moveBy(int dx, int dy);

	void   setRect(int x, int y, int w, int h);
	void   setCoords(int x1, int y1, int x2, int y2);

	TSize  size()	const;
	int	   width()	const;
	int	   height()	const;
	void   setWidth(int w);
	void   setHeight(int h);
	void   setSize(const TSize &s);

	bool   contains(const TPoint &p, bool proper = false) const;
	bool   contains(const TRect &r, bool proper = false) const;
	TRect  unite(const TRect &r) const;
	TRect  intersect(const TRect &r) const;
	bool   intersects(const TRect &r) const;
	void   intersectInr(TRect *r);

	friend  bool operator==(const TRect &, const TRect &);
	friend  bool operator!=(const TRect &, const TRect &);

private:
	int32 x1;
	int32 y1;
	int32 x2;
	int32 y2;
};

 bool operator==(const TRect &, const TRect &);
 bool operator!=(const TRect &, const TRect &);


/*****************************************************************************
TRect inline member functions
*****************************************************************************/

inline TRect::TRect(int left, int top, int width, int height)
{
	x1 = (int32)left;
	y1 = (int32)top;
	x2 = (int32)(left + width - 1);
	y2 = (int32)(top + height - 1);
}

inline bool TRect::isNull() const
{
	return x2 == x1 - 1 && y2 == y1 - 1;
}

inline bool TRect::isEmpty() const
{
	return x1 > x2 || y1 > y2;
}

inline bool TRect::isValid() const
{
	return x1 <= x2 && y1 <= y2;
}

inline bool TRect::isValidStrict() const
{
	return x1 < x2 && y1 < y2;
}

inline int TRect::left() const
{
	return x1;
}

inline int TRect::top() const
{
	return y1;
}

inline int TRect::right() const
{
	return x2;
}

inline int TRect::bottom() const
{
	return y2;
}

inline int TRect::x() const
{
	return x1;
}

inline int TRect::y() const
{
	return y1;
}

inline void TRect::setLeft(int pos)
{
	x1 = (int32)pos;
}

inline void TRect::setTop(int pos)
{
	y1 = (int32)pos;
}

inline void TRect::setRight(int pos)
{
	x2 = (int32)pos;
}

inline void TRect::setBottom(int pos)
{
	y2 = (int32)pos;
}

inline void TRect::setX(int x)
{
	x1 = (int32)x;
}

inline void TRect::setY(int y)
{
	y1 = (int32)y;
}

inline TPoint TRect::topLeft() const
{
	return TPoint(x1, y1);
}

inline TPoint TRect::bottomRight() const
{
	return TPoint(x2, y2);
}

inline TPoint TRect::topRight() const
{
	return TPoint(x2, y1);
}

inline TPoint TRect::bottomLeft() const
{
	return TPoint(x1, y2);
}

inline TPoint TRect::center() const
{
	return TPoint((x1 + x2) / 2, (y1 + y2) / 2);
}

inline int TRect::width() const
{
	return  x2 - x1 + 1;
}

inline int TRect::height() const
{
	return  y2 - y1 + 1;
}

inline TSize TRect::size() const
{
	return TSize(x2 - x1 + 1, y2 - y1 + 1);
}


#endif // _TRECT_H_
