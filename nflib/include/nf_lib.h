#ifndef __NF_LIB_H__
#define __NF_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif




	// NightFox LIB - Include General
	// Requiere DevkitARM R28
	// Codigo por NightFox
	// http://blogs.gamefilia.com/knightfox
	// Version 20100301



	/*

	Notas sobre BITSHIFT

	(n >> x)	Divide			n / x
	(n << x)	Multiplica		n * x

	Valores de X
	2	  =	1
	4	  =	2
	8	  =	3
	16	  =	4
	32	  =	5
	64	  =	6
	128	  =	7
	256	  =	8
	512	  =	9
	1024  =	10
	2048  =	11
	4096  =	12
	8192  =	13
	16384 =	14
	32768 =	15
	65536 =	16

	Dado que la DS no tiene unidad de coma flotante, siempre que dividas o
	multipliques por numeros de base 2, usa el bitshift
	Por ejemplo:
	a = (512 / 8);
	seria equivalente a
	a = (512 >> 3);
	Multiplicando
	b = (3 * 2048);
	seria con bitshift
	b = (3 << 11);

	*/




	
	// Libreria de funciones basicas y comunes
	#include "nf_basic.h"

	// Libreria de funciones 2D comunes
	#include "nf_2d.h"

	// Libreria de fondos con Tiles
	#include "nf_tiledbg.h"

	// Libreria de fondos en modo Bitmap
	#include "nf_bitmapbg.h"

	// Libreria de sprites de 256 colores
	#include "nf_sprite256.h"

	// Libreria de textos
	#include "nf_text.h"

	// Libreria de textos de 16 pixeles
	#include "nf_text16.h"

	// Libreria de colisiones
	#include "nf_colision.h"

	// Libreria de sonido
	#include "nf_sound.h"

	// Libreria de archivos multimedia
	#include "nf_media.h"





#ifdef __cplusplus
}
#endif


#endif
