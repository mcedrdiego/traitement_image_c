# Traitement d'image en c

Transformation des image en .png et .bmp :

1. Transformer en nuances de gris 
2. Binerisation de l'image en couleur 
3. Binerisation de l'image en niveau de gris 
4. Negatif de l'image en couleur 
5. Negatif puis transformer l'image en nuances de gris 
6. Negatif puis Binerisation de l'image en couleur 
7. Negatif puis Binerisation de l'image en niveau de gris 
8. Sobel y de l'image
9. Sobel x de l'image
10. Gaussien de l'image
11. Ajout du bruit sur l'image
12. Laplacce de l'image

## Compilation
```
make 
```
## Usage
```
./treat_image path/to/image.bmp 
```
*The output is stored in images directory*