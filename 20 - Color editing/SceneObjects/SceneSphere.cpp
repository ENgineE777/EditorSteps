
#include "SceneSphere.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneSphere)

META_DATA_DESC(SceneSphere)
COLOR_PROP(SceneSphere, color, COLOR_CYAN, "Color", "color")
FLOAT_PROP(SceneSphere, radius, 0.5f, "Geometry", "Radius")
STRING_PROP(SceneSphere, text, "", "Misc", "Text")
META_DATA_DESC_END()

SceneSphere::SceneSphere() : SceneObject()
{
}

SceneSphere::~SceneSphere()
{
}

void SceneSphere::Init()
{
	Tasks()->AddTask(0, this, (Object::Delegate)&SceneSphere::Draw);
}

void SceneSphere::Draw(float dt)
{
	render.DebugSphere(transform.Pos(), color, radius);
}