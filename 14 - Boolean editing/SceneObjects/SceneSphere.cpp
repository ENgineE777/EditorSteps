
#include "SceneSphere.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneSphere)

META_DATA_DESC(SceneSphere)
BOOL_PROP(SceneSphere, red, true, "Color", "Red")
BOOL_PROP(SceneSphere, green, true, "Color", "Green")
BOOL_PROP(SceneSphere, blue, false, "Color", "Blue")
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
	Color clr;
	clr.r = red ? 1 : 0;
	clr.g = green ? 1 : 0;
	clr.b = blue ? 1 : 0;

	render.DebugSphere(transform.Pos(), clr, 0.5f);
}