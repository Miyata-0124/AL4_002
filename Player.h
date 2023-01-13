#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include <cassert>

class Player
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& viewProjection);

	void Translation();

	//ÉQÉbÉ^Å[
	Vector3 GetWorldTransform() { return worldTransform_.translation_; }
	float GetRadius();
private:
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//îºåa
	const float radius_ = 1.0f;
};

