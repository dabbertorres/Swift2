#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "SoundsLimit.hpp"

#include <vector>

#include <SFML/Audio/Music.hpp>

namespace swift
{
	class MusicPlayer : public SoundsLimit
	{
		public:
			MusicPlayer();
			
			void update();
			
			void play();
			void pause();
			void stop();
			void setVolume(float v);
			
			bool newTrack(sf::Music& m, bool loop = false);

		private:
			std::vector<sf::Music*> musics;
			unsigned activeTrack;
			float volume;
	};
}

#endif // MUSICPLAYER_HPP
