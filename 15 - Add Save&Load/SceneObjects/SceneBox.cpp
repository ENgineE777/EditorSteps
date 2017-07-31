
#include "SceneBox.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneBox)

META_DATA_DESC(SceneBox)
BOOL_PROP(SceneBox, red, true, "Color", "Red")
BOOL_PROP(SceneBox, green, false, "Color", "Green")
BOOL_PROP(SceneBox, blue, true, "Color", "Blue")
META_DATA_DESC_END()

SceneBox::SceneBox() : SceneObject()
{
}

SceneBox::~SceneBox()
{
}

void SceneBox::Init()
{
	Tasks()->AddTask(0, this, (Object::Delegate)&SceneBox::Draw);
}

void SceneBox::Draw(float dt)
{
	Color clr;
	clr.r = red ? 1 : 0;
	clr.g = green ? 1 : 0;
	clr.b = blue ? 1 : 0;

	render.DebugBox(transform, clr, Vector(1.0f));
}