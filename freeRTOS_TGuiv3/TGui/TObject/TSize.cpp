#include "TObject/TSize.h"

TSize TSize::expandedTo(const TSize & otherSize) const
{
	int32 w = wd > otherSize.wd ? wd : otherSize.wd;
	int32 h = ht > otherSize.ht ? ht : otherSize.ht;
	return TSize(w ,h );
}

TSize TSize::boundedTo(const TSize & otherSize) const
{
	int32 w = wd < otherSize.wd ? wd : otherSize.wd;
	int32 h = ht < otherSize.ht ? ht : otherSize.ht;
	return TSize(w,h);
}

void TSize::transpose()
{
	int32 tmp = wd;
	wd = ht;
	ht = tmp;
}
