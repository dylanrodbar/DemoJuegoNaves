//Demo para explicar la librería allegro
//Estudiante: Dylan Rodríguez Barboza

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <conio.h>

#include "Asteroide.h"
#include "Bala.h"
#include "Nave.h"

#include <allegro5/allegro.h>

#include <allegro5/allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

#define numeroAsteroides 4
#define numeroBalas 4
//************************Globales************************

Asteroide *asteroides[numeroAsteroides];
Bala *balas[numeroBalas];
Nave *naveJuego;


int numeroBalasActuales = 0;

bool ciclo = true;
//******************************************

//Allegro
const ALLEGRO_COLOR transparente = al_map_rgb(0, 0, 0);
ALLEGRO_SAMPLE *musicaJuego = NULL;
ALLEGRO_SAMPLE *explosion = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *buffer = NULL;
ALLEGRO_BITMAP *asteroideBuffer = NULL;
ALLEGRO_BITMAP *marcoVerticalBuffer = NULL;
ALLEGRO_BITMAP *marcoHorizontalBuffer = NULL;
ALLEGRO_BITMAP *balaBuffer = NULL;
ALLEGRO_BITMAP *naveBuffer = NULL;
ALLEGRO_BITMAP *corazonBuffer = NULL;
ALLEGRO_BITMAP *asteroide = NULL;
ALLEGRO_BITMAP *bala = NULL;
ALLEGRO_BITMAP *nave = NULL;
ALLEGRO_BITMAP *explosionNave = NULL;
ALLEGRO_BITMAP *corazon = NULL;
ALLEGRO_BITMAP *marcoVertical = NULL;
ALLEGRO_BITMAP *marcoHorizontal = NULL;
ALLEGRO_BITMAP *marcoHorizontal1 = NULL;
ALLEGRO_BITMAP *marcoHorizontal2 = NULL;
ALLEGRO_BITMAP *marcoHorizontal3 = NULL;
ALLEGRO_BITMAP *marco = NULL;
//****************************************


//Funciones encargadas de actualizar la interfaz

//Pantalla: función que se encarga de actualizar la pantalla 
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void pantalla(){

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(buffer, 0, 0, 0);
	al_flip_display();  //Necesario para que actualice la interfaz gráfica en la pantalla
	al_clear_to_color(transparente); //Limpia la pantalla
}


//pintarElemento: función que pinta en la pantalla una nave, asteroide o bala
//Entradas: tipo (nave, asteroide o bala), eje x y eje y del elemento
//Salidas: ninguna
//Restricciones: ninguna
void pintarElemento(int tipo, int _x, int _y){

	if (tipo == 1){
		al_set_target_bitmap(naveBuffer);
		al_clear_to_color(transparente);
		al_draw_bitmap_region(nave, 0, 0, 30, 30, 0, 0, 0);
		al_set_target_bitmap(buffer);
		al_draw_bitmap(naveBuffer, _x, _y, 0);

	}

	else if (tipo == 2){
		//cout << "Entro al 2" << endl;
		al_set_target_bitmap(asteroideBuffer);
		al_clear_to_color(transparente);
		al_draw_bitmap_region(asteroide, 0, 0, 30, 30, 0, 0, 0);
		al_set_target_bitmap(buffer);
		al_draw_bitmap(asteroideBuffer, _x, _y, 0);

	}

	else if (tipo == 3){
		
		al_set_target_bitmap(balaBuffer);
		al_clear_to_color(transparente);
		al_draw_bitmap_region(bala, 0, 0, 30, 30, 0, 0, 0);
		al_set_target_bitmap(buffer);
		al_draw_bitmap(balaBuffer, _x, _y, 0);

	}
}

//pintarCorazonesNave: función que pinta en la interfaz gráfica los corazones correspondientes a la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void pintarCorazonesNave(){
	int ejeX = 30;
	for (int i = 0; i < naveJuego->corazones; i++){
		al_set_target_bitmap(corazonBuffer);
		al_clear_to_color(transparente);
		al_draw_bitmap_region(corazon, 0, 0, 30, 30, 0, 0, 0);
		al_set_target_bitmap(buffer);
		al_draw_bitmap(corazonBuffer, 180 + i * 30, 0, 0);
	}
}

//asignarMarco: se asigna un marco que tiene pintado el número de vidas, de acuerdo a las vidas de la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void asignarMarco(){
	if (naveJuego->vidas == 1){
		marco = marcoHorizontal1;
	}

	else if (naveJuego->vidas == 2){
		marco = marcoHorizontal2;
	}

	else if (naveJuego->vidas == 3){
		marco = marcoHorizontal3;
	}
}

