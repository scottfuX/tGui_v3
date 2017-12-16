#ifndef _OBJECT_H_  
#define _OBJECT_H_    

#include "tContainter/tStack.h"
#include "tContainter/tList.h"
#include "tContainter/tObjList.h"

//class tObject;
class connection
{
	friend class tConnectList;
	friend class tObject;
private:
	void(*signal) ();
	tFuncList* slotList;
public:
	connection(void(*sig) ());
	~connection() {}
	void addSlot(void(*slot)()) { slotList->append(slot); }
	void active();
};



class tObject
{
public:
	tObject(tString* n ,tObject* obj= NULL);
	virtual ~tObject();
	bool		connect(void(*sig)(), void(*slot)());
	bool		disconnect(void(*sig)(), void(*slot)());
	void		addChild(tObject* child);
	void		remChild(tObject* child);
	void		setParent(tObject* obj) { parents = obj; };
	tObject*	getParents() { return parents; }
	
	virtual void eventFilter()=0;

	
private:
	tString* name;
	tObject* parents;
	tObjList* childList;
	tConnectList* connections;
};


#endif  //!_OBJECT_H_  