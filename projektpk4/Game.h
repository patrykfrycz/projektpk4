#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"
#include "Button.h"
#include "Platform.h"
#include "Item.h"
#include "Coin.h"
#include "HUD.h"
#include "Enemy.h"
#include "MysteryBlock.h"
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
	sf::RenderWindow window; 
	GameState currentState; 
	GameState previousState;

	Player mario;
	sf::Texture marioTex;

	sf::Texture playTex;
	Button play_button;
	sf::Texture setTex;
	Button settings_button;
	Button settings_button2;
	sf::Texture tableTex;
	Button table_button;
	Button table_button2;
	sf::Texture exitTex;
	Button exit_button;
	Button exit_button2;
	Button exit_button3;
	sf::Texture pauseTex;
	Button pause_button;
	sf::Texture menubutTex;
	Button menu_button;
	sf::Texture resumeTex;
	Button resume_button;

	std::vector<std::unique_ptr<Item>> items;
	int score = 0;

	void processEvents(); // Odpowiada za sprawdzanie klawiatury (Spacja, Esc) i zamykanie okna
	void update(); // Tutaj liczy siê matematyka i fizyka
	void render(); // Tutaj wyœwietlamy kolory i rysunki na ekranie

	void spawnItem(sf::Vector2f position);

	Platform ground; 
	Platform ground2;
	Platform ground3;
	Platform ground4;
	Platform ground5;
	Platform ground6;
	Platform ground7;
	Platform ground8;
	Platform ground9;
	Platform ground10;
	Platform ground11;
	Platform ground12;

	Platform platform;
	Platform platform1;
	Platform platform2;
	Platform platform3;
	Platform platform4;
	Platform platform5;
	Platform platform6;
	Platform platform7;
	Platform platform8;
	Platform platform9;
	Platform platform10;
	Platform platform11;
	Platform platform12;
	Platform platform13;
	Platform platform14;
	Platform platform15;
	Platform platform16;
	Platform platform17;
	Platform platform18;
	Platform platform19;
	Platform platform20;

	Platform pipe1;
	Platform pipe2;
	Platform pipe3;
	Platform pipe4;
	Platform pipe5;

	sf::Texture blockTex; 
	sf::Texture blockUsedTex;   
	std::vector<std::unique_ptr<MysteryBlock>> blocks;

	sf::Texture pipeTex;
	sf::Texture platformTex;
	sf::Texture groundTex;

	sf::Texture backgroundTex;
	std::optional<sf::Sprite> background;

	sf::Texture pauzaTex;
	std::optional<sf::Sprite> pauza;

	sf::Texture overTex;
	std::optional<sf::Sprite> gameover;

	HUD hud;

	sf::View camera;//poruszanie sie ekranu

	sf::Clock clock;

	std::vector<std::unique_ptr<Enemy>> enemies; // Pude³ko na naszych przeciwników
	sf::Texture goombaTexture; // Pamiêæ na grafikê wroga
	sf::Texture troopaTexture;

	sf::Texture menuTex;
	std::optional<sf::Sprite> menu;

	

public:
	Game(); // KONSTRUKTOR. S³u¿y do ustawienia ustawieñ pocz¹tkowych (rozmiaru okna, tytu³u).
	void run(); // Wrzucamy do niej g³ówn¹ pêtlê "while(window.isOpen())",

	void resetGame();

	void spawnCoins();

	void spawnEnemies();
};