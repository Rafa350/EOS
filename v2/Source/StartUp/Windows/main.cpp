#include <windows.h>


// Comprova si son valids els parametres de compilacio
//
#if !(defined(_WIN32) || defined(_WIN64))
#error Hardware no soportado. Solo es valido EOS_WINDOWS
#endif


static const char g_szClassName[] = "myWindowClass";
static const char g_szWindowTitle[] = "EOS v2.0 Windows Emulator."


/// ----------------------------------------------------------------------
/// \brief Procesa les comandes de la clase de la finestra principal.
/// \param: hwnd: Handler de la finestra.
/// \param: msg: El missatge a procesar.
/// \param wParam: Parametre 1 del missatge.
/// \param lParam: Parametre 2 del missatge.
/// \return El resultat de l'operacio. Depend de cada missatge.
///
LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam) {

    switch(msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada al programa.
/// \param hInstance:
/// \param hPrevInstance:
/// \param lpCmdLine: Linea de comanda.
/// \param nCmdShow: Modus de presentacio inicial de la finestra.
/// \return 0 si tot es correcte
/// 
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
	int nCmdShow) {
   
    // Registra la clase de finestra
    //
	WNDCLASSEX wc;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    // Crea la finestra principal
    //
	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    // Mostra la finestra
    //
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

    // Procesa els missatges
    //
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
