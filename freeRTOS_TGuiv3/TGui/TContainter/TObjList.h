#ifndef _TOBJLIST_H_
#define _TOBJLIST_H_

#include "TObject/TObject.h"
#include "TContainter/TList.h"

class TObject;

	class TObjList :public TList<TObject*>
	{
	public:
		void append(TObject* t) { TList<TObject*>::append(t); }
		virtual uint32 count() { return TList<TObject*>::count(); }
		bool insertAt(uint32 index, TObject* obj) { return TList<TObject*>::insertAt(index, obj); }
		tLNode<TObject*> *  unlink(TObject* obj) { return TList<TObject*>::take(obj); }
		void relink(tLNode<TObject*> * node) { TList<TObject*>::relinkNode(node); }
		bool remove(TObject* obj) { return TList<TObject*>::remove(obj); }
		bool removeLast() { return TList<TObject*>::removeLast(); }
		bool remove(tLNode<TObject*>* node) { return TList<TObject*>::removeNode(node); }
		TObject* at(uint32 index) { return TList<TObject*>::at(index); }
		virtual void clear() { TList<TObject*>::clear(); }
		int32 find(TObject* t) { return TList<TObject*>::findRef(t, true); };
		TObject*  getNext() { return TList<TObject*>::next(); }
		TObject*  getLast() { return TList<TObject*>::last(); }
		TObject*  getFirst() { return TList<TObject*>::first(); }
		void setCurNode(tLNode<TObject*> * node) { TList<TObject*>::setCurNode(node); }
		void setCurIndex(int32 index) { TList<TObject*>::setCurIndex(index); }
		tLNode<TObject*> *  getCurrent() { return TList<TObject*>::currentNode(); }
		int32 getCurIndex() { return TList<TObject*>::currentIndex(); }
		virtual int32 compareItems(TObject* item1, TObject* item2)
		{
			return TList<TObject*>::compareItems(item1, item2);
		};
	};

	
	
#endif // !_TOBJLIST_H_

