#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"
#include "Platform.h"
#include "Item.h"
#include "Coin.h"
#include "HUD.h"
#include "Enemy.h"
#include <algorithm>

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

	Player mario;
	sf::Texture marioTex;

	sf::Font font; //czcionka do przyciskow
	Button play_button;
	Button resume_button;
	Button table_button;
	Button settings_button;
	Button exit_button;
	Button pause_button;
	Button menu_button;

	std::vector<std::unique_ptr<Item>> items;
	int score = 0;

	void processEvents(); // Odpowiada za sprawdzanie klawiatury (Spacja, Esc) i zamykanie okna
	void update(); // Tutaj liczy siê matematyka i fizyka
	void render(); // Tutaj wyœwietlamy kolory i rysunki na ekranie

	void spawnItem(sf::Vector2f position);

	Platform ground; //platormy
	Platform ground2;
	Platform ground3;
	Platform ground4;
	//Platform ground5;
	//Platform ground6;

	Platform platform;
	Platform platform2;
	Platform platform3;

	HUD hud;

	sf::View camera;//poruszanie sie ekranu

	sf::Clock clock;

	std::vector<std::unique_ptr<Enemy>> enemies; // Pude³ko na naszych przeciwników
	sf::Texture enemyTexture; // Pamiêæ na grafikê wroga

public:
	Game(); // KONSTRUKTOR. S³u¿y do ustawienia ustawieñ pocz¹tkowych (rozmiaru okna, tytu³u).
	void run(); // Wrzucamy do niej g³ówn¹ pêtlê "while(window.isOpen())",

	void resetGame();

	void spawnCoins();

	void spawnEnemies();
};