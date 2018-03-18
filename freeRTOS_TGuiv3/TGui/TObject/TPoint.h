#ifndef _TPOINT_H_
#define _TPOINT_H_

#include "TGlobal.h"

class  TPoint
{
public:
    TPoint()	{}
    TPoint( int32 xpos, int32 ypos );

    bool   isNull()	const;

    int32	   x()		const;
    int32	   y()		const;
    void   setX( int32 x );
    void   setY( int32 y );

    TPoint &operator+=( const TPoint &p );
    TPoint &operator-=( const TPoint &p );
    TPoint &operator*=( int32 c );
    TPoint &operator*=( double c );
    TPoint &operator/=( int32 c );
    TPoint &operator/=( double c );

    friend inline bool	 operator==( const TPoint &, const TPoint & );
    friend inline bool	 operator!=( const TPoint &, const TPoint & );
    friend inline TPoint operator+( const TPoint &, const TPoint & );
    friend inline TPoint operator-( const TPoint &, const TPoint & );
    friend inline TPoint operator*( const TPoint &, int32 );
    friend inline TPoint operator*( int32, const TPoint & );
    friend inline TPoint operator*( const TPoint &, double );
    friend inline TPoint operator*( double, const TPoint & );
    friend inline TPoint operator-( const TPoint & );
    friend inline TPoint operator/( const TPoint &, int32 );
    friend inline TPoint operator/( const TPoint &, double );


private:
	int32 xp;
	int32 yp;
};


/*****************************************************************************
  TPoint inline functions
 *****************************************************************************/

inline TPoint::TPoint( int32 xpos, int32 ypos )
{ xp=xpos; yp=ypos; }

inline bool TPoint::isNull() const
{ return xp == 0 && yp == 0; }

inline int32 TPoint::x() const
{ return xp; }

inline int32 TPoint::y() const
{ return yp; }

inline void TPoint::setX( int32 x )
{ xp = x; }

inline void TPoint::setY( int32 y )
{ yp = y; }

inline TPoint &TPoint::operator+=( const TPoint &p )
{ xp += p.xp; yp += p.yp; return *this; }

inline TPoint &TPoint::operator-=( const TPoint &p )
{ xp -= p.xp; yp -= p.yp; return *this; }

inline TPoint &TPoint::operator*=( int32 c )
{ xp *= c; yp *= c; return *this; }

inline TPoint &TPoint::operator*=( double c )
{ xp = (xp*c); yp = (yp*c); return *this; }

inline bool operator==( const TPoint &p1, const TPoint &p2 )
{ return p1.xp == p2.xp && p1.yp == p2.yp; }

inline bool operator!=( const TPoint &p1, const TPoint &p2 )
{ return p1.xp != p2.xp || p1.yp != p2.yp; }

inline TPoint operator+( const TPoint &p1, const TPoint &p2 )
{ return TPoint(p1.xp+p2.xp, p1.yp+p2.yp); }

inline TPoint operator-( const TPoint &p1, const TPoint &p2 )
{ return TPoint(p1.xp-p2.xp, p1.yp-p2.yp); }

inline TPoint operator*( const TPoint &p, int32 c )
{ return TPoint(p.xp*c, p.yp*c); }

inline TPoint operator*( int32 c, const TPoint &p )
{ return TPoint(p.xp*c, p.yp*c); }

inline TPoint operator*( const TPoint &p, double c )
{ return TPoint((p.xp*c), (p.yp*c)); }

inline TPoint operator*( double c, const TPoint &p )
{ return TPoint((p.xp*c), (p.yp*c)); }

inline TPoint operator-( const TPoint &p )
{ return TPoint(-p.xp, -p.yp); }

//
// The TPoint functions below are inline if DEBUG is not defined.
// The debug implementation in qpoint.cpp checks c and gives a warning
// before dividing by zero.
//


inline TPoint &TPoint::operator/=( int32 c )
{ xp/=c; yp/=c; return *this; }

inline TPoint &TPoint::operator/=( double c )
{ xp=(xp/c); yp=(yp/c); return *this; }

inline TPoint operator/( const TPoint &p, int32 c )
{ return TPoint(p.xp/c, p.yp/c); }

inline TPoint operator/( const TPoint &p, double c )
{ return TPoint((p.xp/c), (p.yp/c)); }




#endif // _TPOINT_H_
