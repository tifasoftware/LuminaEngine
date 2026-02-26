#include <SDL_mixer.h>
#include <sound/soundsystem.h>

SoundSystem::SoundSystem()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
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

int SoundSystem::firstOpenSlot()
{
    for (int i = 0; i < MAX_SFX; i++)
    {
        if (sfxBank[i] == nullptr)
        {
            return i;
        }
    }
    return -1;
}

int SoundSystem::loadSFX(const char* file)
{
    int slot = firstOpenSlot();

    sfxBank[slot] = Mix_LoadWAV(file);

    return slot;
}

bool SoundSystem::unloadSFX(int index)
{
    if (sfxBank[index] == nullptr)
    {
        return false;
    }
    Mix_FreeChunk(sfxBank[index]);
    sfxBank[index] = nullptr;
    return true;
}

bool SoundSystem::unloadAllSFX()
{
    for (int i = 0; i < MAX_SFX; i++)
    {
        unloadSFX(i);
    }
    return true;
}

void SoundSystem::playSFX(int index)
{
    if (sfxBank[index] != nullptr)
    {
        Mix_PlayChannel(-1, sfxBank[index], 0);
    }
}