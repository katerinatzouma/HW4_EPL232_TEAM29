/**
 * @mainpage Homework 4
 *
 * @author Aikaterini Tzouma (ID:AK350186)
 * @authoe Gor Mkhitaryan (ID:AP0262790)
 *
 *This is the library for the program
 *that all the classes use it.
 *
 *@bugs no known bugs.
 *
 */

#define LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief there are the structures 
 * that we need for the program.
 **/
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct {
	byte bfType1;
	byte bfType2;
	dword bfSize;
	word bfReserved1;
	word bfReserved2;
	dword bfOffBits;
}__attribute__((packed)) BITMAP_FILE_HEADER;

typedef struct {
	dword biSize;
	dword biWidth;
	dword biHeight;
	word biPlanes;
	word biBitCount;
	dword biCompression;
	dword biSizeImage;
	dword biXPelsPerMeter;
	dword biYPelsPerMeter;
	dword biClrUsed;
	dword biClrImportant;
}__attribute__((packed)) BITMAP_INFO_HEADER;

typedef struct {
	byte red;
	byte green;
	byte blue;
}__attribute__((packed)) RGB;


/**
 * @brief in this function there are some
 * controls that to check the image before the editing.
 **/
int checkImage(BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info);
/**
 * @brief this function includes 
 * all the headers of the program.
 **/
int Headers(FILE* fp, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info);

/**
 *@brief this function is about to recognizes 
 *and read the image.
 **/

int open_image(FILE* fp, RGB** image, BITMAP_INFO_HEADER* info);
/**
 *@brief this function is about to save 
 *the image after any change that we will do.
 **/
int saving(char* filename, BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info,
		RGB** image);
/**
 * @brief this function is about the calculationg of width
 **/
int editing (dword biWidth);


/**
 * @brief This class is for the first issue of the program.
 *Gives information about the image that you
 *want to know every single time.
 */
int list(BITMAP_FILE_HEADER* fh, BITMAP_INFO_HEADER* info);

int grayscale(char *filename, BITMAP_FILE_HEADER *fh, BITMAP_INFO_HEADER *info,
		RGB **image);
/**
 * @brief This class is for the nineth issue of the program.
 *Sharpens the images.
 */
int sharpen(char *filename, BITMAP_FILE_HEADER *fh, BITMAP_INFO_HEADER *info,
		RGB **image);


#endif
