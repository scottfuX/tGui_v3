#ifndef _TSTRING_H_
#define _TSTRING_H_
//#include "tArray.h"
#include "tGlobal.h"
#include "tArray.h"
#include <string.h>

int32 stricmp(const char *str1, const char *str2);
int32 strnicmp(const char *str1, const char *str2, uint32 len);


class  tString : public tArray 	// string class
{
public:
	tString() {}				// make null string
	tString(uint32 size);  			// allocate size incl. \0
	tString(const char *str);  			// deep copy
	tString(const char *str, uint32 maxlen);  	// deep copy, max length

	operator const char *() const;
	
	bool	isNull()	const;
	bool	isEmpty()	const;
	uint32	length()	const;
	bool	resize(uint32 newlen);
	bool	truncate(uint32 pos);
	
	tString		copy()	const;

	uint32		find(char c, uint32 index = 0, bool cs = true) const;
	uint32		find(const char *str, uint32 index = 0, bool cs = true) const;
	uint32		contains(char c, bool cs = true) const;
	uint32		contains(const char *str, bool cs = true) const;

	tString		left(uint32 len)  const;
	tString		right(uint32 len) const;
	tString		mid(uint32 index, uint32 len) const;

	tString		lower() const;
	tString		upper() const;
	
	uint32		toUInt(bool *ok) const;
	char*		toCharPoint() const;

	tString		&insert(uint32 index, const char *);
	tString		&insert(uint32 index, char);
	tString		&append(const char *);
	tString		&prepend(const char *);
	tString		&remove(uint32 index, uint32 len);
	tString		&replace(uint32 index, uint32 len, const char *);

	tString		&setStr(const char *s);
	tString		&setNum(uint32);
	
	tString    &operator=(const tString &s);    	// shallow copy
	tString    &operator=(const char *str);    	// deep copy
	

	tString		&operator+=(const char *str);
	tString		&operator+=(char c);

};
inline char* tString::toCharPoint() const
{	return data(); }
inline tString &tString::operator=(const tString &s)
{ return (tString&)assign(s); }

inline tString &tString::operator=(const char *str)
{ return (tString&)duplicate(str, strlen(str) + 1); }

inline bool tString::isNull() const
{ return data() == 0; }

inline bool tString::isEmpty() const
{ return data() == 0 || *data() == '\0'; }

inline uint32 tString::length() const
{return strlen(data());}

inline bool tString::truncate(uint32 pos)
{ return resize(pos + 1); }

inline tString tString::copy() const
{ return tString(data()); }

inline tString &tString::prepend(const char *s)
{ return insert(0, s); }

inline tString &tString::append(const char *s)
{ return operator+=(s); }


///*****************************************************************************
//  tString non-member operators
// *****************************************************************************/
//
//-----------------------这个是放在类里面的-----------------------
//	bool operator==(const tString &s1, const tString &s2);
//	bool operator==(const tString &s1, const char *s2);
//	bool operator==(const char *s1, const tString &s2);
//	bool operator!=(const tString &s1, const tString &s2);
//	bool operator!=(const tString &s1, const char *s2);
//	bool operator!=(const char *s1, const tString &s2);
//	bool operator<(const tString &s1, const char *s2);
//	bool operator<(const char *s1, const tString &s2);
//	bool operator<=(const tString &s1, const char *s2);
//	bool operator<=(const char *s1, const tString &s2);
//	bool operator>(const tString &s1, const char *s2);
//	bool operator>(const char *s1, const tString &s2);
//	bool operator>=(const tString &s1, const char *s2);
//	bool operator>=(const char *s1, const tString &s2);
//	tString  &operator+(const tString &s1, const tString &s2);
//	tString &operator+(const tString &s1, const char *s2);
//	tString &operator+(const char *s1, const tString &s2);
//	tString &operator+(const tString &s1, char c2);
//	tString &operator+(char c1, const tString &s2);
//-----------------------end-----------------------

//inline bool tString::operator==(const tString &s1, const tString &s2)
//{ return strcmp(s1.data(), s2.data()) == 0; }
//
//inline bool tString::operator==(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) == 0; }
//
//inline bool tString::operator==(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) == 0; }
//
//inline bool tString::operator!=(const tString &s1, const tString &s2)
//{ return strcmp(s1.data(), s2.data()) != 0; }
//
//inline bool tString::operator!=(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) != 0; }
//
//inline bool tString::operator!=(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) != 0; }
//
//inline bool tString::operator<(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) < 0; }
//
//inline bool tString::operator<(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) < 0; }
//
//inline bool tString::operator<=(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) <= 0; }
//
//inline bool tString::operator<=(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) <= 0; }
//
//inline bool tString::operator>(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) > 0; }
//
//inline bool tString::operator>(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) > 0; }
//
//inline bool tString::operator>=(const tString &s1, const char *s2)
//{ return strcmp(s1.data(), s2) >= 0; }
//
//inline bool tString::operator>=(const char *s1, const tString &s2)
//{ return strcmp(s1, s2.data()) >= 0; }
//
//inline tString  &tString::operator+(const tString &s1, const tString &s2)
//{
//	tString tmp(s1.data());
//	tmp += s2;
//	return tmp;
//}
//
//inline tString &tString::operator+(const tString &s1, const char *s2)
//{
//	tString tmp(s1.data());
//	tmp += s2;
//	return tmp;
//}
//
//inline tString &tString::operator+(const char *s1, const tString &s2)
//{
//	tString tmp(s1);
//	tmp += s2;
//	return tmp;
//}
//
//inline tString &tString::operator+(const tString &s1, char c2)
//{
//	tString tmp(s1.data());
//	tmp += c2;
//	return tmp;
//}
//
//inline tString &tString::operator+(char c1, const tString &s2)
//{
//	tString tmp(c1);
//	tmp += s2;
//	return tmp;
//}

#endif // _TSTRING_H_



