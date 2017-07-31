
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneSphere : public SceneObject
{
public:

	META_DATA_DECL(SceneSphere)

	bool red;
	bool green;
	bool blue;

	CLASSDECLDIF(SceneObject, SceneSphere)
	SceneSphere();
	virtual ~SceneSphere();

	virtual void Init();
	void Draw(float dt);
};

