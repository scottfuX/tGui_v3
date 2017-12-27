#ifndef _TLIST_H_
#define _TLIST_H_
#include "tGlobal.h"
#include "tCollection.h"
#include "tVector.h"
/*****************************************************************************
  tLNode<T> class (internal doubly linked list node)
 *****************************************************************************/
template<class T>
	class tListIterator;
template<class T>
	class tVector;
template<class T>
	class tMap;
template<class T>
	class tMapIterator;
template<class T>

class  tLNode
{
	friend class tList<T>;
	friend class tListIterator<T>;
public:
    T	    getData()	{ return data; }
private:
    T	    data;
    tLNode *prev;
    tLNode *next;
	tLNode(T d) { data = d; prev = NULL; next = NULL; }
};


/*****************************************************************************
  tList class
 *****************************************************************************/
template <class T>
class  tList : public tCollection<T>	// doubly linked generic list
{
	friend class tListIterator<T>;
	friend class tVector<T>;	
	friend class tMap<T>;
	friend class tMapIterator<T>;
public :
    uint32  count() const { return numNodes;};			// return number of nodes

protected:
    tList();					// create empty list
    tList( const tList & );			// make copy of other list
   ~tList();

    tList &operator=( const tList & );	// assign from other list

    void  append( T );			// add item at end of list
    bool  insertAt( uint32 index, T );		// add item at i'th position
    void  relinkNode( tLNode<T> * );		// relink as first item
    bool  removeNode( tLNode<T> * );		// remove node
    bool  remove( T = 0 );			// remove item (0=current)
    bool  removeRef( T = 0 );			// remove item (0=current)
    bool  removeFirst(){first();return remove();};			// remove first item
    bool  removeLast(){last();return remove();};				// remove last item
    bool  removeAt( uint32 index );		// remove item at i'th position
    T	  takeNode( tLNode<T> * );			// take out node
    T	  take();				// take out current item
    T	  takeAt( uint32 index );			// take out item at i'th pos
    T	  takeFirst();				// take out first item
    T	  takeLast();				// take out last item
	tLNode<T> *take(T t) { find(t); return unlink(); }

    void  clear();				// remove all items

    int32	  findRef( T, bool = true );		// find exact item in list
    int32	  find( T, bool = true );		// find equal item in list

    uint32  containsRef( T )	const;		// get number of exact matches
    uint32  contains( T )	const;		// get number of equal matches

    T	  at(uint32 index) {tLNode<T> *n = locate( index );return n ? n->data : 0;};			// access item at i'th pos
    int32	  at() const { return curIndex;};				// get current index
    T	  get() const { return curNode ? curNode->data : 0;};				// get current item

    T	  cfirst() const {return firstNode ? firstNode->data : 0;};			// get ptr to first list item
    T	  clast()  const {return lastNode ? lastNode->data : 0;};			// get ptr to last list item
    T	  first();				// set first item in list curr
    T	  last();				// set last item in list curr
    T	  next();				// set next item in list curr
    T	  prev();				// set prev item in list curr

	tLNode<T>* currentNode() const { return curNode; };		// get current node
	int32 currentIndex() const { return curIndex; }
	void setCurNode(tLNode<T> * node) { curNode = node; }
	void setCurIndex(int32 index) { curIndex = index; }

	void  toVector(tVector<T> * ) const;		// put items in vector

    virtual int32 compareItems(T item1, T item2) {	return item1 != item2;}			// compare pointers;
	virtual T	     newItem(T d) {tCollection<T>::newItem(d); }		// create object
	virtual void     deleteItem(void* d) {tCollection<T>::deleteItem(d); }  		// delete object
private:
    void  prepend( T );			// add item at start of list

    tLNode<T> *firstNode;				// first node
    tLNode<T> *lastNode;				// last node
    tLNode<T> *curNode;				// current node
    int32	   curIndex;				// current index
    uint32    numNodes;				// number of nodes
    tList *  iterators;				// list of iterators

