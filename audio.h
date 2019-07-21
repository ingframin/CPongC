#ifndef __AUDIO__H_INCLUDED
#define __AUDIO__H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
typedef struct{
    Mix_Chunk** chunks;
    int cnk_size;
    Mix_Music** musics;
    int msc_size;
    int rate;
    Uint16 format;
    int channels;
    int buffers;
    int current_channel;
}Audio;

Audio initAudio(int audio_rate, Uint16 audio_format, int audio_channels, int audio_buffers,int n_sound, int n_music);
int loadSound(Audio* au,const char* path);
int loadMusic(Audio* au,const char* path);
void playSound(Audio* au,int ind);
void playMusic(Audio* au,int ind, bool loop);
void quitAudio();
void changeSoundVolume(int channel, int vol);
void changeMusicVolume(int vol);
#endif