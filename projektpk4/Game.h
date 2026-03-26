#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"

enum class GameState {
	Menu,
	Playing,
	GameOver,
	Pause,
	Settings
};

class Game {
private:
	sf::RenderWindow window; // Obiekt reprezentuj¹cy prawdziwe okienko Windowsa
	GameState currentState; // Zmienna przechowuj¹ca informacjê, na którym ekranie aktualnie jesteœmy
	GameState previousState; // Zmienna przechowuj¹ca informacjê, na którym ekranie przebywalismy poprzednio

	Player mario; //tworzymy obiekt Mario

	sf::Font font; //czcionka do przyciskow
	Button play_button;
	Button resume_button;
	Button table_button;
	Button settings_button;
	Button exit_button;
	Button pause_button;
	

	void processEvents(); // Odpowiada za sprawdzanie klawiatury (Spacja, Esc) i zamykanie okna
	void update(); // Tutaj liczy siê matematyka i fizyka
	void render(); // Tutaj wyœwietlamy kolory i rysunki na ekranie

public:
	Game(); // KONSTRUKTOR. S³u¿y do ustawienia ustawieñ pocz¹tkowych (rozmiaru okna, tytu³u).
	void run(); // Wrzucamy do niej g³ówn¹ pêtlê "while(window.isOpen())",
};