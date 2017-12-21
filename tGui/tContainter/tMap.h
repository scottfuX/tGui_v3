#ifndef _TMAP_H_
#define _TMAP_H_

#include "tCollection.h"
#include "tList.h"
#include "tString.h"
#include <ctype.h>

template<class T>
class tBucket;	// internal classes
template<class T>
class tMapIterator;
template<class T>
class tList;
//class QListM_QGDictIterator;
//#define tList<T> QListM_QGDictIterator

template<class T>
class  tMap : public tCollection<T>		// generic dictionary class
{
	friend class tMapIterator<T>;
public:
	uint32	count() const { return numItems; }
	uint32	size()	const { return vlen; }
	T		look(const char *key, T, int32);

//protected:
	tMap(uint32 len, bool cs, bool ck, bool th);
	tMap(const tMap<T> &);
	~tMap();

	tMap<T>     &operator=(const tMap<T> &);

	bool	remove(const char *key);
	T		take(const char *key);
	void	clear();
	void	resize(uint32);

	virtual int32 hashKey(const char *);


private:
	tBucket<T>   **vec;
	uint32	vlen;
	uint32	numItems;
	uint32	cases : 1;
	uint32	copyk : 1;
	uint32	triv : 1;
	tList<T>  *iterators;
	tBucket<T>    *unlink(const char *);
	void        init(uint32);
	virtual T	     newItem(T d) { tCollection<T>::newItem(d); }		// create object
	virtual void     deleteItem(void* d) { tCollection<T>::deleteItem(d); }  		// delete object

};

template<class T>
class  tMapIterator				// generic dictionary iterator
{
	friend class tMap<T>;
public:
	tMapIterator(const tMap<T> &);
	tMapIterator(const tMapIterator &);
	tMapIterator &operator=(const tMapIterator &);
	~tMapIterator();

	T		toFirst();

	T		get()	 const;
	const char *getKey() const;

	T		operator()();
	T		operator++();
	T		operator+=(uint32);

protected:
	tMap<T>     *dict;

private:
	tBucket<T>    *curNode;
	uint32	curIndex;
};


/*!
\class tMap<T> qgdict.h
\brief The tMap<T> class is an internal class for implementing QDict and QIntDict.

tMap<T> is a strictly internal class that acts as a base class for the
\link collection.html collection classes\endlink QDict and QIntDict.

tMap<T> has some virtual functions that can be reimplemented to customize
the subclasses.
<ul>
<li> hashKey() implements the hashing function for the dictionary.
<li> read() reads a collection/dictionary item from a QDataStream.
<li> write() writes a collection/dictionary item to a QDataStream.
</ul>
Normally, you do not have to reimplement any of these functions.
*/

static const int32 op_find = 0;
static const int32 op_insert = 1;
static const int32 op_replace = 2;

template<class T>
int32 tMap<T>::hashKey(const char *key)
{
	register const char *k = key;
	register uint32 h = 0;
	uint32 g;
	if (cases) {				// case sensitive
		while (*k) {
			h = (h << 4) + *k++;
			if ((g = h & 0xf0000000))
				h ^= g >> 24;
			h &= ~g;
		}
	}
	else {					// case insensitive
		while (*k) {
			h = (h << 4) + tolower(*k);
			if ((g = h & 0xf0000000))
				h ^= g >> 24;
			h &= ~g;
			k++;
		}
	}
	int32 index = h;
	if (index < 0)				// adjust index to table size
		index = -index;
	return index;
}


/*****************************************************************************
tBucket<T> class (internal hash node)
*****************************************************************************/
template<class T>
class tBucket
{
public:
	char   *getKey() { return key; }
	char   *setKey(char *k) { return key = k; }
	T	    getData() { return data; }
	T	    setData(T d) { return data = d; }
	tBucket<T> *getNext() { return next; }
	void    setNext(tBucket<T> *n) { next = n; }
private:
	char   *key;
	T	    data;
	tBucket<T> *next;
};


