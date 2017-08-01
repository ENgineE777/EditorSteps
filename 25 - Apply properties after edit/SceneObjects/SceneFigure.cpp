
#include "SceneFigure.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneFigure)

META_DATA_DESC(SceneFigure)
COLOR_PROP(SceneFigure, color, COLOR_CYAN, "Geometry", "color")
FLOAT_PROP(SceneFigure, size, 1.0f, "Geometry", "size")
ENUM_PROP(SceneFigure, figure, 1, "Geometry", "figure")
	ENUM_ELEM("Sphere", 0)
	ENUM_ELEM("Box", 1)
ENUM_END

META_DATA_DESC_END()

SceneFigure::SceneFigure() : SceneObject()
{
}

SceneFigure::~SceneFigure()
{
}

void SceneFigure::Init()
{
	Tasks()->AddTask(100, this, (Object::Delegate)&SceneFigure::Draw);
}

void SceneFigure::Draw(float dt)
{
	if (figure == Sphere)
	{
		render.DebugSphere(transform.Pos(), color, size * 0.5f);
	}
	else
	if (figure == Box)
	{
		render.DebugBox(transform, color, Vector(size));
	}
}