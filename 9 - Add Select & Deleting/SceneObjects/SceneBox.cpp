
#include "SceneBox.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneBox)

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
	render.DebugBox(transform, COLOR_GREEN, Vector(1.0f));
}