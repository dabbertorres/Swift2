#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class Player : public sf::Drawable
	{
		public:
			Player();
			~Player();
			
			void update(float dt);
			
			void setTexture(const sf::Texture& texture);
			void setMass(float m);
			
			void addForce(sf::Vector2f n);
			
			sf::FloatRect getGlobalBounds() const;
			sf::Vector2f getPosition() const;
			void setPosition(const sf::Vector2f& pos);
			
			float getAngle() const;
			void setAngle(float a);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			sf::Sprite sprite;
			
			float mass;
			
			sf::Vector2f acceleration;
			
			sf::Vector2f velocity;
			
			sf::Vector2f position;
			
			float angle;
	};
}

#endif // PLAYER_HPP
