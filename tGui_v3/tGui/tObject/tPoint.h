#ifndef _TPOINT_H_
#define _TPOINT_H_

#include "tGlobal.h"

class  tPoint
{
public:
    tPoint()	{}
    tPoint( int32 xpos, int32 ypos );

    bool   isNull()	const;

    int32	   x()		const;
    int32	   y()		const;
    void   setX( int32 x );
    void   setY( int32 y );

    tPoint &operator+=( const tPoint &p );
    tPoint &operator-=( const tPoint &p );
    tPoint &operator*=( int32 c );
    tPoint &operator*=( double c );
    tPoint &operator/=( int32 c );
    tPoint &operator/=( double c );

    friend inline bool	 operator==( const tPoint &, const tPoint & );
    friend inline bool	 operator!=( const tPoint &, const tPoint & );
    friend inline tPoint operator+( const tPoint &, const tPoint & );
    friend inline tPoint operator-( const tPoint &, const tPoint & );
    friend inline tPoint operator*( const tPoint &, int32 );
    friend inline tPoint operator*( int32, const tPoint & );
    friend inline tPoint operator*( const tPoint &, double );
    friend inline tPoint operator*( double, const tPoint & );
    friend inline tPoint operator-( const tPoint & );
    friend inline tPoint operator/( const tPoint &, int32 );
    friend inline tPoint operator/( const tPoint &, double );


private:
	int32 xp;
	int32 yp;
};


/*****************************************************************************
  tPoint inline functions
 *****************************************************************************/

inline tPoint::tPoint( int32 xpos, int32 ypos )
{ xp=xpos; yp=ypos; }

inline bool tPoint::isNull() const
{ return xp == 0 && yp == 0; }

inline int32 tPoint::x() const
{ return xp; }

inline int32 tPoint::y() const
{ return yp; }

inline void tPoint::setX( int32 x )
{ xp = x; }

inline void tPoint::setY( int32 y )
{ yp = y; }

inline tPoint &tPoint::operator+=( const tPoint &p )
{ xp += p.xp; yp += p.yp; return *this; }

inline tPoint &tPoint::operator-=( const tPoint &p )
{ xp -= p.xp; yp -= p.yp; return *this; }

inline tPoint &tPoint::operator*=( int32 c )
{ xp *= c; yp *= c; return *this; }

inline tPoint &tPoint::operator*=( double c )
{ xp = (xp*c); yp = (yp*c); return *this; }

inline bool operator==( const tPoint &p1, const tPoint &p2 )
{ return p1.xp == p2.xp && p1.yp == p2.yp; }

inline bool operator!=( const tPoint &p1, const tPoint &p2 )
{ return p1.xp != p2.xp || p1.yp != p2.yp; }

inline tPoint operator+( const tPoint &p1, const tPoint &p2 )
{ return tPoint(p1.xp+p2.xp, p1.yp+p2.yp); }

inline tPoint operator-( const tPoint &p1, const tPoint &p2 )
{ return tPoint(p1.xp-p2.xp, p1.yp-p2.yp); }

inline tPoint operator*( const tPoint &p, int32 c )
{ return tPoint(p.xp*c, p.yp*c); }

inline tPoint operator*( int32 c, const tPoint &p )
{ return tPoint(p.xp*c, p.yp*c); }

inline tPoint operator*( const tPoint &p, double c )
{ return tPoint((p.xp*c), (p.yp*c)); }

inline tPoint operator*( double c, const tPoint &p )
{ return tPoint((p.xp*c), (p.yp*c)); }

inline tPoint operator-( const tPoint &p )
{ return tPoint(-p.xp, -p.yp); }

//
// The tPoint functions below are inline if DEBUG is not defined.
// The debug implementation in qpoint.cpp checks c and gives a warning
// before dividing by zero.
//


inline tPoint &tPoint::operator/=( int32 c )
{ xp/=c; yp/=c; return *this; }

inline tPoint &tPoint::operator/=( double c )
{ xp=(xp/c); yp=(yp/c); return *this; }

inline tPoint operator/( const tPoint &p, int32 c )
{ return tPoint(p.xp/c, p.yp/c); }

inline tPoint operator/( const tPoint &p, double c )
{ return tPoint((p.xp/c), (p.yp/c)); }




#endif // _TPOINT_H_
