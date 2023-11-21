#pragma once
#include <SFML/Graphics.hpp>

class GameObject;
class Ball;
class Cannon;
class Window;

class GameManager
{
private:

	static GameManager* pInstance;
	void Initialize();
	int money;
	int metal;
	int health;
	std::vector<Ball*>* _o_balls;
	Window* _o_window;
	Cannon* _o_cannon;
	GameManager() {};
	sf::Clock o_timer;
	float timer;

	sf::RenderWindow* _window;
	sf::Font _font;

public:

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

	void MthrowBall();
	void Mretry();
	void Mquit();
	bool Mwin();
	void MmoveCannon();

	float _speed = 90.f; //
	void launchGame();
	void addToEntity(int iLabel, GameObject* o_gameObject);
};

