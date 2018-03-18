#ifndef _TCOLLECTION_H_
#define _TCOLLECTION_H_


#include "TGlobal.h"



template <class T>
class  tCollection			// inherited by all collections
{
public:
	bool autoDelete()	const	       { return del_item; }
	void setAutoDelete(bool enable)  { del_item = enable; }

	virtual uint32  count() const = 0;
	virtual void  clear() = 0; 			// delete all objects

protected :
	tCollection() { del_item = false; }		// no deletion of objects
	tCollection(const tCollection &) { del_item = false; }
	virtual ~tCollection() {}

	bool del_item; 				// default FALSE

	virtual T	     newItem(T);   		// create object
	virtual void     deleteItem(void*);  		// delete object
};

/*!
  Virtual function that creates a copy of an object that is about to
  be inserted into the collection.

  The default implementation returns the \e d pointer, i.e. no copy
  is made.

  This function is seldom reimplemented in the collection template
  classes. It is not common practice to make a copy of something
  that is being inserted.

  \sa deleteItem()
*/
template<class T>
T tCollection<T>::newItem(T d)
{
	return d;					// just return reference
}

/*!
  Virtual function that deletes an item that is about to be removed from
  the collection.

  The default implementation deletes \e d pointer if and only if
  auto-delete has been enabled.

  This function is always reimplemented in the collection template
  classes.

  \sa newItem(), setAutoDelete()
*/
template<class T>
void tCollection<T>::deleteItem(void* d)
{
	if (del_item)
	{
		delete d; 				// default operation
	}	
}


#endif // _TCOLLECTION_H_
