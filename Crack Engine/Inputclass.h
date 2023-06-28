#pragma once
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

/// <summary>
/// Base Class for handling inputs
/// </summary>
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();
	/// <summary>
	/// Checks if given key was pressed in the current frame
	/// </summary>
	/// <param name="KeyIndex">The unique key index</param>
	void KeyDown(unsigned int KeyIndex);
	/// <summary>
	/// Checks if given key was released in the current frame
	/// </summary>
	/// <param name="KeyIndex">The unique key index</param>
	void KeyUp(unsigned int KeyIndex);

	/// <summary>
	/// Checks if given key is pressed in the current frame
	/// </summary>
	/// <param name="KeyIndex">The unique key index</param>
	/// <returns></returns>
	bool IsKeyDown(unsigned int KeyIndex);

private:
	//all 256 keys
	bool m_keys[256];
};


#endif