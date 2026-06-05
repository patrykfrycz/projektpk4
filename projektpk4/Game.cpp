#include "Game.h"
#include <optional>
#include "Platform.h"
#include "Coin.h"
#include "HUD.h"


Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Super Mario Bros - OOP"),
   

    play_button(20.f, 190.f),
    settings_button(20.f, 250.f),
    settings_button2(225.f, 220.f),
    table_button(20.f, 310.f),
    table_button2(300.f, 280.f),
    exit_button(20.f, 360.f),
    exit_button2(290.f, 330.f),
    exit_button3(285.f, 260.f),
    pause_button(20.f, 20.f),
    menu_button(310.f, 200.f),
    resume_button(300.f, 150.f),
   

    ground(0.f, 500.f, 1200.f, 100.f),
    ground2(1350.f, 500.f, 900.f, 100.f),
    ground3(2450.f, 500.f, 1000.f, 100.f),
    ground4(3600.f, 500.f, 800.f, 100.f),
    ground5(4650.f, 500.f, 1200.f, 100.f),
    ground6(6000.f, 500.f, 900.f, 100.f),
    ground7(7100.f, 500.f, 1100.f, 100.f),
    ground8(8400.f, 500.f, 800.f, 100.f),
    ground9(9450.f, 500.f, 1500.f, 100.f),
    ground10(11200.f, 500.f, 900.f, 100.f),
    ground11(12300.f, 500.f, 1200.f, 100.f),
    ground12(13800.f, 500.f, 2000.f, 100.f),

    platform(400.f, 350.f, 50.f, 50.f),
    platform1(500.f, 350.f, 50.f, 50.f),
    platform2(600.f, 200.f, 100.f, 50.f),
    platform3(1220.f, 400.f, 100.f, 50.f),
    platform4(1650.f, 300.f, 200.f, 50.f),
    platform5(1850.f, 150.f, 100.f, 50.f),
    platform6(2250.f, 400.f, 100.f, 50.f),
    platform7(2350.f, 300.f, 100.f, 50.f),
    platform8(2800.f, 350.f, 300.f, 50.f),
    platform9(3200.f, 200.f, 150.f, 50.f),
    platform10(3450.f, 300.f, 100.f, 50.f),
    platform11(4450.f, 350.f, 150.f, 50.f),
    platform12(5000.f, 350.f, 150.f, 50.f),
    platform13(5400.f, 250.f, 200.f, 50.f),
    platform14(6300.f, 300.f, 150.f, 50.f),
    platform15(6600.f, 150.f, 150.f, 50.f),
    platform16(6900.f, 300.f, 150.f, 50.f),
    platform17(8250.f, 350.f, 100.f, 50.f),
    platform18(9250.f, 400.f, 150.f, 50.f),
    platform19(11000.f, 350.f, 150.f, 50.f),
    platform20(12150.f, 300.f, 100.f, 50.f),

    pipe1(1130.f, 406.f, 70.f, 94.f),
    pipe2(1350.f, 406.f, 70.f, 94.f),
    pipe3(2180.f, 406.f, 70.f, 94.f),
    pipe4(2450.f, 406.f, 70.f, 94.f),
    pipe5(3380.f, 406.f, 70.f, 94.f)

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

    if (!playTex.loadFromFile("graj.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    play_button.initTexture(playTex);

    if (!setTex.loadFromFile("ustawienia.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    settings_button.initTexture(setTex);
    settings_button2.initTexture(setTex);

    if (!tableTex.loadFromFile("tabela.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    table_button.initTexture(tableTex);
    table_button2.initTexture(tableTex);

    if (!exitTex.loadFromFile("wyjscie.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    exit_button.initTexture(exitTex);
    exit_button2.initTexture(exitTex);
    exit_button3.initTexture(exitTex);

    if (!pauseTex.loadFromFile("pauza.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    pause_button.initTexture(pauseTex);

    if (!menubutTex.loadFromFile("menu.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    menu_button.initTexture(menubutTex);

    if (!resumeTex.loadFromFile("wznow.png")) {
        // tutaj obs³uga b³êdu, jeœli plik nie istnieje
    }

    resume_button.initTexture(resumeTex);

    // --- TUTAJ JEST DODANY KOD WGRAWJ¥CY TEKSTURÊ PLATFORM ---
    if (!groundTex.loadFromFile("ground.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
    groundTex.setRepeated(true);

    if (!platformTex.loadFromFile("platform.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
    platformTex.setRepeated(true);

    if (!blockTex.loadFromFile("mystery.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }

    if (!blockUsedTex.loadFromFile("mystery_after.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }
  

    if (!pipeTex.loadFromFile("toppipe.png")) {
        // to w przysz³oœci mo¿emy tu wyrzuciæ b³¹d do konsoli
    }

    if (!backgroundTex.loadFromFile("tlo.png")) {
        // tutaj obs³uga b³êdu
    }
    background.emplace(backgroundTex);

    if (!menuTex.loadFromFile("menutex.png")) {
        // tutaj obs³uga b³êdu
    }
    menu.emplace(menuTex);

    if (!pauzaTex.loadFromFile("tlopauza.png")) {
        // tutaj obs³uga b³êdu
    }
    pauza.emplace(pauzaTex);

    if (!overTex.loadFromFile("gameover.png")) {
        // tutaj obs³uga b³êdu
    }
    gameover.emplace(overTex);

    ground.initTexture(groundTex);
    ground2.initTexture(groundTex);
    ground3.initTexture(groundTex);
    ground4.initTexture(groundTex);
    ground5.initTexture(groundTex);
    ground6.initTexture(groundTex);
    ground7.initTexture(groundTex);
    ground8.initTexture(groundTex);
    ground9.initTexture(groundTex);
    ground10.initTexture(groundTex);
    ground11.initTexture(groundTex);
    ground12.initTexture(groundTex);

    platform.initTexture(platformTex); 
    platform1.initTexture(platformTex);
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
    platform14.initTexture(platformTex);
    platform15.initTexture(platformTex);
    platform16.initTexture(platformTex);
    platform17.initTexture(platformTex);
    platform18.initTexture(platformTex);
    platform19.initTexture(platformTex);
    platform20.initTexture(platformTex);

    pipe1.initTexture(pipeTex);
    pipe2.initTexture(pipeTex);
    pipe3.initTexture(pipeTex);
    pipe4.initTexture(pipeTex);
    pipe5.initTexture(pipeTex);


    if (!goombaTexture.loadFromFile("goombas.png")) {
        // Jeœli pliku nie ma, program nadal ruszy, ale wyœwietli w konsoli b³¹d od SFML
    }

    if (!troopaTexture.loadFromFile("troopa.png")) {
        // Jeœli pliku nie ma, program nadal ruszy, ale wyœwietli w konsoli b³¹d od SFML
    }

    blocks.emplace_back(std::make_unique<MysteryBlock>(450.f, 350.f, 50.f, 50.f));

    for (auto& block : blocks) {
        block->initTextures(blockTex, blockUsedTex);
    }


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
                    if (exit_button2.isClicked(window)) currentState = GameState::Menu;
                    if (settings_button2.isClicked(window))
                    {
                        previousState = currentState;
                        currentState = GameState::Settings;
                    }
                }

                if (currentState == GameState::Playing) {
                    if (pause_button.isClicked(window)) currentState = GameState::Pause;
                }

                if (currentState == GameState::Settings) {
                    if (exit_button2.isClicked(window)) currentState = previousState;

                }

                if (currentState == GameState::GameOver) {
                    if (menu_button.isClicked(window)) currentState = GameState::Menu;
                    if (exit_button3.isClicked(window)) window.close();
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
        ground10.resolveCollision(mario);
        ground11.resolveCollision(mario);
        ground12.resolveCollision(mario);

        platform.resolveCollision(mario);
        platform1.resolveCollision(mario);
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
        platform14.resolveCollision(mario);
        platform15.resolveCollision(mario);
        platform16.resolveCollision(mario);
        platform17.resolveCollision(mario);
        platform18.resolveCollision(mario);
        platform19.resolveCollision(mario);
        platform20.resolveCollision(mario);

        pipe1.resolveCollision(mario);
        pipe2.resolveCollision(mario);
        pipe3.resolveCollision(mario);
        pipe4.resolveCollision(mario);
        pipe5.resolveCollision(mario);

        for (auto& block : blocks) {
            block->update(deltaTime);
            block->resolveCollision(mario);
        }

        //Jeœli mario poza ekranem to koniec gry
        if (mario.getY() > 600.f) {
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
            enemy->resolveCollision(ground10);
            enemy->resolveCollision(ground11);
            enemy->resolveCollision(ground12);

            enemy->resolveCollision(platform);
            enemy->resolveCollision(platform1);
            enemy->resolveCollision(platform2);
            enemy->resolveCollision(platform3);
            enemy->resolveCollision(platform4);
            enemy->resolveCollision(platform5);
            enemy->resolveCollision(platform6);
            enemy->resolveCollision(platform7);
            enemy->resolveCollision(platform8);
            enemy->resolveCollision(platform9);
            enemy->resolveCollision(platform10);
            enemy->resolveCollision(platform11);
            enemy->resolveCollision(platform12);
            enemy->resolveCollision(platform13);
            enemy->resolveCollision(platform14);
            enemy->resolveCollision(platform15);
            enemy->resolveCollision(platform16);
            enemy->resolveCollision(platform17);
            enemy->resolveCollision(platform18);
            enemy->resolveCollision(platform19);
            enemy->resolveCollision(platform20);

            enemy->resolveCollision(pipe1);
            enemy->resolveCollision(pipe2);
            enemy->resolveCollision(pipe3);
            enemy->resolveCollision(pipe4);
            enemy->resolveCollision(pipe5);

            if (mario.getBounds().findIntersection(enemy->getBounds()).has_value()) {
                sf::FloatRect inter = mario.getBounds().findIntersection(enemy->getBounds()).value();

                if (inter.size.x > inter.size.y && mario.getY() < enemy->getBounds().position.y) {

                    if (!enemy->isSquashed()) {
                        enemy->squash();
                        mario.bounceUp();
                        hud.addScore(100);
                    }
                    else if (enemy->getType() == EnemyType::Troopa) {
                        enemy->setDead();
                        mario.bounceUp();
                        hud.addScore(100); 
                    }
                }

                else {
                    if (enemy->getType() == EnemyType::Troopa && enemy->isSquashed() && !enemy->isShellMoving()) {
                        enemy->kick(mario.getX());
                    }
                    else if (!enemy->isSquashed() || enemy->isShellMoving()) {
                        currentState = GameState::GameOver;
                    }
                }
            }
        }

        for (size_t i = 0; i < enemies.size(); ++i) {
            for (size_t j = i + 1; j < enemies.size(); ++j) {
                if (enemies[i]->getBounds().findIntersection(enemies[j]->getBounds()).has_value()) {

                    bool shell1 = (enemies[i]->getType() == EnemyType::Troopa && enemies[i]->isShellMoving());
                    bool shell2 = (enemies[j]->getType() == EnemyType::Troopa && enemies[j]->isShellMoving());

                    if (shell1 && !shell2) {
                        enemies[j]->setDead(); 
                        hud.addScore(100);
                    }
                    else if (shell2 && !shell1) {
                        enemies[i]->setDead(); 
                        hud.addScore(100);
                    }
                    else if (shell1 && shell2) {
                        enemies[i]->setDead();
                        enemies[j]->setDead();
                        hud.addScore(200);
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
        if (menu.has_value()) {
            window.draw(*menu);
        }
        play_button.draw(window);
        settings_button.draw(window);
        table_button.draw(window);
        exit_button.draw(window);
        
    }
    else if (currentState == GameState::Settings)
    {
        window.clear(sf::Color::Black);
        if (pauza.has_value()) {
            window.draw(*pauza);
        }
        exit_button2.draw(window);
  
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
        ground10.draw(window);
        ground11.draw(window);
        ground12.draw(window);

        platform.draw(window);
        platform1.draw(window);
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
        platform14.draw(window);
        platform15.draw(window);
        platform16.draw(window);
        platform17.draw(window);
        platform18.draw(window);
        platform19.draw(window);
        platform20.draw(window);

        pipe1.draw(window);
        pipe2.draw(window);
        pipe3.draw(window);
        pipe4.draw(window);
        pipe5.draw(window);

        for (auto& block : blocks) {
            block->draw(window);
        }

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
        if (pauza.has_value()) {
            window.draw(*pauza);
        }
        resume_button.draw(window);
        table_button2.draw(window);
        settings_button2.draw(window);
        exit_button2.draw(window);
    }
    else if (currentState == GameState::GameOver) {
        window.clear(sf::Color::Black);
        if (gameover.has_value()) {
            window.draw(*gameover);
        }
        menu_button.draw(window);
        exit_button3.draw(window);
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
    ground10.resetPlatform();
    ground11.resetPlatform();
    ground12.resetPlatform();


    platform.resetPlatform();
    platform1.resetPlatform();
    platform2.resetPlatform();
    platform3.resetPlatform();
    platform4.resetPlatform();
    platform5.resetPlatform();
    platform6.resetPlatform();
    platform7.resetPlatform();
    platform8.resetPlatform();
    platform9.resetPlatform();
    platform10.resetPlatform();
    platform11.resetPlatform();
    platform12.resetPlatform();
    platform13.resetPlatform();
    platform14.resetPlatform();
    platform15.resetPlatform();
    platform16.resetPlatform();
    platform17.resetPlatform();
    platform18.resetPlatform();
    platform19.resetPlatform();
    platform20.resetPlatform();

    pipe1.resetPlatform();
    pipe2.resetPlatform();
    pipe3.resetPlatform();
    pipe4.resetPlatform();
    pipe5.resetPlatform();

    for (auto& block : blocks) {
        block->resetBlock();
    }

    Coin::resetCounters();
    hud.reset();
    items.clear();
    spawnCoins();

    enemies.clear();
    spawnEnemies();

    clock.restart();
}

void Game::spawnCoins() {

    items.emplace_back(std::make_unique<Coin>(450.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(620.f, 150.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(1250.f, 350.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(1680.f, 250.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(1880.f, 100.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(2850.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(3250.f, 150.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(4500.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(5050.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(5450.f, 200.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(6650.f, 100.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(8300.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });
    items.emplace_back(std::make_unique<Coin>(11050.f, 300.f));
    items.back()->setOnPickup([this](Player& p) { hud.addScore(10); });

    hud.reset();
}

void Game::spawnEnemies() {

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(600.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(1100.f, 440.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(1500.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(1900.f, 440.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(2700.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(3200.f, 440.f), 16, 22, EnemyType::Troopa));

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(3900.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(4800.f, 440.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(6200.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(7400.f, 440.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(8600.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(9700.f, 440.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(11500.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(12800.f, 440.f), 16, 22, EnemyType::Troopa));

}