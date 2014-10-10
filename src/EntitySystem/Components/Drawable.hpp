#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	class Drawable : public Component
	{
		public:
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			sf::Sprite sprite;
			std::string texture;
	};
}

#endif // DRAWABLE_HPP
