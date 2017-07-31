#include <windows.h>

#include <time.h>

#include <EUI.h>

#include "Services/Render/Render.h"

class Listener : public EUIWidget::Listener
{
public:
	virtual void OnUpdate(EUIWidget* sender)
	{
		for (int i = 0; i <= 20; i++)
		{
			int pos = i - 10;

			render.DebugLine(Vector(pos, 0, -10), COLOR_WHITE, Vector(pos, 0, 10), COLOR_WHITE);
			render.DebugLine(Vector(-10, 0, pos), COLOR_WHITE, Vector(10, 0, pos), COLOR_WHITE);
		}

		render.GetDevice()->Clear(true, COLOR_GRAY, true, 1.0f);

		render.Execute(0.0f);

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

	Matrix view;
	view.BuildView(Vector(0.0f, 6.0f, 0.0f), Vector(10.0f, 2.0f, 0.0f), Vector(0, 1, 0));

	Matrix proj;
	proj.BuildProjection(45.0f * RADIAN, 600.0f / 800.0f, 1.0f, 1000.0f);

	render.SetTransform(Render::View, view);
	render.SetTransform(Render::Projection, proj);

	wnd->Show(true);

	return EUI::Run();
}