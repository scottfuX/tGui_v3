#ifndef _TFUNCLIST_H_
#define _TFUNCLIST_H_

#include "tGlobal.h"
#include "tContainter/tFuncNode.h"

class tFuncList
{
public:
	tFuncList();
	~tFuncList() { clear(); }
	void append(func  t);// { tList<func >::append(t); }
	uint32  count() const { return numNodes; };
	bool remove(func  t = 0);// { return tList<func  >::remove(t); }
	func  at(uint32 index) { tFuncNode *n = locate(index); return n ? n->data : 0; };
	void clear();// { tList<func >::clear(); }
	int32 find(func  t);// { return tList<func >::findRef(t, true); };
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


#endif // !_TFUNCLIST_H_

