#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <array>

namespace swift
{
	class SpriteBatch;
	
	class Sprite
	{
		friend class SpriteBatch;
		
		private:
			Sprite(SpriteBatch* b, const std::array<std::size_t, 4>& verts);
			
		public:
			Sprite();
			~Sprite();

			void move(const sf::Vector2f& offset);
			void rotate(float a);
			void scale(const sf::Vector2f& factor);

			sf::IntRect getTextureRect() const;
			sf::Color getColor() const;
			sf::Vector2f getPosition() const;
			float getRotation() const;
			sf::Vector2f getScale() const;
			sf::Vector2f getOrigin() const;

			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;

			void setTextureRect(const sf::IntRect& texRect);
			void setColor(const sf::Color& color);
			void setPosition(const sf::Vector2f& pos);
			void setRotation(float a);
			void setScale(const sf::Vector2f& scale);
			void setOrigin(const sf::Vector2f& o);

		private:
			std::array<std::size_t, 4> vertices;
			
			sf::Vector2f origin;
			sf::Vector2f scaleFactor;
			float angle;
			
			SpriteBatch* batch;
	};
}

#endif // SPRITE_HPP
