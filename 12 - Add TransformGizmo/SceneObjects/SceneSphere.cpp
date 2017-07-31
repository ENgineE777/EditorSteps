
#include "SceneSphere.h"
#include "Services/Render/Render.h"

CLASSDECLDECL(SceneObject, SceneSphere)

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
	render.DebugSphere(transform.Pos(), COLOR_GREEN, 0.5f);
}