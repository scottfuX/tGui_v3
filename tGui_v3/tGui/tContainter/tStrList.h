#ifndef _TSTRLIST_H_
#define _TSTRLIST_H_

#include "tContainter/tString.h"
#include "tContainter/tList.h"


class tStrList :public tList<tString*>
{
public:
	void append(tString* t) { tList<tString*>::append(t); }
	uint32 count() { return tList<tString*>::count(); }
	bool insertAt(uint32 index, tString* obj) { return tList<tString*>::insertAt(index, obj); }
	tLNode<tString*> *  unlink(tString* obj) { return tList<tString*>::take(obj); }
	void relink(tLNode<tString*> * node) { tList<tString*>::relinkNode(node); }
	bool remove(tString* obj) { return tList<tString*>::remove(obj); }
	bool removeLast() { return tList<tString*>::removeLast(); }
	bool remove(tLNode<tString*>* node) { return tList<tString*>::removeNode(node); }
	tString* at(uint32 index) { return tList<tString*>::at(index); }
	void clear() { tList<tString*>::clear(); }
	int32 find(tString* t) { return tList<tString*>::findRef(t, true); };
	tString*  getNext() { return tList<tString*>::next(); }
	tString*  getLast() { return tList<tString*>::last(); }
	tString*  getFirst() { return tList<tString*>::first(); }
	void setCurNode(tLNode<tString*> * node) { tList<tString*>::setCurNode(node); }
	void setCurIndex(int32 index) { tList<tString*>::setCurIndex(index); }
	tLNode<tString*> *  getCurrent() { return tList<tString*>::currentNode(); }
	int32 getCurIndex() { return tList<tString*>::currentIndex(); }
	virtual int32 compareItems(tString* item1, tString* item2)
	{
		return tList<tString*>::compareItems(item1, item2);
	};
};



#endif // !_TSTRLIST_H_


