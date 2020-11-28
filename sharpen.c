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
 * ou should have received a copy of the GNU General Public License
 *along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*library integration*/
#include "lib.h"

/*function  for the value of the image*/
static void value(int* b);

void value(int* b) {
	if (*b > 255)
		*b = 255;
	else if (*b < 0)
		*b = 0;
}

int sharpen(char* filename, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info,
		RGB** image) {
  int j;
  int i;
  int k;
  int  edit = editing(info->biWidth);
  int  temp;
  int temp_1 = info->biHeight;
  int temp_2 = info->biWidth;
  int l=0;
  RGB **sharpen_image;

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

	sharpen_image = (RGB**) malloc(sizeof(RGB*) * temp_1);

	while ( l < temp_1){
             sharpen_image[l] = (RGB*) malloc(sizeof(RGB) * (temp_2 + edit));
	     l++;
	}

	for (i = 0; i < temp_1; i++) {
		for (j = 0; j < temp_2; j++) {
		  if (i != 0 && j != 0 )
                    if(i != temp_1 - 1
					&& j != temp_2 - 1) {
				temp = (-1) * (int) image[i - 1][j - 1].red
						+ (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i - 1][j + 1].red
						+ (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[i + 1][j - 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[i + 1][j + 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * image[i - 1][j - 1].green
						+ (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i - 1][j + 1].green
						+ (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[i + 1][j - 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[i + 1][j + 1].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].blue
						+ (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i - 1][j + 1].blue
						+ (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i][j + 1].blue
						+ (-1) * (int) image[i + 1][j - 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[i + 1][j + 1].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
                        if (i == 0 && j == 0) {
				//"left-upCorner"
				temp = 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[i + 1][j + 1].red
						+ (-1) * (int) image[temp_1 - 1][0].red
						+ (-1)
								* (int) image[temp_1 - 1][temp_2
										- 1].red
						+ (-1) * (int) image[0][temp_2 - 1].red
						+ (-1) * (int) image[temp_1 - 1][1].red
						+ (-1) * (int) image[1][temp_2 - 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[i + 1][j + 1].green
						+ (-1) * (int) image[info->biHeight - 1][0].green
						+ (-1)
								* (int) image[temp_1- 1][temp_2
										- 1].green
						+ (-1) * (int) image[0][temp_2 - 1].green
						+ (-1) * (int) image[temp_1 - 1][1].green
						+ (-1) * (int) image[1][temp_2 - 1].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i][j + 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[i + 1][j + 1].blue
						+ (-1) * (int) image[temp_1 - 1][0].blue
						+ (-1)
								* (int) image[temp_1 - 1][temp_2
										- 1].blue
						+ (-1) * (int) image[0][temp_2 - 1].blue
						+ (-1) * (int) image[temp_1 - 1][1].blue
						+ (-1) * (int) image[1][temp_2 - 1].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
			if (i == 0 )
			  if( j == temp_2 - 1) {
				//Right-UpCorner"
				temp = (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i + 1][j - 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[temp_1 - 1][0].red
						+ (-1) * (int) image[temp_1 - 1][j].red
						+ (-1) * (int) image[i][0].red + image[i][1].red
						+ (-1) * (int) image[temp_1 - 1][j - 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i + 1][j - 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[temp_1 - 1][0].green
						+ (-1) * (int) image[temp_1 - 1][j].green
						+ (-1) * (int) image[i][0].green + image[i][1].green
						+ (-1) * (int) image[temp_1 - 1][j - 1].green;
			       value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i + 1][j - 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[temp_1 - 1][0].blue
						+ (-1) * (int) image[temp_1 - 1][j].blue
						+ (-1) * (int) image[i][0].blue + image[i][1].blue
						+ (-1) * (int) image[temp_1 - 1][j - 1].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
                        if (i == 0 && j != 0)
                          if (j != temp_2 - 1) {
				//"Horizontical Up Row"
				temp = (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[i + 1][j - 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[i + 1][j + 1].red
						+ (-1) * (int) image[temp_1 - 1][j - 1].red
						+ (-1) * (int) image[temp_1 - 1][j].red
						+ (-1) * (int) image[temp_1 - 1][j + 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[i + 1][j - 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[i + 1][j + 1].green
						+ (-1) * (int) image[temp_1 - 1][j - 1].green
						+ (-1) * (int) image[temp_1 - 1][j].green
						+ (-1) * (int) image[temp_1 - 1][j + 1].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * image[i][j + 1].blue
						+ (-1) * (int) image[i + 1][j - 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[i + 1][j + 1].blue
						+ (-1) * (int) image[temp_1 - 1][j - 1].blue
						+ (-1) * (int) image[temp_1 - 1][j].blue
						+ (-1) * (int) image[temp_1 - 1][j + 1].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
                        if (i == temp_1 - 1 && j == 0) {
				//"Left-Down Corner"
				temp = (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i - 1][j + 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[0][j + 1].red
						+ (-1) * (int) image[0][j].red
						+ (-1) * (int) image[0][temp_2 - 1].red
						+ (-1) * (int) image[i][temp_2 - 1].red
						+ (-1) * (int) image[i - 1][temp_2 - 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i - 1][j + 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[0][j + 1].green
						+ (-1) * (int) image[0][j].green
						+ (-1) * (int) image[0][temp_2 - 1].green
						+ (-1) * (int) image[i][temp_2 - 1].green
						+ (-1) * (int) image[i - 1][temp_2 - 1].green;
				value(&temp);
			       sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i - 1][j + 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i][j + 1].blue
						+ (-1) * (int) image[0][j + 1].blue
						+ (-1) * (int) image[0][j].blue
						+ (-1) * (int) image[0][temp_2 - 1].blue
						+ (-1) * (int) image[i][temp_2 - 1].blue
						+ (-1) * (int) image[i - 1][temp_2 - 1].blue;
			       value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
                        if (i == temp_1 - 1 && j == temp_2 - 1) {
				//"Right-Down Corner"
				temp = (-1) * (int) image[i - 1][j - 1].red
						+ (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[0][0].red
						+ (-1) * (int) image[0][j].red
						+ (-1) * (int) image[0][j - 1].red
						+ (-1) * (int) image[i][0].red
						+ (-1) * (int) image[i - 1][0].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].green
						+ (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[0][0].green
						+ (-1) * (int) image[0][j].green
						+ (-1) * (int) image[0][j - 1].green
						+ (-1) * (int) image[i][0].green
						+ (-1) * (int) image[i - 1][0].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].blue
						+ (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[0][0].blue
						+ (-1) * (int) image[0][j].blue
						+ (-1) * (int) image[0][j - 1].blue
						+ (-1) * (int) image[i][0].blue
						+ (-1) * (int) image[i - 1][0].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
                        if (i == temp_1 - 1 )
			  if( j != 0 && j != temp_2 - 1) {
				//"Horizontical Last row"
				temp = (-1) * (int) image[i - 1][j - 1].red
						+ (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i - 1][j + 1].red
						+ (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[0][j - 1].red
						+ (-1) * (int) image[0][j].red
						+ (-1) * (int) image[0][j + 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].green
						+ (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i - 1][j + 1].green
						+ (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[0][j - 1].green
						+ (-1) * (int) image[0][j].green
						+ (-1) * (int) image[0][j + 1].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].blue
						+ (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i - 1][j + 1].blue
						+ (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i][j + 1].blue
						+ (-1) * (int) image[0][j - 1].blue
						+ (-1) * (int) image[0][j].blue
						+ (-1) * (int) image[0][j + 1].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
			if (i != 0 && i != temp_1 - 1 )
			  if( j == 0) {
				//"Vertical first coloumn"
				temp = (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i - 1][j + 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i][j + 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[i + 1][j + 1].red
						+ (-1) * (int) image[i - 1][temp_2 - 1].red
						+ (-1) * (int) image[i][temp_2 - 1].red
						+ (-1) * (int) image[i + 1][temp_2 - 1].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i - 1][j + 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i][j + 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[i + 1][j + 1].green
						+ (-1) * (int) image[i - 1][temp_2 - 1].green
						+ (-1) * (int) image[i][temp_2 - 1].green
						+ (-1) * (int) image[i + 1][temp_2 - 1].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i - 1][j + 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i][j + 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[i + 1][j + 1].blue
						+ (-1) * (int) image[i - 1][temp_2 - 1].blue
						+ (-1) * (int) image[i][temp_2 - 1].blue
						+ (-1) * (int) image[i + 1][temp_2 - 1].blue;
			       value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			} 
			if (i != 0 && i != temp_1 - 1)
			  if( j == temp_2 - 1) {
				//"Vertical Last Column"
				temp = (-1) * (int) image[i - 1][j - 1].red
						+ (-1) * (int) image[i - 1][j].red
						+ (-1) * (int) image[i][j - 1].red
						+ 9 * (int) image[i][j].red
						+ (-1) * (int) image[i + 1][j - 1].red
						+ (-1) * (int) image[i + 1][j].red
						+ (-1) * (int) image[i - 1][0].red
						+ (-1) * (int) image[i][0].red
						+ (-1) * (int) image[i + 1][0].red;
				value(&temp);
				sharpen_image[i][j].red = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].green
						+ (-1) * (int) image[i - 1][j].green
						+ (-1) * (int) image[i][j - 1].green
						+ 9 * (int) image[i][j].green
						+ (-1) * (int) image[i + 1][j - 1].green
						+ (-1) * (int) image[i + 1][j].green
						+ (-1) * (int) image[i - 1][0].green
						+ (-1) * (int) image[i][0].green
						+ (-1) * (int) image[i + 1][0].green;
				value(&temp);
				sharpen_image[i][j].green = (byte) temp;

				temp = (-1) * (int) image[i - 1][j - 1].blue
						+ (-1) * (int) image[i - 1][j].blue
						+ (-1) * (int) image[i][j - 1].blue
						+ 9 * (int) image[i][j].blue
						+ (-1) * (int) image[i + 1][j - 1].blue
						+ (-1) * (int) image[i + 1][j].blue
						+ (-1) * (int) image[i - 1][0].blue
						+ (-1) * image[i][0].blue
						+ (-1) * (int) image[i + 1][0].blue;
				value(&temp);
				sharpen_image[i][j].blue = (byte) temp;
			}
		}
		if (edit != 0)
			for (k = j; k < temp_2 + edit; k++) {
				sharpen_image[i][k].red = '\0';
				sharpen_image[i][k].green = '\0';
				sharpen_image[i][k].blue = '\0';
			}
	}

	saving(filename, fh, info, sharpen_image);
	for (i = 0; i < temp_1; i++)
		free(sharpen_image[i]);
	free(sharpen_image);

	return 0;
}


/**
 * @brief the main of the class
 *Includes all the controls of files 
 *and the initilization of the headers.
 * 
 */
#ifdef DEBUGSHARPEN
int main() {
        /*initilization of the headers*/
	BITMAP_FILE_HEADER* fh = NULL;
	BITMAP_INFO_HEADER* info = NULL;
	RGB** image = NULL;
	FILE* fp = NULL;
	int edit;
        int j=0;
 printf("Wavengine.c Copyright (C) 2019 Adamantia Elia Aikaterini Tzouma This program comes with ABSOLUTELY NO WARRANTY; for details type `show This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.\n");
	/*initialization for the memory of headers*/
	fh = (BITMAP_FILE_HEADER*) malloc(sizeof(BITMAP_FILE_HEADER));
	info = (BITMAP_INFO_HEADER*) malloc(sizeof(BITMAP_INFO_HEADER));
	/*controls for null files*/
	if(fh == NULL){
	  printf("ERROR\n");
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
	while (j < info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	sharpen("3x4.bmp",fh,info, image);
	while(j < info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);

        /*checks if the file can open.*/
	if ((fp = fopen("4x3.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while (j < info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
	open_image(fp, image, info);
	sharpen("4x3.bmp",fh,info, image);
	while (j < info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);

        /*checks if the file can open.*/
	if ((fp = fopen("image1.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while(j< info->biHeight){
	  image[j] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	  j++;
	}
      open_image(fp, image, info);
	sharpen("image1.bmp",fh,info, image);
	while (j < info->biHeight){
	  free(image[j]);
	  j++;
	}
	free(image);

	/*checks if the file can open.*/
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
	sharpen("image7.bmp",fh,info, image);
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
