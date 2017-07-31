
#pragma once

#include "Support/Support.h"
#include "Services/Render/Render.h"
#include "Services/Controls/Controls.h"
#include "Services/Scene/SceneObject.h"
#include <EUI.h>
#include "freecamera.h"
#include "Support/Timer.h"

class Editor : public Object
{
	enum Const
	{
		MenuNewID = 1000,
		MenuOpenID = 1001,
		MenuSaveID = 1002,
		MenuSaveAsID = 1003,
		MenuExitID = 1003,

		MenuDeleteID = 1100,

		MenuSceneObjectID = 1400,
		ViewportID = 1500
	};

	class Listener : public EUIWidget::Listener
	{
		Editor* owner;
	public:
		Listener(Editor* owner);

		virtual void OnMouseMove(EUIWidget* sender, int mx, int my);
		virtual void OnRightMouseUp(EUIWidget* sender, int mx, int my);
		virtual void OnMenuItem(EUIWidget* sender, int id);
		virtual void OnUpdate(EUIWidget* sender);
		virtual void OnResize(EUIWidget* sender);
	};

	FreeCamera freecamera;
	Listener   listener;
	float      prev_t;

	std::string  sceneName;
	EUIListBox*  sceneList;

	Scene scene;

	TaskExecutor::SingleTaskPool* renderTaskPool;

public:

	Editor();
	virtual ~Editor();

	void Init();
	int  Run();

	void CreateSceneObject(const char* name);
	void SetUniqueName(SceneObject* obj, const char* name);
	void ProcessMenu(int id);
	void OnResize(int width, int height);
	void Update();
	void Draw(float dt);
};
