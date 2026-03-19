#include "Game.h"
#include <optional>

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Super Mario Bros - OOP")
{
    window.setFramerateLimit(60);

    currentState = GameState::Menu;
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
            currentState = GameState::Playing; // Odpalamy grê!
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