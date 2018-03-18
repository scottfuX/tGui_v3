#include "TString.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

int32 stricmp(const char *str1, const char *str2)
{
	register const char *s1 = (const char *)str1;
	register const char *s2 = (const char *)str2;
	int res;
	char c;
	if (!s1 || !s2)
		return (int)((long)s2 - (long)s1);
	for (; (*s1) != '\0'; s1++, s2++) {
		if ((res = (c = tolower(*s1)) - tolower(*s2))!=0)
			return res;
		if (!c && (*s2) == '\0')				// strings are equal
			break;
	}
	return 0;
}
int32 strnicmp(const char *str1, const char *str2, uint32 len)
{
	register const char *s1 = (const char *)str1;
	register const char *s2 = (const char *)str2;
	int res;
	char c;
	if (!s1 || !s2)
		return (int)((long)s2 - (long)s1);
	for (; len--; s1++, s2++) {
		if ((res = (c = tolower(*s1)) - tolower(*s2))!=0)
			return res;
		if (!c)				// strings are equal
		    break;
	}
	return 0;
}



/*****************************************************************************
  TString member functions
 *****************************************************************************/

/*!
  \class TString TString.h

  \brief The TString class provides an abstraction of the classic C
  zero-terminated char array (<var>char*</var>).

  \ingroup tools
  \ingroup shared

  TString inherits TArray, which is defined as QArray\<char\>.

  Since TString is a QArray, it uses explicit
  \link shclass.html sharing\endlink with a reference count.

  Note that for the TString methods that take a <var>const char *</var>
  parameter the results are undefined if the TString is not
  zero-terminated.  It is legal for the <var>const char *</var> parameter
  to be 0.

  A TString that has not been assigned to anything is \e null, i.e. both
  the length and data pointer is 0. A TString that references the empty
  string ("", a single '\0' char) is \e empty.	Both null and empty
  QStrings are legal parameters to the methods. Assigning <var>const char
  * 0</var> to TString gives a null TString.

  \sa \link shclass.html Shared classes\endlink
*/



/*!
  Constructs a string with room for \e size characters, including the
  '\0'-terminator.  Makes a null string if \e size == 0.

  If \e size \> 0, then the first and last characters in the string are
  initialized to '\0'.	All other characters are uninitialized.

  \sa resize(), isNull()
*/

TString::TString(uint32 size): TArray(size)
{
	if (size > 0) {
		*data() = '\0'; 				// set terminator
		*(data() + (size - 1)) = '\0';
	}
}

/*!
  Constructs a string that is a deep copy of \e str.

  If \a str is 0 a null string is created.

  \sa isNull()
*/

TString::TString(const char *str)
	
{
	duplicate(str, strlen(str) + 1);
}


/*!
  Constructs a string that is a deep copy of \e str, that is no more
  than \a maxlen bytes long including the '\0'-terminator.

  Example:
  \code
    TString str("helloworld",6); // Assigns "hello" to str.
  \endcode

  If \a str contains a 0 byte within the first \a maxlen bytes, the
  resulting TString will be terminated by the 0.  If \a str is 0 a
  null string is created.

  \sa isNull()
*/

TString::TString(const char *str, uint32 maxlen)
{
	uint32 len;  // index of last nul character
	// cannot use memchr - we need the *index*, not void*
	for(len = 0 ; len < maxlen - 1 ; len++) {
		if (!str[len]) break;
	}
	duplicate(str, len + 1);
	data()[len] = 0;
}
/*!
  \fn QString::operator const char *() const
  Returns the string data.
*/
TString::operator const char *() const
{
	return (const char *)data();
}


/*!
  \fn TString &TString::operator=( const TString &s )
  Assigns a shallow copy of \e s to this string and returns a reference to
  this string.
*/

/*!
  Extends or shrinks the string to \e len bytes, including the
  '\0'-terminator.

  A \0-terminator is set at position <code>len - 1</code> unless
  <code>len == 0</code>.

  Example:
  \code
    TString s = "resize this string";
    s.resize( 7 );				// s == "resize"
  \endcode

  \sa truncate()
*/

bool TString::resize(uint32 len)
{
	if(!TArray::resize(len))
	return false;
	if (len)
		*(data() + len - 1) = '\0';
	return true;
}




/*!
  Finds the first occurrence of the character \e c, starting at
  position \e index.

  The search is case sensitive if \e cs is true, or case insensitive if \e
  cs is false.

  Returns the position of \e c, or -1 if \e c could not be found.
*/

uint32 TString::find(char c, uint32 index, bool cs) const
{
	if ((uint32)index >= size())		// index outside string
	return -1;
	register const char *d;
	if (cs) {
							// case sensitive
	d = strchr(data() + index, c);
	}
	else {
		d = data() + index;
		c = tolower(c);
		while (*d && tolower(*d) != c)
			d++;
		if (!*d && c)				// not found
		    d = 0;
	}
	return d ? (uint32)(d - data()) : -1;
}

