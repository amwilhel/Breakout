#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

class Ball {

public:
	RectangleShape ball;
	Ball();
	Ball(RenderWindow &board);
	Ball(Vector2f vel, RenderWindow &board);
	void Draw(RenderWindow &board);
	Vector2f velocity;
	Vector2f board_size;
	bool Ball::Move(float time);
	void Ball::setVelocity(Vector2f vel);
	void Ball::setPosition(Vector2f pos);
	Vector2f getPosition();
	
};
