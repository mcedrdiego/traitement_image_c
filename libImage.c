#include "libImage.h"

pixel * LireImage( char filename[], bmpInfo *p_bin, bmpHeader *p_bh)
{
    //unsigned long nb, pos;
    FILE * fichier = fopen(filename, "rb");
    pixel *p_pxImage;
    if( fichier != NULL)
    {
        fread(p_bh, sizeof(bmpHeader), 1, fichier);
        fread(p_bin, sizeof(bmpInfo), 1, fichier);
        //pos  = ftell(fichier);
        //fseek(fichier, 0, SEEK_END);
        //nb  = (ftell(fichier) - sizeof(bmpHeader) - sizeof(bmpInfo))/sizeof(pixel);
        //fseek(fichier, pos, SEEK_SET);
        p_pxImage = (pixel*) calloc((p_bin->Hauteur)*(p_bin ->Largeur), sizeof(pixel));
        fread(p_pxImage, sizeof(pixel), (p_bin->Hauteur)*(p_bin ->Largeur), fichier);
        fclose(fichier);
        return p_pxImage;
    }
    return NULL;
}

int EcrireImage(char filename[], bmpInfo bin, bmpHeader bh, pixel *table)
{
    FILE *fichier;
    fichier = fopen(filename, "wb");
    if(fichier != NULL)
    {
        fwrite(&bh, sizeof(bmpHeader), 1, fichier);
        fwrite(&bin, sizeof(bmpInfo), 1, fichier);
        fwrite(table, sizeof(pixel), (bin.Hauteur * bin.Largeur), fichier);
        fclose(fichier);
        return 0;
    }
    return -1;
}

void NuancesGris(pixel* tabPixel, int nb)
{
    int i;
    for(i=0; i<nb; i++)
    {
        tabPixel[i].Bleu = (tabPixel[i].Bleu + tabPixel[i].Vert + tabPixel[i].Rouge)/3 ;
        tabPixel[i].Rouge = tabPixel[i].Bleu;
        tabPixel[i].Vert = tabPixel[i].Bleu;
    }
}

void Binerisation(pixel * tabPixel, int nb, int seuil)
{
    int i;
    for(i=0; i<nb; i++)
    {
        if((tabPixel[i].Bleu) < seuil)
            tabPixel[i].Bleu = 0;
        else if((tabPixel[i].Bleu) >=  seuil)
            tabPixel[i].Bleu = 255;
        if((tabPixel[i].Vert) < seuil)
            tabPixel[i].Vert = 0;
        else if((tabPixel[i].Rouge) >=  seuil)
            tabPixel[i].Rouge = 255;
        if((tabPixel[i].Rouge) < seuil)
            tabPixel[i].Rouge = 0;
        else if((tabPixel[i].Vert) >=  seuil)
            tabPixel[i].Vert = 255;
    }
}

void NegatifImage(pixel* tabPixel, int nb)
{
    int i;
    for(i=0; i<nb; i++)
    {
        tabPixel[i].Bleu = 255 - tabPixel[i].Bleu;
        tabPixel[i].Vert = 255 - tabPixel[i].Vert;
        tabPixel[i].Rouge = 255 - tabPixel[i].Rouge;
    }
}

pixel * Convolution2D(pixel * p, int w, int h, float se[3][3])
{
    pixel * ptr_img;
    float B, V, R;
    short m, n;
    ptr_img = (pixel*) calloc(h*w, sizeof(pixel));
    int i, j;
    for(i=1; i<h-1; i++)
    {
        for(j=1; j<w-1; j++)
        {
            B = V = R = 0.0;
            for(n=-1; n<=1; n++)
            {
                for(m=-1; m<=1; m++)
                {
                    B = B + p[((i+n)*w) + j+m].Bleu * se[n+1][m+1];
                    R = R + p[((i+n)*w) + j+m].Rouge * se[n+1][m+1];
                    V = V + p[((i+n)*w) + j+m].Vert * se[n+1][m+1];
                }
                //ptr_img[((i+n)*w) + j+m].Bleu = ptr_img[((i+n)*w) + j+m].Bleu + sat((p[((i+n)*w) + j+m].Bleu * se[n+1][m+1]));
                //ptr_img[((i+n)*w) + j+m].Rouge = ptr_img[((i+n)*w) + j+m].Rouge + sat((p[((i+n)*w) + j+m].Rouge * se[n+1][m+1]));
                //ptr_img[((i+n)*w) + j+m].Vert = ptr_img[((i+n)*w) + j+m].Vert + sat((p[((i+n)*w) + j+m].Vert * se[n+1][m+1]));

            }
/*            ptr_img[(i*w) + j].Bleu = (unsigned char)B; //sat(B);
            ptr_img[(i*w) + j].Rouge = (unsigned char)R; //sat(R);
            ptr_img[(i*w) + j].Vert = (unsigned char)V; //sat(V);*/
            ptr_img[(i*w) + j].Bleu = sat(B);
            ptr_img[(i*w) + j].Rouge = sat(R);
            ptr_img[(i*w) + j].Vert = sat(V);

        }
    }
    return ptr_img;
}
unsigned char sat(float a)
{
    if(a<0.0)
        return 0;
    else if(a>255.0)
        return 255;
    else
        return (unsigned char)a;
}

void ajoutBruit(pixel * p , int nb, unsigned char vmax)
{
    unsigned char v;
    int i;
    for(i=0; i<nb; i++)
    {
        v= rand()%(2*vmax+1) - vmax;
        p[i].Bleu = p[i].Bleu+v;
        p[i].Rouge = p[i].Rouge+v;
        p[i].Vert = p[i].Vert+v;
    }
}

pixel * Laplacian(pixel *t1, pixel *t2, int nb)
{
	pixel * ptr_image;
	int i;
	ptr_image = (pixel *) calloc(sizeof(pixel), nb);
	for(i=0; i<nb; i++)
	{
		ptr_image[i].Bleu = pow( pow(t1[i].Bleu,2) + pow(t2[i].Bleu,2) ,0.5 ) ;
		ptr_image[i].Vert = pow( pow(t1[i].Vert,2) + pow(t2[i].Vert,2) ,0.5 ) ;
		ptr_image[i].Rouge = pow( pow(t1[i].Rouge,2) + pow(t2[i].Rouge,2) ,0.5 ) ;
	}
	return ptr_image;
}
