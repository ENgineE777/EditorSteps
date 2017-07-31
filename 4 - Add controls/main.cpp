#include <windows.h>

#include <time.h>

#include <EUI.h>

#include "Services/Render/Render.h"
#include "Services/Controls/Controls.h"

#include "Support/Timer.h"

#include "Editor/freecamera.h"

float prev_t;
FreeCamera freecamera;

class Listener : public EUIWidget::Listener
{
public:

	void OnMouseMove(EUIWidget* sender, int mx, int my)
	{
		controls.OverrideMousePos(mx, my);
	}

	virtual void OnUpdate(EUIWidget* sender)
	{
		float t = Timer::GetMillisFloat();
		float dt = (t - prev_t) * 0.001f;
		prev_t = t;

		for (int i = 0; i <= 20; i++)
		{
			int pos = i - 10;

			render.DebugLine(Vector(pos, 0, -10), COLOR_WHITE, Vector(pos, 0, 10), COLOR_WHITE);
			render.DebugLine(Vector(-10, 0, pos), COLOR_WHITE, Vector(10, 0, pos), COLOR_WHITE);
		}

		render.GetDevice()->Clear(true, COLOR_GRAY, true, 1.0f);

		freecamera.Update(dt);
		render.Execute(dt);
		controls.Update(dt);

		render.GetDevice()->Present();
	}
};

Listener listener;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EUI::Init("settings/EUI/theme.dat");

	EUIWindow* wnd = new EUIWindow("Editor", false, true, 30, 30, 800, 600);

	EUIPanel* pn = new EUIPanel(wnd, 0, 0, 800, 600);
	pn->SetListener(&listener, EUIWidget::OnResize | EUIWidget::OnUpdate);
	render.Init("DX11", 800, 600, pn->GetNative());

	controls.Init(pn->GetNative(), "settings/controls/hardware_pc", "settings/controls/user_pc");

	Timer::Init();
	freecamera.Init();

	prev_t = Timer::GetMillisFloat();

	wnd->Show(true);

	return EUI::Run();
}