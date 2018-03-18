#ifndef _OBJECT_H_  
#define _OBJECT_H_    

#include "TObject/TEven.h"
#include "TContainter/TString.h"
#include "TContainter/TObjList.h"
#include "TContainter/TConnectList.h"


class TConnectList;
class TObject
{
public:
	TObject(const char* n = 0, TObject* obj = 0);
	virtual ~TObject();
	bool		connect(func  sig, TObject* receiver, func  slot);
	bool		disconnect(func  sig, TObject* receiver, func  slot);
	void		addChild(TObject* child);
	void		remChild(TObject* child);
	void		destroyChild(TObject*);
	tLNode<TObject*> *		unlink(TObject* obj);
	void			relink(tLNode<TObject*> * node);
	void		regist(TObject* obj);
	void		logout(TObject* obj);

	void		setParent(TObject* obj) { parents = obj; };
	void		setName(TString* str) { delete name; name = str; }
	void		setName(const char* str);
	const char*	getName() { return (const char*)(*name); }
	int32       getNameLen() { return name->length(); }
	TObject*	getParents() { return parents; }
	TObjList*	getChildList() {return childList;}
	TConnectList* getConnections() { return TConnections; }
	
	virtual void eventFilter(TEvent*)=0;
protected:
	void callSlot(func sig, int32 d1, int32 d2); //寻找connect 呼出slot
private:
	TString* name;
	TObject* parents;
	TObjList* childList;
	TConnectList* TConnections;
};




#endif  //!_OBJECT_H_  
