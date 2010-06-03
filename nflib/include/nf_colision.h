#ifndef __NF_COLISION_H__
#define __NF_COLISION_H__

#ifdef __cplusplus
extern "C" {
#endif





	// NightFox LIB - Include de Colisiones
	// Requiere DevkitARM R28
	// Codigo por NightFox
	// http://blogs.gamefilia.com/knightfox
	// Version 20100301





	// Includes devKitPro
	#include <nds.h>





	// Define los slots maximos para los mapas de colisiones
	#define NF_SLOTS_CMAP 32

	// Define la estructura de control de mapas de colisiones
	typedef struct {
		char* buffer;	// Buffer para almacenar el mapa de colisiones
		u32 size;		// Tamaño de archivo
		u16 width;		// Ancho del mapa (en pixeles)
		u16 height;		// Alto del mapa (en pixeles)
		bool inuse;		// Esta en uso el slot?
	} NF_TYPE_CMAP_INFO;
	extern NF_TYPE_CMAP_INFO NF_CMAP[NF_SLOTS_CMAP];		// Datos de los mapas de colision




	// Funcion NF_InitCmapBuffers();
	void NF_InitCmapBuffers(void);
	// Inicializa los buffers que almacenaran los mapas de colision
	// Debes usar esta funcion una unica vez antes de cargar ningun mapa de colision



	// Funcion NF_ResetCmapBuffers();
	void NF_ResetCmapBuffers(void);
	// Reinicia los buffers y variables de los mapas de colisiones.



	// Funcion NF_LoadColisionMap();
	void NF_LoadColisionMap(const char* file, u8 id, u16 width, u16 height);
	// Carga un mapa de colisiones en el slot indicado.



	// Funcion NF_UnloadColisionMap();
	void NF_UnloadColisionMap(u8 id);
	// Borra de la RAM el mapa de colisiones con el nº de slot indicado.



	// Funcion NF_GetTile();
	extern u8 NF_GetTile(u8 slot, u16 x, u16 y);
	// Devuelve el numero de tile de la posicion especificada.



	// Funcion NF_SetTile();
	void NF_SetTile(u8 slot, u16 x, u16 y, u8 value);
	// Cambia el valor del tile en la posicion especificada.





#ifdef __cplusplus
}
#endif


#endif