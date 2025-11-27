//
// Created by richa on 2025-11-26.
//

#ifndef TEST_AUDIOMANAGER_H
#define TEST_AUDIOMANAGER_H
#include <unordered_map>
#include <string>
#include "SDL3_mixer/SDL_mixer.h"
class AudioManager {
    MIX_Mixer *mixer = nullptr;
    MIX_Track *musicTrack = nullptr;
    static MIX_Track *sfxTrack;
    static std::unordered_map<std::string, MIX_Audio*> audio;

public:
    AudioManager();

    void loadAudio(const std::string& name, const char* path) const;
    void playMusic(const std::string& name) const;

    void stopMusic() const;

    static void playSFX(const std::string& name);
};
#endif //TEST_AUDIOMANAGER_H