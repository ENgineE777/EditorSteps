
#include "SceneBox.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneBox)

META_DATA_DESC(SceneBox)
COLOR_PROP(SceneBox, color, COLOR_RED, "Color", "color")
FLOAT_PROP(SceneBox, sizeX, 1.0f, "Geometry", "SizeX")
FLOAT_PROP(SceneBox, sizeY, 1.0f, "Geometry", "SizeY")
FLOAT_PROP(SceneBox, sizeZ, 1.0f, "Geometry", "SizeZ")
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
	Tasks()->AddTask(100, this, (Object::Delegate)&SceneBox::Draw);
}

void SceneBox::Draw(float dt)
{
	render.DebugBox(transform, color, Vector(sizeX, sizeY, sizeZ));
}