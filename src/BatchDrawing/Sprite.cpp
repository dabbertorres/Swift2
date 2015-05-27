#include "Sprite.hpp"

#include "../Math/Math.hpp"

#include "SpriteBatch.hpp"

namespace swift
{
	Sprite::Sprite(SpriteBatch* b, const std::array<std::size_t, 4>& verts)
	:	vertices(verts),
		origin(0, 0),
	    scaleFactor(1, 1),
	    angle(0),
		batch(b)
	{}
	
	Sprite::Sprite()
	:	vertices({0}),
		origin(0, 0),
		scaleFactor(1, 1),
		angle(0),
		batch(nullptr)
	{}

	Sprite::~Sprite()
	{
		batch->remove(vertices);
	}

	void Sprite::move(const sf::Vector2f& offset)
	{
		for(auto& v : vertices)
		{
			batch->getVertex(v)->position += offset;
		}
	}

	void Sprite::rotate(float a)
	{
		angle += a;

		setRotation(angle);
	}

	void Sprite::scale(const sf::Vector2f& factor)
	{
		setScale({scaleFactor.x * factor.x, scaleFactor.y * factor.y});
	}

	sf::IntRect Sprite::getTextureRect() const
	{
		return {static_cast<sf::Vector2i>(batch->getVertex(vertices[0])->texCoords), static_cast<sf::Vector2i>(batch->getVertex(vertices[3])->texCoords) - static_cast<sf::Vector2i>(batch->getVertex(vertices[0])->texCoords)};
	}

	sf::Color Sprite::getColor() const
	{
		return batch->getVertex(vertices[0])->color;
	}

	sf::Vector2f Sprite::getPosition() const
	{
		return batch->getVertex(vertices[0])->position + origin;
	}

	float Sprite::getRotation() const
	{
		return angle;
	}

	sf::Vector2f Sprite::getScale() const
	{
		return scaleFactor;
	}

	sf::Vector2f Sprite::getOrigin() const
	{
		return origin;
	}

	sf::FloatRect Sprite::getLocalBounds() const
	{
		return {batch->getVertex(vertices[0])->texCoords + origin, batch->getVertex(vertices[2])->texCoords - batch->getVertex(vertices[0])->texCoords};
	}

	sf::FloatRect Sprite::getGlobalBounds() const
	{
		return {batch->getVertex(vertices[0])->position + origin, batch->getVertex(vertices[2])->position - batch->getVertex(vertices[0])->position};
	}


	void Sprite::setTextureRect(const sf::IntRect& texRect)
	{
		batch->getVertex(vertices[0])->texCoords = {static_cast<float>(texRect.left), static_cast<float>(texRect.top)};
		batch->getVertex(vertices[1])->texCoords = {static_cast<float>(texRect.left) + static_cast<float>(texRect.width), static_cast<float>(texRect.top)};
		batch->getVertex(vertices[2])->texCoords = {static_cast<float>(texRect.left) + static_cast<float>(texRect.width), static_cast<float>(texRect.top) + static_cast<float>(texRect.height)};
		batch->getVertex(vertices[3])->texCoords = {static_cast<float>(texRect.left), static_cast<float>(texRect.top) + static_cast<float>(texRect.height)};
	}

	void Sprite::setColor(const sf::Color& color)
	{
		for(auto& v : vertices)
			batch->getVertex(v)->color = color;
	}

	void Sprite::setPosition(const sf::Vector2f& pos)
	{
		sf::Vector2f topLeft = batch->getVertex(vertices[0])->position;

		for(auto& v : vertices)
		{
			sf::Vertex* ver = batch->getVertex(v);
			ver->position = pos + ver->position - topLeft - origin;
		}
	}

	void Sprite::setRotation(float a)
	{
		angle = a;
		
		// normalize angle to 0..360
		angle = math::normalizeWrap(angle, 0.f, 360.f);

		constexpr float PI = 3.14159265359;

		sf::Vector2f topLeft = batch->getVertex(vertices[0])->position;
		
		for(auto& v : vertices)
		{
			sf::Vertex* ver = batch->getVertex(v);
			
			sf::Vector2f local = ver->position - topLeft - origin;
			
			ver->position = {local.x * std::cos(angle * PI / 180.f) - local.y * std::sin(angle * PI / 180.f),
			                local.x * std::sin(angle * PI / 180.f) + local.y * std::cos(angle * PI / 180.f)};
							
			ver->position += origin + topLeft;
		}
	}

	void Sprite::setScale(const sf::Vector2f& scale)
	{
		sf::Vector2f topLeft = batch->getVertex(vertices[0])->position;

		for(auto& v : vertices)
		{
			sf::Vector2f dist = batch->getVertex(v)->position - topLeft - origin;
			dist.x *= scale.x / scaleFactor.x;
			dist.y *= scale.y / scaleFactor.y;
			batch->getVertex(v)->position = dist + topLeft + origin;
		}

		origin.x *= scale.x / scaleFactor.x;
		origin.y *= scale.y / scaleFactor.y;

		scaleFactor = scale;
	}

	void Sprite::setOrigin(const sf::Vector2f& o)
	{
		origin = o;
	}
}
