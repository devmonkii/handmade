#include <windows.h>

#define internal static;
#define local_persist static;
#define global_variable static;

// TODO(daniel): This is a global for now
global_variable bool Running;

LRESULT CALLBACK MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
	LRESULT Result = 0;

	switch(Message) {
		case WM_SIZE: {
			OutputDebugStringA("WM_SIZE\n");
		}
		break;
		case WM_DESTROY: {
			// TODO(daniel): Handle this with as an error - recreate window?
			Running = false;
		}
		break;
		case WM_CLOSE: {
			// TODO(daniel): Handle this with a message to the user?
			Running = false;
		}
		break;
		case WM_ACTIVATEAPP: {
			OutputDebugStringA("WM_ACTIVATEAPP\n");

		}
		break;
		case WM_PAINT: {
			
			PAINTSTRUCT Paint;			
			HDC DeviceContext = BeginPaint(Window, &Paint);

			INT X       = Paint.rcPaint.left;
			INT Y       = Paint.rcPaint.top;
			LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			LONG Width  = Paint.rcPaint.right - Paint.rcPaint.left;

			local_persist DWORD COLOR_TO_USE = WHITENESS;
			PatBlt(DeviceContext, X, Y, Width, Height, COLOR_TO_USE);
			if(COLOR_TO_USE == WHITENESS) {
				COLOR_TO_USE = BLACKNESS;
			} else {
				COLOR_TO_USE = WHITENESS;
			}

			EndPaint(Window, &Paint);
		}
		default: {
			OutputDebugStringA("DEFAULT\n");
			Result = DefWindowProc(Window, Message, WParam, LParam);
		}
		break;
	}

	return Result;
}

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CommandLine, INT ShowCode) {
	

	WNDCLASS WindowClass      = {};
	WindowClass.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc   = &MainWindowCallback;
	WindowClass.hInstance     = Instance;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass";

	RegisterClass(&WindowClass);
	
	HWND WindowHandle = CreateWindowEx(
		0,
		WindowClass.lpszClassName,
		"Handmade Hero",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		Instance,
		0);

	if(WindowHandle) {
		Running = true;

		while(Running) {
			MSG Message;
			BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
			if(MessageResult > 0) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
	}
	return 0;
}
