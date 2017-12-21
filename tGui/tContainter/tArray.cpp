#include "tArray.h"
#include "tString.h"
#include <stdlib.h>

//use new
//#define USE_MALLOC				// comment to use new/delete
#undef NEW
#undef delete

#if defined(USE_MALLOC)
#define NEW(type,size)	((type*)malloc(size*sizeof(type)))
#define delete(array)	(free((char*)array))
#else
#define NEW(type,size)	(new type[size])
#define DELETE(array)	(delete[] array)
#define DONT_USE_REALLOC			// comment to use realloc()
#endif


/*!
  \class QShared qshared.h
  \brief The QShared struct is internally used for implementing shared classes.

  It only contains a reference count and member functions to increment and
  decrement it.

  Shared classes normally have internal classes that inherit QShared and
  add the shared data.

  \sa \link shclass.html Shared Classes\endlink
*/


/*!
  \class tArray tArray.h
  \brief The tArray class is an internal class for implementing the QArray class.

  tArray is a strictly internal class that acts as base class for the
  QArray template array.

  It contains an array of bytes and has no notion of an array element.
*/


/*!
  \internal
  Constructs a null array.
*/

tArray::tArray()
{
	shd = newData();
}

/*!
  \internal
  Dummy constructor; does not allocate any data.

  This constructor does not initialize any array data so subclasses
  must do it. The intention is to make the code more efficient.
*/

tArray::tArray(int32, int32)
{
}

/*!
  \internal
  Constructs an array with room for \e size bytes.
*/

tArray::tArray(int32 size)
{
	if (size < 0) 
	{
		size = 0;
	}
	shd = newData();
	if (size == 0)					//zero length
		return;
	shd->data = NEW(char, size);
	shd->len = size;
}

/*!
  \internal
  Constructs a shallow copy of \e a.
*/

tArray::tArray(const tArray &a)
{
	shd = a.shd;
	shd->ref();
}

/*!
  \internal
  Dereferences the array data and deletes it if this was the last
  reference.
*/

tArray::~tArray()
{
	if (shd && shd->deref()) {
				// delete when last reference
	if(shd->data)			// is lost
	    DELETE(shd->data);
		deleteData(shd);
	}
}


/*!
  \fn tArray &tArray::operator=( const tArray &a )
  \internal
  Assigns a shallow copy of \e a to this array and returns a reference to
  this array.  Equivalent to assign().
*/

/*!
  \fn void tArray::detach()
  \internal
  Detaches this array from shared array data.
*/

/*!
  \fn char *tArray::data() const
  \internal
  Returns a pointer to the actual array data.
*/

/*!
  \fn uint32 tArray::nrefs() const
  \internal
  Returns the reference count.
*/

/*!
  \fn uint32 tArray::size() const
  \internal
  Returns the size of the array, in bytes.
*/


/*!
  \internal
  Returns true if this array is equal to \e a, otherwise false.
  The comparison is bitwise, of course.
*/

bool tArray::isEqual(const tArray &a) const
{
	if (size() != a.size())			// different size
	return false;
	if (data() == a.data())			// has same data
	return true;
	return (size() ? memcmp(data(), a.data(), size()) : 0) == 0;
}


/*!
  \internal
  Resizes the array to \e newsize bytes.
*/

bool tArray::resize(uint32 newsize)
{
	if (newsize == shd->len)			// nothing to do
	return true;
	if (newsize == 0) {
					// remove array
	duplicate(0, 0);
		return true;
	}
	if (shd->data) {
						// existing data

		shd->data = (char *)realloc(shd->data, newsize);
	}
	else {
		shd->data = NEW(char, newsize);
	}
	if (!shd->data)				// no memory
	return false;
	shd->len = newsize;
	return true;
}

/*!
  \internal
  Shallow copy. Dereference the current array and references the data
  contained in \e a instead. Returns a reference to this array.
  \sa operator=()
*/

tArray &tArray::assign(const tArray &a)
{
	a.shd->ref(); 				// avoid 'a = a'
	if(shd->deref()) {
					// delete when last reference
		if(shd->data)			// is lost
			DELETE(shd->data);
		deleteData(shd);
	}
	shd = a.shd;
	return *this;
}

