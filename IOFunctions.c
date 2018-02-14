#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "IOFunctions.h"

float rmin(float l, float r) {
	if (l <= r)
		return l;
	return r;
}

/* Updates the contents of a buffer by copying the bufpos residu to the beginning, and adding the rest from file */
int update_xml_buffer(char* buffer, char* bufpos, FILE* file_handle, int buffersize)
{
	int residu, read;

	residu = strlen(bufpos);
	if (residu < 0 || feof(file_handle))
		return 0;

	memmove(buffer, bufpos, residu);
	read = fread(buffer+residu, sizeof(char), buffersize-(residu+1), file_handle);
	buffer[residu+read+1] = '\0';
	bufpos = buffer;

	return read;

}

/* Copies data from the input file to the output file */
void copy_input_output(char* buffer, int buf_len, FILE* inputf, FILE* outputf, int copy_len)
{
	int copies, i, read_chars, toberead;

	copies = (copy_len / (buf_len-1)) + 1;
	for (i=0; i<copies; i++) {
		toberead = rmin(copy_len, buf_len-1);
		read_chars = fread(buffer, sizeof(char), toberead+1, inputf);
		buffer[read_chars] = '\0';
		fprintf(outputf, "%s", buffer);
		copy_len -= toberead;
	}// for

}


