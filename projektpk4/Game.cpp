#include "Game.h"
#include <optional>
#include "Platform.h"


Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Super Mario Bros - OOP"),
    /*
    * tutaj w konstruktorze game przy okazji konstruujemy przyciski podaj¹c kolejno:
    * pozycje X przycisku; pozycje Y przycisku; pozycje X napisu; pozycje Y napisu
    */
    resume_button(300.f, 100.f, 370.f, 105.f, font, "WZNÓW"),
    play_button(300.f, 100.f, 375.f, 105.f, font, "GRAJ"),
    table_button(300.f, 150.f, 305.f, 155.f, font, "TABELA WYNIKOW"),
    settings_button(300.f, 200.f, 340.f, 205.f, font, "USTAWIENIA"),
    exit_button(300.f, 250.f, 360.f, 255.f, font, "WYJSCIE"),
    pause_button(20.f, 20.f, 90.f, 25.f, font, "PAUZA"),
    menu_button(300.f, 200.f, 375.f, 205.f, font, "MENU"),

    ground(0.f, 500.f, 500.f, 100.f), // Dodajemy platformê
    ground2(600.f, 500.f, 400.f, 100.f),
    ground3(1100.f, 500.f, 1000.f, 100.f),
    ground4(2200.f, 500.f, 800.f, 100.f),
    //ground5(0.f, 500.f, 1000.f, 100.f),
    //ground6(0.f, 500.f, 1200.f, 100.f)

	platform(400.f, 300.f, 300.f, 50.f)
{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;
    previousState = GameState::Menu;

    camera.setSize({ 800.f, 600.f });
    camera.setCenter({ 400.f, 300.f });

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

                if (currentState == GameState::GameOver) {
                    if (menu_button.isClicked(window)) currentState = GameState::Menu;
                    if (exit_button.isClicked(window)) window.close();
                }
            }
        }

        
    }
}

void Game::update()
{
    //w ponizszych if-ach aktualizujemy pozycje np gracza lub innych obiektow ktore sie szybko zmieniaja
    if (currentState == GameState::Playing) {
        mario.update();

        // Jeœli pozycja X gracza jest wiêksza ni¿ œrodek kamery, przesuñ kamerê
        if (mario.getX() > camera.getCenter().x) {
            camera.setCenter({ mario.getX(), 300.f });
        }

        // BLOKADA COFANIA (Lewa krawêdŸ ekranu)
        float leftEdge = camera.getCenter().x - 400.f;

        if (mario.getX() < leftEdge) {
            mario.setX(leftEdge); // Wypychamy Mario z powrotem na lew¹ krawêdŸ
        }

        // Sprawdzamy kolizjê gracza z platform¹ 
       /* std::optional<sf::FloatRect> intersection = mario.getBounds().findIntersection(ground.getBounds());
        std::optional<sf::FloatRect> intersection2 = mario.getBounds().findIntersection(ground2.getBounds());
        std::optional<sf::FloatRect> intersection3 = mario.getBounds().findIntersection(ground3.getBounds());
        std::optional<sf::FloatRect> intersection4 = mario.getBounds().findIntersection(ground4.getBounds());

        // Jeœli jest kolizja (has_value() zwraca true)
        if (intersection.has_value()) {
            // Wypychamy gracza na wierzch platformy (pozycja Y platformy)
            mario.stopFalling(ground.getBounds().position.y);
        }

        // Jeœli jest kolizja (has_value() zwraca true)
        if (intersection2.has_value()) {
            // Wypychamy gracza na wierzch platformy (pozycja Y platformy)
            mario.stopFalling(ground2.getBounds().position.y);
        }

        if (intersection3.has_value()) {
            // Wypychamy gracza na wierzch platformy (pozycja Y platformy)
            mario.stopFalling(ground3.getBounds().position.y);
        }

        if (intersection4.has_value()) {
            // Wypychamy gracza na wierzch platformy (pozycja Y platformy)
            mario.stopFalling(ground4.getBounds().position.y);
        }*/


        // poprawione platformy zeby nie przyci¹ga³y przy upadku
        ground.resolveCollision(mario);
        ground2.resolveCollision(mario);
        ground3.resolveCollision(mario);
        ground4.resolveCollision(mario);

        platform.resolveCollision(mario);


        //Jeœli mario poza ekranem to koniec gry
        if (mario.getY()>600.f) {
            currentState = GameState::GameOver;
        }
    }
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
        exit_button.draw(window);
    }
    else if (currentState == GameState::Playing)
    {
        window.clear(sf::Color::Black);
        window.setView(camera);
        mario.draw(window);

        ground.draw(window);
        ground2.draw(window);
        ground3.draw(window);
        ground4.draw(window);

        platform.draw(window);

        window.setView(window.getDefaultView());
        pause_button.draw(window);
    }
    else if (currentState == GameState::Pause)
    {
        window.clear(sf::Color::Blue);
        resume_button.draw(window);
        table_button.draw(window);
        settings_button.draw(window);
        exit_button.draw(window);
    }
    else if (currentState == GameState::GameOver) {
        window.clear(sf::Color::Black);
        menu_button.draw(window);
        exit_button.draw(window);
    }


    window.display();
}


void Game::resetGame() {
    mario.reset();
    camera.setCenter({ 400.f, 300.f });
    ground.resetPlatform();
    ground2.resetPlatform();
    ground3.resetPlatform();
    ground4.resetPlatform();

    platform.resetPlatform();
}