/*!
  Finds the first occurrence of the string \e str, starting at position
  \e index.

  The search is case sensitive if \e cs is true, or case insensitive if \e
  cs is false.

  Returns the position of \e str, or -1 if \e str could not be found.
*/

uint32 TString::find(const char *str, uint32 index, bool cs) const
{
	if ((uint32)index >= size())		// index outside string
	return - 1;
	register const char *d;
	if (cs) {
							// case sensitive
	d = strstr(data() + index, str);
	}
	else {
							// case insensitive
	d = data() + index;
		uint32 len = strlen(str);
		while (*d) {
			if (strnicmp(d, str, len) == 0)
				break;
			d++;
		}
		if (!*d)				// not found
		    d = 0;
	}
	return d ? (uint32)(d - data()) : -1;
}



/*!
  Returns the number of times the character \e c occurs in the string.

  The match is case sensitive if \e cs is true, or case insensitive if \e cs
  if false.
*/

uint32 TString::contains(char c, bool cs) const
{
	uint32 count = 0;
	char *d = data();
	if (!d)
		return 0;
	if (cs) {
							// case sensitive
	while(*d)
	    if(*d++ == c)
		count++;
	}
	else {
							// case insensitive
	c = tolower(c);
		while (*d) {
			if (tolower(*d) == c)
				count++;
			d++;
		}
	}
	return count;
}

/*!
  Returns the number of times \e str occurs in the string.

  The match is case sensitive if \e cs is true, or case insensitive if \e
  cs if false.

  This function counts overlapping substrings, for example, "banana"
  contains two occurrences of "ana".

  \sa findRev()
*/

uint32 TString::contains(const char *str, bool cs) const
{
	uint32 count = 0;
	char *d = data();
	if (!d)
		return 0;
	uint32 len = strlen(str);
	while (*d) {
						// counts overlapping strings
	if(cs) {
			if (strncmp(d, str, len) == 0)
				count++;
		} else {
			if (strnicmp(d, str, len) == 0)
				count++;
		}
		d++;
	}
	return count;
}

/*!
  Returns a substring that contains the \e len leftmost characters
  of the string.

  The whole string is returned if \e len exceeds the length of the string.

  Example:
  \code
    TString s = "Pineapple";
    TString t = s.left( 4 );			// t == "Pine"
  \endcode

  \sa right(), mid()
*/

TString TString::left(uint32 len) const
{
	if (isEmpty()) {
		TString empty;
		return empty;
	}
	else if (len >= size()) {
		TString same(data());
		return same;
	}
	else {
		TString s(len + 1);
		strncpy(s.data(), data(), len);
		*(s.data() + len) = '\0';
		return s;
	}
}

/*!
  Returns a substring that contains the \e len rightmost characters
  of the string.

  The whole string is returned if \e len exceeds the length of the string.

  Example:
  \code
    TString s = "Pineapple";
    TString t = s.right( 5 );			// t == "apple"
  \endcode

  \sa left(), mid()
*/

TString TString::right(uint32 len) const
{
	if (isEmpty()) {
		TString empty;
		return empty;
	}
	else {
		uint32 l = length();
		if (len > l)
			len = l;
		char *p = data() + (l - len);
		return TString(p);
	}
}

/*!
  Returns a substring that contains the \e len characters of this
  string, starting at position \e index.

  Returns a null string if the string is empty or \e index is out
  of range.  Returns the whole string from \e index if \e index+len exceeds
  the length of the string.

  Example:
  \code
    TString s = "Two pineapples";
    TString t = s.mid( 4, 4 );			// t == "pine"
  \endcode

  \sa left(), right()
*/

TString TString::mid(uint32 index, uint32 len) const
{
	uint32 slen = strlen(data());
	if (isEmpty() || index >= slen) {
		TString empty;
		return empty;
	}
	else {
		register char *p = data() + index;
		TString s(len + 1);
		strncpy(s.data(), p, len);
		*(s.data() + len) = '\0';
		return s;
	}
}



/*!
  Returns a new string that is the string converted to lower case.

  Presently it only handles 7-bit ASCII, or whatever tolower()
  handles (if $LC_CTYPE is set, most UNIX systems do the Right Thing).

  Example:
  \code
    TString s("TeX");
    TString t = s.lower();			// t == "tex"
  \endcode

  \sa upper()
*/

TString TString::lower() const
{
	TString s(data());
	register char *p = s.data();
	if (p) {
		while (*p) {
			*p = tolower(*p);
			p++;
		}
	}
	return s;
}

/*!
  Returns a new string that is the string converted to upper case.

  Presently it only handles 7-bit ASCII, or whatever toupper()
  handles (if $LC_CTYPE is set, most UNIX systems do the Right Thing).

  Example:
  \code
    TString s("TeX");
    TString t = s.upper();			// t == "TEX"
  \endcode

  \sa lower()
*/

TString TString::upper() const
{
	TString s(data());
	register char *p = s.data();
	if (p) {
		while (*p) {
			*p = toupper(*p);
			p++;
		}
	}
	return s;
}



