#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "ProjectileController.h"

class ArrowController : public ProjectileController<ArrowMesh,Arrow>
{
public:

	//ArrowController(ArrowMesh mesh, Arrow arrow)
	//	: ProjectileController(std::move(mesh), std::move(arrow))
	//{
	//}
	ArrowController(ArrowMesh&& mesh, Arrow&& arrow)
		: ProjectileController(std::move(mesh), std::move(arrow))
	{
	}

	Vector2f GetPosition()
	{
		return this->projMesh.GetPosition();
	}
};