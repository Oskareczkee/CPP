#pragma once
#include <iostream>


enum class GameSymbols
{
	//this is actually the first letter that player model begins with
	Player = L'(',
	Box = L'□',
	Target = L'▴',
	BoxOnPlace = L'■'
};

const wchar_t immovableObjects[]{
	(wchar_t)GameSymbols::BoxOnPlace,//box on place is immovable
	//(wchar_t)GameSymbols::Target,//target for now is immovable
	//walls and decorations
	L'╗',
	L'║',
	L'╝',
	L'╚',
	L'╔',
	L'═',
	L'╬',
	L'╦',
	L'╩',
	L'╠',
	L'╣'
};

const wchar_t bufferableObjects[]{
	(wchar_t)GameSymbols::Target
};

bool isImmovable(const wchar_t& object)
{
	if (std::find(std::begin(immovableObjects), std::end(immovableObjects), object) == std::end(immovableObjects))
		return false;
	return true;
}

bool isBufferable(const wchar_t& object)
{
	if (std::find(std::begin(bufferableObjects), std::end(bufferableObjects), object) == std::end(bufferableObjects))
		return false;
	return true;
}

enum class Input
{
	Invalid,
	Up = 'w',
	Down = 's',
	Right = 'd',
	Left = 'a',
	Menu = 'q',
	OFFSET_UP = 'i',
	OFFSET_DOWN = 'm',
	OFFSET_LEFT = 'j',
	OFFSET_RIGHT = 'k',
	UNDO='u',
	REDO = 'r',
};

Input charToInput(const wchar_t& c)
{
	switch (c)
	{
	case (char)Input::Up:
		return Input::Up;

	case (char)Input::Left:
		return Input::Left;

	case (char)Input::Down:
		return Input::Down;

	case (char)Input::Right:
		return Input::Right;

	case (char)Input::Menu:
		return Input::Menu;

	case (char)Input::OFFSET_UP:
		return Input::OFFSET_UP;

	case (char)Input::OFFSET_DOWN:
		return Input::OFFSET_DOWN;

	case (char)Input::OFFSET_RIGHT:
		return Input::OFFSET_RIGHT;

	case (char)Input::OFFSET_LEFT:
		return Input::OFFSET_LEFT;

	case (char)Input::UNDO:
		return Input::UNDO;

	case (char)Input::REDO:
		return Input::REDO;

	default:
		return Input::Invalid;
	}
}
