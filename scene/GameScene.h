#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
//自作クラス
#include "MyMatrix.h"
#include "Player.h"
#include "Box.h"

#define PI 3.14

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollision();
  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	float Angle(float angle);
	int scene_;
	float sceneTimer_;
	uint32_t textureHandle[4] = { 0u,0u,0u,0u };
	Sprite* sprite_[4] = {};
	//ゲーム用
	Model* playerModel_ = nullptr;
	Model* boxModel_ = nullptr;
	Player* player_ = nullptr;
	Box* box_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
