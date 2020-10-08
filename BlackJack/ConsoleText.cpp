#include "ConsoleText.h"
#include <iostream>
#include "TerminalHelpers.h"
CMDText::CMDText()
	:offset{0,0}, text{}
{
}
CMDText::CMDText(iVec2D off, std::wstring tex)
	:offset(off), text(tex)
{
}
void CMDText::SetText(std::wstring text)
{
	this->text = text;
}

void CMDText::SetOffset(iVec2D offset)
{
	this->offset = offset;
}

void CMDText::Print()
{
	SetCursorPosition(offset);
	std::wcout << text;
}

void CMDText::Clear()
{
	std::wstring clearBuff;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == L'\n')
			clearBuff += text[i];
		else
			clearBuff += L' ';
	}
	SetCursorPosition(offset);
	std::wcout << clearBuff.c_str();
}
