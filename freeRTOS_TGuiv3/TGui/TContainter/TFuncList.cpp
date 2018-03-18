#include "TContainter/TFuncList.h"


TFuncList::TFuncList()
{
	firstNode = lastNode = curNode = 0; 		// initialize list
	numNodes = 0;
	curIndex = -1;
}

void TFuncList::append(func d)
{
	register tFuncNode *n = new tFuncNode(d);
	n->next = 0;
	if ((n->prev = lastNode)!=0)			// list is not empty
		lastNode->next = n;
	else					// initialize list
		firstNode = n;
	lastNode = curNode = n; 			// curNode affected
	curIndex = numNodes;
	numNodes++;
}

bool TFuncList::insertAt(uint32 index, func d)
{
	if (index == 0) {
		// insert at head of list
		prepend(d);
		return true;
	}
	else if (index == numNodes) {
		// append at tail of list
		append(d);
		return true;
	}
	tFuncNode* nextNode = locate(index);
	if (!nextNode)				// illegal position
		return false;
	tFuncNode *prevNode = nextNode->prev;
	register tFuncNode *n = new tFuncNode(d);
	nextNode->prev = n;
	prevNode->next = n;
	n->prev = prevNode; 				// link new node into list
	n->next = nextNode;
	curNode = n; 				// curIndex set by locate()
	numNodes++;
	return true;
}

void TFuncList::prepend(func d)
{
	register tFuncNode *n = new tFuncNode(d);

	n->prev = 0;
	if ((n->next = firstNode)!=0)		// list is not empty
		firstNode->prev = n;
	else					// initialize list
		lastNode = n;
	firstNode = curNode = n; 			// curNode affected
	numNodes++;
	curIndex = 0;
}

tFuncNode *TFuncList::locate(uint32 index)
{
	if (index == (uint32)curIndex)		// current node ?
		return curNode;
	if (!curNode && firstNode) {
		// set current node
		curNode = firstNode;
		curIndex = 0;
	}
	register tFuncNode *node;
	int32	 distance = index - curIndex; 		// node distance to cur node
	bool forward; 				// direction to traverse

	if (index >= numNodes) {
		return 0;
	}

	if (distance < 0)
		distance = -distance;
	if ((uint32)distance < index && (uint32)distance < numNodes - index) {
		node = curNode; 			// start from current node
		forward = index >(uint32)curIndex;
	}
	else if (index < numNodes - index) {
		// start from first node
		node = firstNode;
		distance = index;
		forward = true;
	}
	else {
		// start from last node
		node = lastNode;
		distance = numNodes - index - 1;
		if (distance < 0)
			distance = 0;
		forward = false;
	}
	if (forward) {
		// now run through nodes
		while (distance--)
			node = node->next;
	}
	else {
		while (distance--)
			node = node->prev;
	}
	curIndex = index; 				// must update index
	return curNode = node;
}


int32 TFuncList::find(func d)
{
	register tFuncNode *n;
	int32	  index;
	n = firstNode;
	index = 0;
	while (n && n->data != d) {
		// find exact match
		n = n->next;
		index++;
	}
	curNode = n;
	curIndex = n ? index : -1;
	return curIndex;				// return position of item
}

void TFuncList::clear()
{
	register tFuncNode *n = firstNode;
	tFuncNode *prevNode;
	while (n)
	{				// for all nodes ...
		prevNode = n;
		n = n->next;
		delete prevNode; 			// deallocate node
	}
	firstNode = lastNode = curNode = 0; 		// initialize list
	numNodes = 0;
	curIndex = -1;
}

bool TFuncList::remove(func d)
{
	if (d) {
		// find the item
		if (find(d) == -1)
			return false;
	}
	tFuncNode *n = unlink(); 			// unlink node
	if (!n)
		return false;
	delete n;
	curNode = firstNode;
	curIndex = curNode ? 0 : -1;
	return true;
}


tFuncNode* TFuncList::unlink()
{
	if (curNode == 0)				// null current node
		return 0;
	register tFuncNode *n = curNode; 		// unlink this node
	if (n == firstNode) {
		// removing first node ?
		if ((firstNode = n->next)!=0) {
			firstNode->prev = 0;
		}
		else {
			lastNode = curNode = 0; 		// list becomes empty
			curIndex = -1;
		}
	}
	else {
		if (n == lastNode) {
			// removing last node ?
			lastNode = n->prev;
			lastNode->next = 0;
		}
		else {
			// neither last nor first node
			n->prev->next = n->next;
			n->next->prev = n->prev;
		}
	}
	if (n->next) {
		// change current node
		curNode = n->next;
	}
	else if (n->prev) {
		curNode = n->prev;
		curIndex--;
	}
	numNodes--;
	return n;
}
