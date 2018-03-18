#include "TObject/TRect.h"


/*****************************************************************************
TRect member functions
*****************************************************************************/
/*!
Constructs a rectangle with \e topLeft as the top left corner and
\e bottomRight as the bottom right corner.
*/

TRect::TRect(const TPoint &topLeft, const TPoint &bottomRight)
{
	x1 = topLeft.x();
	y1 = topLeft.y();
	x2 = bottomRight.x();
	y2 = bottomRight.y();
}

/*!
Constructs a rectangle with \e topLeft as the top left corner and
\e size as the rectangle size.
*/

TRect::TRect(const TPoint &topLeft, const TSize &size)
{
	x1 = topLeft.x();
	y1 = topLeft.y();
	x2 = (x1 + size.width() - 1);
	y2 = (y1 + size.height() - 1);
}


/*!
Returns a normalized rectangle, i.e. one that has a non-negative width
and height.

It swaps left and right if left() \> right(), and swaps top and bottom if
top() \> bottom().

\sa isValid()
*/

TRect TRect::normalize() const
{
	TRect r;
	if (x2 < x1) {				// swap bad x values
		r.x1 = x2;
		r.x2 = x1;
	}
	else {
		r.x1 = x1;
		r.x2 = x2;
	}
	if (y2 < y1) {				// swap bad y values
		r.y1 = y2;
		r.y2 = y1;
	}
	else {
		r.y1 = y1;
		r.y2 = y2;
	}
	return r;
}


/*!
Extracts the rectangle parameters as the position and the size.
\sa setRect(), coords()
*/

void TRect::rect(int *x, int *y, int *w, int *h) const
{
	*x = x1;
	*y = y1;
	*w = x2 - x1 + 1;
	*h = y2 - y1 + 1;
}

/*!
Extracts the rectangle parameters as the top left point and the
bottom right point.
\sa setCoords(), rect()
*/

void TRect::coords(int *xp1, int *yp1, int *xp2, int *yp2) const
{
	*xp1 = x1;
	*yp1 = y1;
	*xp2 = x2;
	*yp2 = y2;
}

/*!
Sets the top left position of the rectangle to \e p, leaving the
size unchanged.
\sa topLeft(), moveTopRight(), moveBottomLeft(), moveBottomRight(),
setTop(), setLeft()
*/

void TRect::moveTopLeft(const TPoint &p)
{
	x2 += (p.x() - x1);
	y2 += (p.y() - y1);
	x1 = p.x();
	y1 = p.y();
}

void TRect::moveTopLeft(int32 xt, int32 yt)
{
	x2 += (xt - x1);
	y2 += (yt - y1);
	x1 = xt;
	y1 = yt;
}

/*!
Sets the bottom right position of the rectangle to \e p, leaving the size
unchanged.
\sa bottomRight(), moveBottomLeft(), moveTopLeft(), moveTopRight(),
setBottom(), setRight()
*/

void TRect::moveBottomRight(const TPoint &p)
{
	x1 += (p.x() - x2);
	y1 += (p.y() - y2);
	x2 = p.x();
	y2 = p.y();
}

/*!
Sets the top right position of the rectangle to \e p, leaving the
size unchanged.
\sa topRight(), moveTopLeft(), moveBottomLeft(), moveBottomRight(),
setTop(), setRight()
*/

void TRect::moveTopRight(const TPoint &p)
{
	x1 += (p.x() - x2);
	y2 += (p.y() - y1);
	x2 = p.x();
	y1 = p.y();
}

/*!
Sets the bottom left position of the rectangle to \e p, leaving
the size unchanged.
\sa bottomLeft(), moveBottomRight(), moveTopLeft(), moveTopRight(),
setBottom(), setLeft()
*/

void TRect::moveBottomLeft(const TPoint &p)
{
	x2 += (p.x() - x1);
	y1 += (p.y() - y2);
	x1 = p.x();
	y2 = p.y();
}


/*!
Sets the center point of the rectangle to \e p, leaving the size
unchanged.
\sa center(), moveTopLeft(), moveTopRight(), moveBottomLeft(), moveBottomRight()
*/

void TRect::moveCenter(const TPoint &p)
{
	int32 w = x2 - x1;
	int32 h = y2 - y1;
	x1 = (p.x() - w / 2);
	y1 = (p.y() - h / 2);
	x2 = x1 + w;
	y2 = y1 + h;
}


/*!
Moves the rectangle \e dx along the X axis and \e dy along the Y
axis, relative to the current position. (Positive values moves the
rectangle rightwards and/or downwards.)
*/


