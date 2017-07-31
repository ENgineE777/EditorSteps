
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneSphere : public SceneObject
{
public:
	CLASSDECLDIF(SceneObject, SceneSphere)
	SceneSphere();
	virtual ~SceneSphere();

	virtual void Init();
	void Draw(float dt);
};

