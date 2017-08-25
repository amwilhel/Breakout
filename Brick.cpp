#include "Ball.h"
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

//Make a new brick
Brick::Brick() {
	brick.setSize(Vector2f(80, 20));
	regBrickTex.loadFromFile("brick1.jpg");
	upBrickTex.loadFromFile("brick2.jpg");
	brick.setTexture(&regBrickTex);
	brickHealth = 1;
}

//Upgrade a brick to a two hit brick
void Brick::UpgradeBrick() {
	brickHealth += 1;
}

//Draw the brick on the board
void Brick::Draw(RenderWindow &board) {
	board.draw(brick);
}

//Get the position of the brick
Vector2f Brick::getPosition() {
	return brick.getPosition();
}

//Set the position of the brick
void Brick::setPosition(Vector2f pos) {
	brick.setPosition(pos);
}

//Change the texture of the brick
void Brick::setTexture(sf::Texture &tex) {
	brick.setTexture(&tex);
}