void TRect::moveBy(int dx, int dy)
{
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

/*!
Sets the coordinates of the rectangle's top left corner to \e
(x,y), and its size to (w,h).
\sa rect(), setCoords()
*/

void TRect::setRect(int x, int y, int w, int h)
{
	x1 = x;
	y1 = y;
	x2 = (x + w - 1);
	y2 = (y + h - 1);
}

/*!
Sets the coordinates of the rectangle's top left corner to \e (xp1,yp1),
and the coordinates of its bottom right corner to \e (xp2,yp2).
\sa coords(), setRect()
*/

void TRect::setCoords(int xp1, int yp1, int xp2, int yp2)
{
	x1 = xp1;
	y1 = yp1;
	x2 = xp2;
	y2 = yp2;
}


/*!
Sets the width of the rectangle to \e w. The right edge is
changed, but not the left edge.
\sa width(), setLeft(), setRight(), setSize()
*/

void TRect::setWidth(int w)
{
	x2 = (x1 + w - 1);
}

/*!
Sets the height of the rectangle to \e h. The top edge is not
moved, but the bottom edge may be moved.
\sa height(), setTop(), setBottom(), setSize()
*/

void TRect::setHeight(int h)
{
	y2 = (y1 + h - 1);
}

/*!
Sets the size of the rectangle to \e s. The top left corner is not moved.
\sa size(), setWidth(), setHeight()
*/

void TRect::setSize(const TSize &s)
{
	x2 = (s.width() + x1 - 1);
	y2 = (s.height() + y1 - 1);
}

/*!
Returns TRUE if the point \e p is inside or on the edge of the
rectangle.

If \e proper is TRUE, this function returns TRUE only if \e p is
inside (not on the edge).
*/

bool TRect::contains(const TPoint &p, bool proper) const
{
	if (proper)
		return p.x() > x1 && p.x() < x2 &&
		p.y() > y1 && p.y() < y2;
	else
		return p.x() >= x1 && p.x() <= x2 &&
		p.y() >= y1 && p.y() <= y2;
}

/*!
Returns TRUE if the rectangle \e r is inside this rectangle.

If \e proper is TRUE, this function returns TRUE only if \e r is
entirely inside (not on the edge).

\sa unite(), intersect(), intersects()
*/

bool TRect::contains(const TRect &r, bool proper) const
{
	if (proper)
		return r.x1 > x1 && r.x2 < x2 && r.y1 > y1 && r.y2 < y2;
	else
		return r.x1 >= x1 && r.x2 <= x2 && r.y1 >= y1 && r.y2 <= y2;
}

/*!
Returns the union rectangle of this rectangle and \e r.  The union
rectangle of a nonempty rectangle and an empty or invalid rectangle
is defined to be the nonempty rectangle.

\sa intersect(), intersects(), contains()
*/

TRect TRect::unite(const TRect &r) const
{
	if (isValid()) {
		if (r.isValid()) {
			TRect tmp;
			tmp.setLeft(MIN(x1, r.x1));
			tmp.setRight(MAX(x2, r.x2));
			tmp.setTop(MIN(y1, r.y1));
			tmp.setBottom(MAX(y2, r.y2));
			return tmp;
		}
		else {
			return *this;
		}
	}
	else {
		return r;
	}
}




//比较之后把交集区域 存回 参数中
void TRect::intersectInr(TRect *r) 
{
	r->x1 = MAX(x1, r->x1);
	r->x2 = MIN(x2, r->x2);
	r->y1 = MAX(y1, r->y1);
	r->y2 = MIN(y2, r->y2);
}

/*!
Returns the intersection rectangle of this rectangle and \e r.

Returns an empty rectangle if there is no intersection.

\sa isEmpty(), intersects(), unite(), contains()
*/

TRect TRect::intersect(const TRect &r) const
{
	TRect tmp;
	tmp.x1 = MAX(x1, r.x1);
	tmp.x2 = MIN(x2, r.x2);
	tmp.y1 = MAX(y1, r.y1);
	tmp.y2 = MIN(y2, r.y2);
	return tmp;
}

/*!
Returns TRUE if this rectangle intersects with \e r (there is at
least one pixel which is within both rectangles).
\sa intersect(), contains()
*/

bool TRect::intersects(const TRect &r) const
{
	return (MAX(x1, r.x1) <= MIN(x2, r.x2) &&
		MAX(y1, r.y1) <= MIN(y2, r.y2));
}


/*!
\relates TRect
Returns TRUE if \e r1 and \e r2 are equal, or FALSE if they are different.
*/

bool operator==(const TRect &r1, const TRect &r2)
{
	return r1.x1 == r2.x1 && r1.x2 == r2.x2 && r1.y1 == r2.y1 && r1.y2 == r2.y2;
}

/*!
\relates TRect
Returns TRUE if \e r1 and \e r2 are different, or FALSE if they are equal.
*/

bool operator!=(const TRect &r1, const TRect &r2)
{
	return r1.x1 != r2.x1 || r1.x2 != r2.x2 || r1.y1 != r2.y1 || r1.y2 != r2.y2;
}
