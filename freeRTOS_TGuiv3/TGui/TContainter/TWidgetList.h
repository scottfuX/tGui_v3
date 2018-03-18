#ifndef _TWIDGETLIST_H_
#define _TWIDGETLIST_H_
#include "TContainter/TList.h"
#include "TWidget/TWidget.h"

class TWidget;
class tWidgetList :public TList<TWidget*>
{
public:
	void append(TWidget* t) { TList<TWidget*>::append(t); }
	virtual uint32 count() { return TList<TWidget*>::count(); }
	bool insertAt(uint32 index, TWidget* obj) { return TList<TWidget*>::insertAt(index, obj); }
	tLNode<TWidget*> *  unlink(TWidget* obj) { return TList<TWidget*>::take(obj); }
	bool remove(TWidget* obj = 0) { return TList<TWidget*>::remove(obj); }
	bool removeLast() { return TList<TWidget*>::removeLast(); }
	bool remove(tLNode<TWidget*>* node) { return TList<TWidget*>::removeNode(node); }
	TWidget* at(uint32 index) { return TList<TWidget*>::at(index); }
	virtual void clear() { TList<TWidget*>::clear(); }
	int32 find(TWidget* t) { return TList<TWidget*>::findRef(t, true); };
	TWidget*  getNext() { return TList<TWidget*>::next(); }
	TWidget*  getLast() { return TList<TWidget*>::last(); }
	TWidget*  getFirst() { return TList<TWidget*>::first(); }
	void setCurNode(tLNode<TWidget*> * node) { TList<TWidget*>::setCurNode(node); }
	void setCurIndex(int32 index) { TList<TWidget*>::setCurIndex(index); }
	tLNode<TWidget*> *  getCurrent() { return TList<TWidget*>::currentNode(); }
	int32	   currentIndex() const { return TList<TWidget*>::currentIndex(); };				// get current index

	//virtual int32 compareItems(TWidget* item1, TWidget* item2)
	//{
	//	return TList<TWidget*>::compareItems(item1, item2);
	//};
};



#endif // !_TWIDGETLIST_H_

