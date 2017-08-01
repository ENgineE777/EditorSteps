
#include "programs.h"

Programs::TriangleProgram* Programs::prg = NULL;

void Programs::Init()
{
	if (!prg)
	{
		prg = new TriangleProgram();
		prg->Init();
	}
}