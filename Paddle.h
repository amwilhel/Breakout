#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

class Paddle {

public:
	RectangleShape paddle;
	Paddle();
	void Draw(RenderWindow &board);
	Vector2f getPosition();
	void setPosition(Vector2f pos);
}; 
