#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CREATOR "PDS"
#define MAX_COMPONENT_COLOR 255

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int w, h;
    Pixel *pixels;
} Image;

Pixel g_pixelBlack = { 0, 0, 0 };

//Funcion para leer una imagen PPM. Tenemos que obtener los datos que vienen en las 
//cabeceras de estas imagen que es informacion util para nosotros.
Image *readPPM(const char *filename)
{
    char buff[16];
    Image *img;
    FILE *fp;
    int c, maxComp;

    //Abrimos el archivo PPM para leer los datos.
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }
    //Leemos el formato de la imagen.
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }
    //Comprobamos el formato de la imagen obtenido anteriormente.
    if (buff[0] != 'P' || buff[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }
    //Reserva de memoria.
    img = (Image *) malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    //Comprobacion de los comentarios.
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n') ;
        c = getc(fp);
    }
    ungetc(c, fp);
	
    //Leemos el tamaño de la imagen.
    if (fscanf(fp, "%d %d", &img->w, &img->h) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n",
            filename);
        exit(1);
    }
    //Lectura de la componente RGB.
    if (fscanf(fp, "%d", &maxComp) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n",
            filename);
        exit(1);
    }
    //Comprobacion de la profundidad de las componentes RGB.
    if (maxComp != MAX_COMPONENT_COLOR) {
        fprintf(stderr, "'%s' does not have 8-bits components\n",
            filename);
        exit(1);
    }
	
    while (fgetc(fp) != '\n') ;
    //Reserva de memoria para los valores de los pixeles.
    img->pixels = (Pixel *) malloc(img->w * img->h * sizeof(Pixel));
    if (!img->pixels) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    //Leemos los valores del pixel desde el archivo.
    if (fread(img->pixels, 3 * img->w, img->h, fp) != img->h) {
        fprintf(stderr, "Error loading image '%s'\n", filename);
        exit(1);
    }
    //Cerramos el archivo PPM.
    fclose(fp);

    return img;
}

//Funcion para pasar una matriz de datos a una imagen .PPM.
void writePPM(const char *filename, Image * img)
{
    FILE *fp;

    //Abrimos el archivo para exportar.
    fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }
    //write the header file image format
    fprintf(fp, "P6\n");
    //comments
    fprintf(fp, "# Created by %s\n", CREATOR);
    //image size
    fprintf(fp, "%d %d\n", img->w, img->h);
    //rgb component depth
    fprintf(fp, "%d\n", MAX_COMPONENT_COLOR);
    //pixel data
    fwrite(img->pixels, 3 * img->w, img->h, fp);
    //close file
    fclose(fp);
}

//Obtener el valor de un pixel, verificando si el pixel solicitado se encuentra dentro del rango de la imagen.
Pixel *getPixel(Image * img, int x, int y)
{
    if (x < 0 || x >= img->w || y < 0 || y >= img->h) {
        return &g_pixelBlack;
    }
    return (img->pixels) + (img->w * y + x);
}

void setPixel(Image * img, int x, int y, int r, int g, int b)
{
    Pixel *q;
	
    if (r > MAX_COMPONENT_COLOR)
        r = MAX_COMPONENT_COLOR;
    if (g > MAX_COMPONENT_COLOR)
        g = MAX_COMPONENT_COLOR;
    if (b > MAX_COMPONENT_COLOR)
        b = MAX_COMPONENT_COLOR;
    if (r < 0)
        r = 0;
    if (g < 0)
        g = 0;
    if (b < 0)
        b = 0;
	
    q = (img->pixels) + (img->w * y + x);
    q->r = (unsigned char)r;
    q->g = (unsigned char)g;
    q->b = (unsigned char)b;
}

Image *getNewImage(int w, int h)
{
    Image *img;

    //Reservamos memoria para la imagen.
    img = (Image *) malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    //Guardamos el tamaño de la imagen en w y h.
    img->w = w;
    img->h = h;
    //Reservamos la memoria de los pixeles
    img->pixels = (Pixel *) malloc(img->w * img->h * sizeof(Pixel));
    if (!img->pixels) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    return img;
}

//Liberamos la memoria de la imagen
void freeImage(Image * img)
{
    if (img != NULL) {
        if (img->pixels != NULL) {
            free(img->pixels);
        }
        free(img);
    }
}

//Funcion para realizar la convolucion de una imagen. (img x la matriz de convolucion)
Image *rgb2YCrCb(Image * img){
    //Definimos las variabes para la convolucion.
    int i, j;
    Image *out;
    Pixel *p;
    //Variables dnde iremos guardando los valores RGB para cada pixel.
    int r, g, b, y; 
	//int Cr, Cb;

    out = getNewImage(img->w, img->h);

    for (i = 0; i < img->w; i++) {
        for (j = 0; j < img->h; j++) {
            p = getPixel(img,i,j);
			//FORMULA -> Y=R*0.3+G*0.59+B*0.11
			y=((p->r)*0.299)+((p->g)*0.587)+((p->b)*0.114);
			//Cr=((p->r))*(-0.147)+((p->g)*(-0.289))+((p->b)*0.436);
			//Cb=((p->r)*0.615)+((p->g)*(-0.515))+((p->b)*(-0.1));
			r = y;
            g = y;
            b = y;
            setPixel(out, i, j, r, g, b);
        }
    }
    return out;
}

//Funcion para realizar la binarizacion de una imagen. (img x la matriz de convolucion)
Image *Binarizacion(Image * img){
    //Definimos las variabes para la convolucion.
    int i, j;
    Image *out;
    Pixel *p;
    //Variables dnde iremos guardando los valores RGB para cada pixel.
    int r, g, b;

    out = getNewImage(img->w, img->h);

    for (i = 0; i < img->w; i++) {
        for (j = 0; j < img->h; j++) {
	        //Obtencion del pixel dela imagen original para realizar la operacion.
            p = getPixel(img,i,j);
                    
			if(p->r >= 128 & p->g >= 128 & p->b >= 128 ){
				r=255;
				g=255;
				b=255;
				//Asignacion del pixen a la iamgen out
				setPixel(out, i, j, r, g, b);
			}
			else {
				r=0;
				g=0;
				b=0;
				//Asignacion del pixen a la iamgen out
				setPixel(out, i, j, r, g, b);
			}
			
        }
    }
    return out;
}

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}


int main(){
	LARGE_INTEGER t_ini, t_fin;
	double seg;
    Image *in = NULL, *gray = NULL, *final = NULL;

    //Cargamos la imagen
    in = readPPM("in2.ppm");

	QueryPerformanceCounter(&t_ini); //Obtener tiempo antes de realizar la operacion
	
    //Pasamos la foto a esta funcion para obtenerla en escala de grises.
    gray = rgb2YCrCb(in);
	//Con la imagen conseguida en escala de grises, la binarizamos en la siguiente funcion.
	final = Binarizacion(gray);
	
	QueryPerformanceCounter(&t_fin); //Obtener tiempo antes de realizar la operacion

    //Escribimos la imagen en el fichero out.ppm
    writePPM("out.ppm", final);

	seg = performancecounter_diff(&t_fin, &t_ini);
	printf("El tiempo de ejecucion es: %.16g ms\n", seg * 1000.0);

    //Liberar memoria
    freeImage(in);
	freeImage(gray);
    freeImage(final);
}
