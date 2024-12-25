#include "SFML/Graphics.hpp"
#include "Player.h"

#include "iostream"
#include "ctime"
#include "stdlib.h"

using namespace sf;
using namespace std;

class Game {

private:
	RenderWindow* ventana;
	Event* evento;
	Clock* reloj;
	Time* tiempo;
	Font fuente;
	Text texto_uno;
	Text texto_dos;
	Text texto_tres;
	Text texto_gameOver;


	String string_uno;
	String string_dos;
	String string_tres;
	String string_gameOver;

	Sprite* sp_fondo;
	Texture* tx_fondo;

	Vector2f pos_mouse;
	Vector2f pos_inicial;
	CircleShape* plato;
	Player* mira;

	float vel_caida;
	float vel_x;
	float vel_y;
	float aceleracion;
	int puntaje;
	int puntaje_pausa;
	int opcion;


	Color color_rectangulo;
	Color color_menu;
	RectangleShape* rect_jugar;
	RectangleShape* rect_salir;
	RectangleShape* rect_menu;
	FloatRect floatrect_salir;
	FloatRect floatrect_jugar;
	FloatRect floatrect_plato;



public:
	Game(int, int, string);
	Game();
	~Game();
	void dibujar();
	void actualizar();
	void procesar_eventos();


};