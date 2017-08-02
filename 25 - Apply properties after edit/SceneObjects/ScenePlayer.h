
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

	int alias_forward;
	int alias_strafe;
	int alias_fast;
	int alias_rotate_active;
	int alias_rotate_x;
	int alias_rotate_y;

	CLASSDECLDIF(SceneObject, ScenePlayer)
		ScenePlayer();
	virtual ~ScenePlayer();

	virtual void Init();
	void Update(float dt);
	bool TestPos(Vector& pos);
};

