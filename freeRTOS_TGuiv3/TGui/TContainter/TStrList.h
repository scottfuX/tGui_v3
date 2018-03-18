#ifndef _TSTRLIST_H_
#define _TSTRLIST_H_

#include "TContainter/TString.h"
#include "TContainter/TList.h"


class tStrList :public TList<TString*>
{
public:
	void append(TString* t) { TList<TString*>::append(t); }
	virtual uint32 count() { return TList<TString*>::count(); }
	bool insertAt(uint32 index, TString* obj) { return TList<TString*>::insertAt(index, obj); }
	tLNode<TString*> *  unlink(TString* obj) { return TList<TString*>::take(obj); }
	void relink(tLNode<TString*> * node) { TList<TString*>::relinkNode(node); }
	bool remove(TString* obj) { return TList<TString*>::remove(obj); }
	bool removeLast() { return TList<TString*>::removeLast(); }
	bool remove(tLNode<TString*>* node) { return TList<TString*>::removeNode(node); }
	TString* at(uint32 index) { return TList<TString*>::at(index); }
	virtual	void clear() { TList<TString*>::clear(); }
	int32 find(TString* t) { return TList<TString*>::findRef(t, true); };
	TString*  getNext() { return TList<TString*>::next(); }
	TString*  getLast() { return TList<TString*>::last(); }
	TString*  getFirst() { return TList<TString*>::first(); }
	void setCurNode(tLNode<TString*> * node) { TList<TString*>::setCurNode(node); }
	void setCurIndex(int32 index) { TList<TString*>::setCurIndex(index); }
	tLNode<TString*> *  getCurrent() { return TList<TString*>::currentNode(); }
	int32 getCurIndex() { return TList<TString*>::currentIndex(); }
	virtual int32 compareItems(TString* item1, TString* item2)
	{
		return TList<TString*>::compareItems(item1, item2);
	};
};



#endif // !_TSTRLIST_H_


