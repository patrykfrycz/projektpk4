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
#include "Flag.h"
#include "Mushroom.h"
#include <algorithm>

enum class GameState {
	Menu,
	Playing,
	GameOver,
	Pause,
	Settings,
	Win
};

class Game {
private:
	sf::RenderWindow window; 
	GameState currentState; 
	GameState previousState;

	sf::Texture flagTex;
	Flag endFlag;

	sf::Texture winTex;
	std::optional<sf::Sprite> gamewin;

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

	std::vector<Platform> platforms; 
	std::vector<Platform> grounds;
	std::vector<Platform> pipes;

	sf::Texture blockTex; 
	sf::Texture blockUsedTex;   
	std::vector<std::unique_ptr<MysteryBlock>> blocks;

	sf::Texture starTex;
	sf::Texture mushroomTex;

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

	void spawnGround(float x, float y, float w, float h);
	void spawnPlatform(float x, float y, float w, float h);
	void spawnPipe(float x, float y, float w, float h);

	void spawnCoins();

	void spawnMysteryBlock(float x, float y, ItemType content);

	void spawnEnemies();
};