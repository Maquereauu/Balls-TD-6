#include "Window.h"

#include "GameObject.h"

Window::Window(int sizeX, int sizeY)
{
	_sizeX = sizeX;
	_sizeY = sizeY;
	_window = new sf::RenderWindow(sf::VideoMode(_sizeX, _sizeY), "Casse-briques");

}

void Window::winDraw(std::vector<GameObject*> list)
{
	for (int i = 0; i < list.size(); i++) {
		_window->draw(list.at(i)->getShape());
	}
}

sf::RenderWindow* Window::getWindow()
{
	return _window;
}