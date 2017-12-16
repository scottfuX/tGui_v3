#ifndef _TCBTREE_H_
#define _TCBTREE_H_

template <class T>
class tCBTree;
template<class T>
class  tCBTNode
{
	friend class tCBTree<T>;
public:
	T	getData() { return data; }
	tCBTNode<T>*	getChild() { return child; }
	tCBTNode<T>*	getBrother() { return brother; }
	tCBTNode<T>*	getParents() { return parents; }
private:
	T	    data;
	tCBTNode<T> *child;
	tCBTNode<T> *brother;
	tCBTNode<T> *parents;
	tCBTNode(const T &d, tCBTNode<T>* p = NULL) {data = d; child = NULL; brother = NULL; parents = p; }
};

template <class T>
class tCBTree
{
private:
	tCBTNode<T> *root;

	void clear(tCBTNode<T> *pRoot);
	uint32 height(tCBTNode<T> *pRoot) const;
	uint32 count(tCBTNode<T> *pRoot) const;

public:
	tCBTree(T d);
	~tCBTree(void);
	tCBTNode<T>*  getRoot() { return root; };
	void addChild(tCBTNode<T> *pRoot, T d);
	void addBrother(tCBTNode<T> *pRoot, T d);
	void preOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const;
	void inOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const;
	void postOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const;
	uint32 getHeight(void) const;
	uint32 getNumberOfNode(void) const;
};



template <class T>
tCBTree<T>::tCBTree(T d)
{
	root = new tCBTNode<T>(d);
}


template <class T>
inline tCBTree<T>::~tCBTree(void)
{
	clear(root);
}

template <class T>
void tCBTree<T>::addChild(tCBTNode<T> *pRoot, T d)
{
	if (pRoot->child == NULL)
		pRoot->child = new tCBTNode<T>(d,pRoot);
	else
	{
		tCBTNode<T>* node = new tCBTNode<T>(d,pRoot);
		node->brother = pRoot->child;
		pRoot->child = node;
	}

}

template <class T>
void tCBTree<T>::addBrother(tCBTNode<T> *pRoot, T d)
{
	if (pRoot->brother == NULL)
		pRoot->brother = new tCBTNode<T>(d,pRoot);
	else
	{
		tCBTNode<T>* node = new tCBTNode<T>(d,pRoot);
		node->brother = pRoot->brother;
		pRoot->brother = node;
	}
}
//
// 删除所有节点. 
//
template <class T>
void tCBTree<T>::clear(tCBTNode<T> *pRoot)
{
	if (NULL != pRoot)
	{
		clear(pRoot->child);
		clear(pRoot->brother);
		delete pRoot;
	}
}

//
// 前序遍历. 
//
template <class T>
void tCBTree<T>::preOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const
{
	if (NULL != pRoot)
	{
		visit(pRoot);
		preOrder(pRoot->child,visit);
		preOrder(pRoot->brother,visit);
	}
}

//
// 中序遍历. 
//
template <class T>
void tCBTree<T>::inOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const
{
	if (NULL != pRoot)
	{
		inOrder(pRoot->child,visit);
		visit(pRoot);
		inOrder(pRoot->brother,visit);
	}
}

//
// 后序遍历. 
//
template <class T>
void tCBTree<T>::postOrder(tCBTNode<T> *pRoot, void(*visit)(tCBTNode<T>* cbnode)) const
{
	if (NULL != pRoot)
	{
		postOrder(pRoot->child, visit);
		postOrder(pRoot->brother, visit);
		visit(pRoot);
	}
}

//
// 通过后序遍历方式计算二叉树高度. 
//
template <class T>
uint32 tCBTree<T>::height(tCBTNode<T> *pRoot) const
{
	static uint32 height = 0, leftHeight = 0, rightHeight = 0;

	if (NULL != pRoot)
	{
		leftHeight = height(pRoot->child);
		rightHeight = height(pRoot->brother);

		height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}
	else {
		height = 0;
	}

	return height;
}

//
// 通过前序遍历方式计算二叉树节点数. 
//
template <class T>
uint32 tCBTree<T>::count(tCBTNode<T> *pRoot) const
{
	static uint32 counter = 0;

	if (NULL != pRoot) {
		counter = count(pRoot->child) + count(pRoot->brother) + 1;
	}
	else {
		counter = 0;
	}
	return counter;
}


template <class T>
uint32 tCBTree<T>::getHeight(void) const
{
	return height(root);
}


template <class T>
uint32 tCBTree<T>::getNumberOfNode(void) const
{
	return count(root);
}



#endif //_TCBTREE_H_