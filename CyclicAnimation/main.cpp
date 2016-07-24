#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

struct AnimationSpeed
{
	float rectanglesSpeedInStep[10];
	float animationSpeedInStep[10];
};

struct Animation
{
	RectangleShape *rectangles[5];
	int animationStep;
	AnimationSpeed *animationSpeed;
};

struct Application
{
	RenderWindow *window;
	Clock *applicationClock;
	Clock *updateClock;
	float applicationTime;
	float updateTime;
	int antialiasing;
	Animation *animation;
};

void initApplication(Application *application, int width, int height, int antialiasing);
void initAnimation(Animation *animation);
void initAnimationSpeed(Animation *animation);
void moveAnimation(Application *application, float dx, float dy);
void rotateAnimation(Application *application, float rotationSpeed);

void initApplication(Application *application,int width, int height, int antialiasing)
{
	application->window = new RenderWindow (VideoMode (width, height), "My animation");
	application->applicationClock = new Clock;
	application->updateClock = new Clock;
	application->antialiasing = antialiasing;
	application->animation = new Animation;
	initAnimation(application->animation);
}

void initAnimation(Animation *animation)
{
	animation->animationStep = 0;
	for (int i = 0; i < 5; i++) 
	{
		animation->rectangles[i] = new RectangleShape(Vector2f(20, 20));
		animation->rectangles[i]->setOrigin(10, 10);
		animation->rectangles[i]->setPosition(70, 70);
		animation->rectangles[i]->setFillColor(Color::Green);
	}
	animation->animationSpeed = new AnimationSpeed;
	initAnimationSpeed(animation);
}

void initAnimationSpeed(Animation *animation)
{
	animation->animationSpeed->rectanglesSpeedInStep[1] = 40.0f / 2.0f;
	animation->animationSpeed->rectanglesSpeedInStep[2] = animation->animationSpeed->rectanglesSpeedInStep[1];
	animation->animationSpeed->rectanglesSpeedInStep[3] = animation->animationSpeed->rectanglesSpeedInStep[1];
	animation->animationSpeed->rectanglesSpeedInStep[4] = animation->animationSpeed->rectanglesSpeedInStep[1];
	animation->animationSpeed->rectanglesSpeedInStep[5] = animation->animationSpeed->rectanglesSpeedInStep[1];
	animation->animationSpeed->rectanglesSpeedInStep[8] = animation->animationSpeed->rectanglesSpeedInStep[1] * 2.0f;
	animation->animationSpeed->rectanglesSpeedInStep[9] = animation->animationSpeed->rectanglesSpeedInStep[1] * 20.0f;
	//
	animation->animationSpeed->animationSpeedInStep[2] = 230.0f / 2.0f;
	animation->animationSpeed->animationSpeedInStep[3] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[4] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[5] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[6] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[7] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[8] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[9] = animation->animationSpeed->animationSpeedInStep[2];
	animation->animationSpeed->animationSpeedInStep[10] = animation->animationSpeed->animationSpeedInStep[2];
}

void doStep0(Application *application)
{
	for (int i = 0; i < 5; i++)
	{
		application->animation->rectangles[i]->setOrigin(10, 10);
		application->animation->rectangles[i]->setPosition(70, 70);
		application->animation->rectangles[i]->setFillColor(Color::Green);
	}
	application->animation->animationStep = (application->applicationClock->getElapsedTime().asSeconds() >= 1) ? 1 : 0;
	//cout << application->applicationClock->getElapsedTime().asSeconds() << endl;
}

void doStep1(Application *application)
{
	application->animation->rectangles[0]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[1] * application->updateTime);
	application->animation->rectangles[1]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[1] * application->updateTime, 0);
	application->animation->rectangles[3]->move(application->animation->animationSpeed->rectanglesSpeedInStep[1] * application->updateTime, 0);
	application->animation->rectangles[4]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[1] * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 3) ? 2 : 1;
}

void doStep2(Application *application)
{
	moveAnimation(application, 0, application->animation->animationSpeed->animationSpeedInStep[2] * application->updateTime);
	application->animation->rectangles[0]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[2] * application->updateTime, 0);
	application->animation->rectangles[1]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[2] * application->updateTime);
	application->animation->rectangles[3]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[2] * application->updateTime);
	application->animation->rectangles[4]->move(application->animation->animationSpeed->rectanglesSpeedInStep[2] * application->updateTime, 0);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 5) ? 3 : 2;
}

void doStep3(Application *application)
{
	moveAnimation(application, 0, application->animation->animationSpeed->animationSpeedInStep[3] * application->updateTime);
	application->animation->rectangles[0]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[3] * application->updateTime);
	application->animation->rectangles[1]->move(application->animation->animationSpeed->rectanglesSpeedInStep[3] * application->updateTime, 0);
	application->animation->rectangles[3]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[3] * application->updateTime, 0);
	application->animation->rectangles[4]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[3] * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 7) ? 4 : 3;
}

