#ifndef _TOBJLIST_H_
#define _TOBJLIST_H_

#include "tObject/tObject.h"
#include "tContainter/tList.h"

class tObject;

	class tObjList :public tList<tObject*>
	{
	public:
		void append(tObject* t) { tList<tObject*>::append(t); }
		uint32 count() { return tList<tObject*>::count(); }
		bool insertAt(uint32 index, tObject* obj) { return tList<tObject*>::insertAt(index, obj); }
		tLNode<tObject*> *  unlink(tObject* obj) { return tList<tObject*>::take(obj); }
		bool remove(tObject* obj) { return tList<tObject*>::remove(obj); }
		bool removeLast() { return tList<tObject*>::removeLast(); }
		bool remove(tLNode<tObject*>* node) { return tList<tObject*>::removeNode(node); }
		tObject* at(uint32 index) { return tList<tObject*>::at(index); }
		void clear() { tList<tObject*>::clear(); }
		int32 find(tObject* t) { return tList<tObject*>::findRef(t, true); };
		tObject*  getNext() { return tList<tObject*>::next(); }
		tObject*  getLast() { return tList<tObject*>::last(); }
		tObject*  getFirst() { return tList<tObject*>::first(); }
		tLNode<tObject*> *  getCurrent() { return tList<tObject*>::currentNode(); }
		virtual int32 compareItems(tObject* item1, tObject* item2)
		{
			return tList<tObject*>::compareItems(item1, item2);
		};
	};

	
	
#endif // !_TOBJLIST_H_

