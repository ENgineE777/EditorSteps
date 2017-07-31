
#include "Editor.h"

Editor::Listener::Listener(Editor* set_owner)
{
	owner = set_owner;
}

void Editor::Listener::OnMouseMove(EUIWidget* sender, int mx, int my)
{
	if (sender->GetID() == Editor::ViewportID)
	{
		controls.OverrideMousePos(mx, my);
	}
}

void Editor::Listener::OnRightMouseUp(EUIWidget* sender, int mx, int my)
{
}

void Editor::Listener::OnMenuItem(EUIWidget* sender, int id)
{
	owner->ProcessMenu(id);
}

void Editor::Listener::OnUpdate(EUIWidget* sender)
{
	owner->Update();
}

void Editor::Listener::OnResize(EUIWidget* sender)
{
	owner->OnResize(sender->GetWidth(), sender->GetHeight());
}

Editor::Editor() : listener(this)
{
}

Editor::~Editor()
{
}

void Editor::Init()
{
	EUI::Init("settings/EUI/theme.dat");

	EUIWindow* wnd = new EUIWindow("Editor", false, true, 30, 30, 800, 600);

	EUIMenu* menu = new EUIMenu(wnd);
	menu->SetListener(&listener, 0);

	menu->StartSubMenu("File");

	menu->AddItem(MenuNewID, "New...");
	menu->AddItem(MenuOpenID, "Open...");
	menu->AddItem(MenuSaveID, "Save...");
	menu->AddItem(MenuSaveAsID, "Save as...");
	menu->AddSeparator();
	menu->AddItem(MenuExitID, "Exit...");

	menu->EndSubMenu();

	menu->AddItem(1301, "About");

	EUILayout* lt = new EUILayout(wnd, false);

	EUITabPanel* tabPanel = new EUITabPanel(lt, 30, 50, 100, 30);
	tabPanel->SetListener(&listener, 0);

	lt->SetChildSize(tabPanel, 200, false);

	EUITabSheet* sheet = tabPanel->AddTab("Scene");

	EUILayout* scene_lt = new EUILayout(sheet, false);

	sceneList = new EUIListBox(scene_lt, 200, 10, 200, 100);
	sceneList->SetListener(&listener, 0);

	sheet = tabPanel->AddTab("Object");

	EUIPanel* pn = new EUIPanel(lt, 10, 10, 100, 30);
	pn->SetListener(&listener, EUIWidget::OnResize | EUIWidget::OnUpdate);
	pn->SetID(ViewportID);

	controls.Init(pn->GetNative(), "settings/controls/hardware_pc", "settings/controls/user_pc");
	render.Init("DX11", 100, 100, pn->GetNative());

	render.AddExecutedLevelPool(1);

	renderTaskPool = render.AddTaskPool();
	renderTaskPool->AddTask(1, this, (Object::Delegate)&Editor::Draw);

	Timer::Init();
	freecamera.Init();
	scene.Init();

	wnd->Show(true);
	wnd->Maximaze();
}

int Editor::Run()
{
	prev_t = Timer::GetMillisFloat();

	return EUI::Run();
}

void Editor::OnResize(int width, int height)
{
	freecamera.OnResize(width, height);
	render.GetDevice()->SetVideoMode(width, height);
}

void Editor::Update()
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

	freecamera.Update(dt);

	scene.Execute(dt);

	render.Execute(dt);

	controls.Update(dt);
}

void Editor::ProcessMenu(int activated_id)
{
}

void Editor::Draw(float dt)
{
	render.GetDevice()->Clear(true, COLOR_GRAY, true, 1.0f);

	render.ExecutePool(1000, dt);

	render.GetDevice()->Present();
}