/*****************************************************************************
tMap<T> member functions
*****************************************************************************/

/*!
\internal
Constructs a dictionary.
*/
template<class T>
tMap<T>::tMap(uint32 len, bool cs, bool ck, bool th)
{
	init(len);
	cases = cs;
	copyk = ck;
	triv = th;
	if (triv)					// copyk must be false for
		copyk = false;				//   int32-hashed dicts
}

template<class T>
void tMap<T>::init(uint32 len)
{
	vec = new tBucket<T> *[vlen = len];		// allocate hash table
	memset((char*)vec, 0, vlen * sizeof(tBucket<T>*));
	numItems = 0;
	iterators = 0;

	// Be careful not to break resize() if you add something.
}

/*!
\internal
Constructs a copy of \e dict.
*/
template<class T>
tMap<T>::tMap(const tMap<T> & dict)
	: tCollection<T>(dict)
{
	init(dict.vlen);
	cases = dict.cases;
	copyk = dict.copyk;
	triv = dict.triv;
	tMapIterator<T> it(dict);
	while (it.get()) {			// copy from other dict
		look(it.getKey(), it.get(), op_insert);
		++it;
	}
}

/*!
\internal
Removes all items from the dictionary and destroys it.
*/
template<class T>
tMap<T>::~tMap()
{
	clear();					// delete everything
	delete[] vec;
	if (!iterators)				// no iterators for this dict
		return;
	register tMapIterator<T> *i = (tMapIterator<T>*)iterators->first();
	while (i) {				// notify all iterators that
		i->dict = 0;				// this dict is deleted
		i = (tMapIterator<T>*)iterators->next();
	}
	delete (tMapIterator<T>*)iterators;
}


/*!
\internal
Assigns \e dict to this dictionary.
*/
template<class T>
tMap<T> &tMap<T>::operator=(const tMap<T> &dict)
{
	clear();
	tMapIterator<T> it(dict);
	while (it.get()) {			// copy from other dict
		look(it.getKey(), it.get(), op_insert);
		++it;
	}
	return *this;
}


/*!
\fn uint32 tMap<T>::count() const
\internal
Returns the number of items in the dictionary.
*/

/*!
\fn uint32 tMap<T>::size() const
\internal
Returns the size of the hash array.
*/


/*!
\internal
The do-it-all function; op is one of op_find, op_insert, op_replace
*/
template<class T>
T tMap<T>::look(const char *key, T d, int32 op)
{
	register tBucket<T> *n;
	int32	 index;
	if (triv) {				// key is a long/ptr
		index = (int32)(long(key) % vlen);	// simple hash
		if (op == op_find) {			// find
			for (n = vec[index]; n; n = n->getNext()) {
				if (n->getKey() == key)
					return n->getData();	// item found
			}
			return 0;				// not such item
		}
	}
	else {					// key is a string
		index = hashKey(key) % vlen;
		if (op == op_find) {			// find
			for (n = vec[index]; n; n = n->getNext()) {
				if ((cases ? strcmp(n->getKey(), key): stricmp(n->getKey(), key)) == 0)
					return n->getData();	// item found
			}
			return 0;				// did not find the item
		}
	}
	if (op == op_replace) {			// replace
		if (vec[index] != 0)			// maybe something there
			remove(key);
	}
	tBucket<T> *node = new tBucket<T>();		// insert new node
	if (!node)				// no memory
		return 0;
	node->setKey((char *)(copyk ? strdup(key) : key));
	node->setData(newItem(d));
	node->setNext(vec[index]);		// link node into table
	vec[index] = node;
	numItems++;
	return node->getData();
}

