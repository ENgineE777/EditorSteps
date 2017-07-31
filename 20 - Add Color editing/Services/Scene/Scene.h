
#pragma once

#include "Services/TaskExecutor/TaskExecutor.h"
#include <vector>

class SceneObject;

class Scene
{
	friend class SceneObject;

	std::vector<SceneObject*> objects;
	TaskExecutor::SingleTaskPool* taskPool;
	TaskExecutor::SingleTaskPool* renderTaskPool;

public:

	Scene();
	virtual ~Scene();

	void Init();

	SceneObject* AddObject(const char* name);
	SceneObject* Find(const char* name);
	SceneObject* GetObj(int index);
	int  GetObjectsCount();
	void DeleteObject(SceneObject* obj);
	void DeleteAllObjects();
	void Load(const char* name);
	void Save(const char* name);
	void Execute(float dt);
};
