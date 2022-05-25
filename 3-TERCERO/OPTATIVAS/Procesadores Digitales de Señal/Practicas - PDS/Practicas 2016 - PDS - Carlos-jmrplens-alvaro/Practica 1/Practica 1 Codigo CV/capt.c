#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#define BUFFER_SIZE 256

int main() {
    int err;
    unsigned char buf[BUFFER_SIZE];
    unsigned int rate = 44100;
    snd_pcm_t *snd_handle;
    snd_pcm_hw_params_t *hw_params;

    if ((err = snd_pcm_open(&snd_handle, "hw:0,0", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf(stderr, "cannot open audio device %s (%s)\n", "hw:0,0", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
        fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_any(snd_handle, hw_params)) < 0) {
        fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_set_access(snd_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_set_format(snd_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_set_rate_near(snd_handle, hw_params, &rate, 0)) < 0) {
        fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params_set_channels(snd_handle, hw_params, 2)) < 0) {
        fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
        return(1);
    }
    if ((err = snd_pcm_hw_params(snd_handle, hw_params)) < 0) {
        fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
        return(1);
    }
    
    snd_pcm_hw_params_free(hw_params);

    if ((err = snd_pcm_prepare(snd_handle)) < 0) {
        fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
        return(1);
    }

    while(1) {
        if ((err = snd_pcm_readi(snd_handle, buf, 64)) != 64) {
            fprintf(stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
            return(1);
        }
        fwrite(buf, sizeof(char), BUFFER_SIZE, stdout);
        fflush(stdout);
    }

    snd_pcm_close(snd_handle);
    return(0);
}

