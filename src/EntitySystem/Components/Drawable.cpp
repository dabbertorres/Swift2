#include "Drawable.hpp"

#include "../Entity.hpp"

namespace swift
{
	std::string Drawable::getType()
	{
		return "Drawable";
	}
	
	/*template<>
	Drawable* Entity::get(std::string c)
	{
		if(c != "Drawable")
			return nullptr;
		
		if(this->has<Drawable>())
		{
			return static_cast<Drawable*>(components["Drawable"]);
		}
		else
			return nullptr;
	}*/
}
