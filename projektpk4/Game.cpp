#include "Game.h"
#include <optional>

int button_size_x = 400;
int button_size_y = 110;
int but_size_x = button_size_x / 2;
int but_size_y = button_size_y / 2;

Game::Game()
    : window(sf::VideoMode({ 1200, 800 }), "Super Mario Bros - OOP"),
    world(window.getSize()),
    backgroundTex("tlo.png"),
	backgroundSprite(backgroundTex),
    /*
    * tutaj w konstruktorze game przy okazji konstruujemy przyciski podaj¹c kolejno:
    * pozycje X przycisku; pozycje Y przycisku; pozycje X napisu; pozycje Y napisu
    */
    resume_button(300.f,100.f, 370.f, 105.f, font, "WZNÓW"),
    play_button(300.f, 100.f, 375.f, 105.f, font, "GRAJ"),
    table_button(300.f, 150.f, 305.f, 155.f, font, "TABELA WYNIKOW"),
    settings_button(300.f, 200.f, 340.f, 205.f, font, "USTAWIENIA"),
    exit_button(300.f, 250.f, 360.f, 255.f, font, "WYJSCIE"),
    pause_button(20.f, 20.f, 90.f, 25.f, font, "PAUZA")
    
{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;
    previousState = GameState::Menu;


    if (!font.openFromFile("ALGER.ttf"))
    {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }

    if (!backgroundTex.loadFromFile("tlo.png")) {

        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli 
    }

    backgroundSprite.setTexture(backgroundTex); // dopasowanie do okna
    backgroundSprite.setScale(sf::Vector2f(
        2.f * static_cast<float>(window.getSize().x) / backgroundTex.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTex.getSize().y
    ));

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
        //w ponizszych if-ach okreslamy co ma sie stac gdy nacisniemy dany przycisk

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

        if (const auto* mouseEvents = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseEvents->button == sf::Mouse::Button::Left)
            {
                if (currentState == GameState::Menu)
                {
                    if (play_button.isClicked(window)) {
                        resetGame();
                        currentState = GameState::Playing;
                    }
                    if (exit_button.isClicked(window)) window.close();
                    if (settings_button.isClicked(window)) 
                    {                     
                        previousState = currentState;
                        currentState = GameState::Settings;
                    }
                }

                if (currentState == GameState::Pause) {
                    if (resume_button.isClicked(window)) currentState = GameState::Playing;
                    if (exit_button.isClicked(window)) currentState = GameState::Menu;
                    if (settings_button.isClicked(window)) 
                    {
                        previousState = currentState;
                        currentState = GameState::Settings;
                    }
                }

                if (currentState == GameState::Playing) {
                    if (pause_button.isClicked(window)) currentState = GameState::Pause;
                }

                if (currentState == GameState::Settings) {
                    if (exit_button.isClicked(window)) currentState = previousState;
                }
            }
        }
    }
}

void Game::update()
{
    //w ponizszych if-ach aktualizujemy pozycje np gracza lub innych obiektow ktore sie szybko zmieniaja
    if (currentState == GameState::Playing) mario.update(); 
}

void Game::render()
{
    //w poni¿szych if-ach w zaleznosci od stanu gry ktory ma sie zaladowac
    //podajemy rzeczy ktore maja byc renderowane odrazu na poczatek zaladowanego stanu

    if (currentState == GameState::Menu)
    {
        window.clear(sf::Color::Black);
        play_button.draw(window);
        table_button.draw(window);
        settings_button.draw(window);
        exit_button.draw(window);
    }
    else if (currentState == GameState::Settings)
    {
        window.clear(sf::Color::Black);
        // proste ustawienia - tylko przycisk wyjœcia (wraca do previousState)
        exit_button.draw(window);
    }
    else if (currentState == GameState::Playing)
    {
        window.clear(sf::Color::Green);  
        mario.draw(window);
        pause_button.draw(window);
    }
    else if (currentState == GameState::Pause)
    {
        // poka¿ scenê gry + pó³przezroczyste t³o i menu pauzy
        window.clear();
        window.draw(backgroundSprite);
        for (const auto& pl : platforms) pl.draw(window);
        mario.draw(window);

        // overlay, ¿eby menu by³o czytelne
        sf::RectangleShape overlay(
            sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y))
        );
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        resume_button.draw(window);
        table_button.draw(window);
        settings_button.draw(window);
        exit_button.draw(window);
    }
    
  
    window.display();
}


void Game::resetGame() {
    mario.reset();
    camera.setCenter({ 400.f, 300.f });
    ground.resetPlatform();
}