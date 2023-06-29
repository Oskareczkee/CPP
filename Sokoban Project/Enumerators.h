#pragma once
enum class GameSymbols
{
	Player = '$',
	Wall = '#',
	Box = 'X',
	Target = 'O',
	BoxOnPlace = '*'
};

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
	OFFSET_RIGHT = 'k'
};

Input charToInput(const char& c)
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

	default:
		return Input::Invalid;
	}
}
