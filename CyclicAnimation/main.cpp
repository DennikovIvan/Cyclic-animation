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
	float animationOpacity;
	bool isOriginChanged = false;
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
void setAnimationSettingsOnStart(Application *application);
void setAnimationOpacity(Application *application);

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
	animation->animationOpacity = 0.0f;
	for (int i = 0; i < 5; i++) 
	{
		animation->rectangles[i] = new RectangleShape(Vector2f(20, 20));
		animation->rectangles[i]->setOrigin(10, 10);
		animation->rectangles[i]->setPosition(70, 70);
		animation->rectangles[i]->setFillColor(Color(0, 255, 0, Uint8(animation->animationOpacity)));
	}
	animation->rectanglesSpeed = 20.0f;
	animation->animationSpeed = 115.0f;
}

void doStep0(Application *application)
{
	application->animation->animationOpacity = (application->animation->animationOpacity >= 255.0f) ? 255.0f : application->animation->animationOpacity + 0.3f;
	setAnimationSettingsOnStart(application);
	application->animation->rectangles[2]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
	if (application->applicationClock->getElapsedTime().asSeconds() >= 3)
	{
		setAnimationOpacity(application);
		application->animation->animationStep = 1;
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
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 7 ? 3 : 2;
}

void doStep3(Application *application)
{
	moveAnimation(application, 0, application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[3]->move(-application->animation->rectanglesSpeed * application->updateTime, 0);
	application->animation->rectangles[4]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 9 ? 4 : 3;
}

void doStep4(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->rectanglesSpeed * application->updateTime, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[3]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->rectanglesSpeed * application->updateTime, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 11 ? 5 : 4;
}

void doStep5(Application *application) 
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	application->animation->rectangles[0]->move(application->animation->rectanglesSpeed * application->updateTime, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[1]->move(0, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[3]->move(0, application->animation->rectanglesSpeed * application->updateTime);
	application->animation->rectangles[4]->move(-application->animation->rectanglesSpeed * application->updateTime, -application->animation->rectanglesSpeed * application->updateTime);
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 13 ? 6 : 5;
}

void doStep6(Application *application)
{
	moveAnimation(application, application->animation->animationSpeed * application->updateTime, application->animation->animationSpeed * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x < 3.0f) application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 1.001f, application->animation->rectangles[2]->getScale().y * 1.001f);
	application->animation->rectangles[0]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[1]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[2]->rotate(-180.0f * application->updateTime);
	application->animation->rectangles[3]->rotate(180.0f * application->updateTime);
	application->animation->rectangles[4]->rotate(180.0f * application->updateTime);
	if (application->applicationClock->getElapsedTime().asSeconds() >= 15) 
	{
		for (int i = 0; i < 5; i++)
		{
			application->animation->rectangles[0]->setRotation(0);
		}
		application->animation->animationStep = 7;
	}
	else
	{
		application->animation->animationStep = 6;
	}
}

void doStep7(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, application->animation->animationSpeed * application->updateTime);
	rotateAnimation(application, 90.0f);
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 17 ? 8 : 7;
}

void doStep8(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	if (application->animation->rectangles[2]->getScale().x > 0.5f)
	{
		application->animation->rectangles[2]->setScale(application->animation->rectangles[2]->getScale().x * 0.9985f, application->animation->rectangles[2]->getScale().y * 0.9985f);
	}
	application->animation->animationStep = application->applicationClock->getElapsedTime().asSeconds() >= 19 ? 9 : 8;
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
	application->animation->animationOpacity = (application->animation->animationOpacity <= 0) ? 0 : application->animation->animationOpacity - 260.0f * application->updateTime;
	setAnimationOpacity(application);
	application->animation->animationStep = (application->applicationClock->getElapsedTime().asSeconds() >= 20) ? 10 : 9;
	application->animation->animationOpacity = (application->applicationClock->getElapsedTime().asSeconds() >= 20) ? 255.0f : application->animation->animationOpacity;
}

void doStep10(Application *application)
{
	moveAnimation(application, -application->animation->animationSpeed * application->updateTime, -application->animation->animationSpeed * application->updateTime);
	application->animation->animationOpacity = (application->animation->animationOpacity <= 0) ? 0 : application->animation->animationOpacity - 260.0f / 2.0f * application->updateTime;
	application->animation->rectangles[2]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
	if (application->applicationClock->getElapsedTime().asSeconds() >= 22)
	{
		application->animation->animationOpacity = 0;
		application->animation->animationStep = 0;
		application->applicationClock->restart();
	}
	else
	{
		application->animation->animationStep = 10;
	}
}

void setAnimationSettingsOnStart(Application *application)
{
	for (int i = 0; i < 5; i++)
	{
		application->animation->rectangles[i]->setOrigin(10, 10);
		application->animation->rectangles[i]->setPosition(70, 70);
		application->animation->rectangles[i]->setRotation(0);
		application->animation->rectangles[i]->setFillColor(Color(0, 255, 0, 0));
	}
}

void setAnimationOpacity(Application *application)
{
	application->animation->rectangles[0]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
	application->animation->rectangles[1]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
	application->animation->rectangles[3]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
	application->animation->rectangles[4]->setFillColor(Color(0, 255, 0, Uint8(application->animation->animationOpacity)));
}

void setAnimationOrigin(Application *application)
{
	application->animation->rectangles[0]->setOrigin(-30.0f, 10.0f);
	application->animation->rectangles[1]->setOrigin(10.0f, -30.0f);
	application->animation->rectangles[3]->setOrigin(10.0f, 30.0f);
	application->animation->rectangles[4]->setOrigin(30.0f, 10.0f);
}

void rotateAnimation(Application *application, float rotationSpeed)
{
	if (!application->animation->isOriginChanged)
	{
		setAnimationOrigin(application);
		application->animation->isOriginChanged = true;
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

void deleteObjects(Application *application)
{
	delete application->applicationClock;
	delete application->updateClock;
	for (int i = 0; i < 5; i++) 
	{
		delete application->animation->rectangles[i];
	}
	delete application->animation;
	delete application->window;
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
			{
				application->window->close();
			}
		}
		updateAnimation(application);
		drawAFrame(application);
	}
	deleteObjects(application);
}

int main()
{
	Application application;
	initApplication(&application, 900, 600);
	gameLoop(&application);
	return 0;
}