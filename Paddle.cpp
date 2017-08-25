#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

//Create a new paddle
Paddle::Paddle() {
	paddle.setSize(Vector2f(80, 20));
	paddle.setFillColor(sf::Color::White);
}

//Draw the paddle on the board
void Paddle::Draw(RenderWindow &board) {
	board.draw(paddle);
}

//Get the position of the paddle
Vector2f Paddle::getPosition() {
	return paddle.getPosition();
}

//Set the position of the paddle
void Paddle::setPosition(Vector2f pos) {
	 paddle.setPosition(pos);
}
