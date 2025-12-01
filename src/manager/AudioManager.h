//
// Created by richa on 2025-11-26.
//

#ifndef TEST_AUDIOMANAGER_H
#define TEST_AUDIOMANAGER_H
#include <unordered_map>
#include <string>
#include "SDL3_mixer/SDL_mixer.h"
class AudioManager {
    static MIX_Mixer *mixer;
    static MIX_Track *musicTrack;
    static MIX_Track *sfxTrack;
    static std::unordered_map<std::string, MIX_Audio*> audio;

public:
    AudioManager();

    void loadAudio(const std::string& name, const char* path) const;
    void playMusic(const std::string& name) const;

    void stopMusic() const;

    static void playSFX(const std::string& name);

    static void clean();
};
#endif //TEST_AUDIOMANAGER_H