    tLNode<T> *locate( uint32 );			// get node at i'th pos
	tLNode<T> *unlink();				// unlink node
};



/*****************************************************************************
  tListIterator<T> class
 *****************************************************************************/
template<class T>
class  tListIterator		// tList iterator
{
	friend class tList<T>;
public:
    tListIterator( const tList<T> & );
    tListIterator( const tListIterator & );
    tListIterator &operator=( const tListIterator & );
   ~tListIterator();

	bool  atFirst() const {return curNode == list->firstNode;};			// test if at first item
    bool  atLast()  const {return curNode == list->lastNode;};			// test if at last item
    T	  toFirst();				// move to first item
    T	  toLast();				// move to last item

    T	  get() const { return curNode ? curNode->data : 0;};				// get current item
    T	  operator()();				// get current and move to next
    T	  operator++();				// move to next item (prefix)
    T	  operator+=(uint32);			// move n positions forward
    T	  operator--();				// move to prev item (prefix)
    T	  operator-=(uint32);			// move n positions backward

protected:
    tList<T> *list;				// reference to list

private:
    tLNode<T>  *curNode;				// current node in list
};



/*****************************************************************************
  tList<T> member functions
 *****************************************************************************/

/*!
  \internal
  Constructs an empty list.
*/
template<class T>
tList<T>::tList()
{
	firstNode = lastNode = curNode = 0; 		// initialize list
	numNodes  = 0;
	curIndex  = -1;
	iterators = 0; 				// initialize iterator list
}

/*!
  \internal
  Constructs a copy of \e list.
*/

template<class T>
tList<T>::tList(const tList<T> & list)
	: tCollection<T>(list)
{
	firstNode = lastNode = curNode = 0; 		// initialize list
	numNodes  = 0;
	curIndex  = -1;
	iterators = 0; 				// initialize iterator list
	register tLNode<T> *n = list.firstNode;
	while (n) {
						// copy all items from list
	append(n->data);
		n = n->next;
	}
}

/*!
  \internal
  Removes all items from the list and destroys the list.
*/

template<class T>
tList<T>::~tList()
{
	clear();
	if (!iterators)				// no iterators for this list
		return;
	register tListIterator<T> *i = (tListIterator<T>*)iterators->first();
	while (i) 
	{					// notify all iterators that
		i->list = 0; 				// this list is deleted
		i = (tListIterator<T>*)iterators->next();
	}
	delete iterators;
}


/*!
  \internal
  Assigns \e list to this list.
*/

template<class T>
tList<T>& tList<T>::operator=(const tList<T> &list)
{
	clear();
	if (list.count() > 0) {
		register tLNode<T> *n = list.firstNode;
		while (n) {
							// copy all items from list
		    append(n->data);
			n = n->next;
		}
		curNode	 = firstNode;
		curIndex = 0;
	}
	return *this;
}


/*!
  \fn uint32 tList<T>::count() const
  \internal
  Returns the number of items in the list.
*/


/*!
  \internal
  Returns the node at position \e index.  Sets this node to current.
*/

template<class T>
tLNode<T> *tList<T>::locate(uint32 index)
{
	if (index == (uint32)curIndex)		// current node ?
		return curNode;
	if (!curNode && firstNode) {
				// set current node
	curNode	 = firstNode;
		curIndex = 0;
	}
	register tLNode<T> *node;
	int32	 distance = index - curIndex; 		// node distance to cur node
	bool forward; 				// direction to traverse

	if(index >= numNodes) {
		return 0;
	}

	if (distance < 0)
		distance = -distance;
	if ((uint32)distance < index && (uint32)distance < numNodes - index) {
		node =	curNode; 			// start from current node
		forward = index > (uint32)curIndex;
	}
	else if (index < numNodes - index) {
			// start from first node
	node = firstNode;
		distance = index;
		forward = true;
	}
	else {
							// start from last node
	node = lastNode;
		distance = numNodes - index - 1;
		if (distance < 0)
			distance = 0;
		forward = false;
	}
	if (forward) {
						// now run through nodes
	while(distance--)
	    node = node->next;
	}
	else {
		while (distance--)
			node = node->prev;
	}
	curIndex = index; 				// must update index
	return curNode = node;
}


