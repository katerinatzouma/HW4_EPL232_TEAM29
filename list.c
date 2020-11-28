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

/*checks for null files/images */
int list(BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info) {
  if(fh == NULL){
    printf("ERROR\n");
    return 1;
  }
  if (info == NULL ) {
      printf("ERROR\n");
      return 1;
     }

  /*print the inforation in the console*/
	printf("\nBITMAP_FILE_HEADER\n");
	printf("==================\n");
	printf("bfType: %c%c\n", fh->bfType1, fh->bfType2);
	printf("bfSize: %d\n", fh->bfSize);
	printf("bfReserved1: %d\n", fh->bfReserved1);
	printf("bfReserved2: %d\n", fh->bfReserved2);
	printf("bfOffBits: %d\n", fh->bfOffBits);

	printf("\nBITMAP_INFO_HEADER\n");
	printf("==================\n");
	printf("biSize: %d\n", info->biSize);
	printf("biWidth: %d\n", info->biWidth);
	printf("biHeight: %d\n", info->biHeight);
	printf("biPlanes: %d\n", info->biPlanes);
	printf("biBitCount: %d\n", info->biBitCount);
	printf("biCompression: %d\n", info->biCompression);
	printf("biSizeImage: %d\n", info->biSizeImage);
	printf("biXPelsPerMeter: %d\n", info->biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", info->biYPelsPerMeter);
	printf("biClrUsed: %d\n", info->biClrUsed);
	printf("biClrImportant: %d\n", info->biClrImportant);

	return 0;
}

/**
 * @brief the main of the class
 *Includes all the controls of files 
 *and the initilization of the headers.
 */
#ifdef DEBUGLIST
int main() {
 printf("Wavengine.c Copyright (C) 2020 Gor Mkhitaryan Aikaterini Tzouma This program comes with ABSOLUTELY NO WARRANTY; for details type `show This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.\n");

	BITMAP_FILE_HEADER* fh = NULL;
	BITMAP_INFO_HEADER* info = NULL;
	FILE* fp = NULL;
	/*initialization for the memory of headers*/
	fh = (BITMAP_FILE_HEADER*) malloc(sizeof(BITMAP_FILE_HEADER));
	info = (BITMAP_INFO_HEADER*) malloc(sizeof(BITMAP_INFO_HEADER));
	/*controls about fh and info*/
  if(fh == NULL){
    printf("ERROR\n");
    return 1;
  }
  if (info == NULL ) {
		printf(" ERROR\n");
		return 1;
	}
  /*checks the file*/
  	if ((fp = fopen("image2.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	list(fh,info);
	/*checs the file*/
	if ((fp = fopen("4x3.bmp", "rb")) == NULL ) {
		printf("Can not open this file\n");
		return 1;
	}
	Headers(fp, fh, info);
	list(fh,info);

	free(fh);
	free(info);
	return 0;
}
#endif
