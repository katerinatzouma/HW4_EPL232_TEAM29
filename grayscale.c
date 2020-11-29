/**
 * Copyright (C) <2020> <Gor Mkhitaryan> <Aikaterini Tzouma>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *Υou should have received a copy of the GNU General Public License
 *along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*library integration*/
#include "lib.h"
/*this brightnnening of the image*/
static int brightness(RGB pixel);

static int brightness(RGB pixel) {
	return (int) (0.299 * (int) pixel.red + 0.587 * (int) pixel.green
			+ 0.114 * (int) pixel.blue);
}

int grayscale(char* filename, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info,
		RGB** image) {
  int i = 0;
  int j = 0;
  int  bright;
  int temp_1 = info->biHeight;
  int temp_2 = info->biWidth;
	/*checks for null files*/
	if(filename==NULL){
	  printf("ERROR\n");
	  return 1;
	}
	if(fh==NULL){
	  printf("ERROR\n");
	  return 1;
	}
	if(image==NULL){
	  printf("ERROR\n");
	  return 1;
	}
	if(info==NULL){
	  printf("ERROR\n");
	  return 1;
	}
	for (i = 0; i < temp_1; i++)
		for (j = 0; j < temp_2; j++) {
			bright = brightness(image[i][j]);
			image[i][j].red = (byte) bright;
			image[i][j].green = (byte) bright;
			image[i][j].blue = (byte) bright;
		}
	saving(filename, fh, info, image);
	return 0;
}

/**
 * @brief the main of the class
 *Includes all the controls of files 
 *and the initilization of the headers.
 * 
 */
#ifdef DEBUGGRAYSCALE
int main() {
	BITMAP_FILE_HEADER* fh = NULL;
	BITMAP_INFO_HEADER* info = NULL;
	RGB** image = NULL;
	FILE* fp = NULL;
	int j=0;
        int edit;
 printf("Wavengine.c Copyright (C) 2020 Gor Mkhitaryan Aikaterini Tzouma This program comes with ABSOLUTELY NO WARRANTY; for details type `show This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.\n");

	fh = (BITMAP_FILE_HEADER*) malloc(sizeof(BITMAP_FILE_HEADER));
	info = (BITMAP_INFO_HEADER*) malloc(sizeof(BITMAP_INFO_HEADER));
        /*controls for null files*/
	if(fh == NULL){
	  printf("ERROE\n");
	  return 1;
	}
	if(info == NULL){
	  printf("ERROE\n");
	  return 1;
	}

	/*controls if can open the file.*/
	if ((fp = fopen("3x4.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while (j< info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	grayscale("3x4.bmp",fh,info, image);
	while (j< info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);
	/*controls if can open the file.*/
	if ((fp = fopen("4x3.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while (j< info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	grayscale("4x3.bmp",fh,info, image);
	while (j< info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);

	/*controls if can open the file.*/
	if ((fp = fopen("image1.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while (j< info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	grayscale("image1.bmp",fh,info, image);
	while (j < info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);
	/*controls if can open the file.*/
	if ((fp = fopen("image7.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while(j < info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	grayscale("image7.bmp",fh,info, image);
	while (j< info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);

	free(fh);
	free(info);
	return 0;
}

#endif
