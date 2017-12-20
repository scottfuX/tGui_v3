#ifndef _OBJECT_H_  
#define _OBJECT_H_    


#include "tContainter/tStack.h"
#include "tContainter/tList.h"
#include "tObject/tEven.h"
#include "tObject/connection.h"
#include "tContainter/tConnectList.h"
#include "tContainter/tObjList.h"



class tObject
{
public:
	tObject(tString* n = 0,tObject* obj= 0);
	virtual ~tObject();
	bool		connect(void(*sig)(), void(*slot)());
	bool		disconnect(void(*sig)(), void(*slot)());
	void		addChild(tObject* child);
	void		remChild(tObject* child);
	void		destroyChild(tObject*);
	void		unlink(tObject* obj);
	void		setParent(tObject* obj) { parents = obj; };
	tObject*	getParents() { return parents; }
	tObjList*	getChildList() {return childList;}
	void		visitAll(tObject* obj, void(*visit)(tObject* obj));
	void        showAll() { showAll(this); }
	virtual void	show() = 0;
	virtual void eventFilter(tEvent*)=0;
	
private:
	tString* name;
	tObject* parents;
	tObjList* childList;
	tConnectList* connections;

	void	showAll(tObject*);

};


#endif  //!_OBJECT_H_  