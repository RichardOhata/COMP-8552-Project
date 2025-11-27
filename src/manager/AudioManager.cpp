//
// Created by richa on 2025-11-26.
//

#include "AudioManager.h"

#include <iostream>

MIX_Track* AudioManager::sfxTrack;
std::unordered_map<std::string, MIX_Audio*> AudioManager::audio;


AudioManager::AudioManager() {

    if (MIX_Init() == 0) {
        std::cout << "Mix Init Failed" << std::endl;
        return;
    }
    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!mixer) {
        std::cout << "Mix Create Device Failed" << std::endl;
        return;
    }

    musicTrack = MIX_CreateTrack(mixer);
    sfxTrack = MIX_CreateTrack(mixer);
    MIX_SetTrackGain(musicTrack, 0.2f); // Change to 0 for demo
}


void AudioManager::loadAudio(const std::string &name, const char *path) const {
    if (audio.contains(path)) {
        return;
    }

    auto audioPtr = MIX_LoadAudio(mixer, path, true);
    if (!audioPtr) {
        std::cout << "Load Audio Failed" << std::endl;
        return;
    }

    audio.emplace(name, audioPtr);
}

void AudioManager::playMusic(const std::string& name) const {
    if (MIX_SetTrackAudio(musicTrack, audio[name]) == 0) {
        std::cout << "Set Track Audio Failed" << std::endl;
        return;
    }
    MIX_PlayTrack(musicTrack, -1);
    std::cout << "Playing music : " << name << std::endl;
}

void AudioManager::stopMusic() const {
    MIX_StopTrack(musicTrack, 0);
}

void AudioManager::playSFX(const std::string& name) {
    if (MIX_SetTrackAudio(sfxTrack, audio[name]) == 0) {
        std::cout << "Set Track Audio Failed" << std::endl;
        return;
    }
    MIX_PlayTrack(sfxTrack, 0);
    std::cout << "Playing SFX : " << name << std::endl;
}

