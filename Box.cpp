#include "Box.h"
#include "MyMatrix.h"

void Box::Initialize(Model* model)
{
	debugText_ = DebugText::GetInstance();

	assert(model);
	model_ = model;
	for (int i = 0; i < 3; i++)
	{
		worldTransform_[i].Initialize();
		worldTransform_[0].translation_ = { 0.0f,0.0f,-50.0f };
		worldTransform_[1].translation_ = { 4.0f,0.0f,-50.0f };
		worldTransform_[2].translation_ = { -4.0f,0.0f,-50.0f };

		moveTimer[0] = 50.0f;
		moveTimer[1] = 30.0f;
		moveTimer[2] = 30.0f;
		isShot_[i] = 0;
		speed[i] = 0;
		//転送
		worldTransform_[i].TransferMatrix();
	}
}

void Box::Update()
{
	//phasaeの切り替え
	phaseTimer_ -= 0.3f;
	if (phaseTimer_ <= 0.0f)
	{
		phase_ += 1;
		phaseTimer_ = 100.0f;
		if (phase_ == 3)
		{
			phase_ = 0;
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		moveTimer[i] -= 0.5f;

		switch (phase_)
		{
		case 0:
			if (moveTimer[i] <= 0.0f && isShot_[i] == 0)
			{
				speed[i] = 0.5f;
				isShot_[i] = 1;
			}
			if (worldTransform_[0].translation_.z >= 20.0f)
			{
				worldTransform_[0].translation_ = { 0.0f,0.0f,-50.0f };
				moveTimer[0] = 50.0f;
			}
			if (worldTransform_[1].translation_.z >= 20.0f)
			{
				worldTransform_[1].translation_ = { 4.0f,0.0f,-50.0f };
				moveTimer[1] = 30.0f;
			}
			if (worldTransform_[2].translation_.z >= 20.0f)
			{
				worldTransform_[2].translation_ = { -4.0f,0.0f,-50.0f };
				moveTimer[2] = 30.0f;
			}
			
			break;
		case 1:
			if (moveTimer[i] <= 0.0f && isShot_[i] == 0)
			{
				speed[i] = 1.2f;
				isShot_[i] = 1;
			}
			if (worldTransform_[0].translation_.z >= 20.0f)
			{
				worldTransform_[0].translation_ = { 0.0f,0.0f,-50.0f };
				moveTimer[0] = 15.0f;
			}
			if (worldTransform_[1].translation_.z >= 20.0f)
			{
				worldTransform_[1].translation_ = { 4.0f,0.0f,-50.0f };
				moveTimer[1] = 30.0f;
			}
			if (worldTransform_[2].translation_.z >= 20.0f)
			{
				worldTransform_[2].translation_ = { -4.0f,0.0f,-50.0f };
				moveTimer[2] = 45.0f;
			}
			break;
		case 2:
			if (moveTimer[i] <= 0.0f && isShot_[i] == 0)
			{
				speed[i] = 1.5f;
				isShot_[i] = 1;
			}
			if (worldTransform_[0].translation_.z >= 20.0f)
			{
				worldTransform_[0].translation_ = { 0.0f,0.0f,-50.0f };
				moveTimer[0] = 30.0f;
			}
			if (worldTransform_[1].translation_.z >= 20.0f)
			{
				worldTransform_[1].translation_ = { 4.0f,0.0f,-50.0f };
				moveTimer[1] = 10.0f;
			}
			if (worldTransform_[2].translation_.z >= 20.0f)
			{
				worldTransform_[2].translation_ = { -4.0f,0.0f,-50.0f };
				moveTimer[2] = 20.0f;
			}
			break;
		}

		if (isShot_[i] == 1)
		{
			worldTransform_[i].translation_.z += speed[i];
			if (worldTransform_[i].translation_.z >= 20.0f)
			{
				isShot_[i] = 0;
			}
		}
		//行列計算
		worldTransform_[i].matWorld_ = Scale(worldTransform_[i].scale_);
		worldTransform_[i].matWorld_ *= Rot(worldTransform_[i].rotation_);
		worldTransform_[i].matWorld_ *= Transform(worldTransform_[i].translation_);

		//行列の再計算(更新)
		worldTransform_[i].TransferMatrix();
	}
	
}

void Box::Draw(ViewProjection& viewProjection)
{
	for (int i = 0; i < 3; i++)
	{
		model_->Draw(worldTransform_[i], viewProjection);
	}
}

Vector3 Box::GetWorldPosition0()
{
	return worldTransform_[0].translation_;
}

Vector3 Box::GetWorldPosition1()
{
	return worldTransform_[1].translation_;
}

Vector3 Box::GetWorldPosition2()
{
	return worldTransform_[2].translation_;
}

float Box::GetRadius0()
{
	return radius_[0];
}

float Box::GetRadius1()
{
	return radius_[1];
}

float Box::GetRadius2()
{
	return radius_[2];
}
