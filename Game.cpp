#include "Game.h"

Game::Game(int ancho, int alto, string nombre) {
	ventana = new RenderWindow(VideoMode(ancho, alto), nombre);
	ventana->setFramerateLimit(60);
	ventana->setMouseCursorVisible(false);
	srand(time(NULL));

	tx_fondo = new Texture;
	tx_fondo->loadFromFile("fondo.png");
	sp_fondo = new Sprite;
	sp_fondo->setTexture(*tx_fondo);
	fuente.loadFromFile("font1.ttf");
	texto_uno.setFont(fuente);
	string_uno = "Puntaje ";
	texto_uno.setString(string_uno);

	reloj = new Clock;
	tiempo = new Time;

	mira = new Player();

	plato = new CircleShape;
	plato->setRadius(40);
	plato->setFillColor(Color::Red);
	pos_inicial.x = 50;
	pos_inicial.y = 550;
	plato->setPosition(pos_inicial);


	vel_caida = 9.0;
	vel_x = 3.0;
	vel_y = 3.0;
	aceleracion = 9.8;


	texto_uno.setFont(fuente);
	texto_dos.setFont(fuente);
	texto_tres.setFont(fuente);
	texto_gameOver.setFont(fuente);

	color_rectangulo = Color(50, 120, 20, 150);
	color_menu = Color(50, 150, 30, 200);
	rect_jugar = new RectangleShape(Vector2f(100, 40));
	rect_jugar->setPosition(250, 300);
	rect_salir = new RectangleShape(Vector2f(100, 40));
	rect_salir->setPosition(650, 300);
	rect_menu = new RectangleShape(Vector2f(780, 300));

	puntaje = 10;
	puntaje_pausa = puntaje;
	opcion = 2;

	actualizar();

}

Game::Game() {

}

Game::~Game() {
	delete ventana;
	delete evento;
	delete reloj;
	delete tiempo;
	delete sp_fondo;
	delete tx_fondo;
	delete rect_jugar;
	delete rect_salir;
	delete plato;
	delete tiempo;
	delete reloj;
	delete mira;

}


void Game::actualizar() {
	while (ventana->isOpen()) {
		procesar_eventos();
		*tiempo = reloj->getElapsedTime();

		plato->move(vel_x, (-1) * vel_y + (aceleracion * tiempo->asSeconds()));

		switch (opcion) {
		case 0://SALIR
			ventana->close();
			break;
		case 1://JUGAR
			if (plato->getPosition().x >= 800 or plato->getPosition().y <= 0.0) {
				if (plato->getFillColor() == Color::Red) {
					puntaje = puntaje - 5;
				}
				reloj->restart();
				pos_inicial.x = 50;
				pos_inicial.y = 550;
				plato->setPosition(pos_inicial);
				plato->setFillColor(Color::Red);
				vel_x = rand() % 12;
				vel_y = 9 + rand() % 5;
				cout << "vel X " << vel_x << endl;
				cout << "vel Y " << vel_y << endl;
			}
			if (plato->getPosition().x <= 0 or plato->getPosition().y >= 600) {
				if (plato->getFillColor() == Color::Red) {
					puntaje = puntaje - 5;
				}
				reloj->restart();
				pos_inicial.x = 50;
				pos_inicial.y = 530;
				plato->setPosition(pos_inicial);
				plato->setFillColor(Color::Red);
				vel_x = rand() % 12;
				vel_y = 9 + rand() % 5;
				cout << "vel X " << vel_x << endl;
				cout << "vel Y " << vel_y << endl;
			}

			string_dos = "Puntaje " + to_string(static_cast<int>(puntaje));
			texto_dos.setString(string_dos);

			string_uno = " ";
			texto_uno.setString(string_uno);
			texto_uno.setScale(1.f, 1.f);
			if (puntaje <= 0) {//consulta si tiene vidas para saber si perdio
				opcion = 2;
				puntaje = 10;


				string_gameOver = "GAME OVER";
				texto_gameOver.setString(string_gameOver);
				texto_gameOver.setPosition(150, 310);
				texto_gameOver.setScale(2.2f, 2.2f);
				texto_gameOver.setColor(Color::Blue);

			}
			procesar_eventos();
			dibujar();
			break;
		case 2://PAUSA
			string_uno = "Dispara a los objetos para ganar puntos, si no logras hacerlo perderas 5 puntos.\n Si llegas a cero puntos pierdes.";
			texto_uno.setString(string_uno);
			texto_uno.setFillColor(Color::Black);
			texto_uno.setPosition(10, 10);
			texto_uno.setCharacterSize(20);

			rect_jugar->setPosition(170, 500);
			rect_jugar->setFillColor(color_rectangulo);
			rect_jugar->setOutlineColor(Color::Black);
			rect_jugar->setOutlineThickness(3);

			rect_salir->setPosition(500, 500);
			rect_salir->setFillColor(color_rectangulo);
			rect_salir->setOutlineColor(Color::Black);
			rect_salir->setOutlineThickness(3);

			rect_menu->setPosition(10, 10);
			rect_menu->setFillColor(color_menu);
			rect_menu->setOutlineColor(Color::Black);
			rect_menu->setOutlineThickness(3.0);

			string_tres = "Jugar";
			texto_tres.setString(string_tres);
			texto_tres.setPosition(170, 500);
			string_dos = "Salir";
			texto_dos.setString(string_dos);
			texto_dos.setPosition(500, 500);

			reloj->restart();
			procesar_eventos();
			dibujar();
			break;
		}
	}
	dibujar();
}

