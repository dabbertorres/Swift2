#include "Physical.hpp"

namespace swift
{
	float Physical::gravity = -10;
	
	Physical::Physical()
	{
	}

	Physical::~Physical()
	{
	}
	
	void Physical::addForce(sf::Vector2f n)
	{
		// convert from Newtons to m/s/s and add it to the acceleration
		acceleration += (n / mass);
	}
	
	void Physical::update(float dt)
	{
		// convert from m/s/s to m/s and add it to the velocity
		velocity += (acceleration * dt);
		
		// gravity is a const acceleration
		velocity.y += gravity * dt;
		
		// convert from m/s to m and update the position
		position += velocity * dt;
		
		// we zero out the acceleration every update
		acceleration = {0, 0};
	}
	
	float Physical::getGravity()
	{
		return gravity;
	}
	
	void Physical::setGravity(float g)
	{
		gravity = g;
	}
}
