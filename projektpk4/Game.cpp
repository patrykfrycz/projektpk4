#include "Game.h"
#include <optional>
#include "Platform.h"
#include "Coin.h"
#include "HUD.h"


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

    ground(0.f, 500.f, 1500.f, 100.f),
    ground2(1600.f, 500.f, 2000.f, 100.f),
    ground3(3700.f, 500.f, 1000.f, 100.f),
    ground4(4800.f, 500.f, 1500.f, 100.f),
    ground5(6400.f, 500.f, 2000.f, 100.f),
    ground6(8500.f, 500.f, 1000.f, 100.f),
    ground7(9600.f, 500.f, 2000.f, 100.f),
    ground8(11700.f, 500.f, 2500.f, 100.f),
    ground9(14300.f, 500.f, 4000.f, 100.f),

    platform(400.f, 300.f, 300.f, 50.f),
    platform2(1000.f, 300.f, 200.f, 50.f),
    platform3(1700.f, 300.f, 450.f, 50.f),
    platform4(2500.f, 300.f, 200.f, 50.f),
    platform5(4000.f, 300.f, 300.f, 50.f),
    platform6(5300.f, 300.f, 400.f, 50.f),
    platform7(6800.f, 300.f, 450.f, 50.f),
    platform8(7300.f, 100.f, 200.f, 50.f),
    platform9(9000.f, 300.f, 300.f, 50.f),
    platform10(10500.f, 300.f, 400.f, 50.f),
    platform11(11000.f, 100.f, 200.f, 50.f),
    platform12(12000.f, 300.f, 200.f, 50.f),
    platform13(13300.f, 300.f, 400.f, 50.f),

    pipe1(1430.f, 406.f, 70.f, 94.f)
{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;
    previousState = GameState::Menu;

    camera.setSize({ 800.f, 600.f });
    camera.setCenter({ 400.f, 300.f });

    if (!marioTex.loadFromFile("mariotex.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    mario.initTexture(marioTex);

    // --- TUTAJ JEST DODANY KOD WGRAWJ¥CY TEKSTURÊ PLATFORM ---
    if (!groundTex.loadFromFile("ground.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
    groundTex.setRepeated(true);

    if (!platformTex.loadFromFile("platform.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
    platformTex.setRepeated(true);

    if (!pipeTex.loadFromFile("toppipe.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }

    if (!backgroundTex.loadFromFile("tlo.png")) {
        // tutaj obs³uga b³êdu
    }
    background.emplace(backgroundTex);

    ground.initTexture(groundTex);
    ground2.initTexture(groundTex);
    ground3.initTexture(groundTex);
    ground4.initTexture(groundTex);
    ground5.initTexture(groundTex);
    ground6.initTexture(groundTex);
    ground7.initTexture(groundTex);
    ground8.initTexture(groundTex);
    ground9.initTexture(groundTex);
    platform.initTexture(platformTex);
    platform2.initTexture(platformTex);
    platform3.initTexture(platformTex);
    platform4.initTexture(platformTex);
    platform5.initTexture(platformTex);
    platform6.initTexture(platformTex);
    platform7.initTexture(platformTex);
    platform8.initTexture(platformTex);
    platform9.initTexture(platformTex);
    platform10.initTexture(platformTex);
    platform11.initTexture(platformTex);
    platform12.initTexture(platformTex);
    platform13.initTexture(platformTex);
    pipe1.initTexture(pipeTex);

    if (!font.openFromFile("ALGER.ttf"))
    {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }

    if (!goombaTexture.loadFromFile("goombas.png")) {
        // Jeœli pliku nie ma, program nadal ruszy, ale wyœwietli w konsoli b³¹d od SFML
    }

    if (!troopaTexture.loadFromFile("troopa.png")) {
        // Jeœli pliku nie ma, program nadal ruszy, ale wyœwietli w konsoli b³¹d od SFML
    }

    hud.init(font);

    spawnCoins();

    spawnEnemies();

    /*Coin* coin1 = new Coin(400.f, 430.f);
    coin1->coinCollect(hud, items, { 400.f, 430.f });

    Coin* coin2 = new Coin(500.f, 430.f);
    coin2->coinCollect(hud, items, { 500.f, 430.f });

    Coin* coin3 = new Coin(800.f, 430.f);
    coin3->coinCollect(hud, items, { 800.f, 430.f });

    Coin* coin4 = new Coin(1150.f, 430.f);
    coin4->coinCollect(hud, items, { 1150.f, 430.f });*/
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
    //zegar gry
    sf::Time time = clock.restart();
    float deltaTime = time.asSeconds();


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
        ground5.resolveCollision(mario);
        ground6.resolveCollision(mario);
        ground7.resolveCollision(mario);
        ground8.resolveCollision(mario);
        ground9.resolveCollision(mario);

        platform.resolveCollision(mario);
		platform2.resolveCollision(mario);
		platform3.resolveCollision(mario);
        platform4.resolveCollision(mario);
        platform5.resolveCollision(mario);
        platform6.resolveCollision(mario);
        platform7.resolveCollision(mario);
        platform8.resolveCollision(mario);
        platform9.resolveCollision(mario);
        platform10.resolveCollision(mario);
        platform11.resolveCollision(mario);
        platform12.resolveCollision(mario);
        platform13.resolveCollision(mario);

        pipe1.resolveCollision(mario);

        //Jeœli mario poza ekranem to koniec gry
        if (mario.getY()>600.f) {
            currentState = GameState::GameOver;
        }

        for (auto& enemy : enemies) {
            enemy->update(deltaTime);

            enemy->resolveCollision(ground);
            enemy->resolveCollision(ground2);
            enemy->resolveCollision(ground3);
            enemy->resolveCollision(ground4);
            enemy->resolveCollision(ground5);
            enemy->resolveCollision(ground6);
            enemy->resolveCollision(ground7);
            enemy->resolveCollision(ground8);
            enemy->resolveCollision(ground9);
            enemy->resolveCollision(platform);
            enemy->resolveCollision(platform2);
            enemy->resolveCollision(platform3);


            if (mario.getBounds().findIntersection(enemy->getBounds()).has_value()) {
                auto intersectionOpt = mario.getBounds().findIntersection(enemy->getBounds());

                if (intersectionOpt.has_value() && !enemy->isSquashed()) {
                    sf::FloatRect inter = intersectionOpt.value();

                    if (inter.size.x > inter.size.y && mario.getY() < enemy->getBounds().position.y) {
                        enemy->squash();   
                        mario.bounceUp();  
                        hud.addScore(100); 
                    }
                    else {
                        currentState = GameState::GameOver;
                    }
                }
            }
        }

        for (auto& it : items) {
            if (!it->isActive()) continue;
            it->update();
            if (mario.getBounds().findIntersection(it->getBounds()).has_value()) {
                it->onPickup(mario);
            }
        }

        std::erase_if(enemies, [](const std::unique_ptr<Enemy>& e) {
            return e->isReadyToRemove();
            });
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

        window.setView(window.getDefaultView());
        if (background.has_value()) {
            window.draw(*background); 
        }

        window.setView(camera);

        ground.draw(window);
        ground2.draw(window);
        ground3.draw(window);
        ground4.draw(window);
        ground5.draw(window);
        ground6.draw(window);
        ground7.draw(window);
        ground8.draw(window);
        ground9.draw(window);

        platform.draw(window);
        platform2.draw(window);
        platform3.draw(window);
        platform4.draw(window);
        platform5.draw(window);
        platform6.draw(window);
        platform7.draw(window);
        platform8.draw(window);
        platform9.draw(window);
        platform10.draw(window);
        platform11.draw(window);
        platform12.draw(window);
        platform13.draw(window);

        pipe1.draw(window);

        for (auto& it : items) {
            if (it && it->isActive()) it->draw(window);
        }

        for (auto& enemy : enemies) {
            if (enemy) { 
                enemy->draw(window);
            }
        }

        mario.draw(window);

        window.setView(window.getDefaultView());
        pause_button.draw(window);


        hud.update();
        hud.draw(window);
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
    ground5.resetPlatform();
    ground6.resetPlatform();
    ground7.resetPlatform();
    ground8.resetPlatform();
    ground9.resetPlatform();


    platform.resetPlatform();
    platform2.resetPlatform();
    platform3.resetPlatform();

    pipe1.resetPlatform();

    Coin::resetCounters();
    hud.reset();
    items.clear();
	spawnCoins();

    enemies.clear(); 
    spawnEnemies();

    clock.restart();
}

void Game::spawnCoins() {

    items.emplace_back(std::make_unique<Coin>(400.f, 430.f));
    items.back()->setOnPickup([this](Player& p) {
        hud.addScore(10); // wynik
        });

    items.emplace_back(std::make_unique<Coin>(500.f, 430.f));
    items.back()->setOnPickup([this](Player& p) {
        hud.addScore(10); // wynik
        });

    items.emplace_back(std::make_unique<Coin>(800.f, 430.f));
    items.back()->setOnPickup([this](Player& p) {
        hud.addScore(10); // wynik
        });

    items.emplace_back(std::make_unique<Coin>(1150.f, 430.f));
    items.back()->setOnPickup([this](Player& p) {
        hud.addScore(10); // wynik
        });

    hud.reset();
}

void Game::spawnEnemies() {

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(450.f, 440.f), 18, 22));

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(900.f, 440.f), 18, 22));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(1100.f, 440.f), 16, 22));

}