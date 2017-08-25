#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
using namespace std;

void update_state(float dt);
void render_frame();

RenderWindow window;
RectangleShape shape;
Texture tex;
SoundBuffer buf;
SoundBuffer buf1;
SoundBuffer buf2;
SoundBuffer buf3;
SoundBuffer buf4;
SoundBuffer buf5;
Sound sound;
Sound sound1;
Sound sound2;
Sound sound3;
Sound sound4;
Sound sound5;
Ball ball;
Paddle paddle1;
vector<Brick> brickLevel(10);
Font font;
Text gameover;
int health;
int score;
int levelsPlayed;
int bricksHit;
bool isgameover;
bool startLevel;
bool loadLevel2;


int main()
{
	//Set the game up
	isgameover = false;
	startLevel = false;
	loadLevel2 = false;
	window.create(VideoMode(800, 600), "Breakout");
	ball = Ball (Vector2f(0, 0), window);
	paddle1.setPosition(Vector2f(400, 560));
	health = 3;
	score = 0;
	bricksHit = 0;
	levelsPlayed = 1;

	//Set up level 1
	for (int i = 0; i < brickLevel.size(); i++) {
		brickLevel[i].brickHealth = 1;
		if (i == 3 || i == 8) {
			brickLevel[i].UpgradeBrick();
			brickLevel[i].setTexture(brickLevel[i].upBrickTex);
		}

	}
	
	//Set up audio, textures, and fonts
	font.loadFromFile("starjedi.TTF");
	buf.loadFromFile("sound_destroyBrick.wav");
	buf1.loadFromFile("sound_damageBrick.wav");
	buf2.loadFromFile("sound_hitPaddle.wav");
	buf3.loadFromFile("sound_wallHit.wav");
	buf4.loadFromFile("sound_loseLife.wav");
	buf5.loadFromFile("sound_winLevel.wav");
	sound.setBuffer(buf);
	sound1.setBuffer(buf1);
	sound2.setBuffer(buf2);
	sound3.setBuffer(buf3);
	sound4.setBuffer(buf4);
	sound5.setBuffer(buf5);
	sound5.play();


	//Set up timing and update events
	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		update_state(dt);
		render_frame();
		window.display();
	}

	return 0;
}

