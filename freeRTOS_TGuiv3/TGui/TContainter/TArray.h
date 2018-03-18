#ifndef _TGARRAY_H_
#define _TGARRAY_H_

#include "TGlobal.h"

struct tShared
{
	tShared()		{ count = 1; }
	void ref()		{ count++; }
	bool deref()	{ return !--count; }
	uint32 count;
};

class TArray					// generic array
{
	friend class tBuffer;
public:
	struct array_data : public tShared {
			// shared array
	array_data()	{ data = 0; len = 0; }
		char *data; 				// actual array data
		uint32  len;
	};
	TArray();
protected:
	TArray(int32, int32); 			// dummy; does not alloc
	TArray(int32 size); 			// allocate 'size' bytes
	TArray(const TArray &a); 		// shallow copy
	virtual ~TArray();

	TArray&operator=(const TArray &a) { return assign(a); }

	virtual void detach()	{ duplicate(*this); }

	char    *data()	 const	{ return shd->data; }
	uint32	nrefs()	 const	{ return shd->count; }
	uint32	size()	 const	{ return shd->len; }
	bool	isEqual(const TArray &a) const;
	bool	resize(uint32 newsize);

	TArray	&assign(const TArray &a);			   //shadow copy
	TArray	&assign(const char *d, uint32 len);	   //shadow copy
	TArray	&duplicate(const TArray &a);		   //deep copy
	TArray	&duplicate(const char *d, uint32 len); //deep copy
	void	store(const char *d, uint32 len);

	array_data *sharedBlock()	const		{ return shd; }
	void	setSharedBlock(array_data *p) { shd = (array_data*)p; }

	TArray	&setRawData(const char *d, uint32 len);
	void	resetRawData(const char *d, uint32 len);
	
	int32	find(const char *d, uint32 index, uint32 sz) const;
	int32	contains(const char *d, uint32 sz) const;
	
	bool	setExpand(uint32 index, const char *d, uint32 sz);

protected:
	virtual array_data *newData()		    { return new array_data; }
	virtual void	deleteData(array_data *p) { delete p; }

private:
	array_data *shd;
};




#endif // _TGARRAY_H_

