#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

class Brick {

public:
	RectangleShape brick;
	Texture regBrickTex;
	Texture upBrickTex;
	int brickHealth;
	Brick();
	void UpgradeBrick();
	void Draw(RenderWindow &board);
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	void setTexture(sf::Texture &tex);
};

