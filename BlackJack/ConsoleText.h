#pragma once
#include "Vec.h"
#include <string>
struct CMDText
{
private:
	iVec2D offset;
	std::wstring text;
public:
	CMDText();
	CMDText(iVec2D off, std::wstring tex);
	
	void SetText(std::wstring text);
	void SetOffset(iVec2D offset);
	void Print();
	void Clear();
};