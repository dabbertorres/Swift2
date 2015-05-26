#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <map>

namespace swift
{
	class Component
	{
		public:
			enum class Type : int
			{
				Animated = 1 << 0,
				BatchDrawable = 1 << 1,
				Controllable = 1 << 2,
				Drawable = 1 << 3,
				Movable = 1 << 4,
				Name = 1 << 5,
				Noisy = 1 << 6,
				Pathfinder = 1 << 7,
				Physical = 1 << 8,
				
				MAX = 1 << 9,
			};
			
			Component(unsigned int i);
			virtual ~Component() = default;
			
			unsigned int ID() const;

			static Type type();

			virtual std::map<std::string, std::string> serialize() const = 0;
			virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;
			
		private:
			unsigned int id;
	};
	
	inline Component::Component(unsigned int i)
	:	id(i)
	{}
	
	inline unsigned int Component::ID() const
	{
		return id;
	}
}

// implementation of std::hash for Component:Type enum class.
// Allowing it to be used in unordered_maps and such.
namespace std
{
	template<>
	struct hash<swift::Component::Type>
	{
		std::size_t operator()(const swift::Component::Type& t) const
		{
			return std::hash<std::underlying_type<swift::Component::Type>::type>()(static_cast<std::underlying_type<swift::Component::Type>::type>(t));
		}
	};
}

#endif // COMPONENT_HPP
