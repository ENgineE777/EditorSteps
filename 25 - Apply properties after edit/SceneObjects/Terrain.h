
#pragma once

#include "Services/Render/Render.h"

#include "Services/Scene/SceneObject.h"

class Terrain : public SceneObject
{
public:
	META_DATA_DECL(Terrain)

	GeometryBuffer* buffer = NULL;
	Texture*        texture = NULL;
	int      hwidth;
	int      hheight;
	float    scaleh;
	float    scalev;
	Color    color;
	uint8_t* hmap = NULL;
	std::string tex_name;
	std::string hgt_name;

	struct VertexTri
	{
		Vector  position;
		Vector2 texCoord;
		Vector  normal;
	};

	int sz;

	CLASSDECLDIF(SceneObject, Terrain)
	Terrain();
	virtual ~Terrain();

	virtual void Init();
	virtual void ApplyProperties();
	float GetHeight(int i, int j);
	void LoadHMap(const char* hgt_name);
	void Render(float dt);
};
