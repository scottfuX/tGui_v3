#ifndef _TFuncList_H_
#define _TFuncList_H_

#include "TGlobal.h"
#include "TContainter/tFuncNode.h"

class TFuncList
{
public:
	TFuncList();
	~TFuncList() ;
	void append(func  t);// { TList<func >::append(t); }
	uint32  count() const { return numNodes; };
	bool remove(func  t = 0);// { return TList<func  >::remove(t); }
	func  at(uint32 index) { tFuncNode *n = locate(index); return n ? n->data : 0; };
	void clear();// { TList<func >::clear(); }
	int32 find(func  t);// { return TList<func >::findRef(t, true); };
	bool insertAt(uint32 index, func d);
	void prepend(func d);
	tFuncNode*locate(uint32 index);
private:
	tFuncNode *firstNode;				// first node
	tFuncNode *lastNode;				// last node
	tFuncNode *curNode;				// current node
	int32	   curIndex;				// current index
	uint32    numNodes;				// number of nodes

	tFuncNode* unlink();
};


#endif // !_TFuncList_H_

