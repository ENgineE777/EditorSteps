
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
	void DeleteObject(SceneObject* obj);
	void Execute(float dt);
};
