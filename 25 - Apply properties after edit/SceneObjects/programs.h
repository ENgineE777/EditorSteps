
#include "Services/Render/Render.h"

class Programs
{
public:

	class TriangleProgram : public Program
	{
	public:
		virtual const char* GetVsName() { return "shaders//triangle_vs.shd"; };
		virtual const char* GetPsName() { return "shaders//triangle_ps.shd"; };

		virtual void Apply()
		{
			Program::Apply();
			render.GetDevice()->SetAlphaBlend(false);
			render.GetDevice()->SetDepthWriting(true);
			render.GetDevice()->SetDepthTest(true);
		};
	};

	static TriangleProgram* prg;

	static void Init();
};
