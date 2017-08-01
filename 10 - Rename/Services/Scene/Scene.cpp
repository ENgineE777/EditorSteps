
#include "Scene.h"
#include "SceneObject.h"
#include "Support/json/JSONReader.h"
#include "Support/json/JSONWriter.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Init()
{
	taskPool = taskExecutor.CreateSingleTaskPool();
	renderTaskPool = render.AddTaskPool();
}

SceneObject* Scene::AddObject(const char* name)
{
	SceneObject* obj = ClassFactorySceneObject::Create(name);

	if (obj)
	{
		obj->owner = this;
		obj->className = name;
		obj->Init();

		objects.push_back(obj);
	}

	return obj;
}

SceneObject* Scene::Find(const char* name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (StringUtils::IsEqual(objects[i]->GetName(), name))
		{
			return objects[i];
		}
	}

	return NULL;
}

void Scene::DeleteObject(SceneObject* obj)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] == obj)
		{
			objects.erase(objects.begin() + i);
			obj->Release();
			break;
		}
	}
}

void Scene::Execute(float dt)
{
	taskPool->Execute(dt);
}