/*!
  \internal
  Shallow copy. Dereference the current array and references the
  array data \e d, which contains \e len bytes.
  Returns a reference to this array.

  Do not delete \e d later, because tArray takes care of that.
*/

tArray &tArray::assign(const char *d, uint32 len)
{
	if (shd->count > 1) {
					// disconnect this
	shd->count--;
		shd = newData();
	}
	else {
		if (shd->data)
			DELETE(shd->data);
	}
	shd->data = (char *)d;
	shd->len = len;
	return *this;
}

/*!
  \internal
  Deep copy. Dereference the current array and obtains a copy of the data
  contained in \e a instead. Returns a reference to this array.
  \sa assign(), operator=()
*/

tArray &tArray::duplicate(const tArray &a)
{
	if (a.shd == shd) {
					// a.duplicate(a) !
	if(shd->count > 1) {
			shd->count--;
			register array_data *n = newData();
			if ((n->len = shd->len)) {
				n->data = NEW(char, n->len);
				if (n->data)
					memcpy(n->data, shd->data, n->len);
			}
			else {
				n->data = 0;
			}
			shd = n;
		}
		return *this;
	}
	char *oldptr = 0;
	if (shd->count > 1) {
					// disconnect this
	shd->count--;
		shd = newData();
	}
	else {
							// delete after copy was made
	oldptr = shd->data;
	}
	if (a.shd->len) {
						// duplicate data
	shd->data = NEW(char, a.shd->len);
		if (shd->data)
			memcpy(shd->data, a.shd->data, a.shd->len);
	}
	else {
		shd->data = 0;
	}
	shd->len = a.shd->len;
	if (oldptr)
		DELETE(oldptr);
	return *this;
}

/*!
  \internal
  Deep copy. Dereferences the current array and obtains a copy of the
  array data \e d instead.  Returns a reference to this array.
  \sa assign(), operator=()
*/

tArray &tArray::duplicate(const char *d, uint32 len)
{
	char *data;
	if (d == 0 || len == 0) {
		data = 0;
		len  = 0;
	}
	else {
		if (shd->count == 1 && shd->len == len) {
			memcpy(shd->data, d, len); 	// use same buffer
			return *this;
		}
		data = NEW(char, len);
		memcpy(data, d, len);
	}
	if (shd->count > 1) {
					// detach
	shd->count--;
		shd = newData();
	}
	else {
							// just a single reference
	if(shd->data)
	    DELETE(shd->data);
	}
	shd->data = data;
	shd->len  = len;
	return *this;
}

/*!
  \internal
  Resizes this array to \e len bytes and copies the \e len bytes at
  address \e into it.

  \warning This function disregards the reference count mechanism.  If
  other QGArrays reference the same data as this, all will be updated.
*/

void tArray::store(const char *d, uint32 len)
{
	// store, but not deref
    resize(len);
	memcpy(shd->data, d, len);
}


/*!
  \fn array_data *tArray::sharedBlock() const
  \internal
  Returns a pointer to the shared array block.
*/

/*!
  \fn void tArray::setSharedBlock( array_data *p )
  \internal
  Sets the shared array block to \e p.
*/


/*!
  \internal
  Sets raw data and returns a reference to the array.

  Dereferences the current array and sets the new array data to \e d and
  the new array size to \e len.	 Do not attempt to resize or re-assign the
  array data when raw data has been set.
  Call resetRawData(d,len) to reset the array.

  Setting raw data is useful because it set QArray data without allocating
  memory or copying data.

  Example of intended use:
  \code
    static uchar bindata[] = { 231, 1, 44, ... };
    QByteArray	a;
    a.setRawData( bindata, sizeof(bindata) );	// a points to bindata
    QDataStream s( a, IO_ReadOnly );		// open on a's data
    s >> <something>;				// read raw bindata
    s.close();
    a.resetRawData( bindata, sizeof(bindata) ); // finished
  \endcode

  Example of misuse (do not do this):
  \code
    static uchar bindata[] = { 231, 1, 44, ... };
    QByteArray	a, b;
    a.setRawData( bindata, sizeof(bindata) );	// a points to bindata
    a.resize( 8 );				// will crash
    b = a;					// will crash
    a[2] = 123;					// might crash
      // forget to resetRawData - will crash
  \endcode

  \warning If you do not call resetRawData(), tArray will attempt to
  deallocate or reallocate the raw data, which might not be too good.
  Be careful.
*/

