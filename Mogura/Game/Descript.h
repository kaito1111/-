#pragma once
class Descript:public IGameObject
{
public:
	Descript();
	~Descript();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_Spritender = nullptr;
	prefab::CSoundSource* m_SS = nullptr;
	CVector3 m_position = CVector3::Zero;
	bool reset = false; //
	bool Newgo = false; //false‚ÅƒNƒ‰ƒX‚ğNweGO‚Å‚«‚éB
	float timer = 0.0f;
	bool Delete = false;
	bool Deletego = false;
};