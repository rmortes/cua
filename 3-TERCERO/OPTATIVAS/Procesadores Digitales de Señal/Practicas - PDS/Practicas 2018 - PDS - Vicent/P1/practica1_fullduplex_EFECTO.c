#include <stdio.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <unistd.h>

// Funcion donde aplicaremos un efecto (el que nosotros queramos) al buffer. 
// El buffer es un vector con muestras obtenidas por read.
void effect(unsigned char *buf, int numMuestras) {
    int i,top,n=0,fc,gRate;
    short muestraL, muestraR; //Variables para las muestras del altavoz izquierdo(L) y derecho(R).
	fc=15000;
	gRate=44100;
	
    for (i = 0; i < numMuestras * 4; i += 4) {
        muestraL = buf[i + 1]; 		//La muestra numero 1 la copiamos a la variable.
        muestraL = muestraL << 8; 	//Desplazamos la muestra anterior a la izquierdo, para posteriormente añadir la siguiente a la derecha.
        muestraL = muestraL | buf[i + 0]; //La muestra 0 la copiamos a la variables (a la aprte derecha)

        muestraR = buf[i + 3];		//La muestra numero 3 la copiamos a la variable.
        muestraR = muestraR << 8; 	//Desplamos la muestra añadiada a la izquierda para posteriormente añadir la siguiente a la derecha.
        muestraR = muestraR | buf[i + 2]; //La muestra 2 la copiamos a la variables (a la aprte derecha)

        /**************** EFECTO TREMOLO *******************/
		muestraR = muestraR*cos(2*n*3.14);
		muestraL = muestraL*cos(2*n*3.14);
		n++;
        /***************************************************/

	//Realizamos una operacion AND de 8 bits a la varaible muestra que es de 16, por lo que nos quedaremos solo con los 8 bits de la parte derecha y los copiaremos 	de vuelta a la variable buffer, a la posicion 0.
        buf[i + 0] = (unsigned char) (0xFF & muestraL);
        muestraL = muestraL >> 8; //Desplazamos los 8 bits que nos quedan (de los 16 que teniamos), hacia la derecha.
	//Ahora realizamos la misma operacion que antes para quedarnos con 8 bits y devolverlos a la variable buffer, en la posicion 1.
        buf[i + 1] = (unsigned char) (0xFF & muestraL);
	
	//Realizamos una operacion AND de 8 bits a la varaible muestra que es de 16, por lo que nos quedaremos solo con los 8 bits de la parte derecha y los copiaremos 	de vuelta a la variable buffer, a la posicion 2.	
        buf[i + 2] = (unsigned char) (0xFF & muestraR);
        muestraR = muestraR >> 8;	//Desplazamos los 8 bits que nos quedan (de los 16 que teniamos), hacia la derecha.
	//Ahora realizamos la misma operacion que antes para quedarnos con 8 bits y devolverlos a la variable buffer, en la posicion 3.
        buf[i + 3] = (unsigned char) (0xFF & muestraR);
    }
}


//Declaracion de variables globales para el programa.
char *gPlaybackDevName = "hw:0,0";
char *gCaptureDevName = "hw:0,0";
//Frecuencia de muestro. 44100
unsigned int gRate = 44100;
//Duracion en segundos. 30
int gTestDuration = 5;
//Numero de canales. 2
int gNumChannels = 2;
snd_pcm_format_t gSampleFormat = SND_PCM_FORMAT_S16_LE;
//Tamaño de muestras por pediodo. 512
snd_pcm_uframes_t gPeriodSize = 512;
//Numero de periodos en el buffer.
int gBufferSize = 2;


