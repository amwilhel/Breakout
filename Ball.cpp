#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

Ball::Ball() {

}
//Make a new ball with 0 Velocity
Ball::Ball(RenderWindow &board){
	ball.setSize(Vector2f(10, 10));
	ball.setFillColor(sf::Color::Yellow);
	ball.setPosition(440, 550);
	velocity = Vector2f(0, 0);
	board_size = Vector2f(board.getSize().x, board.getSize().y);
}

//Make a new ball with a given velocity
Ball::Ball(Vector2f vel, RenderWindow &board) {
	ball.setSize(Vector2f(10, 10));
	ball.setFillColor(sf::Color::Yellow);
	ball.setPosition(440, 550);
	board_size = Vector2f(board.getSize().x, board.getSize().y);
	velocity = vel;
};

//Draw the ball
void Ball::Draw(RenderWindow &board) {
	board.draw(ball);
}

//Move the ball and check for the boundaries of the board
bool Ball::Move(float time) {
	Vector2f pos = ball.getPosition() + velocity*time;
	ball.setPosition(pos);

	if (ball.getPosition().x >= board_size.x) {
		velocity.x = velocity.x * -1;
		return true;
	}
	else if (ball.getPosition().x <= 0) {
		velocity.x = velocity.x * -1;
		return true;
	}
	else if (ball.getPosition().y <= 0) {
		velocity.y = velocity.y * -1;
		return true;
	}
	return false;
}

//Set velocity of the ball
void Ball::setVelocity(Vector2f vel) {
	velocity = vel;
}

//Get position of the ball
Vector2f Ball::getPosition() {
	return ball.getPosition();
}

//Set position of the ball
void Ball::setPosition(Vector2f pos) {
	ball.setPosition(pos);
}