
#pragma once

#include "Services/Scene/SceneObject.h"

class ScenePlayer : public SceneObject
{
public:

	META_DATA_DECL(ScenePlayer)

	float radius;
	float camDistance;
	Color color;

	Vector2 angles;

	CLASSDECLDIF(SceneObject, ScenePlayer)
		ScenePlayer();
	virtual ~ScenePlayer();

	virtual void Init();
	void Update(float dt);
	bool TestPos(Vector& pos);
};

