#ifndef SWIFT_SOUNDPLAYER_HPP
#define SWIFT_SOUNDPLAYER_HPP

#include "SoundsLimit.hpp"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Listener.hpp>

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class SoundPlayer : public SoundsLimit
	{
		public:
			SoundPlayer();
			
			void update();
			void setListenerPosition(const sf::Vector3f& pos);
			
			void play();
			void pause();
			void stop();
			void setVolume(float v);
			
			bool newSound(const sf::SoundBuffer& sb, const sf::Vector3f& pos, bool loop = false);
			
		private:
			std::vector<sf::Sound> sounds;
			float volume;
	};
}

#endif // SWIFT_SOUNDPLAYER_HPP