//Funcion donde configuraremos los parametros que vamos a utilizar durante el programa y 
//que nos indique si hay algun error en la configuracion, para poder solucioanrlo.
//Si se detecta algun error, se devolvera la variable err, que activara un if en la funcion main, 
//y aparecera el mensaje de error.
int configure(snd_pcm_t *handle, const char* id) {
    snd_pcm_hw_params_t *hwParams;
    snd_pcm_sw_params_t *swParams;
    int err;
    unsigned int rate;
    snd_pcm_uframes_t frames;

    snd_pcm_hw_params_alloca(&hwParams);
    if ((err = snd_pcm_hw_params_any(handle, hwParams)) < 0) {
        printf("Broken configuration for %s PCM: no configurations available: %s\n", id, snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params_set_rate_resample(handle, hwParams, 1)) < 0) {
        printf("Resample setup failed for %s (val 1): %s\n", id, snd_strerror(err));
        return err;
    }
    if ((err = snd_pcm_hw_params_set_access(handle, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        printf("Access type not available for %s: %s\n", id, snd_strerror(err));
        return err;
    }
    if ((err = snd_pcm_hw_params_set_format(handle, hwParams, gSampleFormat)) < 0) {
        printf("Sample format not available for %s: %s\n", id, snd_strerror(err));
        return err;
    }
    if ((err = snd_pcm_hw_params_set_channels(handle, hwParams, gNumChannels)) < 0) {
        printf("Channels count (%i) not available for %s: %s\n", gNumChannels, id, snd_strerror(err));
        return err;
    }
    rate = gRate;
    if ((err = snd_pcm_hw_params_set_rate_near(handle, hwParams, &rate, 0)) < 0) {
        printf("Rate %iHz not available for %s: %s\n", gRate, id, snd_strerror(err));
        return err;
    }
    if (rate != gRate) {
        printf("Rate doesn't match (requested %iHz, get %iHz)\n", gRate, rate);
        return -EINVAL;
    }
    frames = gPeriodSize * gBufferSize;
    if ((err = snd_pcm_hw_params_set_buffer_size_near(handle, hwParams, &frames)) < 0) {
        printf("Unable to set buffer size %li for %s: %s\n", frames, id, snd_strerror(err));
        return err;
    }
    if ((err = snd_pcm_hw_params_set_period_size_near(handle, hwParams, &gPeriodSize, 0)) < 0) {
        printf("Unable to set period size %li for %s: %s\n", gPeriodSize, id, snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params(handle, hwParams)) < 0) {
        printf("Unable to set hardware parameters for %s: %s\n", id, snd_strerror(err));
        return err;
    }

    snd_pcm_sw_params_alloca(&swParams);
    if ((err = snd_pcm_sw_params_current(handle, swParams)) < 0) {
        printf("Unable to determine current sw parameters for %s: %s\n", id, snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_sw_params_set_start_threshold(handle, swParams, 0x7fffffff)) < 0) {
        printf("Unable to set start threshold mode for %s: %s\n", id, snd_strerror(err));
        return err;
    }
    if ((err = snd_pcm_sw_params_set_avail_min(handle, swParams, gPeriodSize)) < 0) {
        printf("Unable to set avail min for %s: %s\n", id, snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_sw_params(handle, swParams)) < 0) {
        printf("Unable to set software parameters for %s: %s\n", id, snd_strerror(err));
        return err;
    }

    return 0;
}

// Funcion para leer y guardar las muestras en el buffer.
long readBuf(snd_pcm_t *handle, char *buf, long len) {
    long r;
    int frame_bytes;

    frame_bytes = (snd_pcm_format_width(gSampleFormat) / 8) * gNumChannels;
    do {
	//Se guardan las muestras leidas en la varaible buf. r sera el numero de muestras obtenidas.
        r = snd_pcm_readi(handle, buf, len);
	//Si obtiene mas de 0 muestras, significa que lo ha leido correctamente y actualiza las varaibles.
        if (r > 0) {
            buf += r * frame_bytes;
            len -= r;
        }
	//Envia un mensaje de error en el caso que el numero de muestras sea menor que 0, lo que significa que no ha leido bien los datos.
        if (r < 0) {
            printf("Capture error: %s\n", snd_strerror(r));
        }
    } while (len > 0 && r > 0);
    //Nos devuelve r que es el numero de muestras.	
    return r;
}

// Funcion para escribir las muestras del buffer.
long writeBuf(snd_pcm_t *handle, char *buf, long len) {
    long r;
    int frame_bytes;

    frame_bytes = (snd_pcm_format_width(gSampleFormat) / 8) * gNumChannels;
    do {
        r = snd_pcm_writei(handle, buf, len);
        if (r == -EAGAIN)
            continue;
        if (r > 0) {
            buf += r * frame_bytes;
            len -= r;
        }
        if (r < 0) {
            printf("Playback error: %s\n", snd_strerror(r));
        }
    } while (len > 0 && r > 0);

    return r;
}

int main(int argc, char *argv[]) {
	//Declaramos variables y punteros.
    	snd_pcm_t *pHandle, *cHandle;
    	char *buffer;
	//int gPeriodSize;
    	int ok, err;
    	ssize_t r, numFrames;
	gPeriodSize = atoi(argv[1]);

	buffer = malloc(gPeriodSize * snd_pcm_format_width(gSampleFormat) / 8 * gNumChannels);

    if ((err = snd_pcm_open(&pHandle, gPlaybackDevName, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        return -1;
    }
    if ((err = snd_pcm_open(&cHandle, gCaptureDevName, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        printf("Capture open error: %s\n", snd_strerror(err));
        return -1;
    }

    if (configure(pHandle, "playback") < 0) {
        fprintf(stderr, "configuration error\n");
        return -1;
    }
    if (configure(cHandle, "capture") < 0) {
        fprintf(stderr, "configuration error\n");
        return -1;
    }

    if ((err = snd_pcm_prepare(pHandle)) < 0) {
        printf("Prepare error: %s\n", snd_strerror(err));
        return -1;
    }

    if ((err = snd_pcm_link(cHandle, pHandle)) < 0) {
        printf("Streams link error: %s\n", snd_strerror(err));
        return -1;
    }

    if (snd_pcm_format_set_silence(gSampleFormat, buffer, gPeriodSize) < 0) {
        fprintf(stderr, "silence error\n");
        return -1;
    }
    if (writeBuf(pHandle, buffer, gPeriodSize) < 0) {
        fprintf(stderr, "write error\n");
        return -1;
    }
    if (writeBuf(pHandle, buffer, gPeriodSize) < 0) {
        fprintf(stderr, "write error\n");
        return -1;
    }

    if ((err = snd_pcm_start(cHandle)) < 0) {
        printf("Start error: %s\n", snd_strerror(err));
        return -1;
    }
	
	//Declaramos la variable ok, que sera de control, si todo esta correcto ok=1.
    	ok = 1;
	//Variable donde guardaremos el numero total de muestras.
    	numFrames = 0;
    	while (ok && numFrames < gRate * gTestDuration) {
		//Si cuando lee las muestras hay algun error (que no lee las muestras correctamente)-> ok=0 y salimos del bucle.
		if ((r = readBuf(cHandle, buffer, gPeriodSize)) < 0) {
		    ok = 0;
		//Si lee las muestras corerctamente, 
		//llamamos a la funcion effect para aplicar el efecto sobre esas muestras.	
		} else {
		    effect(buffer, r);
		//Si al escribir hay algun error-> ok=0 y salimos del bucle;
		    if (writeBuf(pHandle, buffer, r) < 0)
		        ok = 0;
		//Si todo esta correcto, vamos acumulando el numero de muestras a la variable.
		    else
		        numFrames += r;
		}
	    }
	//LLamada a las funciones de ALSA
	    snd_pcm_drop(cHandle);
	    snd_pcm_drain(pHandle);
	    snd_pcm_unlink(cHandle);
	    snd_pcm_hw_free(pHandle);
	    snd_pcm_hw_free(cHandle);

	    snd_pcm_close(pHandle);
	    snd_pcm_close(cHandle);

    return 0;
}
