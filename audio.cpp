#include "audio.h"

Music* Audio::_current_music = nullptr;
Voice* Audio::_current_voice = nullptr;

int Audio::_sound_vol = 1;
int Audio::_music_vol = 1;
int Audio::_voice_vol = 1;

bool Audio::_sound_mute = false;
bool Audio::_music_mute = false;
bool Audio::_voice_mute = false;

std::map<std::string, Sound*> Audio::all_sound = std::map<std::string, Sound*>();
std::map<std::string, Music*> Audio::all_music = std::map<std::string, Music*>();
std::map<std::string, Voice*> Audio::all_voice = std::map<std::string, Voice*>();

void Audio::init() {
    Mix_AllocateChannels(2);
    Mix_ReserveChannels(1);
    Mix_GroupChannel(0, VOICE_CHANNEL);
    Mix_GroupChannel(1, SOUND_CHANNEL);
}

unsigned int Audio::sound_play(const std::string& name) {
    return sound_loop(name, 0);
}

unsigned int Audio::sound_loop(const std::string& name, const int& loops) {
    auto found = all_sound.find(name);
    if (found != all_sound.end()) {
        if (Mix_GroupAvailable(SOUND_CHANNEL) == 0) {
            // Allocate one more channel if there are not enough
            const int last_channel = Mix_AllocateChannels(-1);
            Mix_AllocateChannels(last_channel + 1);
            Mix_GroupChannel(last_channel, SOUND_CHANNEL);
        }
        return Mix_PlayChannel(-1, found->second->_sound, loops);
    } else {
        return 0;
    }
}

inline void Audio::music_play(const std::string& name) {
    auto found = all_music.find(name);
    if (found != all_music.end()) {
        Mix_PlayMusic(found->second->_music, -1);
    }
}

void Audio::voice_play(const std::string & dialog, const unsigned int & message) {
    auto found = all_voice.find(dialog + '.' + std::to_string(message));
    if (found != all_voice.end()) {
        Mix_PlayChannel(0, found->second->_sound, 0);
    }
}

void Audio::import(const std::string & path) {}

Sound::Sound(const std::string& name, const std::string& path) : _name(name), _sound(Mix_LoadWAV(path.c_str())) {}
Music::Music(const std::string& name, const std::string& path) : _name(name), _music(Mix_LoadMUS(path.c_str())) {}
Voice::Voice(const std::string& dialog, const unsigned int& message, const std::string& path) : _dialog(dialog), _message(message), _sound(Mix_LoadWAV(path.c_str())) {}
