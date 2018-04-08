#ifndef _TQUEUE_H_
#define _TQUEUE_H_

#include "tCollection.h"
#include "TList.h"

template<class T> class  TQueue : private TList<T>
{
public:
	TQueue() {}
	TQueue(const TQueue<T> &q)
		: TList<T>(q) {}
	~TQueue()				{ clear(); }
	TQueue<T>& operator=(const TQueue<T> &q)
			{ return (TQueue<T>&)TList<T>::operator=(q); }
	bool  autoDelete() const		{ return tCollection<T>::autoDelete(); }
	void  setAutoDelete(bool del)	{ tCollection<T>::setAutoDelete(del); }
	uint32  count()   const		{ return TList<T>::count(); }
	bool  isEmpty() const		{ return TList<T>::count() == 0; }
	void  enqueue(const T d)	{ TList<T>::append(d); }
	T dequeue()			{ return TList<T>::takeFirst();}
	bool  remove()			{ return TList<T>::removeFirst(); }
	void  clear()			{ TList<T>::clear(); }
	T head()    const		{ return TList<T>::cfirst(); }
	operator T *() const	{ return TList<T>::cfirst(); }
	T current() const		{ return TList<T>::cfirst(); }
private:
	void  deleteItem(void* d) { TList<T>::deleteItem(d); }
};


#endif //_TQUEUE_H_
