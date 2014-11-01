#include "MusicPlayer.hpp"

namespace swift
{
	MusicPlayer::MusicPlayer()
		:	activeTrack(0),
			volume(100)
	{
	}

	void MusicPlayer::update()
	{
		if(musics[activeTrack]->getStatus() == sf::Music::Status::Stopped && musics.size() != 0)
		{
			activeTrack++;
			
			if(activeTrack >= musics.size())
				activeTrack = 0;
			
			musics[activeTrack]->play();
		}
	}

	void MusicPlayer::play()
	{
		if(musics[activeTrack]->getStatus() != sf::Music::Status::Playing && musics.size() != 0)
			musics[activeTrack]->play();
	}
	
	void MusicPlayer::pause()
	{
		if(musics.size() != 0)
			musics[activeTrack]->pause();
	}
	
	void MusicPlayer::stop()
	{
		if(musics.size() != 0)
		{
			musics[activeTrack]->stop();
			activeTrack = 0;
			
			SoundsLimit::total -= musics.size();
			
			musics.clear();
		}
	}
	
	void MusicPlayer::setVolume(float v)
	{
		for(auto& m : musics)
		{
			m->setVolume(v);
		}
		
		volume = v;
	}

	bool MusicPlayer::newTrack(sf::Music& m, bool loop)
	{
		if(SoundsLimit::total + 1 > SoundsLimit::limit)
			return false;
		
		musics.emplace_back(&m);
		musics.back()->setLoop(loop);
		musics.back()->setVolume(volume);
		musics.back()->setRelativeToListener(true);
		
		SoundsLimit::total++;
		
		return true;
	}
}
