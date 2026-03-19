#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"

enum class GameState {
	Menu,
	Playing,
	GameOver,
	Pause
};

class Game {
private:
	sf::RenderWindow window; // Obiekt reprezentuj¹cy prawdziwe okienko Windowsa
	GameState currentState; // Zmienna przechowuj¹ca informacjê, na którym ekranie aktualnie jesteœmy

	Player mario; //tworzymy obiekt Mario

	Button play_button; //tworzymy obiekt przycisku graj w menu

	void processEvents(); // Odpowiada za sprawdzanie klawiatury (Spacja, Esc) i zamykanie okna
	void update(); // Tutaj liczy siê matematyka i fizyka
	void render(); // Tutaj wyœwietlamy kolory i rysunki na ekranie

public:
	Game(); // KONSTRUKTOR. S³u¿y do ustawienia ustawieñ pocz¹tkowych (rozmiaru okna, tytu³u).
	void run(); // Wrzucamy do niej g³ówn¹ pêtlê "while(window.isOpen())",
};