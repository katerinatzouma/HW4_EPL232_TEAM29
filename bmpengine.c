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
/* @brief this is the main function of all the program. */
int main(int argc, char** argv) {
	BITMAP_FILE_HEADER* fh = NULL;
	BITMAP_INFO_HEADER* info = NULL;
	RGB** image = NULL;
	FILE* fp = NULL;
	int i=0;
	int j=2;
        int edit;
/*checks for null files/images and malloc check */	
	fh = (BITMAP_FILE_HEADER*) malloc(sizeof(BITMAP_FILE_HEADER));
	info = (BITMAP_INFO_HEADER*) malloc(sizeof(BITMAP_INFO_HEADER));
	if(fh==NULL){
	  printf("ERROR\n");
	  return 1;
	}
        if( info == NULL ) {
		printf("ERROR\n");
		return 1;
	}

	for (j=2; j < argc; j++) {
	  	if ((fp = fopen(argv[j], "rb")) == NULL ) {
		  	printf("Can not open this file\n", argv[j]);
			continue;
			} 

		if (Headers(fp, fh, info) == 1) {
			printf(" in %s\n", argv[j]);
			continue;
			}

		edit = editing(info->biWidth);
		image = (RGB**) malloc(sizeof(RGB*) * info->biHeight);
        
		while( i < info->biHeight) {
			image[i] = (RGB*) malloc(sizeof(RGB) * (info->biWidth + edit));
			if (image[i] == NULL ) {
			  while(i>=0){
			      	free(image[i]);
				i--;
			  }
				free(image);
		        
				break;
			}
			i++;
		}
        
			if (open_image(fp, image, info) == 1) {
			printf("in %s\n", argv[j]);
			if (image != NULL ) {
			  while( i < info->biHeight){
					free(image[i]);
					i++;
			  }
				free(image);
			}
			continue;
		}
		    /*controls about all the issues that we have to make*/
		       	if (strcmp(argv[1], "-list") == 0) {
			list(fh, info);
		} else if (strcmp(argv[1], "-grayscale") == 0) {
			grayscale(argv[j], fh, info, image);
		} else if (strcmp(argv[1], "-sharpen") == 0) {
			sharpen(argv[j], fh, info, image);
	
		} else {
                       if (image != NULL ) {
			 while( i < info->biHeight){
					free(image[i]);
					i++;
			 }
				free(image);
			}
			free(fh);
			free(info);
		
			return 1;
			}
		if (image != NULL ) {
		  while(i < info->biHeight){
				free(image[i]);
				i++;
		  }
			free(image);
		}
	}


	
	free(fh);
	free(info);
	return 0;
}
