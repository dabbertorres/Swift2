#include "Player.hpp"

namespace swift
{
	Player::Player()
	{
		angle = 90;
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}

	Player::~Player()
	{
	}
	
	void Player::update(float dt)
	{
		// convert from m/s/s to m/s and add it to the velocity
		velocity += (acceleration * dt);
		
		// convert from m/s to m and update the position
		position += velocity * dt;
		
		// we zero out the acceleration every update
		acceleration = {0, 0};
		
		sprite.setPosition(position);
	}
	
	void Player::setTexture(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}
	
	void Player::setMass(float m)
	{
		mass = m;
	}
	
	void Player::addForce(sf::Vector2f n)
	{
		// convert from Newtons to m/s/s and add it to the acceleration
		acceleration += (n / mass);
	}
	
	sf::FloatRect Player::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}
	
	sf::Vector2f Player::getPosition() const
	{
		return position;
	}
	
	void Player::setPosition(const sf::Vector2f& pos)
	{
		position = pos;
		sprite.setPosition(pos);
	}
	
	float Player::getAngle() const
	{
		return angle;
	}
	
	void Player::setAngle(float a)
	{
		angle = a;
	}
	
	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
