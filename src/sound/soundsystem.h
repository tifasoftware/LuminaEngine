#include <SDL_mixer.h>

static const int MAX_SFX = 32;

class SoundSystem
{
    public:
    SoundSystem();
    void shutdown();
    void startMusic(const char* file);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void setMusicVolume(int vol);

    int loadSFX(const char* file);
    bool unloadAllSFX();
    void playSFX(int index);

    private:
    Mix_Music* bgm;
    Mix_Chunk* sfxBank[MAX_SFX];
    bool musicLoaded = false;
    int sfxCount = -1;

};