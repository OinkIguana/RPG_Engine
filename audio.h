#pragma once

#include <map>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#define VOICE_CHANNEL 0
#define SOUND_CHANNEL 1

// Sound effects
class Sound {
    friend class Audio;
private:
    Sound(const std::string& name, const std::string& path);
    inline ~Sound() { Mix_FreeChunk(_sound); }

    const std::string _name;
    Mix_Chunk* _sound;
};

// Background music
class Music {
    friend class Audio;
private:
    Music(const std::string& name, const std::string& path);
    inline ~Music() { Mix_FreeMusic(_music); }

    const std::string _name;
    Mix_Music* _music;
};

// Spoken dialog
class Voice {
    friend class Audio;
private:
    Voice(const std::string& dialog, const unsigned int& message, const std::string& path);
    inline ~Voice() { Mix_FreeChunk(_sound); }

    const std::string _dialog;
    const unsigned int _message;
    Mix_Chunk* _sound;
};

// Base audio
// Sound effects are played when requested
// Only one music track can be played at once
// Voices play automatically when their dialog comes up
class Audio {
public:
    static void init();
    // Plays a sound, and returns it's channel. (0 on error)
    static unsigned int sound_play(const std::string& name);
    // Plays a sound to loop infinitely, and returns it's channel. (0 on error)
    static unsigned int sound_loop(const std::string& name, const int& loops = -1);
    // Stops a channel
    inline static void sound_stop(const unsigned int& channel) { if (channel != 0) { Mix_HaltChannel(channel); } }
    // Checks if the given channel is playing
    inline static bool sound_is_playing(const unsigned int& channel) { return channel != 0 && Mix_Playing(channel) > 0; }

    // Starts or changes the background music playing
    static void music_play(const std::string& name);
    // Stops the music 
    inline static void music_stop() { Mix_HaltMusic(); }
    // Checks if there is music playing
    inline static bool music_is_playing() { return Mix_PlayingMusic() == 1; }
    // Gives the name of the music that is playing (may be wrong if no music is playing)
    inline static std::string music_playing() { return _current_music->_name; }

    // Plays the voice that corresponds to the dialog and message given. Returns true if there is a voice for this dialog
    static bool voice_play(const std::string& dialog, const unsigned int& message);
    // Stops the voice
    inline static void voice_stop() { Mix_HaltChannel(0); }
    // Checks if there is a voice currently playing
    inline static bool voice_is_playing() { return Mix_Playing(0) == 1; }

    // Imports sounds from a file
    static void import(const std::string& path);
private:
    static Music* _current_music;
    static Voice* _current_voice;

    static int _sound_vol;
    static int _music_vol;
    static int _voice_vol;

    static bool _sound_mute;
    static bool _music_mute;
    static bool _voice_mute;

    static std::map<std::string, Music*> all_music;
    static std::map<std::string, Sound*> all_sound;
    static std::map<std::string, Voice*> all_voice;
};