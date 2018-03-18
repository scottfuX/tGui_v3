#include "TWidget/TTextEdit.h"



TTextEdit::TTextEdit()
{
	offset = 0;
	curLine = 0;
	lineNum = 0;
	total = 0;
	quots = 0;
	spaces = 0;
	letters = 0;
	nums = 0;
	strList = new tStrList();
}


//获取第x个字符串
TString* TTextEdit::getIndex(int32 x) 
{
	if (x < 0)
		x = 0;
	if (x > lineNum)
		x = lineNum;
	TString* str;
	str = strList->getFirst();
	if (!x)
		return str;
	for (int32 num = 1; num != x && (str = strList->getNext()); num++);
	if(str)
		return  str;
	return NULL;
}

TTextEdit::~TTextEdit()
{
	delete strList;
}

void TTextEdit::getCursor(int32 *pLine , int32 *pOffset ) const
{
	*pLine = curLine;
	*pOffset = offset;
}

void TTextEdit::moveCursor(int32 offset)
{
	TString*  index = getIndex(curLine);
	if (!index)
		return;
	this->offset += offset; //加上偏移
	int32 len;
	while (index->length() < this->offset) //若比当前行要长，就换行
	{
		len = index->length();
		index = strList->getNext(); //若到最后了，就直接定位为下一个 
		if (!index)
		{
			this->offset = len;
			return;
		}
		this->offset -= index->length();
		curLine++;	
	}
}

void TTextEdit::setCursor(int32 line, int32 offset)
{
	if (line > lineNum)
		line = lineNum;
	curLine = line;
	if (offset < 0)
		offset = 0;
	if (offset > getIndex(line)->length())
		offset = getIndex(line)->length();
	offset = offset;
}

void TTextEdit::addText(TString * text)
{
	strList->append(text);
	total += text->length();
	for (int i = 0; i<text->length(); i++) 
	{
		if ((*text)[i] == ' ') 
			spaces++; 
		else if ((*text)[i] >= '0' && (*text)[i] <= '9')
			nums++; 
		else if ((*text)[i] >= 'a'&& (*text)[i] <= 'z') 
			letters++; 
		else if ((*text)[i] >= 'A'&& (*text)[i] <= 'Z') 
			letters++; 
		else
			quots++;
	}
	lineNum++;
}

void TTextEdit::insertText(TString* text)
{
	int32 len = text->length();
	total += len;
	for (int i = 0; i<len; i++)
	{
		if ((*text)[i] == ' ')
			spaces++;
		else if ((*text)[i] >= '0' && (*text)[i] <= '9')
			nums++;
		else if ((*text)[i] >= 'a' && (*text)[i] <= 'z')
			letters++;
		else if ((*text)[i] >= 'A' && (*text)[i] <= 'Z')
			letters++;
		else
			quots++;
	
	}
	if (strList->count() == 0)
	{
		strList->append(text);
		offset = len;
		return;
	}
	TString* str = getIndex(curLine);
	str->insert(offset,(*text),len);
	offset += len;
	return ;
}

void TTextEdit::findTextInAll(TString * text, int32 *line, int32 *offset)
{
	TString* str;
	int32 tmpoff;
	int32 num;
	str = strList->getFirst();
	tmpoff = str->find(*text);
	if (tmpoff >= 0)
	{
		*line = 0;
		*offset = tmpoff;
		return;
	}
	for ( num = 1; (str = strList->getNext()); num++) 
	{
		tmpoff = str->find(*text);
		if (tmpoff >= 0)
		{
			*line = num;
			*offset = tmpoff;
			return ;
		}
	}
	*offset = -1;
	return ;
}

void TTextEdit::deleteText(TString &text)
{
	int32 line = 0, offset = -1;
	findTextInAll(&text, &line, &offset);
	while (1) { //把文本框内所有的text都删除
		if (offset == -1)
			break;
		deleteText(line, offset, text.length());
		findTextInAll(&text, &line, &offset);
	}
}

void TTextEdit::deleteText(int32 curline, int32 pos, int32 length)
{
	total -= length;
	TString* text = getIndex(curline);
	int32 len = MIN(text->length(), pos + length);
	for (int i = pos; i<len; i++) {
		if ((*text)[i] == ' ') 
			spaces--; 
		else if ((*text)[i] >= '0'&&(*text)[i] <= '9') 
			nums--; 
		else if ((*text)[i] >= 'a'&&(*text)[i] <= 'z') 
			letters--; 
		else if ((*text)[i] >= 'A'&&(*text)[i] <= 'Z') 
			letters--; 
		else
			quots--;
	}
	text->remove(pos, len);
}

void TTextEdit::saveFile()
{
	//需要实现输入输出流
}