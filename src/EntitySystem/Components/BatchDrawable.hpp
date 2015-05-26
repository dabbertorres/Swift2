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
			BatchDrawable(unsigned int id, const Physical& p);
			
			BatchDrawable(const BatchDrawable& other);
			
			BatchDrawable& operator=(BatchDrawable&& other);
			
			const Physical& getPhysical() const;
			
			static Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			Sprite sprite;
			std::string texture;
			std::string batch;
			
		private:
			const Physical& physical;
	};
}

#endif // BATCHDRAWABLE_HPP
