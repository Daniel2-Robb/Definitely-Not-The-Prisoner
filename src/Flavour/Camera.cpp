
#include "Camera.h"

Camera::Camera(sf::Vector2f size)
{
	view.setSize(size);
	view.setCenter(size.x / 2, size.y / 2);
}


void Camera::update(sf::Vector2f target_pos, float dt)
{
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