#include <windows.h>


LRESULT CALLBACK MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LParam) {
	
}

INT WINAPI WinMain(
	HINSTANCE Instance,
	HINSTANCE PrevInstance,
	PSTR CommandLine,
 	INT ShowCode) {
	
	WNDCLASS WindowClass = {};

	WindowClass.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc   = *MainWindowCallback;
	WindowClass.hInstance     = Instance;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass"

	retun 0;
}