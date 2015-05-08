#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Component.hpp"

#include "../Utility/AssocMap.hpp"

namespace swift
{
	class BaseSystem
	{
		public:
			virtual void update(float dt) = 0;
	};

	template<typename C, typename std::enable_if<std::is_base_of<Component, C>::value>::type* = nullptr>
	class System : public BaseSystem
	{
		public:
			virtual void update(float dt) = 0;
			
			unsigned int size() const
			{
				return components.size();
			}
			
			bool has(unsigned int id) const
			{
				return components.find(id) != components.key_end();
			}

			C& get(unsigned int id)
			{
				return components.at(id);
			}
			
			template<typename... Args>
			void add(unsigned int id, Args&&... args)
			{
				auto res = components.emplace(id, args...);
				
				if(res.second)
					addImpl(res.first);
			}
			
			void remove(unsigned int id)
			{
				removeImpl(id);
				components.erase(components.begin() + id);
			}
			
			void clear()
			{
				components.clear();
			}
			
			Component::Type type() const
			{
				return C::type();
			}

		protected:
			util::AssocMap<unsigned int, C> components;
			
		private:
			virtual void addImpl(const C&)
			{}
			
			virtual void removeImpl(unsigned int)
			{}
	};
}

#endif // SYSTEM_HPP
