/**
 * Copyright (C) <2019> <Gor Mkhitaryan> <Aikaterini Tzouma>
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

#include "lib.h"

int checkImage(BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info) {

	if (info->biBitCount != 24) {
		printf("Not 24 bits\n");
		return 1;
	}
	if (info->biCompression != 0) {
		printf("compressed image\n");
		return 1;
	}
       if (fh->bfType1 != 'B' && fh->bfType2 != 'M') {
		printf("Can not open this file\n");
		return 1;
	}
	return 0;
}

int Headers(FILE* fp, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info) {

  if(fp ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(fh ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(info ==NULL){
    printf("ERROR\n");
    return 1;
  }


	fread(fh, sizeof(BITMAP_FILE_HEADER), 1, fp);
	fread(info, sizeof(BITMAP_INFO_HEADER), 1, fp);
	if (checkImage(fh, info) == 1) {
		fclose(fp);
		return 1;
	}
	return 0;
}

int open_image(FILE* fp, RGB** image, BITMAP_INFO_HEADER* info) {
  int i;
  int  edit;
  int temp_1 = info->biHeight;
  int temp_2 = info->biWidth;

  if(fp ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(image ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(info ==NULL){
    printf("ERROR\n");
    return 1;
  }
	edit = editing(temp_2);
	for (i = temp_1 - 1; i >= 0; i--)
		fread(image[i], sizeof(RGB) * temp_2 + edit, 1, fp);
	fclose(fp);
	return 0;
}

int saving(char* filename, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info,
		RGB** image) {

 if(filename == NULL){
   printf("ERROR\n");
   return 1;
  }
  if(fh ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(image ==NULL){
    printf("ERROR\n");
    return 1;
  }
  if(info ==NULL){
    printf("ERROR\n");
    return 1;
  }
	FILE* out = NULL;
	int size = sizeof(filename) + 4;
	int temp_1 = info->biHeight;
	int temp_2 = info-> biWidth;
	int i = 0;
        int  edit = 0;
	char s[size];
	sprintf(s, "out-%s", filename);
	if ((out = fopen(s, "wb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}

	fwrite(fh, sizeof(BITMAP_FILE_HEADER), 1, out);
	fwrite(info, sizeof(BITMAP_INFO_HEADER), 1, out);
	edit= editing(temp_2);
	for (i = temp_1 - 1; i >= 0; i--)
		fwrite(image[i], sizeof(RGB) * temp_2 + edit, 1, out);
	fclose(out);
	return 0;
}

int editing(dword biWidth) {
	int edit = ((biWidth * 3) % 4);

	if (edit == 0)
		return 0;
	return 4 - edit;
}

#ifdef DEBUG

int main() {
	BITMAP_FILE_HEADER* fh = NULL;
	BITMAP_INFO_HEADER* info = NULL;
	RGB** image = NULL;
	FILE* fp = NULL;
	int i=0;
         int  edit;

	fh = (BITMAP_FILE_HEADER*) malloc(sizeof(BITMAP_FILE_HEADER));
	info = (BITMAP_INFO_HEADER*) malloc(sizeof(BITMAP_INFO_HEADER));
        if(fh == NULL){
         printf("ERROR\n");
         return 1;
        }
        if(info ==NULL){
         printf("ERROR\n");
         return 1;
        }
		/*checks the list*/
	if ((fp = fopen("list.c", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);

	
	if ((fp = fopen("imageErr-8bit.bmp", "rb")) == NULL ) {
		printf("Unable to open the file\n");
		return 1;
	}
	Headers(fp, fh, info);

	printf("Try 3x4.bmp\n");
	if ((fp = fopen("3x4.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	if (Headers(fp, fh, info) == 0)
	
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	while(i < info->biHeight){
	image[i] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	i++;
	}
	if (open_image(fp, image, info) == 0)
	saving("3x4.bmp",fh,info,image);
	while(j < info->biHeight){
	free(image[j]);
	j++;
       }
	free(image);
/*checks the 4x3.bmp image*/
	printf("Try 4x3.bmp\n");
	if ((fp = fopen("4x3.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	if (Headers(fp, fh, info) == 0)
	edit=editing(info->biWidth);
	image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
	for (i = 0; i < info->biHeight; i++)
	image[i] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
	if (open_image(fp, image, info) == 0)
	saving("4x3.bmp",fh,info,image);
       while(i < info->biHeight){
	free(image[i]);
	i++;
     }

	free(image);

	free(fh);
	free(info);
	return 0;
}
#endif
