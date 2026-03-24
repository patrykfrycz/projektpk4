#include "Game.h"
#include <optional>

// DOBRZE - U¿ywamy dwukropka (Listy Inicjalizacyjnej)!
Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Super Mario Bros - OOP"),
    play_button(300.f, 100.f, 375.f, 105.f, font, "GRAJ"),
    table_button(300.f, 150.f, 305.f, 155.f, font, "TABELA WYNIKOW"),
    settings_button(300.f, 200.f, 340.f, 205.f, font, "USTAWIENIA"),
    exit_button(300.f, 250.f, 360.f, 255.f, font, "WYJSCIE")
{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;


    if (!font.openFromFile("ALGER.ttf"))
    { 
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        // Zamkniêcie okna krzy¿ykiem
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        // Sprawdzamy, czy wciœniêto jakiœ klawisz (nowa sk³adnia SFML 3)
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
        {
            // Jeœli jesteœmy w GRZE i wciœniemy ESCAPE -> Ekran Pauzy
            if (currentState == GameState::Playing && keyEvent->code == sf::Keyboard::Key::Escape)
            {
                currentState = GameState::Pause;
            }
            // Jeœli jesteœmy w EKRANIE PAUZY i wciœniemy SPACJE -> Wracamy do Gry
            else if (currentState == GameState::Pause && keyEvent->code == sf::Keyboard::Key::Space)
            {
                currentState = GameState::Playing;
            }

            // Jeœli jesteœmy w EKRANIE PUAZY i wciœniemy Esc -> Wracamy do Menu
            else if (currentState == GameState::Pause && keyEvent->code == sf::Keyboard::Key::Escape)
            {
                currentState = GameState::Menu;
            }
        }
    }
}

void Game::update()
{
    if (currentState == GameState::Playing)
    {
        mario.update(); //Aktualizujemy fizyke mario tylko podczas ekranu gry
    }

    if (currentState == GameState::Menu)
    {
        // Tu gra na ¿ywo, 60 razy na sekundê, sprawdza czy najecha³eœ 
        // na prostok¹t i wcisn¹³eœ lewy przycisk myszy.
        if (play_button.isClicked(window))
        {
            currentState = GameState::Playing; // Odpalamy grê
        }

        if (exit_button.isClicked(window))
        {
            window.close(); // zamykamy grê
        }

        
    }
}

void Game::render()
{
    // Zmieniamy kolor t³a w zale¿noœci od stanu, ¿eby wizualnie udowodniæ dzia³anie
    if (currentState == GameState::Menu)
    {
        window.clear(sf::Color::Black); 
        play_button.draw(window);
        table_button.draw(window);
        settings_button.draw(window);
        exit_button.draw(window);
    }
    else if (currentState == GameState::Playing)
    {
        window.clear(sf::Color::Blue);  
        mario.draw(window);
    }
    else if (currentState == GameState::Pause)
    {
        window.clear(sf::Color::Red);   
    }

    window.display();
}