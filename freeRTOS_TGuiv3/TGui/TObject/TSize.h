#ifndef _TSIZE_H_
#define _TSIZE_H_

#include "TGlobal.h"
#include "TObject/TPoint.h"

class  TSize
{
public:
    TSize()	{ wd = ht = -1; }
    TSize( int32 w, int32 h );

    bool   isNull()	const;
    bool   isEmpty() const;
    bool   isValid() const;

    int32	   width()	const;
    int32	   height()	const;
    void   setWidth( int32 w );
    void   setHeight( int32 h );
    void   transpose();

    TSize expandedTo( const TSize & ) const;
    TSize boundedTo( const TSize & ) const;

    int32 &rwidth();
    int32 &rheight();

    TSize &operator+=( const TSize & );
    TSize &operator-=( const TSize & );
    TSize &operator*=( int32 c );
    TSize &operator*=( float c );
    TSize &operator/=( int32 c );
    TSize &operator/=( float c );

    friend inline bool	operator==( const TSize &, const TSize & );
    friend inline bool	operator!=( const TSize &, const TSize & );
    friend inline TSize operator+( const TSize &, const TSize & );
    friend inline TSize operator-( const TSize &, const TSize & );
    friend inline TSize operator*( const TSize &, int32 );
    friend inline TSize operator*( int32, const TSize & );
    friend inline TSize operator*( const TSize &, float );
    friend inline TSize operator*( float, const TSize & );

    friend inline TSize operator/( const TSize &, int32 );
    friend inline TSize operator/( const TSize &, float );

private:
     int32 wd;
     int32 ht;
};


/*****************************************************************************
  TSize inline functions
 *****************************************************************************/

inline TSize::TSize( int32 w, int32 h )
{ wd=w; ht=h; }

inline bool TSize::isNull() const
{ return wd==0 && ht==0; }

inline bool TSize::isEmpty() const
{ return wd<1 || ht<1; }

inline bool TSize::isValid() const
{ return wd>=0 && ht>=0; }

inline int32 TSize::width() const
{ return wd; }

inline int32 TSize::height() const
{ return ht; }

inline void TSize::setWidth( int32 w )
{ wd=w; }

inline void TSize::setHeight( int32 h )
{ ht=h; }

inline int32 &TSize::rwidth()
{ return wd; }

inline int32 &TSize::rheight()
{ return ht; }

inline TSize &TSize::operator+=( const TSize &s )
{ wd+=s.wd; ht+=s.ht; return *this; }

inline TSize &TSize::operator-=( const TSize &s )
{ wd-=s.wd; ht-=s.ht; return *this; }

inline TSize &TSize::operator*=( int32 c )
{ wd*=c; ht*=c; return *this; }

inline TSize &TSize::operator*=( float c )
{ wd=(wd*c); ht=(ht*c); return *this; }

inline bool operator==( const TSize &s1, const TSize &s2 )
{ return s1.wd == s2.wd && s1.ht == s2.ht; }

inline bool operator!=( const TSize &s1, const TSize &s2 )
{ return s1.wd != s2.wd || s1.ht != s2.ht; }

inline TSize operator+( const TSize & s1, const TSize & s2 )
{ return TSize(s1.wd+s2.wd, s1.ht+s2.ht); }

inline TSize operator-( const TSize &s1, const TSize &s2 )
{ return TSize(s1.wd-s2.wd, s1.ht-s2.ht); }

inline TSize operator*( const TSize &s, int32 c )
{ return TSize(s.wd*c, s.ht*c); }

inline TSize operator*( int32 c, const TSize &s )
{  return TSize(s.wd*c, s.ht*c); }

inline TSize operator*( const TSize &s, float c )
{ return TSize((s.wd*c), (s.ht*c)); }

inline TSize operator*( float c, const TSize &s )
{ return TSize((s.wd*c), (s.ht*c)); }


inline TSize &TSize::operator/=( int32 c )
{ wd/=c; ht/=c; return *this; }

inline TSize &TSize::operator/=( float c )
{ wd=(wd/c); ht=(ht/c); return *this; }

inline TSize operator/( const TSize &s, int32 c )
{ return TSize(s.wd/c, s.ht/c); }

inline TSize operator/( const TSize &s, float c )
{ return TSize((s.wd/c), (s.ht/c)); }


#endif // _TSIZE_H_
