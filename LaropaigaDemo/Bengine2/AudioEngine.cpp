#include "AudioEngine.h"
#include "BengineErrors.h"

namespace Bengine2 {

	void SoundEffect::play(int loops /* = 0*/) {
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
				fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::play(int loops /* = -1*/) {
		Mix_PlayMusic(m_music, loops);
	}

	void Music::fadeIn(int loops) {
		Mix_FadeInMusic(m_music, loops, 10);
	}

	void Music::fadeOut() {
		Mix_FadeOutMusic(10);
	}

	void Music::pause() {
		Mix_PauseMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	void Music::resume() {
		Mix_ResumeMusic();
	 }

	

	AudioEngine::AudioEngine() {
		//empty
	}


	AudioEngine::~AudioEngine() {
		destroy();
	}

	void AudioEngine::init() {
		if (m_isInitialized) {
			fatalError("Tried to initialize AudioEngine twice!\n");
		}

		//Parameter can be a bitwise combination of Mix_Init_FAC,
		//MIX_INIT_MOD, MIX_INIT_MP3, and MIX_INIT_OGG (or .wav files by default)
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			fatalError("MIX_INIT error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			fatalError("MIX_OpenAudio error: " + std::string(Mix_GetError()));
		}
		m_isInitialized = true;
	}

	void AudioEngine::destroy() {
		if (m_isInitialized == true) {
			m_isInitialized = false;

			for (auto& it : m_effectMap) {
				Mix_FreeChunk(it.second);
			}

			for (auto& it : m_musicMap) {
				Mix_FreeMusic(it.second);
			}
			m_effectMap.clear();
			m_musicMap.clear();

			Mix_CloseAudio();

			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
		//try to find the audio in the cache
		auto it = m_effectMap.find(filePath);

		SoundEffect effect;

		if (it == m_effectMap.end()) {
			//failed to find it, must load
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			//check for errors
			if (chunk == nullptr) {
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}

			effect.m_chunk = chunk;

			//creates a node on the tree (if it doesn't already exist), and places the chunk there
			m_effectMap[filePath] = chunk;
		}
		else {
			//its already cached
			effect.m_chunk = it->second;
		}

		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath) {
		//try to find the audio in the cache
		auto it = m_musicMap.find(filePath);

		Music music;

		if (it == m_musicMap.end()) {
			//failed to find it, must load
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			//check for errors
			if (mixMusic == nullptr) {
				fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
			}

			music.m_music = mixMusic;

			//creates a node on the tree (if it doesn't already exist), and places the chunk there
			m_musicMap[filePath] = mixMusic;
		}
		else {
			//its already cached
			music.m_music = it->second;
		}

		return music;
	}


}

