struct Bala{
	int x;
	int y;
	bool activado;

	Bala(){
		x = 0;
		y = 0;
		activado = false;
	}

	Bala(int _x, int _y){
		x = _x;
		y = _y;
		activado = true;

	}


	
	//Las siguientes funciones podr�an ir en el main debido a la librer�a allegro
	void mover();
	void fuera();
	//***************************************************************************
};