void Game::procesar_eventos() {
	while (ventana->pollEvent(*evento)) {
		pos_mouse.x = Mouse::getPosition(*ventana).x;
		pos_mouse.y = Mouse::getPosition(*ventana).y;

		mira->set_position(pos_mouse);

		floatrect_jugar = rect_jugar->getGlobalBounds();
		floatrect_salir = rect_salir->getGlobalBounds();
		floatrect_plato = plato->getGlobalBounds();

		if (evento->type == Event::Closed) {
			ventana->close();
		}
		if (evento->type == Event::MouseButtonPressed) {
			if (evento->key.code == Mouse::Left) {
				cout << "pos_mouse.x " << pos_mouse.x << endl;
				cout << "pos_mouse.y " << pos_mouse.y << endl;
				if (floatrect_jugar.contains(pos_mouse.x, pos_mouse.y)) {//elige jugar
					puntaje = puntaje_pausa;
					texto_dos.setCharacterSize(25);
					texto_dos.setFillColor(Color::Black);
					texto_dos.setPosition(175, 10);
					rect_jugar->setPosition(10, 10);
					string_dos = "Puntaje " + to_string(puntaje);
					texto_dos.setString(string_dos);
					texto_dos.setCharacterSize(20);
					string_tres = " ";
					texto_tres.setString(string_tres);
					texto_tres.setCharacterSize(20);
					texto_tres.setScale(1.f, 1.f);
					texto_tres.setFillColor(Color::Black);
					texto_tres.setPosition(10, 10);

					rect_salir->setPosition(405, 10);
					texto_uno.setPosition(400, 10);
					texto_uno.setCharacterSize(20);
					texto_uno.setFillColor(Color::Black);

					opcion = 1;
					cout << "jugar" << endl;

				}
				if (floatrect_salir.contains(pos_mouse.x, pos_mouse.y)) {
					cout << "salir" << endl;
					opcion = 0;
					ventana->close();
				}
				if (floatrect_plato.contains(pos_mouse.x, pos_mouse.y)) {
					puntaje++;
					plato->setFillColor(Color::Green);
				}
			}
		}
		if (evento->type == Event::KeyPressed) {
			if (evento->key.code == Keyboard::Escape) {
				cout << "pausa" << endl;
				opcion = 2;
				puntaje_pausa = puntaje;
			}
		}
	}
}

void Game::dibujar() {
	ventana->clear(Color::Yellow);
	ventana->draw(*sp_fondo);
	if (opcion == 1) {//solo se dibuja si esta jugando
		ventana->draw(*plato);
	}
	if (opcion == 2) {//solo se dibuja si esta eligiendo una opcion
		ventana->draw(*rect_jugar);
		ventana->draw(*rect_salir);
		ventana->draw(*rect_menu);
		ventana->draw(texto_gameOver);

	}
	ventana->draw(texto_uno);
	ventana->draw(texto_dos);
	ventana->draw(texto_tres);
	ventana->draw(mira->get_sprite());
	ventana->display();
}

