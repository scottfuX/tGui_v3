#ifndef _TTEXTEDIT_H_
#define _TTEXTEDIT_H_

#include "tContainter/tString.h"
#include "tContainter/tStrList.h"

class tTextEdit
{
public:
	tTextEdit();
	~tTextEdit();

	tString* getIndex(int32 x);//获取第x个字符串
	void getCursor(int32 *pLine = NULL, int32 *pOffset = NULL) const;
	void moveCursor(int32 offset);
	void setCursor(int32 line, int32 offset);
	void addText( tString * text);
	void insertText(tString* text);
	void findTextInAll( tString * text,int32 *line, int32 *offset);
	void deleteText( tString &text);
	void deleteText(int32 cursor, int32 pos, int32 length);
	void saveFile();

private:
	int32 curLine;	//坐标行数
	int32 offset;	//偏移
	int32 lineNum;	//行数
	int32 total;	//总数
	int32 letters;	//字母数
	int32 nums;		//数字数
	int32 spaces;	//空格数
	int32 quots;	//引用位置

	tStrList* strList;
};


#endif // !_TTEXTEDIT_H_


