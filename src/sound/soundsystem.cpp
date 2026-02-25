#include <SDL_mixer.h>
#include <sound/soundsystem.h>

SoundSystem::SoundSystem()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void SoundSystem::shutdown()
{
    Mix_CloseAudio();
}

void SoundSystem::startMusic(const char* file)
{
    if (musicLoaded)
    {
        stopMusic();
    }
    bgm = Mix_LoadMUS(file);
    Mix_PlayMusic(bgm, -1);
    Mix_VolumeMusic(64);
    musicLoaded = true;
}

void SoundSystem::stopMusic()
{
    if (musicLoaded)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(bgm);
        musicLoaded = false;
    }
}