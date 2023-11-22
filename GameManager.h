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

	static GameManager* pInstance;
	void Initialize();
	int money;
	int metal;
	int health;
	std::vector<Bullet*>* _o_bullet;
	Window* _o_window;
	Tower* _o_tower;
	GameManager() {};
	sf::Clock o_timer;
	float timer;
	sf::RenderWindow* _window;
	sf::Font _font;

public:
	FileReader* o_model;
	std::vector<std::vector<std::vector<std::vector<double>>>> _modelStats;
	int* _width;
	int* _height;
	std::vector<std::vector<GameObject*>> _entities;
	sf::Vector2i* _mousePos;

	typedef enum GameArea
	{
		None,
		Game,
		Restart,
		Quit
	};

	static void Create();

	static GameManager* Get()
	{
		return pInstance;
	}

	void MthrowBullet();
	void Mretry();
	void Mquit();
	bool Mwin();
	void MmoveTower();

	float _speed = 90.f; //
	void launchGame();
	void addToEntity(int iLabel, GameObject* o_gameObject);
};

