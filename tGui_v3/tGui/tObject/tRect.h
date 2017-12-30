#ifndef _TRECT_H_
#define _TRECT_H_

#include "tGlobal.h"
#include "tSize.h"


class  tRect					// rectangle class
{
public:
	tRect() { x1 = y1 = 0; x2 = y2 = -1; }
	tRect(const tPoint &topleft, const tPoint &bottomright);
	tRect(const tPoint &topleft, const tSize &size);
	tRect(int left, int top, int width, int height);

	bool   isNull()	const;
	bool   isEmpty()	const;
	bool   isValid()	const;
	tRect  normalize()	const;

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

	tPoint topLeft()	 const;
	tPoint bottomRight() const;
	tPoint topRight()	 const;
	tPoint bottomLeft()	 const;
	tPoint center()	 const;

	void   rect(int *x, int *y, int *w, int *h) const;
	void   coords(int *x1, int *y1, int *x2, int *y2) const;

	void   moveTopLeft(const tPoint &p);
	void   moveTopLeft(int32 xt, int32 yt);
	void   moveBottomRight(const tPoint &p);
	void   moveTopRight(const tPoint &p);
	void   moveBottomLeft(const tPoint &p);
	void   moveCenter(const tPoint &p);
	void   moveBy(int dx, int dy);

	void   setRect(int x, int y, int w, int h);
	void   setCoords(int x1, int y1, int x2, int y2);

	tSize  size()	const;
	int	   width()	const;
	int	   height()	const;
	void   setWidth(int w);
	void   setHeight(int h);
	void   setSize(const tSize &s);

	bool   contains(const tPoint &p, bool proper = false) const;
	bool   contains(const tRect &r, bool proper = false) const;
	tRect  unite(const tRect &r) const;
	tRect  intersect(const tRect &r) const;
	bool   intersects(const tRect &r) const;

	friend  bool operator==(const tRect &, const tRect &);
	friend  bool operator!=(const tRect &, const tRect &);

private:
	int32 x1;
	int32 y1;
	int32 x2;
	int32 y2;
};

 bool operator==(const tRect &, const tRect &);
 bool operator!=(const tRect &, const tRect &);


/*****************************************************************************
tRect inline member functions
*****************************************************************************/

inline tRect::tRect(int left, int top, int width, int height)
{
	x1 = (int32)left;
	y1 = (int32)top;
	x2 = (int32)(left + width - 1);
	y2 = (int32)(top + height - 1);
}

inline bool tRect::isNull() const
{
	return x2 == x1 - 1 && y2 == y1 - 1;
}

inline bool tRect::isEmpty() const
{
	return x1 > x2 || y1 > y2;
}

inline bool tRect::isValid() const
{
	return x1 <= x2 && y1 <= y2;
}

inline int tRect::left() const
{
	return x1;
}

inline int tRect::top() const
{
	return y1;
}

inline int tRect::right() const
{
	return x2;
}

inline int tRect::bottom() const
{
	return y2;
}

inline int tRect::x() const
{
	return x1;
}

inline int tRect::y() const
{
	return y1;
}

inline void tRect::setLeft(int pos)
{
	x1 = (int32)pos;
}

inline void tRect::setTop(int pos)
{
	y1 = (int32)pos;
}

inline void tRect::setRight(int pos)
{
	x2 = (int32)pos;
}

inline void tRect::setBottom(int pos)
{
	y2 = (int32)pos;
}

inline void tRect::setX(int x)
{
	x1 = (int32)x;
}

inline void tRect::setY(int y)
{
	y1 = (int32)y;
}

inline tPoint tRect::topLeft() const
{
	return tPoint(x1, y1);
}

inline tPoint tRect::bottomRight() const
{
	return tPoint(x2, y2);
}

inline tPoint tRect::topRight() const
{
	return tPoint(x2, y1);
}

inline tPoint tRect::bottomLeft() const
{
	return tPoint(x1, y2);
}

inline tPoint tRect::center() const
{
	return tPoint((x1 + x2) / 2, (y1 + y2) / 2);
}

inline int tRect::width() const
{
	return  x2 - x1 + 1;
}

inline int tRect::height() const
{
	return  y2 - y1 + 1;
}

inline tSize tRect::size() const
{
	return tSize(x2 - x1 + 1, y2 - y1 + 1);
}


#endif // _TRECT_H_
