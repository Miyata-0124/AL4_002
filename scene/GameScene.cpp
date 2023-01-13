#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete box_;
}

//当たり判定
void GameScene::CheckAllCollision()
{
	// 判定対象AとBの座標
	Vector3 posA, posB;

#pragma region 箱0とプレイヤ-
	posA = box_->GetWorldPosition0();
	//敵弾の座標
	posB = player_->GetWorldTransform();
	Vector3 len = Vectornorm(posA, posB);
	float dis = Length(len);
	float radius = player_->GetRadius() + box_->GetRadius0();
	if (dis <= radius)
	{
		scene_ = 3;
	}
#pragma endregion
#pragma region 箱1とプレイヤ-
	posA = box_->GetWorldPosition1();
	//敵弾の座標
	posB = player_->GetWorldTransform();
	Vector3 len1 = Vectornorm(posA, posB);
	float dis1 = Length(len1);
	float radius1 = player_->GetRadius() + box_->GetRadius1();
	if (dis1 <= radius1)
	{
		scene_ = 3;
	}
#pragma endregion
#pragma region 箱2とプレイヤ-
	posA = box_->GetWorldPosition2();
	//敵弾の座標
	posB = player_->GetWorldTransform();
	Vector3 len2 = Vectornorm(posA, posB);
	float dis2 = Length(len2);
	float radius2 = player_->GetRadius() + box_->GetRadius2();
	if (dis2 <= radius2)
	{
		scene_ = 3;
	}
#pragma endregion
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//モデル
	playerModel_ = Model::CreateFromOBJ("player", true);
	boxModel_ = Model::CreateFromOBJ("enemy", true);
	//テクスチャ
	textureHandle[0] = TextureManager::Load("taitle.png");
	sprite_[0] = Sprite::Create(textureHandle[0], { 100,100 });
	textureHandle[1] = TextureManager::Load("move.png");
	sprite_[1] = Sprite::Create(textureHandle[1], { 0,0 });
	textureHandle[2] = TextureManager::Load("over.png");
	sprite_[2] = Sprite::Create(textureHandle[2], { 0,0 });
	textureHandle[3] = TextureManager::Load("clear.png");
	sprite_[3] = Sprite::Create(textureHandle[3], { 0,0 });
	//シーン
	scene_ = 0;
	sceneTimer_ = 200.0f;
	//自キャラ
	player_ = new Player();
	player_->Initialize(playerModel_);
	//避けるオブジェクト
	box_ = new Box();
	box_->Initialize(boxModel_);

	/*viewProjection_.fovAngleY = Angle(20.0f);*/
	viewProjection_.eye = {0.0f,5.0f,20.0f};
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() 
{
	switch (scene_)
	{
	case 0://タイトル
		if (input_->TriggerKey(DIK_SPACE))
		{
			box_->Initialize(boxModel_);
			scene_ = 1;
		}
		break;
	case 1://プレイ
		sceneTimer_ -= 0.1f;
	
		player_->Update();
		box_->Update();

		CheckAllCollision();
		if (sceneTimer_ <= 0.0f)
		{
			scene_ = 2;
			sceneTimer_ = 200.0f;
		}
		break;
	case 2://クリア
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = 0;
		}
		if (input_->TriggerKey(DIK_R))
		{
			box_->Initialize(boxModel_);
			scene_ = 1;
		}
		break;
	case 3:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = 0;
		}
		if (input_->TriggerKey(DIK_R))
		{
			box_->Initialize(boxModel_);
			scene_ = 1;
		}
		break;
	}
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	switch (scene_)
	{
	case 0:
		break;
	case 1:
		player_->Draw(viewProjection_);
		box_->Draw(viewProjection_);
		break;
	case 2:
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (scene_)
	{
	case 0:
		sprite_[0]->Draw();
		break;
	case 1:
		sprite_[1]->Draw();
		break;
	case 2:
		sprite_[3]->Draw();
		break;
	case 3:
		sprite_[2]->Draw();
		break;
	}
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

float GameScene::Angle(float angle)
{
	return angle * PI / 180;
}