#include "Player.h"
#include "MyMatrix.h"

void Player::Initialize(Model* model)
{
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,10.0f };

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//転送
	worldTransform_.TransferMatrix();
}

void Player::Update()
{
	Translation();

	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//行列の再計算(更新)
	worldTransform_.TransferMatrix();
}

void Player::Translation()
{
	if (input_->TriggerKey(DIK_LEFT)) {
		if (worldTransform_.translation_.x < 4.0f)
		{
			worldTransform_.translation_.x += 4.0f;
		}
	}
	if (input_->TriggerKey(DIK_RIGHT)) {
		if (worldTransform_.translation_.x > -4.0f)
		{
			worldTransform_.translation_.x -= 4.0f;
		}
	}
}

float Player::GetRadius()
{
	return radius_;
}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
