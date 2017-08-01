
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneBox : public SceneObject
{
public:
	CLASSDECLDIF(SceneObject, SceneBox)
	SceneBox();
	virtual ~SceneBox();

	virtual void Init();
	void Draw(float dt);
};
