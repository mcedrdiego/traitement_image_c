#include "libImage.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

int main()
{
    srand(time(NULL));
    char fileName[] = "images/Lena.bmp";
    pixel *px_Image, * px, *py;
    bmpHeader imHeader;
    bmpInfo imInfo;
    short choix;
    float sy[3][3] = {
        {-1.0,-2.0,-1.0},
        {0.0,0.0,0.0},
        {1.0,2.0,1.0}
    };
    float sx[3][3] = {
        {-1.0,0.0,1.0},
        {-2.0,0.0,2.0},
        {-1.0,0.0,1.0}
    };
    float gauss[3][3] = {
        {1.0/16,2.0/16,1.0/16},
        {2.0/16,1.0/16,2.0/16},
        {1.0/16,2.0/16,1.0/16}
    };
    do
    {
        px_Image = LireImage(fileName,&imInfo, &imHeader);
        //Menu
        printf("Que voulez vous faire ? \n");
        printf("\t 1. Transformer en nuances de gris \n");
        printf("\t 2. Binerisation de l'image en couleur \n");
        printf("\t 3. Binerisation de l'image en niveau de gris \n");
        printf("\t 4. Negatif de l'image en couleur \n");
        printf("\t 5. Negatif puis transformer l'image en nuances de gris \n");
        printf("\t 6. Negatif puis Binerisation de l'image en couleur \n");
        printf("\t 7. Negatif puis Binerisation de l'image en niveau de gris \n");
        printf("\t 8. Sobel y de l'image\n");
        printf("\t 9. Sobel x de l'image\n");
        printf("\t 10. Gaussien de l'image\n");
        printf("\t 11. Ajout du bruit sur l'image\n");
        printf("\t 12. Laplace de l'image\n");
        printf("\t 0. Quitter \n");
        scanf("%hu", &choix);
        //fin menu
        switch(choix)
        {
        case 1:
            NuancesGris(px_Image, imInfo.Largeur*imInfo.Hauteur);
            EcrireImage("images/LenaGris.bmp", imInfo, imHeader, px_Image);
            break;
        case 2:
            Binerisation(px_Image, imInfo.Largeur*imInfo.Hauteur, 86 );
            EcrireImage("images/LenaB.bmp", imInfo, imHeader, px_Image);
            break;
        case 3:
            NuancesGris(px_Image, imInfo.Largeur*imInfo.Hauteur);
            Binerisation(px_Image, imInfo.Largeur*imInfo.Hauteur, 86 );
            EcrireImage("images/LenaGrisB.bmp", imInfo, imHeader, px_Image);
            break;
        case 4:
            NegatifImage(px_Image, imInfo.Largeur*imInfo.Hauteur);
            EcrireImage("images/LenaNeg.bmp", imInfo, imHeader, px_Image);
            break;
        case 5:
            NegatifImage(px_Image, imInfo.Largeur*imInfo.Hauteur);
            NuancesGris(px_Image, imInfo.Largeur*imInfo.Hauteur);
            EcrireImage("images/LenaNegG.bmp", imInfo, imHeader, px_Image);
            break;
        case 6:
            NegatifImage(px_Image, imInfo.Largeur*imInfo.Hauteur);
            Binerisation(px_Image, imInfo.Largeur*imInfo.Hauteur, 86 );
            EcrireImage("images/LenaNegB.bmp", imInfo, imHeader, px_Image);
            break;
        case 7:
            NegatifImage(px_Image, imInfo.Largeur*imInfo.Hauteur);
            NuancesGris(px_Image, imInfo.Largeur*imInfo.Hauteur);
            Binerisation(px_Image, imInfo.Largeur*imInfo.Hauteur, 86 );
            EcrireImage("images/LenaNegGrisB.bmp", imInfo, imHeader, px_Image);
            break;
        case 8:
            px = Convolution2D(px_Image, imInfo.Largeur, imInfo.Hauteur, sy);
            EcrireImage("images/LenaConvSy.bmp", imInfo, imHeader, px);
            break;
        case 9:
            px = Convolution2D(px_Image, imInfo.Largeur, imInfo.Hauteur, sx);
            EcrireImage("images/LenaConvSx.bmp", imInfo, imHeader, px);
            free(px);
	    break;
        case 10:
            px = Convolution2D(px_Image, imInfo.Largeur, imInfo.Hauteur, gauss);
            EcrireImage("images/LenaConvGauss.bmp", imInfo, imHeader, px);
            free(px);
            break;
        case 11:
            ajoutBruit(px_Image, imInfo.Largeur*imInfo.Hauteur,100);
            EcrireImage("images/LenaBruit.bmp", imInfo, imHeader, px_Image);
            break;
        case 12:
            px = Convolution2D(px_Image, imInfo.Largeur, imInfo.Hauteur, sx);
            py = Convolution2D(px_Image, imInfo.Largeur, imInfo.Hauteur, sy);
            EcrireImage("images/LenaLapl.bmp", imInfo, imHeader, Laplacian(px, py, imInfo.Largeur*imInfo.Hauteur));
            free(py); free(px);
            break;
        case 0:
            printf("Au Revoir \n");
            break;
        default:
            printf("Choix non dans la liste! Reessayez. \n");
            break;
        }
    } while(choix != 0);
    free(px_Image);
    return 0;
}