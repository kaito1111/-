#pragma once
class GameManager;
class MoguraGenerator:public IGameObject
{
public:
	MoguraGenerator();
	~MoguraGenerator();

	bool Start();
	void Update();

	void UnLock(int No) {
		spornNo[No] = 0;
	}
	int timer = 50;
	int FeintTimer = 0;
	int Kingtimer = 0;
	int KingTimer = 400;
	int Mettimer = 0;
	int MetTimer = 500;
	int sporn = 0;
	int spornNo[46] = {};
	prefab::CSkinModelRender* m_skinModel[45];
	CVector3 m_position = { 1000.0f,0.0f,0.0f };
	//prefab::CSkinModelRender* m_skinModel=nullptr;
	CVector3 m_Scale = CVector3::One*4;
	float m_SetPosition = 100.0f;
	CVector3 EasySporn(CVector3 position);
	template<class t>
	t NormalSporn(t m);
	template<class t>
	t HardSporn(t m);
	//int MoguraPosition[10];
	//int MoguraKazu = 0;
	int SpornZaku = 0;
	int Zakutimer = 0;
	int ZakuTimer = 0;
	bool Delete = false;
};

