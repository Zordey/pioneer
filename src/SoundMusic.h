#ifndef _MUSIC_H
#define _MUSIC_H

#include <SDL.h>
#include "Sound.h"
#include <string>

namespace Sound
{
	class MusicEvent : public Event
	{
	public:
		MusicEvent();
		MusicEvent(Uint32 id);
		~MusicEvent();
		virtual void Play(const char *fx, float volume_left, float volume_right, Op op);
	};

	class MusicPlayer
	{
	public:
		MusicPlayer();
		~MusicPlayer();
		float GetVolume() const;
		void SetVolume(const float);
		void Play(const std::string&, const bool repeat = false, const float fadeDelta = 1.f);
		void Stop();
		void FadeOut(const float fadeDelta);
		void Update();
	private:
		float m_volume;
		//two streams for crossfade
		MusicEvent m_eventOne;
		MusicEvent m_eventTwo;
		bool m_playing;
		bool m_eventOnePlaying;
	};
}

#endif
