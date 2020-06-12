#pragma once
class TotalScore:public IGameObject
{
public:
	TotalScore();
	~TotalScore();

	bool Start();
	void Update();

	int Total = 0;
	prefab::CFontRender* m_Score = nullptr;
	bool Delete = false;
	CVector2 m_Position = { -410.0f,20.0f };
	float timer = 0;
};
