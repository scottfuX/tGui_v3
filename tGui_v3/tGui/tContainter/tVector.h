#ifndef _TVECTOR_H_
#define _TVECTOR_H_

#include "tCollection.h"
#include "tString.h"
#include "tGlobal.h"
#include "tList.h"
#include <stdlib.h>


//#define USE_MALLOC				// comment to use new/deleteItem

#undef NEW
#undef DELETE

#if defined(USE_MALLOC)
#define NEW(type,size)	((type*)malloc(size*sizeof(type)))
#define DELETE(array)	(free((char*)array))
#else
#define NEW(type,size)	(new type[size])
#define DELETE(array)	(delete[] array)
#define DONT_USE_REALLOC			// comment to use realloc()
#endif
template <class T>
	class tList;
template <class T>
class  tVector : public tCollection<T>// generic vector
{
		friend class tList<T>;  				// needed by tList::toVector
protected :
	tVector();  					// create empty vector
	tVector(uint32 size);  			// create vector with nullptrs
	tVector(const tVector &v);  		// make copy of other vector
   ~tVector();
	
	
	tVector &operator=(const tVector &v); 	// assign from other vector //deep copy
	
	T	 *data()    const	{ return vec; }
	uint32  size()    const	{ return len; }
	uint32  count()   const	{ return numItems; }

	int32 compareItems(T d1, T d2);		
	bool  insert(uint32 index, T); 		// insert item at index
	bool  remove(uint32 index); 			// remove item
	T	  take(uint32 index); 			// take out item

	void  clear(); 				// clear vector
	bool  resize(uint32 newsize); 		// resize vector

	bool  fill(T, int32 flen); 		// resize and fill vector

	int32	find(T, uint32 index) const; 	// find equal item in vector
	uint32  contains(T) const; 		// get number of equal matches

	T	  at(uint32 index) const{ return vec[index]; }			// fast
		
	bool insertExpand(uint32 index, T); 	// insert, expand if necessary
	void toList(tList<T> *) const;  		// put items in list
	
	virtual T	     newItem(T d) {tCollection<T>::newItem(d);};    		// create object
	virtual void     deleteItem(void* d) {tCollection<T>::deleteItem(d); };   		// delete object
private:
	T	 *vec;
	uint32  len;
	uint32  numItems;
};

	
/*****************************************************************************
  Default implementation of virtual functions
 *****************************************************************************/
template <class T>
int32 tVector<T>::compareItems(T d1, T d2)
{
	return d1 != d2;				// compare pointers
}



/*****************************************************************************
  tVector member functions
 *****************************************************************************/
template <class T>
tVector<T>::tVector()				// create empty vector
{
	vec = 0;
	len = numItems = 0;
}

template <class T>
tVector<T>::tVector(uint32 size)			// create vectors with nullptrs
{
	len = size;
	numItems = 0;
	if (len == 0) {
						// zero length
	vec = 0;
		return;
	}
	vec = NEW(T, len);
	
	memset((void*)vec, 0, len*sizeof(T)); 	// fill with nulls
}

template <class T>
tVector<T>::tVector(const tVector &a)		// make copy of other vector
    : tCollection<T>(a)
{
	len = a.len;
	numItems = a.numItems;
	vec = NEW(T, len);
	
	for (uint32 i = 0; i < len; i++) {
		vec[i] = a.vec[i] ? newItem(a.vec[i]) : 0;
		CHECK_PTR(vec[i]);
	}
}

template <class T>
tVector<T>::~tVector()
{
	clear();
}

template <class T>
tVector<T>& tVector<T>::operator=(const tVector &v)
{
							// assign from other vector
    clear(); 					// first delete old vector
    len = v.len;
	numItems = v.numItems;
	vec = NEW(T, len); 				// create new vector
	
	for (uint32 i = 0; i < len; i++) {
				// copy elements
	vec[i] = v.vec[i] ? newItem(v.vec[i]) : 0;
		CHECK_PTR(vec[i]);
	}
	return *this;
}

template <class T>
bool tVector<T>::insert(uint32 index, T d)	// insert item at index
{

	if (vec[index]) {
						// remove old item
		deleteItem((void*)vec[index]);
		numItems--;
	}
	if (d) {
		vec[index] = newItem(d);
		numItems++;
		return vec[index] != 0;
	}
	else {
		vec[index] = 0; 				// reset item
	}
	return true;
}

template <class T>
bool tVector<T>::remove(uint32 index)		// remove item at index
{

	if (vec[index]) {
						// valid item
		deleteItem((T)vec[index]);  		// delete it
		vec[index] = 0; 				// reset pointer
		numItems--;
	}
	return true;
}

template <class T>
T tVector<T>::take(uint32 index)		// take out item
{
	T d = vec[index]; 				// don't delete item
	if(d)
	numItems--;
	vec[index] = 0;
	return d;
}

template <class T>
void tVector<T>::clear()				// clear vector
{
	if (vec) {
		for (uint32 i = 0; i < len; i++) {
					// delete each item
		    if(vec[i])
				deleteItem((void*)vec[i]);
		}
		DELETE(vec);
		vec = 0;
		len = numItems = 0;
	}
}

template <class T>
bool tVector<T>::resize(uint32 newsize)		// resize array
{
	if (newsize == len)			// nothing to do
	return true;
	if (vec) {
						// existing data
	if(newsize < len) {
						// shrink vector
	    uint32 i = newsize;
			while (i < len) {
							// delete lost items
			if(vec[i]) {
				deleteItem(vec[i]);
					numItems--;
				}
				i++;
			}
		}
		if (newsize == 0) {
						// vector becomes empty
		    DELETE(vec);
			vec = 0;
			len = numItems = 0;
			return true;
		}
#if defined(DONT_USE_REALLOC)
		T *newvec = NEW(T, newsize); 		// manual realloc
		memcpy(newvec, vec, (len < newsize ? len : newsize)*sizeof(T));
		DELETE(vec);
		vec = newvec;
#else
		vec = (T*)realloc((char *)vec, newsize*sizeof(T));
#endif
	}
	else {
							// create new vector
	vec = NEW(T, newsize);
		len = numItems = 0;
	}
	
	if (!vec)					// no memory
	return false;
	if (newsize > len)			// init extra space added
	memset((void*)&vec[len], 0, (newsize - len)*sizeof(T));
	len = newsize;
	return true;
}

template <class T>
bool tVector<T>::fill(T d, int32 flen)		// resize and fill vector
{
	if (flen < 0)
		flen = len; 				// default: use vector length
		else if(!resize(flen))
		return false;
	for (uint32 i = 0; i < (uint32)flen; i++)		// insert d at every index
	insert(i, d);
	return true;
}


template <class T>
int32 tVector<T>::find(T d, uint32 index) const // find exact item in vector
{
	for (uint32 i = index; i < len; i++) {
		if (vec[i] == d)
			return i;
	}
	return -1;
}

template <class T>
uint32 tVector<T>::contains(T d) const	// get number of exact matches
{
	uint32 count = 0;
	for (uint32 i = 0; i < len; i++) {
		if (vec[i] == d)
			count++;
	}
	return count;
}

template <class T>
bool tVector<T>::insertExpand(uint32 index, T d)// insert and grow if necessary
{
	if (index >= len) {
		if (!resize(index + 1))		// no memory
		    return false;
	}
	insert(index, d);
	return true;
}

template <class T>
void tVector<T>::toList(tList<T> *list) const	// store items in list
{
	list->clear();
	for (uint32 i = 0; i < len; i++) {
		if (vec[i])
			list->append(vec[i]);
	}
}


#endif //_TVECTOR_