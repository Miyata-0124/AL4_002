#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include <cassert>

class Box
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition0();
	Vector3 GetWorldPosition1();
	Vector3 GetWorldPosition2();
	float GetRadius0();
	float GetRadius1();
	float GetRadius2();
private:
	DebugText* debugText_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform worldTransform_[3];
	ViewProjection viewProjection_;

	int isShot_[3];
	int phase_ = 0;
	float phaseTimer_ = 100.0f;
	float moveTimer[3];
	float speed[3];
	//”¼Œa
	const float radius_[3] = { 1.0f,1.0f,1.0f };
};

