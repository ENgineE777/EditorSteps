
#include "SceneBox.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneBox)

META_DATA_DESC(SceneBox)
COLOR_PROP(SceneBox, color, COLOR_RED, "Color", "color")
INT_PROP(SceneBox, size, 1, "Geometry", "Size")
FILENAME_PROP(SceneBox, filename, "", "Misc", "Filename")
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
	render.DebugBox(transform, color, Vector(size));
}