//pintarBordes: función que pinta los bordes verticales y horizontales del jueg
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void pintarBordes(){
	asignarMarco();
	al_set_target_bitmap(marcoVerticalBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(marcoVertical, 0, 0, 30, 500, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(marcoVerticalBuffer, 0, 0, 0);

	al_set_target_bitmap(marcoVerticalBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(marcoVertical, 0, 0, 30, 500, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(marcoVerticalBuffer, 470, 0, 0);

	al_set_target_bitmap(marcoHorizontalBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(marco, 0, 0, 500, 30, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(marcoHorizontalBuffer, 0, 0, 0);

	al_set_target_bitmap(marcoHorizontalBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(marcoHorizontal, 0, 0, 500, 30, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(marcoHorizontalBuffer, 0, 470, 0);


}

//reproducitExplosion: función que se encarga de reproducir el sonido correspondiente a la explosión de la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones
void reproducirExplosion(){

	ALLEGRO_SAMPLE_INSTANCE *instancia1 = al_create_sample_instance(explosion);
	al_set_sample_instance_playmode(instancia1, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(instancia1, al_get_default_mixer());
	al_play_sample_instance(instancia1);


}

//animacionExplosion: función que recorrerá la imagen de explosión de la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void animacionExplosion(){

	al_set_target_bitmap(naveBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(nave, 0, 0, 30, 30, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(naveBuffer, naveJuego->x, naveJuego->y, 0);


	pantalla();


	al_set_target_bitmap(naveBuffer);
	al_clear_to_color(transparente);
	al_draw_bitmap_region(explosionNave, 0, 0, 30, 30, 0, 0, 0);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(naveBuffer, naveJuego->x, naveJuego->y, 0);

	al_rest(0.2);
}

//****************************************************************


//Funciones para la nave

//restarCorazonNave: función que le resta un corazón a la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void restarCorazonNave(){
	
	naveJuego->corazones = naveJuego->corazones-1;
}
//restarVidasNave: función que le resta una vida a la nave
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void restarVidaNave(){
	
	naveJuego->vidas--;
}

//morirNave: función que determina si la nave ha perdido 3 corazones, en ese caso, resta una vida
//Entradas: ninguna
//Salidas: verdadero en caso de que haya perdido 3 corazones
//Restricciones: ninguna
bool morirNave(){
	if (naveJuego->corazones == 0){
		restarVidaNave();
		naveJuego->corazones = 3;
		
		return true;
	}
	return false;
}


//sinVidas: función que se encarga de determinar si la nave posee o no vidas
//Entradas: ninguna
//Salidas: verdadero en caso de que no se posean vidas
//Restricciones: ninguna
bool sinVidas(){
	if (naveJuego->vidas == 0) return true;

	else return false;
}



//**********************

//Funciones para las balas

//desactivarBala: función que se encarga de deshabilitar una bala en juego, una vez que no se necesite en la interfaz gráfica
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void desactivarBala(int numeroBala){
	balas[numeroBala]->activado = false;
	numeroBalasActuales--;
}

//activarBala: función que habilita una bala, una vez que se haya invocado
//Entradas: ninguna
//Salidas: ninguna
//Restricciones ninguna
void activarBala(int numeroBala){
	balas[numeroBala]->activado = true;
	numeroBalasActuales++;
}

//balaFuera: función que determina si una bala está fuera del rango del juego
//Entradas: ninguna
//Salidas: verdadero, en caso de que la bala esté fuera del rango
//Restricciones: ninguna
bool balaFuera(int numeroBala){
	if (balas[numeroBala]->y > 30) return false;
	else return true;
}


//balaEnJuego: determina si una bala está habilitada
//Entradas: ninguna
//Salidas: verdadero, en caso de que la bala esté habilitada
//Restricciones: ninguna
bool balaEnJuego(int numeroBala){
	if (balas[numeroBala]->activado) return true;
	else return false;
}

//cambiarEjeBala: función que se encarga de cambiar el espacio en el que estará la bala
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void cambiarEjeBala(int numeroBala){
	balas[numeroBala]->y -= 30;
}

//crearBala: función que se encarga de crear una bala para el juego
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void crearBala(int _x, int _y){

	if (numeroBalasActuales <= numeroBalas){
		for (int i = 0; i < numeroBalas; i++){
			if (!balaEnJuego(i)){
				balas[i]->x = _x;
				balas[i]->y = _y;
				activarBala(i);
				break;
			}
		}
	}
}

//moverBala: función que se encarga de asignar un nuevo espacio a la bala
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void moverBala(){

	for (int i = 0; i < numeroBalas; i++){
		if (balaEnJuego(i)){
			if (!balaFuera(i)){
				pintarElemento(3, balas[i]->x, balas[i]->y);
				cambiarEjeBala(i);
			}
			else{
				desactivarBala(i);
			}
		}
	}
}

//****************************

//Funciones para los asteroides

//asteroideFuera: función que determina si un asteroide está fuera del espacio del juego
//Entradas: ninguna
//Salidas: verdadero, en caso de que el asteroide esté fuera del espacio
//Restricciones: ninguna
bool asteroideFuera(int numeroAsteroide){
	if (asteroides[numeroAsteroide]->y == 450) return true;
	else return false;
}

//asignarEjesAleatoriosAsteroide: función que asigna un nuevo espacio para los asteroides
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void asignarEjesAleatoriosAsteroide(int numeroAsteroide){
	
	int x = 1 + rand()%(16-1);
	int y = rand() % 5;
	asteroides[numeroAsteroide]->y = y * 30;
	asteroides[numeroAsteroide]->x = x * 30;
}

//cambiarEjeAsteroide: función que se encarga de mover al asteroide
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void cambiarEjeAsteroide(int numeroAsteroide){
	asteroides[numeroAsteroide]->y += 30;
}

//choqueAsteroideBala: función que determina si una bala y un asteroide comparten un espacio
//Entradas: ninguna
//Salidas: verdadero, en caso de que la bala y el asteroide se encuentren en el mismo espacio
//Restricciones: ninguna
bool choqueAsteroideBala(int numeroAsteroide, int numeroBala){
	if (asteroides[numeroAsteroide]->x == balas[numeroBala]->x && asteroides[numeroAsteroide]->y == balas[numeroBala]->y ||
		asteroides[numeroAsteroide]->x == balas[numeroBala]->x && asteroides[numeroAsteroide]->y - 30 == balas[numeroBala]->y)
		return true;

	else return false;
}

//moverAsteroide: función que cambia de lugar al asteroide
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void moverAsteroide(){
	for (int i = 0; i < numeroAsteroides; i++){
		if (asteroideFuera(i)){
			asignarEjesAleatoriosAsteroide(i);
		}
		else cambiarEjeAsteroide(i);
		
		pintarElemento(2, asteroides[i]->x, asteroides[i]->y);
	}
}

//choque: función que determina si un asteroide y la nave han chocado
//Entradas: ninguna
//Salidas: verdadero, en caso de que exista un choque
//Restricciones: ninguna
bool choque(){
	
	for (int i = 0; i < numeroAsteroides; i++){
		
		
		if ((asteroides[i]->x == naveJuego->x  && asteroides[i]->y == naveJuego->y) || (asteroides[i]->x  == naveJuego->x  && asteroides[i]->y - 30 == naveJuego->y)){
			asignarEjesAleatoriosAsteroide(i);
			
			return true;

		}
	
		
	}
	return false;
}

//colision: función encargada de verificar si una bala y un asteroide han colisionado
//Entradas: ninguna
//Salidas: ninguna
//Restriciones: ninguna
void colision(){

	for (int i = 0; i < numeroAsteroides; i++){
		for (int j = 0; j < numeroBalas; j++){
			if (balas[j]->activado){
				if (choqueAsteroideBala(i,j)){
					desactivarBala(j);
					asignarEjesAleatoriosAsteroide(i);
				}
			}
		}
	}
}

//******************************


//iniciarEstructuras: función que se encarga de iniciar los componentes del juego
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna
void iniciarEstructuras()
{

	naveJuego = new Nave(420, 450, 3, 3);
	srand(time(0));
	for (int i = 0; i < numeroAsteroides; i++){
		
		int x = rand() % 15 + 1;
		int y = rand() % 5 + 1;
		

		Asteroide *asteroide = new Asteroide(x*30, y*30);
		asteroides[i] = asteroide;

		Bala *bala = new Bala();
		balas[i] = bala;

	}
	

}
//*********************************************

int main(int argc, char **argv)
{


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(500, 500);
	al_init_image_addon(); //Necesario para que la imagen se cargue



	
	//Instalación de componentes de allegro
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);

	al_init_primitives_addon();
	al_install_keyboard();
	//********************************


	//Buffer
	buffer = al_create_bitmap(500, 500);
	asteroideBuffer = al_create_bitmap(30, 30);
	balaBuffer = al_create_bitmap(30, 30);
	naveBuffer = al_create_bitmap(30, 30);
	corazonBuffer = al_create_bitmap(30, 30);
	marcoVerticalBuffer = al_create_bitmap(30, 500);
	marcoHorizontalBuffer = al_create_bitmap(500, 30);
	corazonBuffer = al_create_bitmap(500, 30);
	//*************************************

	//Carga de imagenes
	asteroide = al_load_bitmap("Asteroide.png");
	bala = al_load_bitmap("Bala.png");
	nave = al_load_bitmap("Nave.png");
	explosionNave = al_load_bitmap("Muerte.png");
	corazon = al_load_bitmap("Corazon.png");
	marcoVertical = al_load_bitmap("BordeV.png");
	marcoHorizontal = al_load_bitmap("BordeH.png");
	marcoHorizontal1 = al_load_bitmap("BordeH1.png");
	marcoHorizontal2 = al_load_bitmap("BordeH2.png");
	marcoHorizontal3 = al_load_bitmap("BordeH3.png");
	musicaJuego = al_load_sample("Music.ogg");
	explosion = al_load_sample("Explosion.ogg");
	//******************************************

	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	ALLEGRO_TIMER *timer = al_create_timer(0.01 / 60); 
	ALLEGRO_EVENT_QUEUE *evento_cola = al_create_event_queue();
	
	al_register_event_source(evento_cola, al_get_keyboard_event_source());
	al_register_event_source(evento_cola, al_get_timer_event_source(timer));
	
	al_play_sample(musicaJuego, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	al_start_timer(timer);
	
	iniciarEstructuras();
	
	while (ciclo){

		
		ALLEGRO_EVENT eventos;
		
		al_wait_for_event(evento_cola, &eventos);
			
		if (eventos.timer.source == timer){
			al_get_keyboard_state(&estadoTeclado);

			while (!al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE)){
				
				

				al_get_keyboard_state(&estadoTeclado);
				al_set_target_bitmap(buffer); 
				al_clear_to_color(transparente); 
				pantalla();

				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_LEFT)){
					if (naveJuego->x > 30) naveJuego->x -= 30;

				}

				else if (al_key_down(&estadoTeclado, ALLEGRO_KEY_RIGHT)){
					if (naveJuego->x < 450) naveJuego->x += 30;
					
				}
					
				else if (al_key_down(&estadoTeclado, ALLEGRO_KEY_UP)){
					if (naveJuego->y > 30) naveJuego->y -= 30;
				}
					
				else if (al_key_down(&estadoTeclado, ALLEGRO_KEY_DOWN)){
					if (naveJuego->y < 450) naveJuego->y += 30;
				}
		
				else if (al_key_down(&estadoTeclado, ALLEGRO_KEY_SPACE)) crearBala(naveJuego->x, naveJuego->y);
				
				pintarBordes();
				pintarCorazonesNave();
				pintarElemento(1, naveJuego->x, naveJuego->y);
				moverAsteroide();
				
				if (choque()) restarCorazonNave();
				
				moverBala();
				colision();
				
				if (morirNave()){
					reproducirExplosion();
					animacionExplosion();
				}
				
				pantalla();
				
				if (sinVidas()) break;

				al_rest(0.1);
			
			}

			

		}


		ciclo = false;



		al_destroy_bitmap(buffer);
		al_destroy_bitmap(asteroideBuffer);
		al_destroy_bitmap(balaBuffer);
		al_destroy_bitmap(naveBuffer);
		al_destroy_bitmap(corazonBuffer);
		al_destroy_bitmap(marcoVerticalBuffer);
		al_destroy_bitmap(marcoHorizontalBuffer);
		al_destroy_bitmap(asteroide);
		al_destroy_bitmap(explosionNave);
		al_destroy_bitmap(bala);
		al_destroy_bitmap(nave);
		al_destroy_bitmap(corazon);
		al_destroy_bitmap(marcoVertical);
		al_destroy_bitmap(marcoHorizontal);
		al_destroy_bitmap(marcoHorizontal1);
		al_destroy_bitmap(marcoHorizontal2);
		al_destroy_bitmap(marcoHorizontal3);
		al_destroy_sample(musicaJuego);
		al_destroy_event_queue(evento_cola);
		al_destroy_timer(timer);





		return 0;
		
	}
	
}

