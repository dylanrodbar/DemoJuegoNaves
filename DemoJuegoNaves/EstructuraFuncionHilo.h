#include <cstdlib>
#include "Nave.h"
#include "Asteroide.h"
#include "Bala.h"
#include <iostream>

using namespace std;
 
struct EstructuraFuncionHilo{
	int id;
	int tipo; //1: Nave, 2: Asteroide, 3: Bala
	int tiempo;
	bool activo;
	bool pausa;
	//Nave *nave;
	//Asteroide *asteroide;
	//Bala *bala;
	EstructuraFuncionHilo *siguiente;



	EstructuraFuncionHilo(){

	}

	EstructuraFuncionHilo(int _tipo){
		tipo = _tipo;
		activo = true;
		pausa = false;
	}

	/*
	//Constructor para la Nave
	EstructuraFuncionHilo(int _x, int _y, int _corazones, int _vidas, int _tipo, int _tiempo, int _id){
		nave = new Nave(_x, _y, _corazones, _vidas);
		id = _id;
		tipo = _tipo;
		tiempo = _tiempo;
		activo = true;
		pausa = false;
		siguiente = NULL;
	}

	//Constructor para los asteroides o balas 
	EstructuraFuncionHilo(int _x, int _y, int _tipo, int _tiempo, int _id){
		tipo = _tipo;
		cout << tipo << endl;
		if (tipo == 2) asteroide = new Asteroide(_x, _y); 
		
		else bala = new Bala(_x, _y);
		id = _id;
		
		tiempo = _tiempo;
		activo = true;
		pausa = false;
		siguiente = NULL;
	}*/

		
	
};