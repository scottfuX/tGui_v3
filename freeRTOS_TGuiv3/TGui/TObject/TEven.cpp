#include "TObject/TEven.h"

//void qRemovePostedEvent(TEvent *);		// defined in qapplication_xxx.cpp

void TEvent::peErrMsg()				// posted event error message
{
	printf(" delete -- event !!! \n");
	//qRemovePostedEvent(this);
}

