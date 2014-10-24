#include "djgraphics.h"

unsigned int LoadBMPTexture(const char* filepath) 
{
		unsigned char header[54];	// BMP Headers are 54 bytes
		unsigned int dataPos; 		// Actual Data Position
		unsigned int width, height;
		unsigned int imageSize;		// width * height * 3 (1 Byte / RGB / Pixel)
		
		// Actual Data
		unsigned char *data;
		
		FILE *file = fopen(filepath, "rb");
		if(!file) {
			printf("Error opening file %s", filepath);
			return 0;
		}
		
		if(fread(header, 1, 54, file) != 54) // Ensure its a bmp
		{
			printf("Not a bmp header %s", filepath);
			return 0;
		}
		
		if(header[0] != 'B' || header[1] != 'M') 
		{
			printf("Not a bmp file %s", filepath);
			return 0;
		}
		
		dataPos = 	*(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = 	*(int*)&(header[0x12]);
		height = 	*(int*)&(header[0x16]);
		
		imageSize = width * height * 3;
		if(dataPos==0) dataPos = 54;
		
		printf("Image Width: %d Height: %d Size: %d\n", width, height, imageSize);
		
		data = (unsigned char *)malloc(imageSize);
		
		fread(data, 1, imageSize, file);
		fclose(file);
		
		unsigned int textureID;
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
		free(data);
		return textureID;		
}
