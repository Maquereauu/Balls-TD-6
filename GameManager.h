#pragma once
#include <SFML/Graphics.hpp>
#include "FileReader.h"
class GameObject;
class Bullet;
class Tower;
class Window;

class GameManager
{
private:
	sf::Font font;
	sf::Text text;
	static GameManager* pInstance;
	void Initialize();
	int money;
	int metal;
	int health;
	std::vector<Bullet*>* _o_bullet;
	Window* _o_window;
	std::vector<Tower*> _o_tower;
	GameObject* _o_enemy;
	GameManager() {};
	sf::Clock o_timer;
	float timer;
	sf::RenderWindow* _window;
	sf::Font _font;
	GameObject* _o_door;
	GameObject* uhdSelectTowerUn;
	GameObject* uhdSelectTowerDeux;
	GameObject* uhdSelectTowertroi;
    int TowerCreated;
public:

	FileReader* o_model;
	std::vector<std::vector<std::vector<std::vector<double>>>> _modelStats;
	int* _width;
	int* _height;
	std::vector<std::vector<GameObject*>> _entities;
	std::vector<Tower*> _towers;
	sf::Vector2i* _mousePos;

	typedef enum GameArea
	{
		Maps,
		TowerArea,
		SelectFirstTurret,
		SelectSecondTurret,
		SelectThirdTurret,
		FirstTurret,
		SecondTurret,
		ThirdTurret,
		start,
		Restart,
		Quit,
		Game
	};

	static void Create();

	static GameManager* Get()
	{
		return pInstance;
	}

	//void MthrowBullet();
	void Mretry();
	void MselectTowerUn();
	void MselectTowerDeux();
	void MselectTowerTroi();
	void Mquit();
	void MPosetaTour();
	void MUpgrade(Tower latour);
	bool Mwin();
	void MmoveTower();
	std::vector<Tower*>& GetTowerList();

	float _speed = 90.f; //
	void launchGame();
	void addToEntity(int iLabel, GameObject* o_gameObject);
	void addToEntity(Tower* o_tower);
};

