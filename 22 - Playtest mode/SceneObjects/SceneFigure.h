
#pragma once

#include "Services/Scene/SceneObject.h"

class SceneFigure : public SceneObject
{
public:

	META_DATA_DECL(SceneFigure)

	enum Figure
	{
		Sphere = 0,
		Box = 1
	};

	Figure figure;
	Color  color;
	float  size;

	CLASSDECLDIF(SceneObject, SceneFigure)
	SceneFigure();
	virtual ~SceneFigure();

	virtual void Init();
	void Draw(float dt);
};

