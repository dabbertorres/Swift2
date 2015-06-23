#ifndef BATCHDRAWABLE_HPP
#define BATCHDRAWABLE_HPP

#include "../Component.hpp"

#include "../../BatchDrawing/Sprite.hpp"

namespace swift
{
	class Physical;
	
	class BatchDrawable : public Component
	{
		public:
			BatchDrawable(unsigned int id = 0);
			
			static constexpr Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			Sprite sprite;
			std::string texture;
			std::string batch;
	};
	
	constexpr Component::Type BatchDrawable::type()
	{
		return Component::Type::BatchDrawable;
	}
}

#endif // BATCHDRAWABLE_HPP
