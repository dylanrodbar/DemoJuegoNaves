struct Asteroide{
	int x;
	int y;

	Asteroide(){

	}

	Asteroide(int _x, int _y){
		x = _x;
		y = _y;
	}

	

	//Las siguientes funciones podrían ir en el main debido a la librería allegro
	void pintar();
	void mover();
	void choque(struct Nave &nave);
	//***************************************************************************
};