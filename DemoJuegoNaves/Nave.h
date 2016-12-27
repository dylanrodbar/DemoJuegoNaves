struct Nave{
	int x;
	int y;
	int xAnterior;
	int yAnterior;
	int corazones;
	int vidas;

	Nave(){

	}

	Nave(int _x, int _y, int _corazones, int _vidas){
		x = _x;
		y = _y;
		xAnterior = 0;
		yAnterior = 0;
		corazones = _corazones;
		vidas = _vidas;

	}


	int getVidas();
	void restarCorazon();
	//Las siguientes funciones podrían ir en el main debido a la librería allegro
	void pintar();
	void mover();
	void pintarCorazones();
	void morir();
	//***************************************************************************
};