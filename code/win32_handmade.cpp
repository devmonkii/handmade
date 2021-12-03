#include <windows.h>


LRESULT CALLBACK MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
	LRESULT Result = 0;

	switch(Message) {
		case WN_SIZE: {
			OutputDebugStringA("WN_SIZE\n")
		}
		break;
		case WN_DESTROY: {
			OutputDebugStringA("WN_DESTROY\n")
		}
		break;
		case WN_CLOSE: {
			OutputDebugStringA("WN_CLOSE\n")

		}
		break;
		case WM_ACTIVATEAPP: {
			OutputDebugStringA("WM_ACTIVATEAPP\n")

		}
		break;
		case WM_PAINT: {
			
			PAINTSTRUCT Paint;			
			HDC DeviceContext = BeginPaint(Window, &Paint)

			INT X       = Paint.rcPaint.left;
			INT Y       = Paint.rcPaint.right;
			LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			LONG Width  =  Paint.rcPaint.right - Paint.rcPaint.left;


			PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS)


			EndPaint(Window, &Paint);
		}
		default: {
			OutputDebugStringA("DEFAULT\n")
			Result = DefWindowProc(Window, Message, WParam, LParam);
		}
		break;
	}

	retun Result;
}

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CommandLine, INT ShowCode) {
	

	WNDCLASS WindowClass      = {};
	WindowClass.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc   = &MainWindowCallback;
	WindowClass.hInstance     = Instance;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass"

	RegisterClass(&WindowClass)
	
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
		for(;;) {
			MSG Message;
			BOOL MessageResult = GetMessage(&Message, 0, 0, 0,0 )
			if(MessageResult > 0) {

			} else {
				break;
			}
		}
	}
	retun 0;
}
