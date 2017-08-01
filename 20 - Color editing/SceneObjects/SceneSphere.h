
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneSphere : public SceneObject
{
public:

	META_DATA_DECL(SceneSphere)

	float radius;
	std::string text;
	Color color;

	CLASSDECLDIF(SceneObject, SceneSphere)
	SceneSphere();
	virtual ~SceneSphere();

	virtual void Init();
	void Draw(float dt);
};

