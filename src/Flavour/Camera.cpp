
#include "Camera.h"

Camera::Camera(sf::RenderWindow& window) : window(window)
{
	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
}


void Camera::update(sf::Vector2f target_pos, float dt)
{
	// Set size to account for window resizing
	view.setSize(sf::Vector2f(window.getSize()));

	sf::Vector2f new_pos = view.getCenter();
	// TODO: Increase speed with distance from player?
	sf::Vector2f difference = (target_pos - view.getCenter()) * speed;
	
	if ((difference.x * difference.x) + (difference.y * difference.y) < (minvalue * minvalue))
	{
		// If difference is small enough camera is set to directly over player to prevent tiny eternal movement
		new_pos = target_pos;
	}
	else
	{
		new_pos = view.getCenter() + (difference * dt);
	}

	view.setCenter(new_pos);
}


sf::View& Camera::getView()
{
	return view;
}

void Camera::setSpeed(float speed)
{
	this->speed = speed;
}

void Camera::setCentre(sf::Vector2f position)
{
	view.setCenter(position);
}

sf::Vector2f Camera::getPosition()
{
	//sf::Vector2f getCenter = ;
	return sf::Vector2f ((view.getCenter().x) - (view.getSize().x / 2), (view.getCenter().y) - (view.getSize().y / 2));
}