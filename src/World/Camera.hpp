#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace swift
{
	class Camera
	{
		public:
			Camera();
			~Camera();
			
			void setCenter(sf::Vector2f c);
			void setViewport(sf::IntRect rect);
			void setViewSize(sf::Vector2f area);

	};
}

#endif // CAMERA_HPP
