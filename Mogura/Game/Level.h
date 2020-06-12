#pragma once
class Level: public IGameObject
{
public:
	Level();
	~Level();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_SpriteRender = nullptr;
	prefab::CSpriteRender* m_YajirusiSR = nullptr;
	prefab::CSoundSource* m_BGM = nullptr;
	CVector3 m_LevelSpritePosition = CVector3::Zero;
	CVector3 m_YajirusiPosition = { -550.0f,-140.0f,0.0f };
	int timar = 0;
	bool Deletego = false;
	bool swich = false;
	bool Newgo = false;
	float Timar = 0.0f;

	bool Play = false;
};
