#ifndef _TSIZE_H_
#define _TSIZE_H_

#include "tGlobal.h"
#include "tPoint.h"

class  tSize
{
public:
    tSize()	{ wd = ht = -1; }
    tSize( int32 w, int32 h );

    bool   isNull()	const;
    bool   isEmpty() const;
    bool   isValid() const;

    int32	   width()	const;
    int32	   height()	const;
    void   setWidth( int32 w );
    void   setHeight( int32 h );
    void   transpose();

    tSize expandedTo( const tSize & ) const;
    tSize boundedTo( const tSize & ) const;

    int32 &rwidth();
    int32 &rheight();

    tSize &operator+=( const tSize & );
    tSize &operator-=( const tSize & );
    tSize &operator*=( int32 c );
    tSize &operator*=( float c );
    tSize &operator/=( int32 c );
    tSize &operator/=( float c );

    friend inline bool	operator==( const tSize &, const tSize & );
    friend inline bool	operator!=( const tSize &, const tSize & );
    friend inline tSize operator+( const tSize &, const tSize & );
    friend inline tSize operator-( const tSize &, const tSize & );
    friend inline tSize operator*( const tSize &, int32 );
    friend inline tSize operator*( int32, const tSize & );
    friend inline tSize operator*( const tSize &, float );
    friend inline tSize operator*( float, const tSize & );

    friend inline tSize operator/( const tSize &, int32 );
    friend inline tSize operator/( const tSize &, float );

private:
     int32 wd;
     int32 ht;
};


/*****************************************************************************
  tSize inline functions
 *****************************************************************************/

inline tSize::tSize( int32 w, int32 h )
{ wd=w; ht=h; }

inline bool tSize::isNull() const
{ return wd==0 && ht==0; }

inline bool tSize::isEmpty() const
{ return wd<1 || ht<1; }

inline bool tSize::isValid() const
{ return wd>=0 && ht>=0; }

inline int32 tSize::width() const
{ return wd; }

inline int32 tSize::height() const
{ return ht; }

inline void tSize::setWidth( int32 w )
{ wd=w; }

inline void tSize::setHeight( int32 h )
{ ht=h; }

inline int32 &tSize::rwidth()
{ return wd; }

inline int32 &tSize::rheight()
{ return ht; }

inline tSize &tSize::operator+=( const tSize &s )
{ wd+=s.wd; ht+=s.ht; return *this; }

inline tSize &tSize::operator-=( const tSize &s )
{ wd-=s.wd; ht-=s.ht; return *this; }

inline tSize &tSize::operator*=( int32 c )
{ wd*=c; ht*=c; return *this; }

inline tSize &tSize::operator*=( float c )
{ wd=(wd*c); ht=(ht*c); return *this; }

inline bool operator==( const tSize &s1, const tSize &s2 )
{ return s1.wd == s2.wd && s1.ht == s2.ht; }

inline bool operator!=( const tSize &s1, const tSize &s2 )
{ return s1.wd != s2.wd || s1.ht != s2.ht; }

inline tSize operator+( const tSize & s1, const tSize & s2 )
{ return tSize(s1.wd+s2.wd, s1.ht+s2.ht); }

inline tSize operator-( const tSize &s1, const tSize &s2 )
{ return tSize(s1.wd-s2.wd, s1.ht-s2.ht); }

inline tSize operator*( const tSize &s, int32 c )
{ return tSize(s.wd*c, s.ht*c); }

inline tSize operator*( int32 c, const tSize &s )
{  return tSize(s.wd*c, s.ht*c); }

inline tSize operator*( const tSize &s, float c )
{ return tSize((s.wd*c), (s.ht*c)); }

inline tSize operator*( float c, const tSize &s )
{ return tSize((s.wd*c), (s.ht*c)); }


inline tSize &tSize::operator/=( int32 c )
{ wd/=c; ht/=c; return *this; }

inline tSize &tSize::operator/=( float c )
{ wd=(wd/c); ht=(ht/c); return *this; }

inline tSize operator/( const tSize &s, int32 c )
{ return tSize(s.wd/c, s.ht/c); }

inline tSize operator/( const tSize &s, float c )
{ return tSize((s.wd/c), (s.ht/c)); }


#endif // _TSIZE_H_
