#include "Game.h"
#include <optional>
#include "Platform.h"
#include "Coin.h"
#include "HUD.h"
#include "Star.h"

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Mario Project"),
   

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

    endFlag(15500.f, 100.f)

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


    if (!flagTex.loadFromFile("flag.png")) {
        // b³¹d
    }
    endFlag.initTexture(flagTex);

    if (!winTex.loadFromFile("wintex.png")) {
        // b³¹d
    }
    gamewin.emplace(winTex);

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

    if (!starTex.loadFromFile("star.png")) {
        // b³¹d
    }

    if (!mushroomTex.loadFromFile("mushroom.png")) {
        // b³¹d
    }

  

    if (!goombaTexture.loadFromFile("goombas.png")) {
        // Jeœli pliku nie ma, program nadal ruszy, ale wyœwietli w konsoli b³¹d od SFML
    }

    if (!troopaTexture.loadFromFile("troopa.png")) {
        // blad
    }

    spawnGround(0.f, 500.f, 2500.f, 100.f);
    spawnGround(2800.f, 500.f, 3000.f, 100.f);
    spawnGround(6200.f, 500.f, 2000.f, 100.f);
    spawnGround(8600.f, 500.f, 1000.f, 100.f);
    spawnGround(10200.f, 500.f, 5500.f, 100.f);

    spawnPipe(1000.f, 406.f, 70.f, 94.f);
    spawnPipe(1800.f, 406.f, 70.f, 94.f);
    spawnPipe(3500.f, 406.f, 70.f, 94.f);
    spawnPipe(3800.f, 406.f, 70.f, 94.f);
    spawnPipe(7000.f, 406.f, 70.f, 94.f);
    spawnPipe(11500.f, 406.f, 70.f, 94.f);

    spawnPlatform(450.f, 370.f, 100.f, 50.f);
    spawnMysteryBlock(550.f, 370.f, ItemType::Mushroom);
    spawnPlatform(600.f, 370.f, 100.f, 50.f);
    spawnPlatform(525.f, 240.f, 100.f, 50.f);

    spawnPlatform(1900.f, 370.f, 250.f, 50.f);
    spawnPlatform(1950.f, 240.f, 50.f, 50.f);
    spawnMysteryBlock(2000.f, 240.f, ItemType::Star);
    spawnPlatform(2050.f, 240.f, 50.f, 50.f);

    spawnPlatform(2600.f, 370.f, 100.f, 50.f);

    spawnPlatform(4100.f, 370.f, 150.f, 50.f);
    spawnMysteryBlock(4250.f, 370.f, ItemType::Mushroom);
    spawnPlatform(4300.f, 370.f, 150.f, 50.f);
    spawnPlatform(4150.f, 240.f, 200.f, 50.f);
    spawnPlatform(4200.f, 110.f, 50.f, 50.f);
    spawnMysteryBlock(4250.f, 110.f, ItemType::Star);
    spawnPlatform(4300.f, 110.f, 50.f, 50.f);

    spawnPlatform(5950.f, 350.f, 100.f, 50.f);

    spawnPlatform(7300.f, 370.f, 200.f, 50.f);
    spawnPlatform(7350.f, 240.f, 50.f, 50.f);
    spawnMysteryBlock(7400.f, 240.f, ItemType::Mushroom);
    spawnPlatform(7450.f, 240.f, 50.f, 50.f);

    spawnPlatform(10800.f, 370.f, 100.f, 50.f);
    spawnMysteryBlock(10900.f, 370.f, ItemType::Star);
    spawnPlatform(10950.f, 370.f, 100.f, 50.f);
    spawnPlatform(10850.f, 240.f, 150.f, 50.f);

    spawnPlatform(13450.f, 240.f, 50.f, 50.f);
    spawnMysteryBlock(13500.f, 240.f, ItemType::Star);
    spawnPlatform(13550.f, 240.f, 50.f, 50.f);

    spawnPlatform(14700.f, 450.f, 50.f, 50.f);
    spawnPlatform(14750.f, 400.f, 50.f, 100.f);
    spawnPlatform(14800.f, 350.f, 50.f, 150.f);
    spawnPlatform(14850.f, 300.f, 50.f, 200.f);
    spawnPlatform(14900.f, 250.f, 50.f, 250.f);
    spawnPlatform(14950.f, 200.f, 50.f, 300.f);

    spawnCoins();

    spawnEnemies();
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

                if (currentState == GameState::Win) {
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

        if (mario.isDead()) {
            mario.update(); 

            
            if (mario.getY() > 800.f) {
                currentState = GameState::GameOver;
            }
            return; 
        }

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

        // poprawione platformy zeby nie przyci¹ga³y przy upadku
        for (auto& plat : platforms) {
            plat.resolveCollision(mario);
        }
        for (auto& ground : grounds) {
            ground.resolveCollision(mario);
        }
        for (auto& pipe : pipes) {
            pipe.resolveCollision(mario);
        }

        for (auto& block : blocks) {
            block->update(deltaTime);
            block->resolveCollision(mario);
        }

        if (endFlag.checkCollision(mario)) {
            currentState = GameState::Win;
        }

        //Jeœli mario poza ekranem to koniec gry
        if (mario.getY() > 600.f && !mario.isDead()) {
            mario.die(); 
        }

        for (auto& enemy : enemies) {
            enemy->update(deltaTime);

            for (auto& ground : grounds) {
                enemy->resolveCollision(ground.getBounds());
            }

            for (auto& plat : platforms) {
                enemy->resolveCollision(plat.getBounds());
            }

            for (auto& pipe : pipes) {
                enemy->resolveCollision(pipe.getBounds());
            }

            for (auto& block : blocks) {
                enemy->resolveCollision(block->getBounds());
            }

            enemy->preventFallingOff();

            if (mario.getBounds().findIntersection(enemy->getBounds()).has_value()) {
                sf::FloatRect inter = mario.getBounds().findIntersection(enemy->getBounds()).value();

                if (mario.hasStar()) {
                    if (!enemy->isReadyToRemove() && !enemy->isKnockedOut()) {

                        enemy->knockOut();

                        hud.addScore(200);
                    }
                }
                else {
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
                    // Dotkniêcie z boku
                    else {
                        if (enemy->getType() == EnemyType::Troopa && enemy->isSquashed() && !enemy->isShellMoving()) {
                            enemy->kick(mario.getX());
                        }
                        else if (!enemy->isSquashed() || enemy->isShellMoving()) {
                            if (!mario.isInvincible()) {
                                if (mario.isMini()) {
                                    mario.deactivateMini();
                                    mario.bounceUp();
                                }
                                else {
                                    mario.die();
                                }
                            }

                        }
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


            if (Star* star = dynamic_cast<Star*>(it.get())) {

                    for (auto& plat : platforms) {
                        star->resolveCollision(plat);
                    }

                    for (auto& ground : grounds) {
                        star->resolveCollision(ground);
                    }

                    for (auto& pipe : pipes) {
                        star->resolveCollision(pipe);
                    }
                
            }

            if(Mushroom* mush = dynamic_cast<Mushroom*>(it.get())) {
                for (auto& plat : platforms) {
                    mush->resolveCollision(plat);
                }

                for (auto& ground : grounds) {
                    mush->resolveCollision(ground);
                }

                for (auto& pipe : pipes) {
                    mush->resolveCollision(pipe);
                }
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

        for (auto& ground : grounds) {
            ground.draw(window);
        }

        for (auto& plat : platforms) {
            plat.draw(window);
        }

        for (auto& pipe : pipes) {
            pipe.draw(window);
        }
        endFlag.draw(window);

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
    else if (currentState == GameState::Win) {
        window.clear(sf::Color::Black);
        if (gamewin.has_value()) {
            window.draw(*gamewin);
        }
        menu_button.draw(window);
        exit_button3.draw(window);
    }

    window.display();
}


void Game::resetGame() {
    mario.reset();
    camera.setCenter({ 400.f, 300.f });
    for (auto& ground : grounds) {
        ground.resetPlatform();
    }


    for (auto& plat : platforms) {
        plat.resetPlatform();
    }

    for (auto& pipe : pipes) {
        pipe.resetPlatform();
    }

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

void Game::spawnGround(float x, float y, float w, float h) {
    platforms.emplace_back(x, y, w, h);
    platforms.back().initTexture(groundTex);
}

void Game::spawnPlatform(float x, float y, float w, float h) {
    platforms.emplace_back(x, y, w, h);
    platforms.back().initTexture(platformTex);
}

void Game::spawnPipe(float x, float y, float w, float h) {
    platforms.emplace_back(x, y, w, h);
    platforms.back().initTexture(pipeTex);
}


void Game::spawnCoins() {
    items.clear();

    items.emplace_back(std::make_unique<Coin>(550.f, 180.f));
    //items.emplace_back(std::make_unique<Coin>(585.f, 180.f));

    items.emplace_back(std::make_unique<Coin>(2550.f, 280.f));
    items.emplace_back(std::make_unique<Coin>(2650.f, 200.f));
    items.emplace_back(std::make_unique<Coin>(2750.f, 280.f));

    items.emplace_back(std::make_unique<Coin>(4200.f, 50.f));
    items.emplace_back(std::make_unique<Coin>(4300.f, 50.f));

    items.emplace_back(std::make_unique<Coin>(5000.f, 400.f));
    items.emplace_back(std::make_unique<Coin>(6000.f, 180.f));

    items.emplace_back(std::make_unique<Coin>(10900.f, 180.f));
    items.emplace_back(std::make_unique<Coin>(12000.f, 350.f));

    for (auto& item : items) {
        if (item->getType() == ItemType::Coin) {
            item->setOnPickup([this](Player& p) { hud.addScore(10); });
        }
    }

    hud.reset();
}

void Game::spawnEnemies() {
    enemies.clear();

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(800.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(600.f, 300.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(1500.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(2000.f, 180.f), 16, 22, EnemyType::Troopa));

    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(3600.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(4250.f, 180.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(4800.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(7350.f, 300.f), 18, 22, EnemyType::Goomba));

    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(11000.f, 440.f), 16, 22, EnemyType::Troopa));
    enemies.emplace_back(std::make_unique<Enemy>(goombaTexture, sf::Vector2f(12500.f, 440.f), 18, 22, EnemyType::Goomba));
    enemies.emplace_back(std::make_unique<Enemy>(troopaTexture, sf::Vector2f(14000.f, 440.f), 16, 22, EnemyType::Troopa));

}

void Game::spawnMysteryBlock(float x, float y, ItemType content) {
    auto block = std::make_unique<MysteryBlock>(x, y, 50.f, 50.f);
    block->initTextures(blockTex, blockUsedTex); 

    block->setOnHitCallback([this, content](sf::Vector2f pos) {

        if (content == ItemType::Star) {
            auto star = std::make_unique<Star>(pos.x, pos.y);
            star->initTexture(starTex);
            star->setOnPickup([this](Player& p) {
                hud.addScore(1000);
                p.activateStar();
                });
            items.push_back(std::move(star));
        }
        else if (content == ItemType::Mushroom) {
            auto mush = std::make_unique<Mushroom>(pos.x, pos.y);
            mush->initTexture(mushroomTex);
            mush->setOnPickup([this](Player& p) {
                hud.addScore(1000);
                p.activateMini();
                });
            items.push_back(std::move(mush));
        }
        });

    blocks.push_back(std::move(block));
}