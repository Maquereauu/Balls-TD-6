#pragma once
#include <SFML/Graphics.hpp>
#include "FileReader.h"
class GameObject;
class Bullet;
class Enemy;
class Tower;
class BlastBullet;
class Window;

class GameManager
{
private:
	sf::Font font;
	sf::Texture _texture;
	sf::Sprite* _background;
	sf::Text text;
	sf::Text winText;
	sf::Text loseText;
	static GameManager* pInstance;
	void Initialize();
	std::vector<Bullet*>* _o_bullet;
	Window* _o_window;
	Enemy* _o_enemy;
	std::vector<Enemy*> firstWave;
	std::vector<Enemy*> secondWave;
	std::vector<Enemy*> thirdWave;
	std::vector<int> firstWaveTypes;
	std::vector<int> secondWaveTypes;
	std::vector<int> thirdWaveTypes;
	std::vector<Tower*> _o_tower;
	GameManager() {};
	sf::Clock o_timer;
	float timer;
	sf::Clock o_timerSpawn;
	float timerSpawn;
	bool _test;
	sf::RenderWindow* _window;
	sf::Font _font;
	std::vector<std::vector<int>> _waves;
public:
	int money;
	int metal;
	GameObject* _o_door;
	int health;
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
	std::vector<Enemy*> _enemies;
	std::vector<BlastBullet*> _blastBullets;
	std::vector<Bullet*> _blastRadius;
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
	void addToEntity(Enemy* o_enemy);
	void addToEntity(BlastBullet* o_blastBullet);
	void addToEntity(Bullet* o_bullet);
};

