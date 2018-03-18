#ifndef _TSTACK_H_
#define _TSTACK_H_

#include "tCollection.h"
#include "tList.h"

template<class T> class  tStack : private tList<T>
{
public:
	tStack() {}
	tStack(const tStack<T> &s): tList<T>(s) {}
	~tStack(){ clear(); }
	tStack<T> &operator=(const tStack<T> &s){ return (tStack<T>&)tList<T>::operator=(s); }
	bool  autoDelete() const		{ return tCollection<T>::autoDelete(); }
	void  setAutoDelete(bool del)	{ tCollection<T>::setAutoDelete(del); }
	uint32  count()   const		{ return tList<T>::count(); }
	bool  isEmpty() const		{ return tList<T>::count() == 0; }
	void  push(const T *d)		{ tList<T>::insertAt(0, T(d)); }
	T 	  pop()				{ return tList<T>::takeFirst(); }
	bool  remove()			{ return tList<T>::removeFirst(); }
	void  clear()			{ tList<T>::clear(); }
	T 	  top()	    const		{ return (T *)tList<T>::cfirst(); }
	operator T *() const	{ return tList<T>::cfirst(); }
	T current() const		{ return tList<T>::cfirst(); }
private:
	void  deleteItem(void* d) { tList<T>::deleteItem(d);}
};


 
#endif /* _TSTACK_ */
 