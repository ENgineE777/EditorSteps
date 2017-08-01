
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneBox : public SceneObject
{
public:
	META_DATA_DECL(SceneBox)

	bool red;
	bool green;
	bool blue;
	int  size;
	std::string filename;

	CLASSDECLDIF(SceneObject, SceneBox)
	SceneBox();
	virtual ~SceneBox();

	virtual void Init();
	void Draw(float dt);
};