/*!
  \internal
  Inserts an item at the start of the list.
*/

template<class T>
void tList<T>::prepend(T d)
{
	register tLNode<T> *n = new tLNode<T>(newItem(d));
	
	n->prev = 0;
	if ((n->next = firstNode))		// list is not empty
	firstNode->prev = n;
	else					// initialize list
	lastNode = n;
	firstNode = curNode = n; 			// curNode affected
	numNodes++;
	curIndex = 0;
}


/*!
  \internal
  Inserts an item at the end of the list.
*/
template<class T>
void tList<T>::append(T d)
{
	register tLNode<T> *n = new tLNode<T>((d));
	n->next = 0;
	if ((n->prev = lastNode))			// list is not empty
		lastNode->next = n;
	else					// initialize list
		firstNode = n;
	lastNode = curNode = n; 			// curNode affected
	curIndex = numNodes;
	numNodes++;
}


/*!
  \internal
  Inserts an item at position \e index in the list.
*/

template<class T>
bool tList<T>::insertAt(uint32 index, T d)
{
	if (index == 0) {
						// insert at head of list
	prepend(d);
		return true;
	}
	else if (index == numNodes) {
				// append at tail of list
	append(d);
		return true;
	}
	tLNode<T> *nextNode = locate(index);
	if (!nextNode)				// illegal position
	return false;
	tLNode<T> *prevNode = nextNode->prev;
	register tLNode<T> *n = new tLNode<T>(newItem(d));
	nextNode->prev = n;
	prevNode->next = n;
	n->prev = prevNode; 				// link new node into list
	n->next = nextNode;
	curNode = n; 				// curIndex set by locate()
	numNodes++;
	return true;
}


/*!
  \internal
  Relinks node \e n and makes it the first node in the list.
*/

template<class T>
void tList<T>::relinkNode(tLNode<T> *n)
{
	if (n == firstNode)			// already first
	return;
	curNode = n;
	unlink();
	n->prev = 0;
	if ((n->next = firstNode))		// list is not empty
	firstNode->prev = n;
	else					// initialize list
	lastNode = n;
	firstNode = curNode = n; 			// curNode affected
	numNodes++;
	curIndex = 0;
}


/*!
  \internal
  Unlinks the current list node and returns a pointer to this node.
*/

template<class T>
tLNode<T> *tList<T>::unlink()
{
	if (curNode == 0)				// null current node
	return 0;
	register tLNode<T> *n = curNode; 		// unlink this node
	if(n == firstNode) {
					// removing first node ?
	if((firstNode = n->next)) {
			firstNode->prev = 0;
		} else {
			lastNode = curNode = 0; 		// list becomes empty
			curIndex = -1;
		}
	} else {
		if (n == lastNode) {
						// removing last node ?
		    lastNode = n->prev;
			lastNode->next = 0;
		}
		else {
							// neither last nor first node
		    n->prev->next = n->next;
			n->next->prev = n->prev;
		}
	}
	if (n->next) {
						// change current node
	curNode = n->next;
	}
	else if (n->prev) {
		curNode = n->prev;
		curIndex--;
	}
	if (iterators) {
						// update iterators
	register tListIterator<T> *i = (tListIterator<T>*)iterators->first();
		while (i) {
							// fix all iterators that
		    if(i->curNode == n)		// refers to pending node
			i->curNode = curNode;
			i = (tListIterator<T>*)iterators->next();
		}
	}
	numNodes--;
	return n;
}


/*!
  \internal
  Removes the node \e n from the list.
*/

template<class T>
bool tList<T>::removeNode(tLNode<T> *n)
{
	curNode = n;
	unlink(); 					// unlink node
	deleteItem(n->data); 			// deallocate this node
	delete n;
	curNode  = firstNode;
	curIndex = curNode ? 0 : -1;
	return true;
}

