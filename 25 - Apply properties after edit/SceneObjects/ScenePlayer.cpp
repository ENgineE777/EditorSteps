
#include "ScenePlayer.h"
#include "Services/Render/Render.h"
#include "SceneBox.h"

CLASSDECLDECL(SceneObject, ScenePlayer)

META_DATA_DESC(ScenePlayer)
COLOR_PROP(ScenePlayer, color, COLOR_CYAN, "Color", "color")
FLOAT_PROP(ScenePlayer, radius, 0.5f, "Geometry", "Radius")
FLOAT_PROP(ScenePlayer, camDistance, 4.0f, "Geometry", "CamDistance")
META_DATA_DESC_END()

ScenePlayer::ScenePlayer() : SceneObject()
{
}

ScenePlayer::~ScenePlayer()
{
}

void ScenePlayer::Init()
{
	Tasks()->AddTask(100, this, (Object::Delegate)&ScenePlayer::Update);

	angles = Vector2(0.0f, -0.5f);

	alias_forward = controls.GetAlias("MOVE_FORWARD");
	alias_strafe = controls.GetAlias("MOVE_STRAFE");
	alias_rotate_active = controls.GetAlias("ROTATE_ACTIVE");
	alias_rotate_x = controls.GetAlias("ROTATE_X");
	alias_rotate_y = controls.GetAlias("ROTATE_Y");
}

void ScenePlayer::Update(float dt)
{
	if (!Playing())
	{
		render.DebugSphere(transform.Pos(), color, radius);

		return;
	}

	if (controls.GetAliasState(alias_rotate_active, false, Controls::Active))
	{
		angles.x -= controls.GetAliasValue(alias_rotate_x, true) * 0.01f;
		angles.y -= controls.GetAliasValue(alias_rotate_y, true) * 0.01f;

		if (angles.y > 0.1f)
		{
			angles.y = 0.1f;
		}

		if (angles.y < -HALF_PI)
		{
			angles.y = -HALF_PI;
		}
	}

	float forward = controls.GetAliasValue(alias_forward, false);
	float strafe = controls.GetAliasValue(alias_strafe, false);
	
	float speed = 3.0f * dt;

	Vector dir = Vector(cosf(angles.x), 0.0f, sinf(angles.x));
	if (TestPos(transform.Pos() + dir * speed * forward))
	{
		transform.Pos() += dir * speed * forward;
	}

	Vector dir_strafe = Vector(dir.z, 0, -dir.x);
	if (TestPos(transform.Pos() + dir_strafe * speed * strafe))
	{
		transform.Pos() += dir_strafe * speed * strafe;
	}

	transform.Pos().y -= dt * 2.0f;

	if (transform.Pos().y < radius)
	{
		transform.Pos().y = radius;
	}

	Matrix view;
	view.BuildView(transform.Pos() - Vector(cosf(angles.x), sinf(angles.y), sinf(angles.x)) * camDistance, transform.Pos(), Vector(0, 1, 0));
	render.SetTransform(Render::View, view);

	Matrix proj;
	proj.BuildProjection(45.0f * RADIAN, (float)render.GetDevice()->GetHeight() / (float)render.GetDevice()->GetWidth(), 1.0f, 1000.0f);
	render.SetTransform(Render::Projection, proj);

	render.DebugSphere(transform.Pos(), color, radius);
}

bool ScenePlayer::TestPos(Vector& pos)
{
	Scene::Group& boxes = owner->GetGroup("Box");

	for (int i = 0; i < boxes.objects.size(); i++)
	{
		SceneBox* box = (SceneBox*)boxes.objects[i];

		if (box->Trans().Pos().y + box->sizeY * 0.5f < 0.0f)
		{
			continue;
		}

		float dmin = 0;
		float dst = box->Trans().Pos().x - box->sizeX * 0.5f;

		if (pos.x < dst)
		{
			dmin += (pos.x - dst) * (pos.x - dst);
		}
		else
		{
			dst = box->Trans().Pos().x + box->sizeX * 0.5f;

			if (pos.x > dst)
			{
				dmin += (pos.x - dst) * (pos.x - dst);
			}
		}

		dst = box->Trans().Pos().z - box->sizeZ * 0.5f;

		if (pos.z < dst)
		{
			dmin += (pos.z - dst) * (pos.z - dst);
		}
		else
		{
			dst = box->Trans().Pos().z + box->sizeZ * 0.5f;

			if (pos.z > dst)
			{
				dmin += (pos.z - dst) * (pos.z - dst);
			}
		}

		if (dmin <= radius * radius)
		{
			return false;
		}
	}

	return true;
}
