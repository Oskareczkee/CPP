#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


//speed up the build process, it reduces the size of the Win32 header files by excluding some of the less used APIs.
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "inputclass.h"
#include "graphicsclass.h"


/// <summary>
/// Handles the entry point for application.
/// This class encapsulates the entire application
/// It has input class inside to handle input, and graphics class, to handle DirectX graphics code
/// </summary>
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass& SystemClass);
	~SystemClass();


	/// <summary>
	/// Does all setup for the application.
	/// It first calls InitializeWindows which will create the window for our application to use.
	/// It also creates and initializes both the input and graphics objects that the application will use for handling user input and rendering graphics to the screen.
	/// </summary>
	/// <returns>Returns true, if everything went ok</returns>
	bool Initialize();

	/// <summary>
	/// Application loop
	/// The application processing is done in the Frame function which is called each loop.
	/// </summary>
	void Run();


	/// <summary>
	/// Does the clean up.
	/// It shuts down and releases everything associated with the graphics and input object.
	/// As well it also shuts down the window and cleans up the handles associated with it.
	/// </summary>
	void Shutdown();

	/// <summary>
	/// This function directs windows messages
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

	//Frame function is where all the processing for our application is done
	bool Frame();
	//Build windows to render into it
	void InitializeWindows(int& width, int& height);
	void ShutdownWindows();

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

};

//Function Prototypes

/// <summary>
/// Function, to which windows sends its messages
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//globals
static SystemClass* ApplicationHandle = 0;

#endif