/*!
  \internal
  Removes the item \e d from the list.	Uses compareItems() to find the item.
*/

template<class T>
bool tList<T>::remove(T d)
{
	if (d) {
							// find the item
	if(find(d) == -1)
	    return false;
	}
	tLNode<T> *n = unlink(); 			// unlink node
	if(!n)
	return false;
	deleteItem((void*)n->data); 			// deallocate this node
	delete n;
	curNode = firstNode;
	curIndex = curNode ? 0 : -1;
	return true;
}

/*!
  \internal
  Removes the item \e d from the list.
*/

template<class T>
bool tList<T>::removeRef(T d)
{
	if (d) {
							// find the item
		if(findRef(d) == -1)
	    return false;
	}
	tLNode<T> *n = unlink(); 			// unlink node
	if(!n)
	return false;
	deleteItem((void*)n->data); 			// deallocate this node
	delete n;
	return true;
}


/*!
  \internal
  Removes the item at position \e index from the list.
*/

template<class T>
bool tList<T>::removeAt(uint32 index)
{
	if (!locate(index))
		return false;
	tLNode<T> *n = unlink(); 			// unlink node
	if(!n)
	return false;
	deleteItem(n->data); 			// deallocate this node
	delete n;
	return true;
}


/*!
  \internal
  Takes the node \e n out of the list.
*/

template<class T>
T tList<T>::takeNode(tLNode<T> *n)
{
	curNode = n;
	unlink(); 					// unlink node
	T d = n->data;
	delete n; 					// delete the node, not data
	curNode  = firstNode;
	curIndex = curNode ? 0 : -1;
	return d;
}

/*!
  \internal
  Takes the current item out of the list.
*/

template<class T>
T tList<T>::take()
{
	tLNode<T> *n = unlink(); 			// unlink node
	T d = n ? n->data : 0;
	delete n; 					// delete node, keep contents
	return d;
}

/*!
  \internal
  Takes the item at position \e index out of the list.
*/

template<class T>
T tList<T>::takeAt(uint32 index)
{
	if (!locate(index))
		return 0;
	tLNode<T> *n = unlink(); 			// unlink node
	T d = n ? n->data : 0;
	delete n; 					// delete node, keep contents
	return d;
}

/*!
  \internal
  Takes the first item out of the list.
*/

template<class T>
T tList<T>::takeFirst()
{
	first();
	tLNode<T>* n = unlink(); 			// unlink node
	T d = n ? n->data : 0;
	delete n;
	return d;
}

/*!
  \internal
  Takes the last item out of the list.
*/

template<class T>
T tList<T>::takeLast()
{
	last();
	tLNode<T> *n = unlink(); 			// unlink node
	T d = n ? n->data : 0;
	delete n;
	return d;
}


/*!
  \internal
  Removes all items from the list.
*/

template<class T>
void tList<T>::clear()
{
	register tLNode<T> *n = firstNode;
	tLNode<T> *prevNode;
	while (n) 
	{				// for all nodes ...
		deleteItem((void*)(n->data)); 			// deallocate data
		prevNode = n;
		n = n->next;
		delete prevNode; 			// deallocate node
	}
	firstNode = lastNode = curNode = 0; 		// initialize list
	numNodes = 0;
	curIndex = -1;
	if (!iterators)				// no iterators for this list
		return;
	register tListIterator<T> *i = (tListIterator<T>*)iterators->first();
	while (i) 
	{		// notify all iterators that
		i->curNode = 0; 				// this list is empty
		i = (tListIterator<T>*)iterators->next();
	}
}


/*!
  \internal
  Finds an item in the list.
*/

template<class T>
int32 tList<T>::findRef(T d, bool fromStart)
{
	register tLNode<T> *n;
	int32	  index;
	if (fromStart) {
						// start from first node
	n = firstNode;
		index = 0;
	}
	else {
							// start from current node
	n = curNode;
		index = curIndex;
	}
	while (n && n->data != d) {
				// find exact match
	n = n->next;
		index++;
	}
	curNode = n;
	curIndex = n ? index : -1;
	return curIndex;				// return position of item
}

