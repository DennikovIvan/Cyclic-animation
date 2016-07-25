#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

struct Animation
{
	RectangleShape *rectangles[5];
	int animationStep;
	float rectanglesSpeed;
	float animationSpeed;
};

struct Application
{
	RenderWindow *window;
	Clock *applicationClock;
	Clock *updateClock;
	float applicationTime;
	float updateTime;
	Animation *animation;
};

void initApplication(Application *application, int width, int height);
void initAnimation(Animation *animation);
void moveAnimation(Application *application, float dx, float dy);
void rotateAnimation(Application *application, float rotationSpeed);

void initApplication(Application *application,int width, int height)
{
	application->window = new RenderWindow (VideoMode (width, height), "My animation", Style::Close, ContextSettings(0, 0, 8));
	application->applicationClock = new Clock;
	application->updateClock = new Clock;
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
	animation->rectanglesSpeed = 20.0f;
	animation->animationSpeed = 115.0f;
}

void doStep0(Application *application)
{
	for (int i = 0; i < 5; i++)
	{
		application->animation->rectangles[i]->setOrigin(10, 10);
		application->animation->rectangles[i]->setPosition(70, 70);
		application->animation->rectangles[i]->setRotation(0);
		if (i == 2) 
		{
			application->animation->rectangles[i]->setFillColor(Color(0, 255, 0, int(application->animation->rectangles[i]->getFillColor().a + 255 * 0.01f)));
		}
		else
		{
			application->animation->rectangles[i]->setFillColor(Color(0, 255, 0, 0));
		}
	}
	if (application->applicationClock->getElapsedTime().asSeconds() >= 3)
	{
		application->animation->animationStep = 1;
		for (int i = 0; i < 5; i++)
		{
			application->animation->rectangles[i]->setFillColor(Color(0, 255, 0, 255));
		}
	}
	else
	{
		application->animation->animationStep = 0;
	}
}

void doStep1(Application *application)
{
	application->animation->rectangles[0]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(-application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[3]->move(application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[4]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 5 ? 2 : 1;
}

void doStep2(Application *application)
{
	moveAnimation(application, 0, application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(-application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[1]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[3]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[4]->move(application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 7) ? 3 : 2;
}

void doStep3(Application *application)
{
	moveAnimation(application, 0, application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[3]->move(-application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[4]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 9) ? 4 : 3;
}

void doStep4(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->rectanglesSpeed * application->updateTime, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[3]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->rectanglesSpeed * application->updateTime, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 11) ? 5 : 4;
}

void doStep5(Application *application) 
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->rectanglesSpeed * application->updateTime, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[3]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->rectanglesSpeed * application->updateTime, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 13) ? 6 : 5;
}

void doStep6(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, application->animation->animationSpeed * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x < 3.0f) 
	{
		application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 1.001f, application->animation->rectangles[2]->getScale().y * 1.001f);
	}
	application->animation->rectangles[0]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[1]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[2]->rotate(-180.0f * application->updateTime);
	application->animation->rectangles[3]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[4]->rotate(180.0f * application->updateTime);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 15) ? 7 : 6;
}

void doStep7(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, application->animation->animationSpeed * application->updateTime);
	//rotateAnimation(application, 90.0f);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 17) ? 8 : 7;
}

void doStep8(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x > 0.5f)
	{
		application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 0.999f, application->animation->rectangles[2]->getScale().y * 0.999f);
	}
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 19) ? 9 : 8;
	//move
	//scale
	//rotate
	//прозразность
}

void doStep9(Application *application)
{
	application->animation->rectangles[2]->setScale(1.0f, 1.0f);
	application->animation->rectangles[0]->move(-application->animation->rectanglesSpeed * 20.0f * application->updateTime, 0);
	application->animation->rectangles[1]->move(0, -application->animation->rectanglesSpeed * 20.0f * application->updateTime);
	application->animation->rectangles[3]->move(0, application->animation->rectanglesSpeed * 20.0f * application->updateTime);
	application->animation->rectangles[4]->move(application->animation->rectanglesSpeed * 20.0f * application->updateTime, 0);
	application->animation->animationStep = float(application->applicationClock->getElapsedTime().asSeconds() >= 20) ? 10 : 9;
}

void doStep10(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	if (application->applicationClock->getElapsedTime().asSeconds() >= 22)
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
	initApplication(&application, 900, 600);
	gameLoop(&application);
	return 0;
}