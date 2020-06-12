#pragma once
class GameManager;
class GameScene :public IGameObject
{
public:
	GameScene();
	~GameScene();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_SR = nullptr;
	CVector4 m_Color = { 1.0f,1.0f,1.0f,0.0f };
	bool StartGame = false;
	prefab::CDirectionLight* m_Light = nullptr;
};