/*!
\internal
Changes the size of the hashtable.
The contents of the dictionary are preserved,
but all iterators on the dictionary become invalid.
*/
template<class T>
void tMap<T>::resize(uint32 newsize)
{
	// Save old information
	tBucket<T>   **old_vec = vec;
	uint32	old_vlen = vlen;
	tList<T>  *old_iterators = iterators;
	bool	old_copyk = copyk;

	init(newsize);
	copyk = false;

	// Reinsert every item from vec, deleting vec as we go
	for (uint32 index = 0; index < old_vlen; index++) {
		tBucket<T> *n = old_vec[index];
		while (n) {
			look(n->getKey(), n->getData(), op_insert);
			tBucket<T> *t = n->getNext();
			delete n;
			n = t;
		}
	}
	delete[] old_vec;

	// Restore state
	iterators = old_iterators;
	copyk = old_copyk;

	// `Invalidate' all iterators, since order is lost
	if (iterators) {			// update iterators
		register tMapIterator<T> *i = iterators->first();
		while (i) {			// fix all iterators
			i->toFirst();
			i = iterators->next();
		}
	}
}

/*!
\internal
Unlinks the bucket with the specified key.
*/
template<class T>
tBucket<T> *tMap<T>::unlink(const char *key)
{
	if (numItems == 0)			// nothing in dictionary
		return 0;
	register tBucket<T> *n;
	tBucket<T> *prev = 0;
	int32 index;
	if (triv)
		index = (int32)(long(key) % vlen);
	else
		index = hashKey(key) % vlen;
	for (n = vec[index]; n; n = n->getNext()) {	// find item in list
		bool equal;
		if (triv)
			equal = n->getKey() == key;
		else
			equal = (cases ? strcmp(n->getKey(), key)
				: stricmp(n->getKey(), key)) == 0;
		if (equal) {				// found key to be removed
			if (iterators) {			// update iterators
				register tMapIterator<T> *i = (tMapIterator<T> *)iterators->first();
				while (i) {			// fix all iterators that
					if (i->curNode == n)	// refers to pending node
						i->operator++();
					i = (tMapIterator<T> *)iterators->next();
				}
			}
			if (prev)				// unlink node
				prev->setNext(n->getNext());
			else
				vec[index] = n->getNext();
			numItems--;
			return n;
		}
		prev = n;
	}
	return 0;
}

/*!
\internal
Removes the item with the specified key.
*/
template<class T>
bool tMap<T>::remove(const char *key)
{
	register tBucket<T> *n = unlink(key);
	if (n) {
		if (copyk)
			delete[] n->getKey();
		deleteItem((void*)n->getData());
		delete n;				// delete bucket
	}
	return n != 0;
}

/*!
\internal
Takes out the item with the specified key.
*/
template<class T>
T tMap<T>::take(const char *key)
{
	register tBucket<T> *n = unlink(key);
	T tmp;
	if (n) {
		tmp = n->getData();
		if (copyk)
			delete[] n->getKey();
		delete n;
	}
	else {
		tmp = 0;
	}
	return tmp;
}


/*!
\internal
Removes all items from the dictionary.
*/
template<class T>
void tMap<T>::clear()
{
	if (!numItems)
		return;
	register tBucket<T> *n;
	numItems = 0;				// disable remove() function
	for (uint32 j = 0; j<vlen; j++) {		// destroy hash table
		if (vec[j]) {
			n = vec[j];
			vec[j] = 0;				// detach list of buckets
			while (n) {
				if (copyk)
					delete[] n->getKey();
				tBucket<T> *next = n->getNext();
				deleteItem((void*)n->getData());
				delete n;
				n = next;
			}
		}
	}
	if (!iterators)				// no iterators for this dict
		return;
	register tMapIterator<T> *i = (tMapIterator<T>*)iterators->first();
	while (i) {				// notify all iterators that
		i->curNode = 0;				// this dict is empty
		i = (tMapIterator<T>*)iterators->next();
	}
}




/*****************************************************************************
tMapIterator<T> member functions
*****************************************************************************/

/*!
\class tMapIterator<T> qgdict.h
\brief An internal class for implementing QDictIterator and QIntDictIterator.

tMapIterator<T> is a strictly internal class that does the heavy work for
QDictIterator and QIntDictIterator.
*/

