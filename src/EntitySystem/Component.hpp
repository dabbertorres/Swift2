#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

namespace swift
{
	class Component
	{
		public:
			Component()
			{
				
			}
			
			virtual ~Component()
			{
				
			}
			
			static std::string getType();
	};
}

#endif // COMPONENT_HPP