/*!
  \internal
  Finds an item in the list.  Uses compareItems().
*/

template<class T>
int32 tList<T>::find(T d, bool fromStart)
{
	register tLNode<T> *n;
	int32	     index;
	if (fromStart) {
						// start from first node
	n = firstNode;
		index = 0;
	}
	else {
							// start from current node
	n = curNode;
		index = curIndex;
	}
	while (n && compareItems(n->data, d)) {
			// find equal match
	n = n->next;
		index++;
	}
	curNode = n;
	curIndex = n ? index : -1;
	return curIndex;				// return position of item
}


/*!
  \internal
  Counts the number an item occurs in the list.
*/

template<class T>
uint32 tList<T>::containsRef(T d) const
{
	register tLNode<T> *n = firstNode;
	uint32     count = 0;
	while (n) {
						// for all nodes...
	if(n->data == d)			// count # exact matches
	    count++;
		n = n->next;
	}
	return count;
}

/*!
  \internal
  Counts the number an item occurs in the list.	 Uses compareItems().
*/

template<class T>
uint32 tList<T>::contains(T d) const
{
	register tLNode<T> *n = firstNode;
	uint32     count = 0;
	tList<T>  *that = (tList<T>*)this; 		// mutable for compareItems()
	while(n) {
						// for all nodes...
	if(!that->compareItems(n->data, d))	// count # equal matches
	    count++;
		n = n->next;
	}
	return count;
}


/*!
  \fn T tList<T>::at( uint32 index )
  \internal
  Sets the item at position \e index to the current item.
*/

/*!
  \fn int32 tList<T>::at() const
  \internal
  Returns the current index.
*/

/*!
  \fn tLNode<T> *tList<T>::currentNode() const
  \internal
  Returns the current node.
*/

/*!
  \fn T tList<T>::get() const
  \internal
  Returns the current item.
*/

/*!
  \fn T tList<T>::cfirst() const
  \internal
  Returns the first item in the list.
*/

/*!
  \fn T tList<T>::clast() const
  \internal
  Returns the last item in the list.
*/


/*!
  \internal
  Returns the first list item.	Sets this to current.
*/
template<class T>
T tList<T>::first()
{
	if (firstNode) {
		curIndex = 0;
		return (curNode = firstNode)->data;
	}
	return 0;
}

/*!
  \internal
  Returns the last list item.  Sets this to current.
*/
template<class T>
T tList<T>::last()
{
	if (lastNode) {
		curIndex = numNodes - 1;
		return (curNode = lastNode)->data;
	}
	return 0;
}

/*!
  \internal
  Returns the next list item (after current).  Sets this to current.
*/
template<class T>
T tList<T>::next()
{
	if (curNode) {
		if (curNode->next) {
			curIndex++;
			curNode = curNode->next;
			return curNode->data;
		}
		curIndex = -1;
		curNode = 0;
	}
	return 0;
}

/*!
  \internal
  Returns the previous list item (before current).  Sets this to current.
*/
template<class T>
T tList<T>::prev()
{
	if (curNode) {
		if (curNode->prev) {
			curIndex--;
			curNode = curNode->prev;
			return curNode->data;
		}
		curIndex = -1;
		curNode = 0;
	}
	return 0;
}


/*!
  \internal
  Converts the list to a vector.
*/
template<class T>
void tList<T>::toVector(tVector<T> *vector) const
{
	vector->clear();
	if (!vector->resize(count()))
		return;
	register tLNode<T> *n = firstNode;
	uint32 i = 0;
	while (n) {
		vector->insert(i, n->data);
		n = n->next;
		i++;
	}
}


/*****************************************************************************
  tListIterator<T> member functions
 *****************************************************************************/

/*!
  \class tListIterator<T> qglist.h
  \brief The tListIterator<T> is an internal class for implementing QListIterator.

  tListIterator<T> is a strictly internal class that does the heavy work for
  QListIterator.
*/

