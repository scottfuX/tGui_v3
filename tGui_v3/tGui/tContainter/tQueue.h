#ifndef _TQUEUE_H_
#define _TQUEUE_H_

#include "tCollection.h"
#include "tList.h"

template<class T> class  tQueue : private tList<T>
{
public:
	tQueue() {}
	tQueue(const tQueue<T> &q)
		: tList<T>(q) {}
	~tQueue()				{ clear(); }
	tQueue<T>& operator=(const tQueue<T> &q)
			{ return (tQueue<T>&)tList<T>::operator=(q); }
	bool  autoDelete() const		{ return tCollection<T>::autoDelete(); }
	void  setAutoDelete(bool del)	{ tCollection<T>::setAutoDelete(del); }
	uint32  count()   const		{ return tList<T>::count(); }
	bool  isEmpty() const		{ return tList<T>::count() == 0; }
	void  enqueue(const T d)	{ tList<T>::append(d); }
	T dequeue()			{ return tList<T>::takeFirst();}
	bool  remove()			{ return tList<T>::removeFirst(); }
	void  clear()			{ tList<T>::clear(); }
	T head()    const		{ return tList<T>::cfirst(); }
	operator T *() const	{ return tList<T>::cfirst(); }
	T current() const		{ return tList<T>::cfirst(); }
private:
	void  deleteItem(void* d) { tList<T>::deleteItem(d); }
};


#endif //_TQUEUE_H_
