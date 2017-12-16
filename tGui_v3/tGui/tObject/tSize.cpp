#include "tSize.h"

tSize tSize::expandedTo(const tSize & otherSize) const
{
	int32 w = wd > otherSize.wd ? wd : otherSize.wd;
	int32 h = ht > otherSize.ht ? ht : otherSize.ht;
	return tSize(w ,h );
}

tSize tSize::boundedTo(const tSize & otherSize) const
{
	int32 w = wd < otherSize.wd ? wd : otherSize.wd;
	int32 h = ht < otherSize.ht ? ht : otherSize.ht;
	return tSize(w,h);
}

void tSize::transpose()
{
	int32 tmp = wd;
	wd = ht;
	ht = tmp;
}
