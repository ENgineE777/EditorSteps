
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

void Editor::Listener::OnListBoxChange(EUIWidget* sender, int index)
{
	owner->SelectObject((SceneObject*)owner->sceneList->GetSelectedItemData());
}

void Editor::Listener::OnEditBoxChange(EUIWidget* sender)
{
	owner->OnObjectNameChanged();
}

void Editor::Listener::OnResize(EUIWidget* sender)
{
	owner->OnResize(sender->GetWidth(), sender->GetHeight());
}

Editor::Editor() : listener(this)
{
	selectedObject = NULL;
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

	menu->StartSubMenu("Edit");

	menu->AddItem(MenuDeleteID, "Delete");

	menu->EndSubMenu();

	menu->StartSubMenu("Create");

	ClassFactorySceneObject* decl = ClassFactorySceneObject::First();

	int id = MenuSceneObjectID;

	while (decl)
	{
		menu->AddItem(id, decl->GetName());
		id++;

		decl = decl->Next();
	}

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

	EUILayout* object_lt = new EUILayout(sheet, true);

	objectName = new EUIEditBox(object_lt, "", 0, 0, 200, 20, EUIEditBox::InputText);
	objectName->SetListener(&listener, 0);
	objectName->Enable(false);
	object_lt->SetChildSize(objectName, 20, false);

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

void Editor::SelectObject(SceneObject* obj)
{
	selectedObject = obj;

	bool enabled = (selectedObject != NULL);
	objectName->Enable(enabled);

	if (selectedObject)
	{
		objectName->SetText(obj->GetName());
	}
	else
	{
		objectName->SetText("");
	}
}

void Editor::SetUniqueName(SceneObject* obj, const char* name)
{
	char baseName[512];
	int index = StringUtils::ExtractNameNumber(name, baseName, 512);
	bool unique = false;
	char uniqueName[512];

	while (!unique)
	{
		StringUtils::Printf(uniqueName, 512, "%s%i", baseName, index);

		index++;
		unique = (scene.Find(uniqueName) == NULL);
	}

	obj->SetName(uniqueName);
}

void Editor::OnObjectNameChanged()
{
	if (!selectedObject ||
		StringUtils::IsEqual(objectName->GetText(), selectedObject->GetName()))
	{
		return;
	}

	SetUniqueName(selectedObject, objectName->GetText());
	sceneList->ChangeItemNameByData(objectName->GetText(), selectedObject);
}

void Editor::CreateSceneObject(const char* name)
{
	SceneObject* obj = scene.AddObject(name);

	obj->Trans().Move(freecamera.pos + Vector(cosf(freecamera.angles.x), sinf(freecamera.angles.y), sinf(freecamera.angles.x)) * 5.0f);

	SetUniqueName(obj, name);
	sceneList->AddItem(obj->GetName(), obj);
	sceneList->SelectItemByData(obj);

	SelectObject(obj);
}

void Editor::DeleteSceneObject(SceneObject* obj)
{
	if (!obj)
	{
		return;
	}

	if (selectedObject == obj)
	{
		SelectObject(NULL);
	}

	sceneList->DeleteItemByData(obj);
	scene.DeleteObject(obj);
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
	ClassFactorySceneObject* decl = ClassFactorySceneObject::First();

	if (activated_id == MenuDeleteID)
	{
		DeleteSceneObject(selectedObject);
	}

	if (activated_id >= MenuSceneObjectID && activated_id <= MenuSceneObjectID + 100)
	{
		int id = MenuSceneObjectID;

		while (decl)
		{
			if (id == activated_id)
			{
				CreateSceneObject(decl->GetName());
				break;
			}

			id++;
			decl = decl->Next();
		}
	}
}

void Editor::Draw(float dt)
{
	render.GetDevice()->Clear(true, COLOR_GRAY, true, 1.0f);

	render.ExecutePool(1000, dt);

	render.GetDevice()->Present();
}