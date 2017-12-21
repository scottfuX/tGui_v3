#ifndef _OBJECT_H_  
#define _OBJECT_H_    


#include "tObject/tEven.h"
#include "tContainter/tString.h"
#include "tContainter/tObjList.h"
#include "tContainter/tConnectList.h"


class tConnectList;
class tObject
{
public:
	tObject(tString* n = 0, tObject* obj = 0);
	virtual ~tObject();
	bool		connect(func  sig, tObject* receiver, func  slot);
	bool		disconnect(func  sig, tObject* receiver, func  slot);
	void		addChild(tObject* child);
	void		remChild(tObject* child);
	void		destroyChild(tObject*);
	void		unlink(tObject* obj);
	void		setParent(tObject* obj) { parents = obj; };
	void		setName(tString* str) { name = str; }
	void		setName(const char* str);
	const char*	getName() { return (const char*)(*name); }
	int32       getNameLen() { return name->length(); }
	tObject*	getParents() { return parents; }
	tObjList*	getChildList() {return childList;}
	tConnectList* getConnections() { return connections; }
	
	virtual void eventFilter(tEvent*)=0;
	
private:
	tString* name;
	tObject* parents;
	tObjList* childList;
	tConnectList* connections;
};




#endif  //!_OBJECT_H_  