tArray &tArray::setRawData(const char *d, uint32 len)
{
	duplicate(0, 0); 				// set null data
	shd->data = (char *)d;
	shd->len  = len;
	return *this;
}

/*!
  \internal
  Resets raw data.

  The arguments must be the data and length that were passed to
  setRawData().	 This is for consistency checking.
*/

void tArray::resetRawData(const char *d, uint32 len)
{
	if (d != shd->data || len != shd->len) {
		return;
	}
	shd->data = 0;
	shd->len  = 0;
}


/*!
  \internal
  Finds the first occurrence of \e d in the array from position \e index,
  where \e sz is the size of the \e d element.

  Note that \e index is given in units of \e sz, not bytes.

  This function only compares whole cells, not bytes.
*/

int32 tArray::find(const char *d, uint32 index, uint32 sz) const
{
	index *= sz;
	if (index >= shd->len) {
		return -1;
	}
	register uint32 i;
	uint32 ii;
	switch (sz) {
	case 1: {
							// 8 bit elements
	    register char *x = data();
			char v = *d;
			for (i = index; i < shd->len; i++) {
				if (*x++ == v)
					break;
			}
			ii = i;
		}
		break;
	case 2: {
							// 16 bit elements
	    register int32 *x = (int32*)(data() + index);
			int32 v = *((int32*)d);
			for (i = index; i < shd->len; i += 2) {
				if (*x++ == v)
					break;
			}
			ii = i / 2;
		}
		break;
	case 4: {
							// 32 bit elements
	    register int32 *x = (int32*)(data() + index);
			int32 v = *((int32*)d);
			for (i = index; i < shd->len; i += 4) {
				if (*x++ == v)
					break;
			}
			ii = i / 4;
		}
		break;
	default: {
							// any size elements
	    for(i = index ; i < shd->len ; i += sz) {
				if (memcmp(d, &shd->data[i], sz) == 0)
					break;
			}
			ii = i / sz;
		}
		break;
	}
	return i < shd->len ? (int32)ii : -1;
}

/*!
  \internal
  Returns the number of occurrences of \e d in the array, where \e sz is
  the size of the \e d element.

  This function only compares whole cells, not bytes.
*/

int32 tArray::contains(const char *d, uint32 sz) const
{
	register uint32 i = shd->len;
	int32 count = 0;
	switch (sz) {
	case 1: {
							// 8 bit elements
	    register char *x = data();
			char v = *d;
			while (i--) {
				if (*x++ == v)
					count++;
			}
		}
		break;
	case 2: {
							// 16 bit elements
	    register int32 *x = (int32*)data();
			int32 v = *((int32*)d);
			i /= 2;
			while (i--) {
				if (*x++ == v)
					count++;
			}
		}
		break;
	case 4: {
							// 32 bit elements
	    register int32 *x = (int32*)data();
			int32 v = *((int32*)d);
			i /= 4;
			while (i--) {
				if (*x++ == v)
					count++;
			}
		}
		break;
	default: {
							// any size elements
	    for(i = 0 ; i < shd->len ; i += sz) {
				if (memcmp(d, &shd->data[i], sz) == 0)
					count++;
			}
		}
		break;
	}
	return count;
}

/*!
  \fn char *tArray::at( uint32 index ) const
  \internal
  Returns a pointer to the byte at offset \e index in the array.
*/

/*!
  \internal
  Expand the array if necessary, and copies (the first part of) its
  contents from the \e index*zx bytes at \e d.

  Returns true if the operation succeeds, false if it runs out of
  memory.

  \warning This function disregards the reference count mechanism.  If
  other QGArrays reference the same data as this, all will be changed.
*/

bool tArray::setExpand(uint32 index, const char *d, uint32 sz)
{
	index *= sz;
	if (index >= shd->len) {
		if (!resize(index + sz))		// no memory
		    return false;
	}
	memcpy(data() + index, d, sz);
	return true;
}



