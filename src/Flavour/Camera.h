
#ifndef _NOTTHEPRISONER_CAMERA_H_
#define _NOTTHEPRISONER_CAMERA_H_

#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::RenderWindow& window;
	sf::View view;
	float speed = 2.f;
	float minvalue = 1.f;

public:
	Camera(sf::RenderWindow& window);

	void update(sf::Vector2f position, float dt);

	sf::View& getView();
	void setSpeed(float speed);
	void setCentre(sf::Vector2f position);
	sf::Vector2f getPosition();
};

#endif // _NOTTHEPRISONER_CAMERA_H_s