void doStep4(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed->animationSpeedInStep[4] * application->updateTime, -application->animation->animationSpeed->animationSpeedInStep[4] * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime, -application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->rectangles[1]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->rectangles[3]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime, application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 9) ? 5 : 4;
}

void doStep5(Application *application) 
{
	moveAnimation(application, application->animation->animationSpeed->animationSpeedInStep[5] * application->updateTime, -application->animation->animationSpeed->animationSpeedInStep[5] * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->animationSpeed->rectanglesSpeedInStep[5] * application->updateTime, application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->rectangles[1]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[5] * application->updateTime);
	application->animation->rectangles[3]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[5] * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[5] * application->updateTime, -application->animation->animationSpeed->rectanglesSpeedInStep[4] * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 11) ? 6 : 5;
}

void doStep6(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed->animationSpeedInStep[6] * application->updateTime, application->animation->animationSpeed->animationSpeedInStep[6] * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x < 3.0f) 
	{
		application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 1.001f, application->animation->rectangles[2]->getScale().y * 1.001f);
	}
	application->animation->rectangles[0]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[1]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[2]->rotate(-180.0f * application->updateTime);
	application->animation->rectangles[3]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[4]->rotate(180.0f * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 13) ? 7 : 6;
}

void doStep7(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed->animationSpeedInStep[7] * application->updateTime, application->animation->animationSpeed->animationSpeedInStep[7] * application->updateTime);
	//rotateAnimation(application, 90.0f);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 15) ? 8 : 7;
}

void doStep8(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed->animationSpeedInStep[8] * application->updateTime, -application->animation->animationSpeed->animationSpeedInStep[8] * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x > 0.5f)
	{
		application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 0.999f, application->animation->rectangles[2]->getScale().y * 0.999f);
	}
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 17) ? 9 : 8;
	//move
	//scale
	//rotate
	//прозразность
}

void doStep9(Application *application)
{
	application->animation->rectangles[2]->setScale(1.0f, 1.0f);
	application->animation->rectangles[0]->move(-application->animation->animationSpeed->rectanglesSpeedInStep[9] * application->updateTime, 0);
	application->animation->rectangles[1]->move(0, -application->animation->animationSpeed->rectanglesSpeedInStep[9] * application->updateTime);
	application->animation->rectangles[3]->move(0, application->animation->animationSpeed->rectanglesSpeedInStep[9] * application->updateTime);
	application->animation->rectangles[4]->move(application->animation->animationSpeed->rectanglesSpeedInStep[9] * application->updateTime, 0);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 18) ? 10 : 9;
}

void doStep10(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed->animationSpeedInStep[10] * application->updateTime, -application->animation->animationSpeed->animationSpeedInStep[10] * application->updateTime);
	if (application->applicationClock->getElapsedTime().asSeconds() >= 20)
	{
		application->animation->animationStep = 0;
		application->applicationClock->restart();
	}
	else
	{
		application->animation->animationStep = 10;
	}
}

void rotateAnimation(Application *application, float rotationSpeed)
{
	if (application->applicationClock->getElapsedTime().asSeconds() <= 15.00001f) {
		for (int i = 0; i < 5; i++)
		{
			application->animation->rectangles[i]->setOrigin(860.0f, 300.0f);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		application->animation->rectangles[i]->rotate(rotationSpeed * application->updateTime);
	}
}

void moveAnimation(Application *application, float dx, float dy)
{
	for (int i = 0; i < 5; i++)
	{
		application->animation->rectangles[i]->move(dx , dy);
	}
}

void updateAnimation(Application *application)
{
	application->updateTime = application->updateClock->getElapsedTime().asSeconds();
	application->updateClock->restart();
	switch (application->animation->animationStep)
	{
		case 0: doStep0(application);	break;
		case 1: doStep1(application);	break;
		case 2: doStep2(application);	break;
		case 3: doStep3(application);	break;
		case 4:	doStep4(application);	break;
		case 5:	doStep5(application);	break;
		case 6:	doStep6(application);	break;
		case 7:	doStep7(application);	break;
		case 8:	doStep8(application);	break;
		case 9:	doStep9(application);	break;
		case 10: doStep10(application);	break;
		default: break;
	}
}

void drawAFrame(Application *application)
{
	application->window->clear();
	for (int i = 0; i < 5; i++)
	{
		application->window->draw(*application->animation->rectangles[i]);
	}
	application->window->display();
}

void gameLoop(Application *application)
{
	while (application->window->isOpen())
	{
		Event event;
		while (application->window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				application->window->close();
		}
		updateAnimation(application);
		drawAFrame(application);
	}
}

int main()
{
	Application application;
	initApplication(&application, 970, 600, 8);
	gameLoop(&application);
	return 0;
}