/*!
\internal
Constructs an iterator that operates on the dictionary \e d.
*/
template<class T>
tMapIterator<T>::tMapIterator(const tMap<T> &d)
{
	dict = (tMap<T> *)&d;			// get reference to dict
	toFirst();					// set to first noe
	if (!dict->iterators) {
		dict->iterators = new tList<T>();	// create iterator list
	}
	dict->iterators->append(this);		// attach iterator to dict
}

/*!
\internal
Constructs a copy of the iterator \e it.
*/
template<class T>
tMapIterator<T>::tMapIterator(const tMapIterator<T> &it)
{
	dict = it.dict;
	curNode = it.curNode;
	curIndex = it.curIndex;
	if (dict)
		dict->iterators->append(this);	// attach iterator to dict
}

/*!
\internal
Assigns a copy of the iterator \e it and returns a reference to this
iterator.
*/
template<class T>
tMapIterator<T> &tMapIterator<T>::operator=(const tMapIterator<T> &it)
{
	if (dict) {				// detach from old dict
		if (dict->iterators->removeRef(this)) {
			if (dict->iterators->count() == 0) {
				delete dict->iterators;		// this was the last iterator
				dict->iterators = 0;
			}
		}
	}
	dict = it.dict;
	curNode = it.curNode;
	curIndex = it.curIndex;
	if (dict)
		dict->iterators->append(this);	// attach to new list
	return *this;
}

/*!
\internal
Destroys the iterator.
*/
template<class T>
tMapIterator<T>::~tMapIterator<T>()
{
	if (dict) {				// detach iterator from dict
		if (dict->iterators->removeRef((T)this)){
			if (dict->iterators->count() == 0) {
				delete dict->iterators;		// this was the last iterator
				dict->iterators = 0;
			}
		}
	}
}


/*!
\internal
Sets the iterator to point to the first item in the dictionary.
*/
template<class T>
T tMapIterator<T>::toFirst()
{
	if (!dict) {

		return 0;
	}
	if (dict->count() == 0) {			// empty dictionary
		curNode = 0;
		return 0;
	}
	register uint32 i = 0;
	register tBucket<T> **v = dict->vec;
	while (!(*v++))
		i++;
	curNode = dict->vec[i];
	curIndex = i;
	return curNode->getData();
}


/*!
\internal
Returns the current item.
*/
template<class T>
T tMapIterator<T>::get() const
{
	return curNode ? curNode->getData() : 0;
}

/*!
\internal
Returns the key of the current item.
*/
template<class T>
const char *tMapIterator<T>::getKey() const
{
	return curNode ? curNode->getKey() : 0;
}


/*!
\internal
Moves to the next item (postfix).
*/
template<class T>
T tMapIterator<T>::operator()()
{
	if (!dict) {
		return 0;
	}
	if (!curNode)
		return 0;
	T d = curNode->getData();
	this->operator++();
	return d;
}

/*!
\internal
Moves to the next item (prefix).
*/
template<class T>
T tMapIterator<T>::operator++()
{
	if (!dict) {
		return 0;
	}
	if (!curNode)
		return 0;
	curNode = curNode->getNext();
	if (!curNode) {				// no next bucket
		register uint32 i = curIndex + 1;		// look from next vec element
		register tBucket<T> **v = &dict->vec[i];
		while (i < dict->size() && !(*v++))
			i++;
		if (i == dict->size()) {		// nothing found
			curNode = 0;
			return 0;
		}
		curNode = dict->vec[i];
		curIndex = i;
	}
	return curNode->getData();
}

/*!
\internal
Moves \e jumps positions forward.
*/
template<class T>
T tMapIterator<T>::operator+=(uint32 jumps)
{
	while (curNode && jumps--)
		operator++();
	return curNode ? curNode->getData() : 0;
}

#endif // !_TMAP_H_




