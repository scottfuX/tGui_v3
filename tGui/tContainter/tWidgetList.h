#ifndef _TWIDGETLIST_H_
#define _TWIDGETLIST_H_
#include "tContainter/tList.h"
#include "tObject/tWidget.h"

class tWidget;
class tWidgetList :public tList<tWidget*>
{
public:
	void append(tWidget* t) { tList<tWidget*>::append(t); }
	uint32 count() { return tList<tWidget*>::count(); }
	bool insertAt(uint32 index, tWidget* obj) { return tList<tWidget*>::insertAt(index, obj); }
	tLNode<tWidget*> *  unlink(tWidget* obj) { return tList<tWidget*>::take(obj); }
	bool remove(tWidget* obj = 0) { return tList<tWidget*>::remove(obj); }
	bool removeLast() { return tList<tWidget*>::removeLast(); }
	bool remove(tLNode<tWidget*>* node) { return tList<tWidget*>::removeNode(node); }
	tWidget* at(uint32 index) { return tList<tWidget*>::at(index); }
	void clear() { tList<tWidget*>::clear(); }
	int32 find(tWidget* t) { return tList<tWidget*>::findRef(t, true); };
	tWidget*  getNext() { return tList<tWidget*>::next(); }
	tWidget*  getLast() { return tList<tWidget*>::last(); }
	tWidget*  getFirst() { return tList<tWidget*>::first(); }
	void setCurNode(tLNode<tWidget*> * node) { tList<tWidget*>::setCurNode(node); }
	void setCurIndex(int32 index) { tList<tWidget*>::setCurIndex(index); }
	tLNode<tWidget*> *  getCurrent() { return tList<tWidget*>::currentNode(); }
	int32	   currentIndex() const { return tList<tWidget*>::currentIndex(); };				// get current index

	//virtual int32 compareItems(tWidget* item1, tWidget* item2)
	//{
	//	return tList<tWidget*>::compareItems(item1, item2);
	//};
};



#endif // !_TWIDGETLIST_H_

