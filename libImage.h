#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */


typedef struct {
	unsigned char   Bleu;
	unsigned char   Vert;
	unsigned char   Rouge;
} pixel;

typedef struct {
	uint32_t    Taille_BMPINFO;   //Taille en octet de BITMAP_INFO
	int32_t	    Largeur;          //Largeur de l'image en pixels
	int32_t	    Hauteur;          //Largeur de l'image en pixels
	uint16_t	Nbr_Plans;        // Nombre de plans. par defaut 1
	uint16_t	Nbr_pixelBits;    //Nombre de Bits par pixel. Ici 24 Bits
	uint32_t	Compression;      // 0: Pas de compression
	uint32_t	SizeImage;        //taille en octets de l'image
	int32_t	    X_Resolution;     //nombre de pixels par metre sur l'axe X
	int32_t	    Y_Resolution;     //nombre de pixels par metre sur l'axe Y
	uint32_t	Palette_Couleur;  //palette des couleurs utilis�es. 0: maximum de couleur
	uint32_t	ClrImportant;     // Couleur importante. 0: toute les couleurs
} bmpInfo;

typedef struct {
	uint16_t	Signature;        //signature de fichier g�n�ralement "BM" pour BitMap
	uint32_t	SizeFile;         //Taille du Fichier en octets
	uint16_t	Reserve1;         //Champs reserve non utilis�
	uint16_t	Reserve2;         //Champs reserve non utilis�
	uint32_t	Position_Data;    //Position en octet correspondant au d�but de l'image
} bmpHeader;

// Mettre ici les prototypes des fonction du TP
pixel * LireImage( char filename[], bmpInfo *p_bin, bmpHeader *p_bh);
int EcrireImage(char filename[], bmpInfo bin, bmpHeader bh, pixel *table);
void NuancesGris(pixel* tabPixel, int nb);
void Binerisation(pixel * tabPixel, int nb, int seuil);
void NegatifImage(pixel* tabPixel, int nb);
pixel * Convolution2D(pixel * p, int w, int h, float se[3][3]);
unsigned char sat(float a);
void ajoutBruit(pixel * p , int nb, unsigned char vmax);
pixel * Laplacian(pixel *t1, pixel *t2, int nb);
// Fin du fichier .h
#pragma pack(pop)   /* restore original alignment from stack */
