#pragma once
#include <Fmod/core/inc/fmod.hpp>
#include <string>
#include <map>

namespace MEN
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		~AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		void AddAudio(const std::string& name, const std::string& fileName);
		void PlayOneShot(const std::string& name, bool loop = false);

	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

	extern AudioSystem g_audioSystem;
}