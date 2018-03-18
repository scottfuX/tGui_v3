#ifndef _TBTREE_H_
#define _TBTREE_H_

template <class T>
	class tBTree;
template<class T>
class  tBTNode
{
	friend class tBTree<T>;
public:
	T	    getData() { return data; }
private:
	T	    data;
	tBTNode<T> *lChild;
	tBTNode<T> *rChild;
	tBTNode(const T &d):data(d),lChild(NULL), rChild(NULL){}
};

template <class T>
class tBTree
{
private:
	tBTNode<T> *root;

	void clear(tBTNode<T> *pRoot);
	uint32 height(tBTNode<T> *pRoot) const;
	uint32 count(tBTNode<T> *pRoot) const;

public:
	tBTree(T d);
	~tBTree(void);
	tBTNode<T>*  getRoot() { return root; };
	void addLChild(tBTNode<T> *pRoot, T d);
	void addRChild(tBTNode<T> *pRoot, T d);
	void preOrder(tBTNode<T> *pRoot, void(*visit)(tBTNode<T>* bnode)) const;
	void inOrder(tBTNode<T> *pRoot, void(*visit)(tBTNode<T>* bnode)) const;
	void postOrder(tBTNode<T> *pRoot, void(*visit)(tBTNode<T>* bnode)) const;
	uint32 getHeight(void) const;
	uint32 getNumberOfNode(void) const;
};



template <class T>
tBTree<T>::tBTree(T d)
{
	root = new tBTNode<T>(d);
}


template <class T>
inline tBTree<T>::~tBTree(void)
{
	clear(root);
}

template <class T>
void tBTree<T>::addLChild(tBTNode<T> *pRoot, T d)
{
	if (pRoot->lChild == NULL)
		pRoot->lChild = new tBTNode<T>(d);

}

template <class T>
void tBTree<T>::addRChild(tBTNode<T> *pRoot, T d)
{
	if (pRoot->rChild == NULL)
		pRoot->rChild = new tBTNode<T>(d);
}
//
// 删除所有节点. 
//
template <class T>
void tBTree<T>::clear(tBTNode<T> *pRoot)
{
	if (NULL != pRoot)
	{
		clear(pRoot->lChild);
		clear(pRoot->rChild);
		delete pRoot;
	}
}

//
// 前序遍历. 
//
template <class T>
void tBTree<T>::preOrder(tBTNode<T> *pRoot, void(*visit)(tBTNode<T>* bnode)) const
{
	if (NULL != pRoot)
	{
		visit(pRoot);
		preOrder(pRoot->lChild, visit);
		preOrder(pRoot->rChild, visit);
	}
}

//
// 中序遍历. 
//
template <class T>
void tBTree<T>::inOrder(tBTNode<T> *pRoot,void(*visit)(tBTNode<T>* bnode)) const
{
	if (NULL != pRoot)
	{
		inOrder(pRoot->lChild, visit);
		visit(pRoot);
		inOrder(pRoot->rChild, visit);
	}
}

//
// 后序遍历. 
//
template <class T>
void tBTree<T>::postOrder(tBTNode<T> *pRoot,void(*visit)(tBTNode<T>* bnode)) const
{
	if (NULL != pRoot)
	{
		postOrder(pRoot->lChild, visit);
		postOrder(pRoot->rChild, visit);
		visit(pRoot);
	}
}

//
// 通过后序遍历方式计算二叉树高度. 
//
template <class T>
uint32 tBTree<T>::height(tBTNode<T> *pRoot) const
{
	static uint32 height = 0, leftHeight = 0, rightHeight = 0;

	if (NULL != pRoot)
	{
		leftHeight = height(pRoot->lChild);
		rightHeight = height(pRoot->rChild);

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
uint32 tBTree<T>::count(tBTNode<T> *pRoot) const
{
	static uint32 counter = 0;

	if (NULL != pRoot) {
		counter = count(pRoot->lChild) + count(pRoot->rChild) + 1;
	}
	else {
		counter = 0;
	}
	return counter;
}


template <class T>
uint32 tBTree<T>::getHeight(void) const
{
	return height(root);
}


template <class T>
uint32 tBTree<T>::getNumberOfNode(void) const
{
	return count(root);
}

#endif //_TBTREE_