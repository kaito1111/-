#include "stdafx.h"
#include "MoguraGenerator.h"
#include "Mogura.h"
#include "GameManager.h"
#include "Player.h"
#include "KingMogura.h"
#include "Metooru.h"
#include "Zaku.h"
#include "FeintMogura.h"

MoguraGenerator::MoguraGenerator()
{

}


MoguraGenerator::~MoguraGenerator()
{
	//DeleteGO(m_skinModel);
	for (int i = 0; i < 45; i++)
	{
		DeleteGO(m_skinModel[i]);
	}
}

bool MoguraGenerator::Start()
{
	for (int i = 0; i < 45; i++)
	{
		m_skinModel[i] = nullptr;
		m_skinModel[i] = NewGO<prefab::CSkinModelRender>(0);
		m_skinModel[i]->Init(L"modelData/Hole.cmo", nullptr, 0);
		m_skinModel[i]->SetScale(m_Scale);
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Easy)
			{
				int i = 0;
				for (int n = 0; n < 3; n++)
				{
					CVector3 m_Position = { -314.0f,0.0f,-407.0f };
					m_Position.x += 381.0f * n;
					for (int j = 0; j < 3; j++) {
						m_Position.z += 210.0f;//x,-314,67,448,z,-197,13,223
						m_skinModel[i]->SetPosition(m_Position);
						i++;
					}
				}
				for (int i = 9; i < 45; i++)
				{
					m_skinModel[i]->SetPosition(m_position);
				}
				return false;
			}
			if (m_Manager->Normal) {
				int i = 0;
				for (int j = 0; j < 5; j++)
				{
					CVector3 m_Position = { -314.0f,0.0f,-302.0f };//原点は67,みぎは448,左は-373
					m_Position.x += 190.5f * j;
					for (int j = 0; j < 5; j++)
					{
						m_Position.z = m_Position.z + 105.0f;
						m_skinModel[i]->SetPosition(m_Position);//223
						i++;
					}
				}
				for (int i = 25; i < 45; i++) {
					m_skinModel[i]->SetPosition(m_position);
				}
				return false;
			}
			if (m_Manager->Hard)
			{
				int i = 0;
				for (int j = 0; j < 9; j++)
				{
					CVector3 m_Position = { -314.0f,0.0f,-302.0f };
					m_Position.x += 94.1f * j;
					for (int j = 0; j < 5; j++)
					{
						m_Position.z = m_Position.z + 105.0f;
						m_skinModel[i]->SetPosition(m_Position);
						i++;
					}
				}
				return false;
			}
			return true;
		});
	SpornZaku = Random().GetRandInt() % 60;
	ZakuTimer = Random().GetRandInt() % 60;
	/*for (int i = 0; i < 10; i++)
	{
		MoguraPosition[i] = 0;
	}*/
	/*m_skinModel= NewGO<prefab::CSkinModelRender>(0);
	m_skinModel->Init(L"modelData/Hole.cmo", nullptr, 0);
	m_skinModel->SetScale(m_Scale);
	m_skinModel->SetPosition(m_Position);*/
	return true;
}