void update_state(float dt)
{
	//Play a new ball on space press
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (!startLevel) {
			ball.setVelocity(Vector2f(-100 * levelsPlayed, -100 * levelsPlayed));
			sound2.play();
			startLevel = true;
		}

	}

	//Start the game with the ball on the paddle
	if (!startLevel) {
		ball.setPosition(Vector2f(paddle1.getPosition().x + 40, paddle1.getPosition().y - 10));
	}

	//Move the ball
	if(ball.Move(dt))
		sound3.play();
	

	//Move the paddle
	Vector2f pos = paddle1.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (pos.x >= 0)
			pos.x -= 200 * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (pos.x <= window.getSize().x - 80)
			pos.x += 200 * dt;
	}
	paddle1.setPosition(pos);


	//Check if ball hits the Paddle
	if (ball.getPosition().x <= paddle1.getPosition().x + 80 && ball.getPosition().x >= paddle1.getPosition().x && ball.getPosition().y <= paddle1.getPosition().y + 20 && ball.getPosition().y >= paddle1.getPosition().y) {
		float ballpos = ball.getPosition().x - paddle1.getPosition().x;
		ball.velocity.y = ball.velocity.y * -1;
		ball.velocity.x += ballpos;
		sound2.play();
	}

	//Check if ball hits a brick
	for (int i = 0; i < brickLevel.size(); i++) {
		if (brickLevel[i].brickHealth > 0 && ball.getPosition().x <= brickLevel[i].getPosition().x + 80 && ball.getPosition().x >= brickLevel[i].getPosition().x && ball.getPosition().y <= brickLevel[i].getPosition().y + 20 && ball.getPosition().y >= brickLevel[i].getPosition().y) {
			ball.velocity.y = ball.velocity.y * -1;
			ball.velocity.x = ball.velocity.x * -1;
			score += 10;
			brickLevel[i].brickHealth -= 1;
			brickLevel[i].setTexture(brickLevel[i].regBrickTex);
			if (brickLevel[i].brickHealth == 0) {
				bricksHit++;
				sound.play();
			}
			sound1.play();
		}
	}

	//If not hit by the paddle check that ball went out of bounds and update health
	if (ball.getPosition().y >= window.getSize().y) {
		health--;
		ball.setPosition(Vector2f(440, 550));
		ball.setVelocity(Vector2f(0, 0));
		if (health > 0)
			sound4.play();
		startLevel = false;
	}

	//Check if health is 0 then gameover
	if (health == 0) {
		gameover.setString("game over");
		ball.setVelocity(Vector2f(0, 0));
		ball.setPosition(Vector2f(440, 550));
		isgameover = true;
	}

	//Check if level is complete
	if (bricksHit == brickLevel.size()) {
		sound5.play();

		//Load odd numbered levels
		if (loadLevel2) {
			brickLevel.resize(10);
			loadLevel2 = false;
			//Set up board 1
			for (int i = 0; i < brickLevel.size(); i++) {
				brickLevel[i].brickHealth = 1;
				brickLevel[i].setTexture(brickLevel[i].regBrickTex);
				if (i == 3 || i == 8) {
					brickLevel[i].UpgradeBrick();
					brickLevel[i].setTexture(brickLevel[i].upBrickTex);
				}
			}
		}

		//Load even number levels
		else {
			brickLevel.resize(24);
			loadLevel2 = true;
			//Set up board 2
			for (int i = 0; i < brickLevel.size(); i++) {
				brickLevel[i].brickHealth = 1;
				brickLevel[i].setTexture(brickLevel[i].regBrickTex);
				if (i == 3 || i == 8 || i == 15 || i == 22 || i == 12) {
					brickLevel[i].UpgradeBrick();
					brickLevel[i].setTexture(brickLevel[i].upBrickTex);
				}
			}
		}

		ball.setPosition(Vector2f(paddle1.getPosition().x + 40, paddle1.getPosition().y - 10));
		ball.setVelocity(Vector2f(0, 0));
		startLevel = false;
		bricksHit = 0;
		levelsPlayed++;
	}
}

void render_frame()
{
	//Draw all UI elements
	window.clear(Color(0, 0, 0));
	window.draw(shape);
	paddle1.Draw(window);
	ball.Draw(window);


	//Draw Board 2
	if (loadLevel2) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				if (brickLevel[i * 3 + j].brickHealth > 0) {
					brickLevel[i * 3 + j].setPosition(Vector2f(i * 90 + 50, j * 40 + 200));
					brickLevel[i * 3 + j].Draw(window);
				}
			}
		}
	}

	//Draw Board 1
	if (!loadLevel2) {
	 for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 5; j++) {
				if (brickLevel[i * 5 + j].brickHealth > 0) {
					brickLevel[i * 5 + j].setPosition(Vector2f(i * 150 + 300, j * 60 + 200));
					brickLevel[i * 5 + j].Draw(window);
				}
			}
		}
	}
	
	//Draw UI Elements
	Text text1;
	Text text2;
	Text text3;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	gameover.setFont(font);
	text1.setCharacterSize(75);
	text2.setCharacterSize(75);
	text3.setCharacterSize(75);
	gameover.setCharacterSize(75);
	text1.setString(to_string(health));
	text2.setString(to_string(score));
	text3.setString("breakout");
	text1.setFillColor(Color::Yellow);
	text2.setFillColor(Color::White);
	text3.setFillColor(Color::White);
	gameover.setFillColor(Color::Yellow);
	text1.setPosition(25, 5);
	text2.setPosition(650, 5);
	text3.setPosition(175, 5);
	gameover.setPosition(165, 400);
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.draw(gameover);
}