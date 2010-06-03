#ifndef __NF_MEDIA_H__
#define __NF_MEDIA_H__

#ifdef __cplusplus
extern "C" {
#endif





	// NightFox LIB - Include de funciones de carga de archivos multimedia
	// Requiere DevkitARM R28
	// Codigo por NightFox
	// http://blogs.gamefilia.com/knightfox
	// Version 20100301



	// Includes devKitPro
	#include <nds.h>





	// Funcion NF_LoadBMP();
	void NF_LoadBMP(const char* file, u8 slot);
	// Carga un archivo BMP de 8, 16 o 24 bits en un slot de imagenes de 16 bits.
	// Debes inicializar el modo 16 bits, el backbuffer y usar la funcion NF_Draw16bitsImage();
	// para mostrarlo.





#ifdef __cplusplus
}
#endif


#endif