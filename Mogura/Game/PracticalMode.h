#pragma once
class PracticalMode:public IGameObject
{
public:
	PracticalMode();
	~PracticalMode();

	bool Start();
	void Update();

	void UnLock(int No) 
	{
		spornNo[No] = 0;
	}
	prefab::CSkinModelRender* m_SMR[5][5];
	CVector3 m_Scale = CVector3::One * 4;
	CVector3 m_position = { -314.0f,0.0f,-100.0f };
	int timer = 50;
	int FeintTimer = 0;
	int Kingtimer = 0;
	int KingTimer = 400;
	int Mettimer = 0;
	int MetTimer = 500;
	int sporn = 0;
	int MoguraPosition[10];
	int MoguraKazu = 0;
	int Masu = 5;
	bool Delete = false;
	int spornNo[46] = {};
};

