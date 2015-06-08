#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	class Physical;
	
	class Drawable : public Component
	{
		public:
			Drawable(unsigned int id, const Physical& p);
			
			Drawable(const Drawable& other);
			
			Drawable& operator=(Drawable&& other);
			
			const Physical& getPhysical() const;
			
			static constexpr Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			sf::Sprite sprite;
			std::string texture;
			
		private:
			const Physical& physical;
	};
			
	constexpr Component::Type Drawable::type()
	{
		return Component::Type::Drawable;
	}
}

#endif // DRAWABLE_HPP
