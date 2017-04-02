#include "texture.h"

GLuint loadTexture2d(const char * path,int* height,int *width) {
	//kontorla formatu
	
	FREE_IMAGE_FORMAT form = FreeImage_GetFileType(path, 0);
	if (form == -1) {
		std::cerr << "Error:Nelze otevrit soubor textury" << std::endl;
	}
	else if(form == FIF_UNKNOWN){
		form = FreeImage_GetFIFFromFilename(path);
		if (!FreeImage_FIFSupportsReading(form)) {
			std::cerr << "Error:Nelze urcit typ souboru" << std::endl;
			return NULL;
		}
	}
	FIBITMAP* bm = FreeImage_Load(form, path,form);
	FIBITMAP* bm32;
	int qu = FreeImage_GetBPP(bm); //v tuturailu to meli kontrolu a konverzi zjistit proc
	if (qu == 32) {
		bm32 = bm;
	}
	else {
		bm32 = FreeImage_ConvertTo32Bits(bm);
	}
	int iWidth = FreeImage_GetWidth(bm32);
	int iHeight = FreeImage_GetHeight(bm32);
	GLubyte * data = FreeImage_GetBits(bm32);

	GLuint ret;
	glActiveTexture(GL_TEXTURE0);
	glCreateTextures(GL_TEXTURE_2D, 1, &ret);
	glBindTexture(GL_TEXTURE_2D, ret);
	GLuint code=GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, code, GL_UNSIGNED_BYTE, data);
	FreeImage_Unload(bm32);
	if (qu != 32) {
		FreeImage_Unload(bm);
	}
	*height = iHeight;
	*width = iWidth;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	std::cout << "nactena textura " << path << " return je " << ret << std::endl;
	return ret;

}

GLuint loadTextureCube(const char * path, GLenum side, GLuint *texture)
{
	FREE_IMAGE_FORMAT form = FreeImage_GetFileType(path, 0);
	if (form == -1) {
		std::cerr << "Error:Nelze otevrit soubor textury" << std::endl;
	}
	else if (form == FIF_UNKNOWN) {
		form = FreeImage_GetFIFFromFilename(path);
		if (!FreeImage_FIFSupportsReading(form)) {
			std::cerr << "Error:Nelze urcit typ souboru" << std::endl;
			return -1;
		}
	}
	FIBITMAP* bm = FreeImage_Load(form, path,form);
	FIBITMAP* bm32;
	int qu = FreeImage_GetBPP(bm); //v tuturailu to meli kontrolu a konverzi zjistit proc
	if (qu == 32) {
		bm32 = bm;
	}
	else {
		bm32 = FreeImage_ConvertTo32Bits(bm);
	}
	int iWidth = FreeImage_GetWidth(bm);
	int iHeight = FreeImage_GetHeight(bm);
	GLubyte * data = FreeImage_GetBits(bm32);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);
	glTexImage2D(side, 0, GL_RGB, iWidth, iHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
	FreeImage_Unload(bm32);
	if (qu != 32) {
		FreeImage_Unload(bm);
	}
	std::cout << "nactena textura " << path << " return je " << std::endl;

	return GLuint();
}

GLuint loadTexture2d(const char * path, GLuint * texture)
{
	FREE_IMAGE_FORMAT form = FreeImage_GetFileType(path, 0);
	if (form == -1) {
		std::cerr << "Error:Nelze otevrit soubor textury" << std::endl;
	}
	else if (form == FIF_UNKNOWN) {
		form = FreeImage_GetFIFFromFilename(path);
		if (!FreeImage_FIFSupportsReading(form)) {
			std::cerr << "Error:Nelze urcit typ souboru" << std::endl;
			return -1;
		}
	}
	FIBITMAP* bm = FreeImage_Load(form, path, form);
	FIBITMAP* bm32;
	int qu = FreeImage_GetBPP(bm); //v tuturailu to meli kontrolu a konverzi zjistit proc
	if (qu == 32) {
		bm32 = bm;
	}
	else {
		bm32 = FreeImage_ConvertTo32Bits(bm);
	}
	int iWidth = FreeImage_GetWidth(bm);
	int iHeight = FreeImage_GetHeight(bm);
	GLubyte * data = FreeImage_GetBits(bm32);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	FreeImage_Unload(bm32);
	if (qu != 32) {
		FreeImage_Unload(bm);
	}
	std::cout << "nactena textura " << path << " return je " << std::endl;

	return GLuint();

}
