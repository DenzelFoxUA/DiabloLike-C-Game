#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "ProjectileController.h"

class ArrowController : public ProjectileController<ArrowMesh,Arrow>
{
public:

	ArrowController(ArrowMesh& mesh, Arrow& arrow)
		: ProjectileController(mesh, arrow)
	{
	}
};