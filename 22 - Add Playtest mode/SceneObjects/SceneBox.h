
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneBox : public SceneObject
{
public:
	META_DATA_DECL(SceneBox)

	float sizeX;
	float sizeY;
	float sizeZ;
	std::string filename;
	Color color;

	CLASSDECLDIF(SceneObject, SceneBox)
	SceneBox();
	virtual ~SceneBox();

	virtual void Init();
	void Draw(float dt);
};
