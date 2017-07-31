#include <windows.h>

#include <time.h>

#include <EUI.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EUI::Init("settings/EUI/theme.dat");

	EUIWindow* wnd = new EUIWindow("Editor", false, true, 30, 30, 800, 600);

	wnd->Show(true);

	return EUI::Run();
}