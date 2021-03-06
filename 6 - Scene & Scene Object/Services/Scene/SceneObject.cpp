
#include "SceneObject.h"
#include "Services/Render/Render.h"

CLASSFACTORYDECL(SceneObject)

SceneObject::SceneObject()
{
	owner = NULL;
}

SceneObject::~SceneObject()
{

}

const char* SceneObject::GetName()
{
	return name.c_str();
}

void SceneObject::SetName(const char* set_name)
{
	name = set_name;
}

Matrix& SceneObject::Trans()
{
	return transform;
}

const char* SceneObject::GetClassName()
{
	return className.c_str();
}

TaskExecutor::SingleTaskPool* SceneObject::Tasks()
{
	return owner->taskPool;
}

TaskExecutor::SingleTaskPool* SceneObject::RenderTasks()
{
	return owner->renderTaskPool;
}

void SceneObject::Release()
{
	Tasks()->DelAllTasks(this);
	RenderTasks()->DelAllTasks(this);

	delete this;
}