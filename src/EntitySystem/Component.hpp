#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <map>

namespace swift
{
	class Component
	{
		public:
			enum class Type : std::size_t
			{
				None = 0,
				Animated = 1,
				BatchDrawable = 2,
				Controllable = 3,
				Drawable = 4,
				Movable = 5,
				Name = 6,
				Noisy = 7,
				Pathfinder = 8,
				Physical = 9,
				Scriptable = 10,
				
				MAX = 11,
			};
			
			Component(unsigned int i);
			virtual ~Component() = default;
			
			unsigned int ID() const;
			
			// must be implemented
			static constexpr Type type();
			
			static constexpr Type type(const char* str);
			static constexpr const char* type(Component::Type en);

			virtual std::map<std::string, std::string> serialize() const = 0;
			virtual void unserialize(const std::map<std::string, std::string>& variables) = 0;
			
		private:
			unsigned int id;
			Type typeVal;
			
			static constexpr std::pair<const char*, Type> TypeStrings[] = 
			{
				{"None", Type::None},
				{"Animated", Type::Animated},
				{"BatchDrawable", Type::BatchDrawable},
				{"Controllable", Type::Controllable},
				{"Drawable", Type::Drawable},
				{"Movable", Type::Movable},
				{"Name", Type::Name},
				{"Noisy", Type::Noisy},
				{"Pathfinder", Type::Pathfinder},
				{"Physical", Type::Physical},
			};
	};
	
	namespace
	{
		constexpr bool isSame(const char* x, const char* y)
		{
			return !*x && !*y ? true : (*x == *y && isSame(x + 1, y + 1));
		}
	}
	
	constexpr Component::Type Component::type(const char* str)
	{
		constexpr std::size_t MAX = static_cast<std::size_t>(Type::MAX);
		
		for(std::size_t i = 1; i < MAX; i++)
		{
			if(isSame(str, TypeStrings[i].first))
			{
				return TypeStrings[i].second;
			}
		}
		
		return Type::None;
	}
	
	constexpr const char* Component::type(Component::Type en)
	{
		constexpr std::size_t MAX = static_cast<std::size_t>(Type::MAX);
		
		std::size_t i = static_cast<std::size_t>(en);
		
		if(i < MAX)
		{
			return TypeStrings[i].first;
		}
		
		return "None";
	}
}

// implementation of std::hash for Component::Type enum class.
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
