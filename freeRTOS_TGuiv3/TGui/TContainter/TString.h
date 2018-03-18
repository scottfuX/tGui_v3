#ifndef _TSTRING_H_
#define _TSTRING_H_
//#include "TArray.h"
#include "TGlobal.h"
#include "TArray.h"
#include <string.h>

int32 stricmp(const char *str1, const char *str2);
int32 strnicmp(const char *str1, const char *str2, uint32 len);


class  TString : public TArray 	// string class
{
public:
	TString() {}				// make null string
	TString(uint32 size);  			// allocate size incl. \0
	TString(const char *str);  			// deep copy
	TString(const char *str, uint32 maxlen);  	// deep copy, max length

	operator const char *() const;
	
	bool	isNull()	const;
	bool	isEmpty()	const;
	uint32	length()	const;
	bool	resize(uint32 newlen);
	bool	truncate(uint32 pos);
	
	TString		copy()	const;

	uint32		find(char c, uint32 index = 0, bool cs = true) const;
	uint32		find(const char *str, uint32 index = 0, bool cs = true) const;
	uint32		contains(char c, bool cs = true) const;
	uint32		contains(const char *str, bool cs = true) const;

	TString		left(uint32 len)  const;
	TString		right(uint32 len) const;
	TString		mid(uint32 index, uint32 len) const;

	TString		lower() const;
	TString		upper() const;
	
	uint32		toUInt(bool *ok) const;
	char*		toCharPoint() const;

	TString		&insert(uint32 index, const char *,uint32 len = 0);
	TString		&insert(uint32 index, char);
	TString		&append(const char *);
	TString		&prepend(const char *);
	TString		&remove(uint32 index, uint32 len);
	TString		&replace(uint32 index, uint32 len, const char *);

	TString		&setStr(const char *s);
	TString		&setNum(uint32);
	
	TString    &operator=(const TString &s);    	// shallow copy
	TString    &operator=(const char *str);    	// deep copy
	

	TString		&operator+=(const char *str);
	TString		&operator+=(char c);

};
inline char* TString::toCharPoint() const
{	return data(); }
inline TString &TString::operator=(const TString &s)
{ return (TString&)assign(s); }

inline TString &TString::operator=(const char *str)
{ return (TString&)duplicate(str, strlen(str) + 1); }

inline bool TString::isNull() const
{ return data() == 0; }

inline bool TString::isEmpty() const
{ return data() == 0 || *data() == '\0'; }

inline uint32 TString::length() const
{return strlen(data());}

inline bool TString::truncate(uint32 pos)
{ return resize(pos + 1); }

inline TString TString::copy() const
{ return TString(data()); }

inline TString &TString::prepend(const char *s)
{ return insert(0, s); }

inline TString &TString::append(const char *s)
{ return operator+=(s); }


///*****************************************************************************
//  TString non-member operators
// *****************************************************************************/
//
//-----------------------这个是放在类里面的-----------------------
//	bool operator==(const TString &s1, const TString &s2);
//	bool operator==(const TString &s1, const char *s2);
//	bool operator==(const char *s1, const TString &s2);
//	bool operator!=(const TString &s1, const TString &s2);
//	bool operator!=(const TString &s1, const char *s2);
//	bool operator!=(const char *s1, const TString &s2);
//	bool operator<(const TString &s1, const char *s2);
//	bool operator<(const char *s1, const TString &s2);
//	bool operator<=(const TString &s1, const char *s2);
//	bool operator<=(const char *s1, const TString &s2);
//	bool operator>(const TString &s1, const char *s2);
//	bool operator>(const char *s1, const TString &s2);
//	bool operator>=(const TString &s1, const char *s2);
//	bool operator>=(const char *s1, const TString &s2);
//	TString  &operator+(const TString &s1, const TString &s2);
//	TString &operator+(const TString &s1, const char *s2);
//	TString &operator+(const char *s1, const TString &s2);
//	TString &operator+(const TString &s1, char c2);
//	TString &operator+(char c1, const TString &s2);
//-----------------------end-----------------------

//inline bool TString::operator==(const TString &s1, const TString &s2)
//{ return strcmp(s1.data(), s2.data()) == 0; }
//
//inline bool TString::operator==(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) == 0; }
//
//inline bool TString::operator==(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) == 0; }
//
//inline bool TString::operator!=(const TString &s1, const TString &s2)
//{ return strcmp(s1.data(), s2.data()) != 0; }
//
//inline bool TString::operator!=(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) != 0; }
//
//inline bool TString::operator!=(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) != 0; }
//
//inline bool TString::operator<(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) < 0; }
//
//inline bool TString::operator<(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) < 0; }
//
//inline bool TString::operator<=(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) <= 0; }
//
//inline bool TString::operator<=(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) <= 0; }
//
//inline bool TString::operator>(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) > 0; }
//
//inline bool TString::operator>(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) > 0; }
//
//inline bool TString::operator>=(const TString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) >= 0; }
//
//inline bool TString::operator>=(const char *s1, const TString &s2)
//{ return strcmp(s1, s2.data()) >= 0; }
//
//inline TString  &TString::operator+(const TString &s1, const TString &s2)
//{
//	TString tmp(s1.data());
//	tmp += s2;
//	return tmp;
//}
//
//inline TString &TString::operator+(const TString &s1, const char *s2)
//{
//	TString tmp(s1.data());
//	tmp += s2;
//	return tmp;
//}
//
//inline TString &TString::operator+(const char *s1, const TString &s2)
//{
//	TString tmp(s1);
//	tmp += s2;
//	return tmp;
//}
//
//inline TString &TString::operator+(const TString &s1, char c2)
//{
//	TString tmp(s1.data());
//	tmp += c2;
//	return tmp;
//}
//
//inline TString &TString::operator+(char c1, const TString &s2)
//{
//	TString tmp(c1);
//	tmp += s2;
//	return tmp;
//}

#endif // _TSTRING_H_



