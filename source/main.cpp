#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>

#define c(x,y) casilla[(x)*6+(y)][2]

int main(void) {
	//-------------------------------------------------
	u8 casilla[54][3] =	{		// Para 9 columnas, 6 filas
		{24,24,0}, {24,48,0}, {24,72,0}, {24,96,0}, {24,120,0}, {24,144,0}, //posicion x     posicion y      estado
		{48,24,0}, {48,48,0}, {48,72,0}, {48,96,0}, {48,120,0}, {48,144,0}, //Estado:  0-vacio    1-rojas    2-azules
		{72,24,0}, {72,48,0}, {72,72,0}, {72,96,0}, {72,120,0}, {72,144,0}, // 0-5 6-11 12-17 18-23 24-29 30-35 36-41 42-47 48-53
		{96,24,0}, {96,48,0}, {96,72,0}, {96,96,0}, {96,120,0}, {96,144,0}, //Pantalla 0-(Arriba) 1-(Abajo)
		{120,24,0},{120,48,0},{120,72,0},{120,96,0},{120,120,0},{120,144,0},
		{144,24,0},{144,48,0},{144,72,0},{144,96,0},{144,120,0},{144,144,0},
		{168,24,0},{168,48,0},{168,72,0},{168,96,0},{168,120,0},{168,144,0},
		{192,24,0},{192,48,0},{192,72,0},{192,96,0},{192,120,0},{192,144,0},
		{216,24,0},{216,48,0},{216,72,0},{216,96,0},{216,120,0},{216,144,0}, };
	//----------------------
	int /*pulsacion,*/ turno = 0, mover_fondo = 0, fin[2] = {0,1};
	touchPosition stylus;
	//-------------------------------------------------
	NF_Set2D(0, 0);					NF_Set2D(1, 0);
	NF_SetRootFolder("NITROFS");
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);			NF_InitTiledBgSys(1);
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);			NF_InitSpriteSys(1);
	NF_InitTextSys(0);				NF_InitTextSys(1);
	NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);		NF_CreateTextLayer(0, 0, 0,	"normal");  NF_DefineTextColor(0, 0, 1, 0, 0, 0);   NF_SetTextColor(0, 0, 1);
	NF_LoadTextFont("fnt/default", "normal2", 256, 256,0);		NF_CreateTextLayer(1, 0, 0,	"normal2");
	NF_LoadTiledBg("bg/map", "tablero", 256, 256);				NF_CreateTiledBg(1, 1, "tablero");
	NF_LoadTiledBg("bg/map2", "fondo", 256, 256);				NF_CreateTiledBg(1, 2, "fondo");    NF_CreateTiledBg(0, 2, "fondo");

	NF_LoadTiledBg("bg/menu", "menu", 256, 256); NF_CreateTiledBg(0, 1, "menu");

	NF_LoadSpritePal("sprites/Ficha", 0);						NF_VramSpritePal(1, 0, 0);
	NF_LoadSpriteGfx("sprites/Ficha", 0, 16, 16);
	//-------------------------------------------------
	for(int x=0;x<=(54-1);x++){ NF_VramSpriteGfx(1, 0, x, true); NF_CreateSprite(1, x, x, 0, casilla[x][0], casilla[x][1]); NF_ShowSprite(1, x, false);}
	NF_WriteText(0,0,1,1,"4 EN LINEA             v0.1.5"); NF_WriteText(0,0,20,22,"by JuDelCo"); NF_WriteText(0,0,1,22,"RESET -> Start");
	NF_WriteText(0, 0, 1, 8, "Empieza rojo !");
	//-------------------------------------------------

	while(1) {
		scanKeys();
		mover_fondo++;
		NF_ScrollBg(1, 2, mover_fondo, 0);  NF_ScrollBg(0, 2, mover_fondo, 0);
		int newpress = keysDown(); //	int held = keysHeld();		int released = keysUp();
		touchRead(&stylus);
		if(newpress & KEY_START) { // RESETEAR EL JUEGO
            for(int r=0;r<54;r++){ casilla[r][2] = 0; NF_ShowSprite(1, r, false); }
            turno = 0; fin[0] = 0; fin[1] = 1;
            NF_WriteText(0, 0, 1, 8, "Empieza rojo !         "); NF_WriteText(0, 0, 1, 10, "                       "); NF_WriteText(0, 0, 1, 11, "                       "); NF_WriteText(0, 0, 1, 13, "                       "); }
		//------------------------------------------------
		/*//char variable[32];sprintf(variable,"%3d", a);NF_WriteText(0, 0, 28, 1, variable);
		char variable[32];	char variable2[32];
		NF_WriteText(0, 0, 1, 3, variable);		NF_WriteText(0, 0, 1, 4, variable2);
		sprintf(variable, "%3d", stylus.px);	sprintf(variable2,"%3d", stylus.py);
		if(released & KEY_TOUCH) NF_WriteText(0, 0, 1, 9, "Released!");
		if(newpress & KEY_TOUCH) {NF_WriteText(0, 0, 1, 6, variable);NF_WriteText(0, 0, 1, 7, variable2);NF_WriteText(0, 0, 1, 9, "         ");}*/
		do{
		for(int x=0;x<=(9-1);x++){ //Comprobar cada columna
			if((newpress & KEY_TOUCH) && (stylus.px >= casilla[(x*6)][0]) && (stylus.px <= (casilla[(x*6)][0] + 16))){ //Si el stylus corresponde a esa columna
				for(int y=5;y>=0;y--){ //Contador para recorrer todas las casillas de la columna
					if (casilla[(x*6+y)][2] == 0){ //Comprueba si esta vacia
						NF_ShowSprite(1, (x*6+y), true);fin[0]++;
						if (turno==0){	NF_WriteText(0, 0, 1, 8, "Le toca a amarillo"); casilla[(x*6+y)][2] = 1;	NF_SpriteFrame(1, (x*6+y), 0);	turno=1;}
						else {			NF_WriteText(0, 0, 1, 8, "Le toca a rojo    "); casilla[(x*6+y)][2] = 2;	NF_SpriteFrame(1, (x*6+y), 1);	turno=0;}
						if (fin[0] == 54) {
                            NF_WriteText(0, 0, 1, 8, "FIN DEL JUEGO!!!");fin[1]=1;
                            int puntos_1 = 0, puntos_2 = 0;
                            int temp_1 = 0, temp_2 = 0;
                            char punt_1[25], punt_2[25];
                            //------------------------------
                            for(int xf=0;xf<=(9-1);xf++)
                                { //Comprobar cada columna
                                for(int yf=5;yf>=0;yf--){
                                    if (casilla[(xf*6+yf)][2] == 1){
                                        temp_1++;
                                        temp_2=0;
                                        if(temp_1==4){temp_1=0;puntos_1++;}
                                        }
                                    if (casilla[(xf*6+yf)][2] == 2){
                                        temp_2++;
                                        temp_1=0;
                                        if(temp_2==4){temp_2=0;puntos_2++;}
                                        } } temp_1=0;temp_2=0; }
                            //------------------------------
                            for(int yf=5;yf>=0;yf--)
                                { //Comprobar cada fila
                                for(int xf=0;xf<=(9-1);xf++)
                                    {
                                    if (casilla[(xf*6+yf)][2] == 1){
                                        temp_1++;
                                        temp_2=0;
                                        if(temp_1==4){temp_1=0;puntos_1++;}
                                        }
                                    if (casilla[(xf*6+yf)][2] == 2){
                                        temp_2++;
                                        temp_1=0;
                                        if(temp_2==4){temp_2=0;puntos_2++;}
                                        } } temp_1=0;temp_2=0; }
                            //------------------------------
                            for(int yf=5;yf>=0;yf--) { //Diagonales /
                                for(int xf=0;xf<=(9-1);xf++) {
                                    if (yf >= 3 && xf <=5) {
                                        if (c(xf,yf) == 1 && c(xf+1,yf-1) == 1 && c(xf+2,yf-2) == 1 && c(xf+3,yf-3) == 1) {
                                            puntos_1++; c(xf,yf) = 3; c(xf+1,yf-1) = 3; c(xf+2,yf-2) = 3; c(xf+3,yf-3) = 3; }
                                        if (c(xf,yf) == 2 && c(xf+1,yf-1) == 2 && c(xf+2,yf-2) == 2 && c(xf+3,yf-3) == 2) {
                                            puntos_2++; c(xf,yf) = 4; c(xf+1,yf-1) = 4; c(xf+2,yf-2) = 4; c(xf+3,yf-3) = 4; }
                                        } } }
                            //------------------------------
                            for(int yf=5;yf>=0;yf--) {
                                for(int xf=0;xf<=(9-1);xf++) {
                                    if (c(xf,yf) == 3) c(xf,yf) = 1;
                                    if (c(xf,yf) == 4) c(xf,yf) = 2;
                                    } }
                            //------------------------------
                            for(int yf=5;yf>=0;yf--) { //Diagonales al otro sentido
                                for(int xf=0;xf<=(9-1);xf++) {
                                    if (yf >= 3 && xf >=3) {
                                        if (c(xf,yf) == 1 && c(xf-1,yf-1) == 1 && c(xf-2,yf-2) == 1 && c(xf-3,yf-3) == 1) {
                                            puntos_1++; c(xf,yf) = 3; c(xf-1,yf-1) = 3; c(xf-2,yf-2) = 3; c(xf-3,yf-3) = 3; }
                                        if (c(xf,yf) == 2 && c(xf-1,yf-1) == 2 && c(xf-2,yf-2) == 2 && c(xf-3,yf-3) == 2) {
                                            puntos_2++; c(xf,yf) = 4; c(xf-1,yf-1) = 4; c(xf-2,yf-2) = 4; c(xf-3,yf-3) = 4; }
                                        } } }
                            //------------------------------
                            sprintf(punt_1,"Puntos Rojo    : %d", puntos_1);
                            sprintf(punt_2,"Puntos Amarillo: %d", puntos_2);
                            NF_WriteText(0, 0, 1, 10, punt_1);
                            NF_WriteText(0, 0, 1, 11, punt_2);
                            if(puntos_1 > puntos_2){        NF_WriteText(0, 0, 1, 13, "GANADOR -> ROJO    "); }
                            else if(puntos_1 < puntos_2){   NF_WriteText(0, 0, 1, 13, "GANADOR -> AMARILLO"); }
                            else { NF_WriteText(0, 0, 1, 13, "EMPATE !!!"); } }
						break;}}}}
		} while(fin[1]!=1);
		//------------------------------------------------
		NF_UpdateTextLayers();
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		//------------------------------------------------
	}
return 0; }