void MoguraGenerator::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_StartTime <= 0.0f)
			{
				Zakutimer += GameTime().GetFrameDeltaTime();
				timer++;
				Kingtimer++;
				Mettimer++;
				FeintTimer++;
				return false;
			}
			return true;
		});
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Easy)
			{
				QueryGOs<Player>("Player", [&](Player* m_player)->bool
					{
						if (m_player->fever >= 20)
						{
							if ((FeintTimer % 20) == 0) {
								FeintMogura* m_Mogura = NewGO<FeintMogura>(0, "FeintMogura");
								do {
									sporn = Random().GetRandInt() % 8 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10)
								{
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++)
								{
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 8 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 7:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								};
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
								return false;
							}
							if ((Kingtimer % 30) == 0)
							{
								KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
								do {
									sporn = Random().GetRandInt() % 8 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10)
								{
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++)
								{
									while (MoguraPosition[i]== sporn)
									{
										sporn = Random().GetRandInt() % 8 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 7:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
									break;
								default:
									break;
								};
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
								return false;
							}
							if ((timer % 20) == 0) {
								Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
								do {
									sporn = Random().GetRandInt() % 8 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10)
								{
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++)
								{
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 8 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 7:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 60.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								};
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
								return false;

							}
							return false;
						}
						return true;
					});
				if (SpornZaku == 1)
				{
					if (Zakutimer >= ZakuTimer)
					{
						Zaku* m_Mogura = NewGO<Zaku>(0, "Zaku");
						sporn = Random().GetRandInt() % 8 + 1;
						Zakutimer = 0;
						/*MoguraPosition[MoguraKazu] = sporn;
						MoguraKazu++;
						if (MoguraKazu == 10)
						{
							MoguraKazu = 0;
						}
						for (int i = 0; i < i < 10; i++)
						{
							while (MoguraPosition[MoguraKazu])
							{
								sporn = Random().GetRandInt() % 8 + 1;
								i = -1;
							}
						};*/
						switch (sporn)
						{
						case 1:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 2:
							m_Mogura->m_position.x = 60.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 3:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 4:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 5:
							m_Mogura->m_position.x = 60.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 6:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 7:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 8:
							m_Mogura->m_position.x = 60.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 9:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						default:
							break;
						};
					}
				}
				if (Kingtimer >= KingTimer)
				{
					KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
					Kingtimer = 0;
					KingTimer--;
					//CVector3 EasySporn(m_Mogura->m_position);
					do {
						sporn = Random().GetRandInt() % 8 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10)
					{
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++)
					{
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 8 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					};
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if ((FeintTimer >= 100)) {
					FeintTimer = 0;
					FeintMogura* m_Mogura = NewGO<FeintMogura>(0, "FeintMogura");
					do {
						sporn = Random().GetRandInt() % 8 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10)
					{
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++)
					{
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 8 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					};
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (timer >= 100)
				{
					Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
					timer = 0;
					do {
						sporn = Random().GetRandInt() % 8 + 1;
					} while (spornNo[sporn] != 0);
					/*	MoguraPosition[MoguraKazu] = sporn;
						MoguraKazu++;
						if (MoguraKazu == 10)
						{
							MoguraKazu = 0;
						}
						for (int i = 0; i < i < 10; i++)
						{
							while (MoguraPosition[MoguraKazu])
							{
								sporn = Random().GetRandInt() % 8 + 1;
								i = -1;
							}
						};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 60.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					};
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
			}
			if (m_Manager->Normal)
			{
				QueryGOs<Player>("Player", [&](Player* m_player)->bool
					{
						if (m_player->fever >= 20)
						{
							Mettimer = 0;
							if ((Kingtimer % 30) == 0)
							{
								KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
								do {
									sporn = Random().GetRandInt() % 24 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 24 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = -302.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 7:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 10:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 13:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 16:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 17:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 19:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 20:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 21:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 22:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 24:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 25:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
							}
							if ((timer % 20) == 0)
							{
								Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
								do {
									sporn = Random().GetRandInt() % 24 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 24 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = -302.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 7:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 10:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 13:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 16:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 17:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 19:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 20:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 21:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 22:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 24:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 25:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
								if ((FeintTimer % 20) == 0)
								{
									FeintMogura* m_Mogura = NewGO< FeintMogura>(0, "FeintMogura");
									do {
										sporn = Random().GetRandInt() % 24 + 1;
									} while (spornNo[sporn] != 0);
									/*MoguraPosition[MoguraKazu] = sporn;
									MoguraKazu++;
									if (MoguraKazu == 10) {
										MoguraKazu = 0;
									}
									for (int i = 0; i < i < 10; i++) {
										while (MoguraPosition[MoguraKazu])
										{
											sporn = Random().GetRandInt() % 24 + 1;
											i = -1;
										}
									};*/
									switch (sporn)
									{
									case 1:
										m_Mogura->m_position.x = -312.0f;
										m_Mogura->m_position.z = 185.0f;
										break;
									case 2:
										m_Mogura->m_position.x = -131.5f;
										m_Mogura->m_position.z = 185.0f;
										break;
									case 3:
										m_Mogura->m_position.x = 55.0f;
										m_Mogura->m_position.z = 185.0f;
										break;
									case 4:
										m_Mogura->m_position.x = 245.5f;
										m_Mogura->m_position.z = 185.0f;
										break;
									case 5:
										m_Mogura->m_position.x = 433.0f;
										m_Mogura->m_position.z = 185.0f;
										break;
									case 6:
										m_Mogura->m_position.x = -302.0f;
										m_Mogura->m_position.z = 78.0f;
										break;
									case 7:
										m_Mogura->m_position.x = -131.5f;
										m_Mogura->m_position.z = 78.0f;
										break;
									case 8:
										m_Mogura->m_position.x = 55.0f;
										m_Mogura->m_position.z = 78.0f;
										break;
									case 9:
										m_Mogura->m_position.x = 245.5f;
										m_Mogura->m_position.z = 78.0f;
										break;
									case 10:
										m_Mogura->m_position.x = 433.0f;
										m_Mogura->m_position.z = 78.0f;
										break;
									case 11:
										m_Mogura->m_position.x = -312.0f;
										m_Mogura->m_position.z = -17.0f;
										break;
									case 12:
										m_Mogura->m_position.x = -131.5f;
										m_Mogura->m_position.z = -17.0f;
										break;
									case 13:
										m_Mogura->m_position.x = 55.0f;
										m_Mogura->m_position.z = -17.0f;
										break;
									case 14:
										m_Mogura->m_position.x = 245.5f;
										m_Mogura->m_position.z = -17.0f;
										break;
									case 15:
										m_Mogura->m_position.x = 433.0f;
										m_Mogura->m_position.z = -17.0f;
										break;
									case 16:
										m_Mogura->m_position.x = -312.0f;
										m_Mogura->m_position.z = -125.0f;
										break;
									case 17:
										m_Mogura->m_position.x = -131.5f;
										m_Mogura->m_position.z = -125.0f;
										break;
									case 18:
										m_Mogura->m_position.x = 55.0f;
										m_Mogura->m_position.z = -125.0f;
										break;
									case 19:
										m_Mogura->m_position.x = 245.5f;
										m_Mogura->m_position.z = -125.0f;
										break;
									case 20:
										m_Mogura->m_position.x = 433.0f;
										m_Mogura->m_position.z = -125.0f;
										break;
									case 21:
										m_Mogura->m_position.x = 433.0f;
										m_Mogura->m_position.z = -222.0f;
										break;
									case 22:
										m_Mogura->m_position.x = 245.5f;
										m_Mogura->m_position.z = -222.0f;
										break;
									case 23:
										m_Mogura->m_position.x = 55.0f;
										m_Mogura->m_position.z = -222.0f;
										break;
									case 24:
										m_Mogura->m_position.x = -131.5f;
										m_Mogura->m_position.z = -222.0f;
										break;
									case 25:
										m_Mogura->m_position.x = -312.0f;
										m_Mogura->m_position.z = -222.0f;
										break;
									default:
										break;
									}
									m_Mogura->spornNo = sporn;
									spornNo[sporn] = 1;
								}
							}
						}
						return true;
					});
				if (FeintTimer >= 100)
				{
					FeintMogura* m_Mogura = NewGO< FeintMogura>(0, "FeintMogura");
					FeintTimer = 0;
					do {
						sporn = Random().GetRandInt() % 24 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 24 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = -302.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 10:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 13:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 16:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 17:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 19:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 20:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 21:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 22:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 24:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 25:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (SpornZaku == 1)
				{
					if (Zakutimer >= ZakuTimer)
					{
						Zaku* m_Mogura = NewGO<Zaku>(0, "Zaku");
						sporn = Random().GetRandInt() % 24 + 1;
						Zakutimer = 0;
						/*MoguraPosition[MoguraKazu] = sporn;
						MoguraKazu++;
						if (MoguraKazu == 10) {
							MoguraKazu = 0;
						}
						for (int i = 0; i < i < 10; i++) {
							while (MoguraPosition[MoguraKazu])
							{
								sporn = Random().GetRandInt() % 24 + 1;
								i = -1;
							}
						};*/
						switch (sporn)
						{
						case 1:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 2:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 3:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 4:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 5:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 6:
							m_Mogura->m_position.x = -302.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 7:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 8:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 9:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 10:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 11:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 12:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 13:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 14:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 15:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 16:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 17:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 18:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 19:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 20:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 21:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 22:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 23:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 24:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 25:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						default:
							break;
						}
					}
				}
				if (Kingtimer >= KingTimer)
				{
					KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
					Kingtimer = 0;
					do {
						sporn = Random().GetRandInt() % 24 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 24 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = -302.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 10:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 13:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 16:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 17:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 19:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 20:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 21:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 22:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 24:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 25:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (timer >= 100)
				{
					Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
					timer = 0;
					do {
						sporn = Random().GetRandInt() % 24 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 24 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = -302.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 10:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 13:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 16:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 17:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 19:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 20:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 21:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 22:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 24:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 25:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (Mettimer >= MetTimer)
				{
					Metooru* m_Mogura = NewGO<Metooru>(0, "Metooru");
					Mettimer = 0;
					do {
						sporn = Random().GetRandInt() % 24 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 24 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = -302.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 7:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 10:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 13:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 16:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 17:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 19:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 20:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 21:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 22:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 24:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 25:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
			}
			if (m_Manager->Hard)
			{
				QueryGOs<Player>("Player", [&](Player* m_player)->bool
					{
						if (m_player->fever >= 20)
						{
							if ((Mettimer % 10) == 0)
							{
								Metooru* m_Mogura = NewGO<Metooru>(0, "Metooru");
								Mettimer = 0;
								do {
									sporn = Random().GetRandInt() % 45 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 45 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -38.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 7:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 10:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 13:
									m_Mogura->m_position.x = -33.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 16:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 17:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 19:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 20:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 21:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 22:
									m_Mogura->m_position.x = -28.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 24:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 25:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 26:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 27:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 28:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 29:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 30:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 31:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 32:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 33:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 34:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 35:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 36:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 37:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 38:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 39:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 40:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 41:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 42:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 43:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 44:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 45:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
							}
							if ((FeintTimer % 20) == 0)
							{
								FeintMogura* m_Mogura = NewGO<FeintMogura>(0, "FeintMogura");
								do {
									sporn = Random().GetRandInt() % 45 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 45 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -38.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 7:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 10:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 13:
									m_Mogura->m_position.x = -33.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 16:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 17:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 19:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 20:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 21:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 22:
									m_Mogura->m_position.x = -28.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 24:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 25:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 26:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 27:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 28:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 29:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 30:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 31:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 32:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 33:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 34:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 35:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 36:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 37:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 38:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 39:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 40:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 41:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 42:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 43:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 44:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 45:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
							}
							if ((Kingtimer % 30) == 0)
							{
								KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
								do {
									sporn = Random().GetRandInt() % 45 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 45 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -38.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 5:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 7:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 10:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 13:
									m_Mogura->m_position.x = -33.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 16:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 17:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 19:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 20:
									m_Mogura->m_position.x = -208.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 21:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 22:
									m_Mogura->m_position.x = -28.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 24:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 25:
									m_Mogura->m_position.x = 235.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 26:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 27:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 28:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 29:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 30:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 31:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 32:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 33:
									m_Mogura->m_position.x = 140.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 34:
									m_Mogura->m_position.x = 225.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 35:
									m_Mogura->m_position.x = 328.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 36:
									m_Mogura->m_position.x = 423.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 37:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 38:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 39:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 40:
									m_Mogura->m_position.x = -48.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 41:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 42:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 43:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 44:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 45:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
							}
							if ((timer % 20) == 0)
							{//モグラのスポーン位置をｘに2,-8,-12,112.5,13、ｚに８０,20,-17,-27,-117ずらす。
								Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
								do {
									sporn = Random().GetRandInt() % 45 + 1;
								} while (spornNo[sporn] != 0);
								/*MoguraPosition[MoguraKazu] = sporn;
								MoguraKazu++;
								if (MoguraKazu == 10) {
									MoguraKazu = 0;
								}
								for (int i = 0; i < i < 10; i++) {
									while (MoguraPosition[MoguraKazu])
									{
										sporn = Random().GetRandInt() % 45 + 1;
										i = -1;
									}
								};*/
								switch (sporn)
								{
								case 1:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 2:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 3:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 4:
									m_Mogura->m_position.x = -88.5f;
									m_Mogura->m_position.z = 96.5f;
									break;
								case 5:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 6:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 7:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 8:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 9:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 185.0f;
									break;
								case 10:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 11:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 12:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 13:
									m_Mogura->m_position.x = -88.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 14:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 15:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 16:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 17:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 18:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = 78.0f;
									break;
								case 19:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 20:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 21:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 22:
									m_Mogura->m_position.x = -88.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 23:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 24:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 25:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 26:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 27:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -17.0f;
									break;
								case 28:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 29:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 30:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 31:
									m_Mogura->m_position.x = -88.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 32:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 33:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 34:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 35:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 36:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -125.0f;
									break;
								case 37:
									m_Mogura->m_position.x = -312.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 38:
									m_Mogura->m_position.x = -221.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 39:
									m_Mogura->m_position.x = -131.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 40:
									m_Mogura->m_position.x = -88.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 41:
									m_Mogura->m_position.x = 55.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 42:
									m_Mogura->m_position.x = 150.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 43:
									m_Mogura->m_position.x = 245.5f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 44:
									m_Mogura->m_position.x = 338.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								case 45:
									m_Mogura->m_position.x = 433.0f;
									m_Mogura->m_position.z = -222.0f;
									break;
								default:
									break;
								}
								m_Mogura->spornNo = sporn;
								spornNo[sporn] = 1;
							}
						}
						return true;
					});
				if (SpornZaku == 1)
				{
					if (Zakutimer >= ZakuTimer)
					{
						Zaku* m_Mogura = NewGO<Zaku>(0, "Zaku");
						sporn = Random().GetRandInt() % 45 + 1;
						Zakutimer = 0;
						/*MoguraPosition[MoguraKazu] = sporn;
						MoguraKazu++;
						if (MoguraKazu == 10) {
							MoguraKazu = 0;
						}
						for (int i = 0; i < i < 10; i++) {
							while (MoguraPosition[MoguraKazu])
							{
								sporn = Random().GetRandInt() % 45 + 1;
								i = -1;
							}
						};*/
						switch (sporn)
						{
						case 1:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 2:
							m_Mogura->m_position.x = -221.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 3:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 4:
							m_Mogura->m_position.x = -38.5f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 5:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 6:
							m_Mogura->m_position.x = 140.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 7:
							m_Mogura->m_position.x = 235.5f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 8:
							m_Mogura->m_position.x = 328.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 9:
							m_Mogura->m_position.x = 423.0f;
							m_Mogura->m_position.z = 185.0f;
							break;
						case 10:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 11:
							m_Mogura->m_position.x = -208.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 12:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 13:
							m_Mogura->m_position.x = -33.5f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 14:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 15:
							m_Mogura->m_position.x = 140.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 16:
							m_Mogura->m_position.x = 225.5f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 17:
							m_Mogura->m_position.x = 328.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 18:
							m_Mogura->m_position.x = 423.0f;
							m_Mogura->m_position.z = 78.0f;
							break;
						case 19:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 20:
							m_Mogura->m_position.x = -208.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 21:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 22:
							m_Mogura->m_position.x = -28.5f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 23:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 24:
							m_Mogura->m_position.x = 140.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 25:
							m_Mogura->m_position.x = 235.5f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 26:
							m_Mogura->m_position.x = 338.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 27:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -17.0f;
							break;
						case 28:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 29:
							m_Mogura->m_position.x = -221.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 30:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 31:
							m_Mogura->m_position.x = -48.5f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 32:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 33:
							m_Mogura->m_position.x = 140.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 34:
							m_Mogura->m_position.x = 225.5f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 35:
							m_Mogura->m_position.x = 328.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 36:
							m_Mogura->m_position.x = 423.0f;
							m_Mogura->m_position.z = -125.0f;
							break;
						case 37:
							m_Mogura->m_position.x = -312.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 38:
							m_Mogura->m_position.x = -221.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 39:
							m_Mogura->m_position.x = -131.5f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 40:
							m_Mogura->m_position.x = -48.5f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 41:
							m_Mogura->m_position.x = 55.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 42:
							m_Mogura->m_position.x = 150.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 43:
							m_Mogura->m_position.x = 245.5f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 44:
							m_Mogura->m_position.x = 338.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						case 45:
							m_Mogura->m_position.x = 433.0f;
							m_Mogura->m_position.z = -222.0f;
							break;
						default:
							break;
						}
					}
				}
				if (FeintTimer >= 100)
				{
					FeintMogura* m_Mogura = NewGO<FeintMogura>(0, "FeintMogura");
					FeintTimer = 0;
					do {
						sporn = Random().GetRandInt() % 45 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 45 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -38.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 7:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 10:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 13:
						m_Mogura->m_position.x = -33.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 16:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 17:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 19:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 20:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 21:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 22:
						m_Mogura->m_position.x = -28.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 24:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 25:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 26:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 27:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 28:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 29:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 30:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 31:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 32:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 33:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 34:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 35:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 36:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 37:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 38:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 39:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 40:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 41:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 42:
						m_Mogura->m_position.x = 150.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 43:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 44:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 45:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (Kingtimer >= KingTimer)
				{
					KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
					do {
						sporn = Random().GetRandInt() % 45 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 45 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -38.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 7:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 10:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 13:
						m_Mogura->m_position.x = -33.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 16:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 17:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 19:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 20:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 21:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 22:
						m_Mogura->m_position.x = -28.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 24:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 25:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 26:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 27:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 28:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 29:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 30:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 31:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 32:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 33:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 34:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 35:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 36:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 37:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 38:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 39:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 40:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 41:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 42:
						m_Mogura->m_position.x = 150.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 43:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 44:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 45:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					KingTimer++;
					Kingtimer = 0;
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (timer >= 100)
				{
					Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
					timer = 0;
					do {
						sporn = Random().GetRandInt() % 45 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 45 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -38.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 7:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 10:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 13:
						m_Mogura->m_position.x = -33.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 16:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 17:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 19:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 20:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 21:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 22:
						m_Mogura->m_position.x = -28.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 24:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 25:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 26:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 27:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 28:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 29:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 30:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 31:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 32:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 33:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 34:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 35:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 36:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 37:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 38:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 39:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 40:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 41:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 42:
						m_Mogura->m_position.x = 150.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 43:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 44:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 45:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
				if (Mettimer >= MetTimer)
				{
					Metooru* m_Mogura = NewGO<Metooru>(0, "Metooru");
					Mettimer = 0;
					Mettimer--;
					do {
						sporn = Random().GetRandInt() % 45 + 1;
					} while (spornNo[sporn] != 0);
					/*MoguraPosition[MoguraKazu] = sporn;
					MoguraKazu++;
					if (MoguraKazu == 10) {
						MoguraKazu = 0;
					}
					for (int i = 0; i < i < 10; i++) {
						while (MoguraPosition[MoguraKazu])
						{
							sporn = Random().GetRandInt() % 45 + 1;
							i = -1;
						}
					};*/
					switch (sporn)
					{
					case 1:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 2:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 3:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 4:
						m_Mogura->m_position.x = -38.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 5:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 6:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 7:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 8:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 9:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 185.0f;
						break;
					case 10:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 11:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 12:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 13:
						m_Mogura->m_position.x = -33.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 14:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 15:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 16:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 17:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 18:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = 78.0f;
						break;
					case 19:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 20:
						m_Mogura->m_position.x = -208.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 21:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 22:
						m_Mogura->m_position.x = -28.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 23:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 24:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 25:
						m_Mogura->m_position.x = 235.5f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 26:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 27:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -17.0f;
						break;
					case 28:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 29:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 30:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 31:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 32:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 33:
						m_Mogura->m_position.x = 140.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 34:
						m_Mogura->m_position.x = 225.5f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 35:
						m_Mogura->m_position.x = 328.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 36:
						m_Mogura->m_position.x = 423.0f;
						m_Mogura->m_position.z = -125.0f;
						break;
					case 37:
						m_Mogura->m_position.x = -312.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 38:
						m_Mogura->m_position.x = -221.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 39:
						m_Mogura->m_position.x = -131.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 40:
						m_Mogura->m_position.x = -48.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 41:
						m_Mogura->m_position.x = 55.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 42:
						m_Mogura->m_position.x = 150.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 43:
						m_Mogura->m_position.x = 245.5f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 44:
						m_Mogura->m_position.x = 338.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					case 45:
						m_Mogura->m_position.x = 433.0f;
						m_Mogura->m_position.z = -222.0f;
						break;
					default:
						break;
					}
					m_Mogura->spornNo = sporn;
					spornNo[sporn] = 1;
				}
			}
			return true;
		});
	/*float t = Random().GetRandDouble();
	float t2= Random().GetRandDouble();
	m_Mogura->m_position.z = CMath::Lerp(t, -200.0f, 200.0f);
	m_Mogura->m_position.x = CMath::Lerp(t2, -400.0f, 400.0f);*/
	/*for (int i = 0; i < 45; i++) {
		m_skinModel[i]->SetPosition(m_Position);
	}*/
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_scale == 4.0f)
			{
				if (Pad(0).IsPress(enButtonB))
				{
					Delete = true;
				}
			}
			return  true;
		});
	if (m_position.y <= -10000.0f) 
	{
		DeleteGO(this);
	}
	if (Delete) {
		m_position.y -= 10.0f;
		for (int i = 0; i < 45; i++) 
		{
			m_skinModel[i]->SetPosition(m_position);
		}
	}
}

CVector3 MoguraGenerator::EasySporn(CVector3 position)
{
	CVector3 m_Position;
	sporn = Random().GetRandInt() % 8 + 1;
	/*MoguraPosition[MoguraKazu] = sporn;
	MoguraKazu++;
	if (MoguraKazu == 10)
	{
		MoguraKazu = 0;
	}
	for (int i = 0; i < i < 10; i++)
	{
		while (MoguraPosition[MoguraKazu])
		{
			sporn = Random().GetRandInt() % 8 + 1;
			i = -1;
		}
	};*/
	switch (sporn)
	{
	case 1:
		/*m_Mogura->m_*/position.x = -312.0f;
		/*m_Mogura->m_*/position.z = 185.0f;
		break;
	case 2:
		/*m_Mogura->m_*/position.x = 60.0f;
		/*m_Mogura->m_*/position.z = 185.0f;
		break;
	case 3:
		/*m_Mogura->m_*/position.x = 433.0f;
		/*m_Mogura->m_*/position.z = 185.0f;
		break;
	case 4:
		/*m_Mogura->m_*/position.x = -312.0f;
		/*m_Mogura->m_*/position.z = -17.0f;
		break;
	case 5:
		/*m_Mogura->m_*/position.x = 60.0f;
		/*m_Mogura->m_*/position.z = -17.0f;
		break;
	case 6:
		/*m_Mogura->m_*/position.x = 433.0f;
		/*m_Mogura->m_*/position.z = -17.0f;
		break;
	case 7:
		/*m_Mogura->m_*/position.x = -312.0f;
		/*m_Mogura->m_*/position.z = -222.0f;
		break;
	case 8:
		/*m_Mogura->m_*/position.x = 60.0f;
		/*m_Mogura->m_*/position.z = -222.0f;
		break;
	case 9:
		/*m_Mogura->m_*/position.x = 433.0f;
		/*m_Mogura->m_*/position.z = -222.0f;
		break;
	default:
		break;
	};
	m_Position = position;
	return m_Position;
}

template<class t>
t MoguraGenerator::NormalSporn(t m_Mogura)
{
	sporn = Random().GetRandInt() % 24 + 1;
	/*MoguraPosition[MoguraKazu] = sporn;
	MoguraKazu++;
	if (MoguraKazu == 10) {
		MoguraKazu = 0;
	}
	for (int i = 0; i < i < 10; i++) {
		while (MoguraPosition[MoguraKazu])
		{
			sporn = Random().GetRandInt() % 24 + 1;
			i = -1;
		}
	};*/
	switch (sporn)
	{
	case 1:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 2:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 3:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 4:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 5:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 6:
		m_Mogura->m_position.x = -302.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 7:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 8:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 9:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 10:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 11:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 12:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 13:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 14:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 15:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 16:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 17:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 18:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 19:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 20:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 21:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 22:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 23:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 24:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 25:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	default:
		break;
	}
}

template<class t>
t MoguraGenerator::HardSporn(t m_Mogura)
{
	sporn = Random().GetRandInt() % 45 + 1;
	/*MoguraPosition[MoguraKazu] = sporn;
	MoguraKazu++;
	if (MoguraKazu == 10) {
		MoguraKazu = 0;
	}
	for (int i = 0; i < i < 10; i++) {
		while (MoguraPosition[MoguraKazu])
		{
			sporn = Random().GetRandInt() % 45 + 1;
			i = -1;
		}
	};*/
	switch (sporn)
	{
	case 1:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 2:
		m_Mogura->m_position.x = -221.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 3:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 4:
		m_Mogura->m_position.x = -88.5f;
		m_Mogura->m_position.z = 96.5f;
		break;
	case 5:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 6:
		m_Mogura->m_position.x = 150.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 7:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 8:
		m_Mogura->m_position.x = 338.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 9:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = 185.0f;
		break;
	case 10:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 11:
		m_Mogura->m_position.x = -221.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 12:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 13:
		m_Mogura->m_position.x = -88.5f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 14:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 15:
		m_Mogura->m_position.x = 150.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 16:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 17:
		m_Mogura->m_position.x = 338.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 18:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = 78.0f;
		break;
	case 19:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 20:
		m_Mogura->m_position.x = -221.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 21:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 22:
		m_Mogura->m_position.x = -88.5f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 23:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 24:
		m_Mogura->m_position.x = 150.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 25:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 26:
		m_Mogura->m_position.x = 338.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 27:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -17.0f;
		break;
	case 28:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 29:
		m_Mogura->m_position.x = -221.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 30:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 31:
		m_Mogura->m_position.x = -88.5f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 32:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 33:
		m_Mogura->m_position.x = 150.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 34:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 35:
		m_Mogura->m_position.x = 338.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 36:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -125.0f;
		break;
	case 37:
		m_Mogura->m_position.x = -312.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 38:
		m_Mogura->m_position.x = -221.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 39:
		m_Mogura->m_position.x = -131.5f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 40:
		m_Mogura->m_position.x = -88.5f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 41:
		m_Mogura->m_position.x = 55.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 42:
		m_Mogura->m_position.x = 150.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 43:
		m_Mogura->m_position.x = 245.5f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 44:
		m_Mogura->m_position.x = 338.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	case 45:
		m_Mogura->m_position.x = 433.0f;
		m_Mogura->m_position.z = -222.0f;
		break;
	default:
		break;
	}
}