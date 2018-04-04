#ifndef _TFUNCNODE_H_
#define _TFUNCNODE_H_

#include "TGlobal.h"
class tFuncNode
{
	friend class TFuncList;
public:
	func	 getData() { return data; }
private:
	func	   data;
	tFuncNode *prev;
	tFuncNode *next;
	
	tFuncNode(func d) { data = d; prev = NULL; next = NULL; }

};
#endif
