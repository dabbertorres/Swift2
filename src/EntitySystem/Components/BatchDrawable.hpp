#ifndef BATCHDRAWABLE_HPP
#define BATCHDRAWABLE_HPP

#include "../Component.hpp"

#include "../../BatchDrawing/Sprite.hpp"

namespace swift
{
	class BatchDrawable : public Component
	{
		public:
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			Sprite sprite;
			std::string texture;
			std::string batch;
	};
}

#endif // BATCHDRAWABLE_HPP
