#ifndef _TRECTLIST_H_
#define _TRECTLIST_H_
#include "tObject/tRect.h"
#include "tContainter/tList.h"

class tRectList :public tList<tRect*>
{
public:
	void append(tRect* t) { tList<tRect*>::append(t); }
	uint32 count() { return tList<tRect*>::count(); }
	bool insertAt(uint32 index, tRect* obj) { return tList<tRect*>::insertAt(index, obj); }
	tLNode<tRect*> *  unlink(tRect* obj) { return tList<tRect*>::take(obj); }
	bool remove(tRect* obj) { return tList<tRect*>::remove(obj); }
	bool removeLast() { return tList<tRect*>::removeLast(); }
	bool remove(tLNode<tRect*>* node) { return tList<tRect*>::removeNode(node); }
	tRect* at(uint32 index) { return tList<tRect*>::at(index); }
	void clear() { tList<tRect*>::clear(); }
	int32 find(tRect* t) { return tList<tRect*>::findRef(t, true); };
	tRect*  getNext() { return tList<tRect*>::next(); }
	tRect*  getLast() { return tList<tRect*>::last(); }
	tRect*  getFirst() { return tList<tRect*>::first(); }
	void setCurNode(tLNode<tRect*> * node) { tList<tRect*>::setCurNode(node); }
	void setCurIndex(int32 index) { tList<tRect*>::setCurIndex(index); }
	tLNode<tRect*> *  getCurrent() { return tList<tRect*>::currentNode(); }
	int32	  at() const { return tList<tRect*>::at(); };				// get current index

	//virtual int32 compareItems(tRect* item1, tRect* item2)
	//{
	//	return tList<tRect*>::compareItems(item1, item2);
	//};
};



#endif // !_TRECTLIST_H_