/*!
  \internal
  Constructs an iterator that operates on the list \e l.
*/
template<class T>
tListIterator<T>::tListIterator(const tList<T> &l)
{
	list = (tList<T> *)&l;  			// get reference to list
	curNode = list->firstNode;  			// set to first node
	if(!list->iterators) {
		list->iterators = new tList<T>;  		// create iterator list	
	}
	list->iterators->append((T)this);  		// attach iterator to list
}
/*!
  \internal
  Constructs a copy of the iterator \e it.
*/
template<class T>
tListIterator<T>::tListIterator(const tListIterator<T> &it)
{
	list = it.list;
	curNode = it.curNode;
	if (list)
		list->iterators->append(this); 	// attach iterator to list
}

/*!
  \internal
  Assigns a copy of the iterator \e it and returns a reference to this
  iterator.
*/
template<class T>
tListIterator<T> &tListIterator<T>::operator=(const tListIterator<T> &it)
{
	if (list) {
						// detach from old list
		if(list->iterators->removeRef(this)) {
			if (list->iterators->count() == 0) {
				delete list->iterators; 		// this was the last iterator
				list->iterators = 0;
			}
		}
	}
	list = it.list;
	curNode = it.curNode;
	if (list)
		list->iterators->append(this); 	// attach to new list
		return *this;
}

/*!
  \internal
  Destroys the iterator.
*/
template<class T>
tListIterator<T>::~tListIterator<T>()
{
	if (list) {
						// detach iterator from list
		if(list->iterators->removeRef((T)this)) {
			if (list->iterators->count() == 0) {
				delete list->iterators; 		// this was the last iterator
				list->iterators = 0;
			}
		}
	}
}


/*!
  \fn bool tListIterator<T>::atFirst() const
  \internal
  Returns true if the iterator points to the first item, otherwise false.
*/

/*!
  \fn bool tListIterator<T>::atLast() const
  \internal
  Returns true if the iterator points to the last item, otherwise false.
*/


/*!
  \internal
  Sets the list iterator to point to the first item in the list.
*/
template<class T>
T tListIterator<T>::toFirst()
{
	if (!list) {
		return 0;
	}
	return list->firstNode ? (curNode = list->firstNode)->getData() : 0;
}

/*!
  \internal
  Sets the list iterator to point to the last item in the list.
*/
template<class T>
T tListIterator<T>::toLast()
{
	if (!list) {
		return 0;
	}
	return list->lastNode ? (curNode = list->lastNode)->getData() : 0;
}


/*!
  \fn T tListIterator<T>::get() const
  \internal
  Returns the iterator item.
*/


/*!
  \internal
  Moves to the next item (postfix).
*/
template<class T>
T tListIterator<T>::operator()()
{
	if (!curNode)
		return 0;
	T d = curNode->getData();
	curNode = curNode->next;
	return d;
}

/*!
  \internal
  Moves to the next item (prefix).
*/
template<class T>
T tListIterator<T>::operator++()
{
	if (!curNode)
		return 0;
	curNode = curNode->next;
	return curNode ? curNode->getData() : 0;
}

/*!
  \internal
  Moves \e jumps positions forward.
*/
template<class T>
T tListIterator<T>::operator+=(uint32 jumps)
{
	while (curNode && jumps--)
		curNode = curNode->next;
	return curNode ? curNode->getData() : 0;
}

/*!
  \internal
  Moves to the previous item (prefix).
*/
template<class T>
T tListIterator<T>::operator--()
{
	if (!curNode)
		return 0;
	curNode = curNode->prev;
	return curNode ? curNode->getData() : 0;
}

/*!
  \internal
  Moves \e jumps positions backward.
*/
template<class T>
T tListIterator<T>::operator-=(uint32 jumps)
{
	while (curNode && jumps--)
		curNode = curNode->prev;
	return curNode ? curNode->getData() : 0;
}


#endif //_TLIST_