/*!
  Insert \e s into the string before position \e index.

  If \e index is beyond the end of the string, the string is extended with
  spaces (ASCII 32) to length \e index and \e s is then appended.

  \code
    TString s = "I like fish";
    s.insert( 2, "don't ");			// s == "I don't like fish"
    s = "x";
    s.insert( 3, "yz" );			// s == "x  yz"
  \endcode
*/

TString &TString::insert(uint32 index, const char *s,uint32 len)
{
	if(!len)
	 len = strlen(s);
	if (len == 0)
		return *this;
	uint32 olen = length();
	uint32 nlen = olen + len;
	if (index >= olen) {
					// insert after end of string

	if(TArray::resize(nlen + index - olen + 1)) {
			memset(data() + olen, ' ', index - olen);
			memcpy(data() + index, s, len + 1);
		}
	}
	else if (TArray::resize(nlen + 1)) {
			// normal insert
	memmove(data() + index + len, data() + index, olen - index + 1);
		memcpy(data() + index, s, len);
	}
	return *this;
}

/*!
  Insert \e c into the string at (before) position \e index and returns
  a reference to the string.

  If \e index is beyond the end of the string, the string is extended with
  spaces (ASCII 32) to length \e index and \e c is then appended.

  Example:
  \code
    TString s = "Yes";
    s.insert( 3, '!');				// s == "Yes!"
  \endcode

  \sa remove(), replace()
*/

TString &TString::insert(uint32 index, char c)	// insert char
{
	char buf[2];
	buf[0] = c;
	buf[1] = '\0';
	return insert(index, buf);
}


/*!
  Removes \e len characters starting at position \e index from the
  string and returns a reference to the string.

  If \e index is too big, nothing happens.  If \e index is valid, but
  \e len is too large, the rest of the string is removed.

  \code
    TString s = "Montreal";
    s.remove( 1, 4 );
    // s == "Meal"
  \endcode

  \sa insert(), replace()
*/

TString &TString::remove(uint32 index, uint32 len)
{
	uint32 olen = length();
	if (index + len >= olen) {
				// range problems
	if(index < olen) {
						// index ok
	    resize(index + 1);
		}
	}
	else if (len != 0) {
		memmove(data() + index, data() + index + len, olen - index - len + 1);
		TArray::resize(olen - len + 1);
	}
	return *this;
}

/*!
  Replaces \e len characters starting at position \e index from the
  string with \e s, and returns a reference to the string.

  If \e index is too big, nothing is deleted and \e s is inserted at the
  end of the string.  If \e index is valid, but \e len is too large, \e
  str replaces the rest of the string.

  \code
    TString s = "Say yes!";
    s.replace( 4, 3, "NO" );			// s == "Say NO!"
  \endcode

  \sa insert(), remove()
*/

TString &TString::replace(uint32 index, uint32 len, const char *s)
{
	remove(index, len);
	insert(index, s);
	return *this;
}


/*!
  Returns the string converted to an <code>unsigned long</code>
  value.

  If \e ok is non-null, \e *ok is set to true if there are no
  conceivable errors, and false if the string is not a number at all,
  or if it has trailing garbage.
*/


uint32 TString::toUInt(bool *ok) const
{
	char *p = data();
	uint32 val = 0;
	const uint32 max_mult = 65535;
	bool is_ok = false;
	if (!p)
		goto bye;
	while (isspace(*p))			// skip leading space
	p++;
	if (*p == '+')
		p++;
	if (!isdigit(*p))
		goto bye;
	while (isdigit(*p)) {
		if (val > max_mult || (val == max_mult && (*p - '0') > 5))
			goto bye;
		val = 10*val + (*p++ -'0');
	}
	while (isspace(*p))			// skip trailing space
	p++;
	if (*p == '\0')
		is_ok = true;
bye:
	if (ok)
		*ok = is_ok;
	return is_ok ? val : 0;
}


/*!
  Makes a deep copy of \e str.
  Returns a reference to the string.
*/

TString &TString::setStr(const char *str)
{

	if(str)					// valid string
	store(str, strlen(str) + 1);
	else					// empty
	resize(0);
	return *this;
}


/*!
  Sets the string to the printed unsigned value of \e n and
  returns a reference to the string.
*/

TString &TString::setNum(uint32 n)
{
	char buf[20];
	register char *p = &buf[19];
	*p = '\0';
	do {
		* --p = ((uint32)(n % 10)) + '0';
		n /= 10;
	} while (n);
	store(p, strlen(p) + 1);
	return *this;
}




/*!
  Appends \e str to the string and returns a reference to the string.
*/

TString& TString::operator+=(const char *str)
{
	if (!str)
		return *this;				// nothing to append
		uint32 len1 = length();
	uint32 len2 = strlen(str);
	if (!TArray::resize(len1 + len2 + 1))
		return *this;				// no memory
		memcpy(data() + len1, str, len2 + 1);
	return *this;
}

/*!
  Appends \e c to the string and returns a reference to the string.
*/

TString &TString::operator+=(char c)
{
	uint32 len = length();
	if (!TArray::resize(len + 2))
		return *this;				// no memory
		*(data() + len) = c;
	*(data() + len + 1) = '\0';
	return *this;
}





