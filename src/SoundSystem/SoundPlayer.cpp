#include "SoundPlayer.hpp"

namespace swift
{
	SoundPlayer::SoundPlayer()
	:	volume(100)
	{
	}

	void SoundPlayer::update()
	{
		for(auto it = sounds.begin(); it != sounds.end();)
		{
			if(it->getStatus() == sf::Sound::Status::Stopped)
			{
				it->stop();
				it = sounds.erase(it);
				SoundsLimit::total--;
			}
			else
			{
				it++;
			}
		}
	}
	
	void SoundPlayer::setListenerPosition(const sf::Vector3f& pos)
	{
		sf::Listener::setPosition(pos);
	}

	void SoundPlayer::play()
	{
		for(auto& s : sounds)
		{
			if(s.getStatus() != sf::Sound::Status::Playing)
			{
				s.play();
			}
		}
	}
	
	void SoundPlayer::pause()
	{
		for(auto& s : sounds)
		{
			s.pause();
		}
	}
	
	void SoundPlayer::stop()
	{
		for(auto& s : sounds)
		{
			s.stop();
		}
			
		SoundsLimit::total -= sounds.size();
		
		sounds.clear();
	}
	
	void SoundPlayer::setVolume(float v)
	{
		for(auto& s : sounds)
		{
			s.setVolume(v);
		}
		
		volume = v;
	}

	bool SoundPlayer::newSound(const sf::SoundBuffer& sb, const sf::Vector3f& pos, bool loop)
	{
		if(SoundsLimit::total + 1 > SoundsLimit::limit)
			return false;
		
		sounds.emplace_back(sb);
		sounds.back().setPosition(pos);
		sounds.back().setLoop(loop);
		sounds.back().setVolume(100);
		
		SoundsLimit::total++;
		
		return true;
	}
}
