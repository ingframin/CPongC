#include "audio.h"


Audio initAudio(int audio_rate, Uint16 audio_format, int audio_channels, int audio_buffers, int n_sound, int n_music){
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
    Mix_AllocateChannels(16);
    Audio au_subsystem;
    
    au_subsystem.buffers = audio_buffers;
    au_subsystem.channels = audio_channels;
    au_subsystem.format = audio_format;
    au_subsystem.rate = audio_rate;
    au_subsystem.current_channel = 0;
    au_subsystem.chunks = (Mix_Chunk**)malloc(n_sound*sizeof(Mix_Chunk*));
    au_subsystem.cnk_size = 0;
    au_subsystem.msc_size = 0;
    au_subsystem.musics = (Mix_Music**) malloc(n_music*sizeof(Mix_Music*));

    return au_subsystem;
}

int loadSound(Audio* au, const char* path){
    int ind = au->cnk_size;
    au->chunks[ind] = Mix_LoadWAV(path);
    au->cnk_size += 1;
    return ind;
}

void playSound(Audio* au, int ind){
    Mix_PlayChannel(-1, au->chunks[ind], 0);
}

int loadMusic(Audio* au,const char* path){
    int ind = au->msc_size;
    au->musics[ind] = Mix_LoadMUS(path);
    au->msc_size += 1;
    return ind;
}

void playMusic(Audio* au,int ind, bool loop){
    int l = (loop)?-1:1;
    Mix_PlayMusic(au->musics[ind], l);
}

void quitAudio(Audio* au){
    for(int i=0;i<au->cnk_size;i++){
        Mix_FreeChunk(au->chunks[i]);
        
    }
    free(au->chunks);
    for(int i=0;i<au->msc_size;i++){
        Mix_FreeMusic(au->musics[i]);
        
    }
    free(au->musics);
    au->cnk_size = 0;
    au->msc_size = 0;
    Mix_CloseAudio();
    Mix_Quit();
}

void changeMusicVolume(int vol){
    Mix_VolumeMusic(vol);
}