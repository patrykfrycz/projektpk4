#include "Game.h"
#include <optional>
#include <filesystem>
#include <iostream>
#include <ranges>
#include "Platform.h"
#include "Coin.h"
#include "HUD.h"
#include "Star.h"

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Mario Project"),
   

    play_button(20.f, 190.f),
    settings_button(20.f, 250.f),
    settings_button2(175.f, 250.f),
    table_button(20.f, 310.f),
    table_button2(250.f, 310.f),
    exit_button(20.f, 365.f),
    exit_button2(230.f, 365.f),
    exit_button3(245.f, 265.f),
    exit_button4(245.f, 385.f),
    pause_button(20.f, 20.f),
    menu_button(310.f, 200.f),
    resume_button(270.f, 180.f),
    audio_button(200.f, 260.f),

    endFlag(15500.f, 100.f)

{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;
    previousState = GameState::Menu;

    camera.setSize({ 800.f, 600.f });
    camera.setCenter({ 400.f, 300.f });

    std::vector<std::string> requiredAssets = {
        "mariotex.png",
        "graj.png",
        "ustawienia.png",
        "tabela.png",
        "wyjscie.png",
        "pauza.png",
        "menu.png",
        "wznow.png",
        "flag.png",
        "wintex.png",
        "ground.png",
        "platform.png",
        "mystery.png",
        "mystery_after.png",
        "toppipe.png",
        "tlo.png",
        "menutex.png",
        "tlopauza.png",
        "gameover.png",
        "star.png",
        "mushroom.png",
        "goombas.png",
        "troopa.png"
    };

    for (const auto& asset : requiredAssets) {
        if (!std::filesystem::exists(asset)) {
            std::cerr << "BLAD: Brak pliku graficznego na dysku: " << asset << "!\n";
        }
    }


    if (!marioTex.loadFromFile("mariotex.png")) {
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
    exit_button4.initTexture(exitTex);

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

    if (clickBuffer.loadFromFile("klik.ogg")) {
        clickSound.emplace(clickBuffer); 
    }
    if (deathBuffer.loadFromFile("smierc.ogg")) {
        deathSound.emplace(deathBuffer); 
    }

    if (squashBuffer.loadFromFile("squash.wav")) {
        squashSound.emplace(squashBuffer);
    }

    bgMusic.emplace(); 

    if (bgMusic->openFromFile("music.wav")) {
        bgMusic->setLooping(true);

    }

    if (hoverBuffer.loadFromFile("hover.wav")) {
        hoverSound.emplace(hoverBuffer);
    }

    if (!audioOnTex.loadFromFile("on.png")) {}
    if (!audioOffTex.loadFromFile("off.png")) {}

    audio_button.initTexture(audioOnTex);

    if (settingsFont.openFromFile("MARIO.ttf")) {
        audioText.emplace(settingsFont);
        audioText->setString("Dzwiek: Wlaczono");
        audioText->setCharacterSize(40);
        audioText->setFillColor(sf::Color::White);
        audioText->setPosition({ 200.f, 210.f }); 

        tableTitleText.emplace(settingsFont);
        tableTitleText->setString("TABELA WYNIKOW");
        tableTitleText->setCharacterSize(50);
        tableTitleText->setFillColor(sf::Color::Black);
        tableTitleText->setPosition({ 170.f, 160.f });

        winScoreText.emplace(settingsFont);
        winScoreText->setCharacterSize(50); 
        winScoreText->setFillColor(sf::Color::Yellow); 
        winScoreText->setOutlineThickness(3.f);
        winScoreText->setOutlineColor(sf::Color::Black);

        winScoreText->setPosition({ 250.f, 400.f });

        hud.init(settingsFont);
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


    //podziemia
    spawnGround(0.f, 3000.f, 5000.f, 100.f);

    spawnPlatform(500.f, 2870.f, 150.f, 50.f);
    spawnMysteryBlock(700.f, 2870.f, ItemType::Star);
    spawnPlatform(750.f, 2870.f, 100.f, 50.f);

    spawnPlatform(1300.f, 2870.f, 200.f, 50.f);
    spawnPlatform(1375.f, 2740.f, 50.f, 50.f);
    spawnMysteryBlock(1425.f, 2740.f, ItemType::Star);

    spawnPlatform(2000.f, 2870.f, 50.f, 50.f);
    spawnPlatform(2150.f, 2740.f, 50.f, 50.f);
    spawnPlatform(2300.f, 2870.f, 50.f, 50.f);

    spawnPlatform(3000.f, 2870.f, 300.f, 50.f);
    spawnMysteryBlock(3125.f, 2740.f, ItemType::Mushroom);

    spawnPlatform(3800.f, 2870.f, 200.f, 50.f);
    spawnPlatform(4100.f, 2740.f, 150.f, 50.f);

    spawnPipe(4800.f, 2906.f, 70.f, 94.f);

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
                if (bgMusic.has_value()) bgMusic->pause();
            }
            // Jeœli jesteœmy w EKRANIE PAUZY i wciœniemy SPACJE -> Wracamy do Gry
            else if (currentState == GameState::Pause && keyEvent->code == sf::Keyboard::Key::Space)
            {
                currentState = GameState::Playing;
                if (bgMusic.has_value()) bgMusic->play();
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
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
                    if (exit_button.isClicked(window)) {
                        window.close();
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
                    
                    if (settings_button.isClicked(window))
                    {
                        previousState = currentState;
                        currentState = GameState::Settings;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }

                    if (table_button.isClicked(window)) {
                        if (clickSound.has_value()) clickSound->play();
                        previousState = currentState;
                        currentState = GameState::Table;
                        loadScores(); 
                    }
                }

                if (currentState == GameState::Pause) {
                    if (resume_button.isClicked(window)) {
                        currentState = GameState::Playing;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                        if (bgMusic.has_value()) bgMusic->play();
                    } 
                    if (exit_button2.isClicked(window)) {
                        currentState = GameState::Menu;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    } 
                    if (settings_button2.isClicked(window))
                    {
                        previousState = currentState;
                        currentState = GameState::Settings;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }

                    if (table_button.isClicked(window)) {
                        if (clickSound.has_value()) clickSound->play();
                        previousState = currentState;
                        currentState = GameState::Table;
                        loadScores(); 
                    }
                }

                if (currentState == GameState::Table) {
                    if (exit_button4.isClicked(window)) {
                        currentState = previousState;
                        if (clickSound.has_value()) clickSound->play();
                    }
                }

                if (currentState == GameState::Playing) {
                    if (pause_button.isClicked(window)) { 
                        currentState = GameState::Pause; 
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                        if (bgMusic.has_value()) bgMusic->pause();
                    }
                }

                if (currentState == GameState::Settings) {
                    if (exit_button2.isClicked(window)) {
                        currentState = previousState;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }

                    if (audio_button.isClicked(window)) {
                        if (clickSound.has_value()) clickSound->play();

                        isMuted = !isMuted;

                        if (isMuted) {
                            sf::Listener::setGlobalVolume(0.f);
                            audio_button.initTexture(audioOffTex);

                            if (audioText.has_value()) {
                                audioText->setString("Dzwiek: Wylaczono");
                            }
                        }
                        else {
                            sf::Listener::setGlobalVolume(100.f);
                            audio_button.initTexture(audioOnTex);

                            if (audioText.has_value()) {
                                audioText->setString("Dzwiek: Wlaczono");
                            }
                        }
                    }
                }

                if (currentState == GameState::GameOver) {
                    if (menu_button.isClicked(window)) {
                        currentState = GameState::Menu;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
                    if (exit_button3.isClicked(window)) {
                        window.close();
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
                }

                if (currentState == GameState::Win) {
                    if (menu_button.isClicked(window)) {
                        currentState = GameState::Menu;
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
                    if (exit_button3.isClicked(window)) {
                        window.close();
                        if (clickSound.has_value()) {
                            clickSound->play();
                        }
                    }
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

    bool playHover = false; 

    if (currentState == GameState::Menu) {
        if (play_button.update(window)) playHover = true;
        if (settings_button.update(window)) playHover = true;
        if (table_button.update(window)) playHover = true;
        if (exit_button.update(window)) playHover = true;
    }
    else if (currentState == GameState::Pause) {
        if (resume_button.update(window)) playHover = true;
        if (settings_button2.update(window)) playHover = true;
        if (table_button2.update(window)) playHover = true;
        if (exit_button2.update(window)) playHover = true;
    }
    else if (currentState == GameState::Settings) {
        if (exit_button2.update(window)) playHover = true;
        if (audio_button.update(window)) playHover = true;
    }
    else if (currentState == GameState::GameOver || currentState == GameState::Win) {
        if (menu_button.update(window)) playHover = true;
        if (exit_button3.update(window)) playHover = true;
    }
    else if (currentState == GameState::Table) {
        if (exit_button4.update(window)) playHover = true;
    }

    if (playHover && hoverSound.has_value()) {
        hoverSound->play();
    }


    //w ponizszych if-ach aktualizujemy pozycje np gracza lub innych obiektow ktore sie szybko zmieniaja
    if (currentState == GameState::Playing) {

        if (mario.isDead()) {
            mario.update(); 

            
            if (mario.getY() > 800.f) {
                currentState = GameState::GameOver;
                saveScore(hud.getScore());
            }
            return; 
        }

        mario.update();

        hud.update();

        float targetCamY = inSubWorld ? 2800.f : 300.f;

        if (mario.getX() > camera.getCenter().x) {
            camera.setCenter({ mario.getX(), targetCamY });
        }
        else {
            camera.setCenter({ camera.getCenter().x, targetCamY });
        }

        float leftEdge = camera.getCenter().x - 400.f;
        if (mario.getX() < leftEdge) {
            mario.setX(leftEdge);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            for (auto& pipe : pipes) {
                if (mario.getBounds().findIntersection(pipe.getBounds()).has_value()) {
                    if (!inSubWorld && pipe.getBounds().position.y < 2000.f && pipe.getBounds().position.x == 3500.f) {
                        inSubWorld = true;
                        returnPosition = { mario.getX(), mario.getY() }; 
                        mario.setX(100.f);  
                        mario.setY(2800.f); 
                        camera.setCenter({ 400.f, 2800.f }); 
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            for (auto& pipe : pipes) {
                if (mario.getBounds().findIntersection(pipe.getBounds()).has_value()) {
                    if (inSubWorld && pipe.getBounds().position.y > 2000.f) {
                        inSubWorld = false;
                        mario.setX(returnPosition.x + 80.f);
                        mario.setY(returnPosition.y - 50.f);
                        camera.setCenter({ mario.getX(), 300.f }); 
                    }
                }
            }
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
            saveScore(hud.getScore());

            if (winScoreText.has_value()) {
                winScoreText->setString("WYNIK: " + std::to_string(hud.getScore()));
            }
        }

        float deathLimitY = inSubWorld ? 3200.f : 600.f;

        if (mario.getY() > deathLimitY && !mario.isDead()) {
            mario.die();
            if (deathSound.has_value()) {
                deathSound->play();
            }
            if (bgMusic.has_value()) bgMusic->stop();
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

            if (mario.getBounds().findIntersection(enemy->getBounds()).has_value()) {
                sf::FloatRect inter = mario.getBounds().findIntersection(enemy->getBounds()).value();

                if (mario.hasStar()) {
                    if (!enemy->isReadyToRemove() && !enemy->isKnockedOut()) {

                        enemy->knockOut();

                        hud.addScore(200);
                        if (squashSound.has_value()) squashSound->play();
                    }
                }
                else {
                    if (inter.size.x > inter.size.y && mario.getY() < enemy->getBounds().position.y) {
                        if (!enemy->isSquashed()) {
                            enemy->squash();
                            mario.bounceUp();
                            hud.addScore(100);
                            if (squashSound.has_value()) squashSound->play();
                        }
                        else if (enemy->getType() == EnemyType::Troopa) {
                            enemy->setDead();
                            mario.bounceUp();
                            hud.addScore(100);
                            if (squashSound.has_value()) squashSound->play();
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
                                    if (deathSound.has_value()) {
                                        deathSound->play();
                                    }
                                    if (bgMusic.has_value()) bgMusic->stop();
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

        auto activeItems = items | std::views::filter([](const std::unique_ptr<Item>& it) {
            return it && it->isActive();
            });

        for (auto& it : activeItems) {
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

            if (Mushroom* mush = dynamic_cast<Mushroom*>(it.get())) {
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

        audio_button.draw(window);

        if (audioText.has_value()) {
            window.draw(*audioText);
        }
  
    }
    else if (currentState == GameState::Playing)
    {
        window.clear(sf::Color::Black);

        window.setView(window.getDefaultView());
        

        if (background.has_value() && !inSubWorld) {
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

        if (inSubWorld) {
            sf::RectangleShape darkFilter(camera.getSize());
            darkFilter.setPosition({ camera.getCenter().x - 400.f, camera.getCenter().y - 300.f });

            darkFilter.setFillColor(sf::Color(0, 0, 40, 120));

            window.draw(darkFilter);
        }

        window.setView(window.getDefaultView());
        pause_button.draw(window);

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

        if (winScoreText.has_value()) {
            window.draw(*winScoreText);
        }
    }

    else if (currentState == GameState::Table)
    {
        window.clear(sf::Color::Black);
        if (pauza.has_value()) {
            window.draw(*pauza);
        }

        if (tableTitleText.has_value()) {
            window.draw(*tableTitleText);
        }

        for (const auto& text : highScoreTexts) {
            window.draw(text);
        }

        exit_button4.draw(window);
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

    inSubWorld = false;

    if (bgMusic.has_value()) {
        bgMusic->play();
    }
}

void Game::spawnGround(float x, float y, float w, float h) {
    grounds.emplace_back(x, y, w, h);
    grounds.back().initTexture(groundTex);
}

void Game::spawnPlatform(float x, float y, float w, float h) {
    platforms.emplace_back(x, y, w, h);
    platforms.back().initTexture(platformTex);
}

void Game::spawnPipe(float x, float y, float w, float h) {
    pipes.emplace_back(x, y, w, h);
    pipes.back().initTexture(pipeTex);
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

    //podziemia
    items.emplace_back(std::make_unique<Coin>(550.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(600.f, 2800.f));

    items.emplace_back(std::make_unique<Coin>(1350.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(1450.f, 2800.f));

    items.emplace_back(std::make_unique<Coin>(2010.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(2160.f, 2670.f));
    items.emplace_back(std::make_unique<Coin>(2310.f, 2800.f));

    items.emplace_back(std::make_unique<Coin>(3050.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(3150.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(3250.f, 2800.f));

    items.emplace_back(std::make_unique<Coin>(3850.f, 2800.f));
    items.emplace_back(std::make_unique<Coin>(4150.f, 2670.f));

    for (auto& item : items) {
        if (item->getType() == ItemType::Coin) {
            item->setOnPickup([this](Player& p) { hud.addScore(150); });
        }
    }

    hud.reset();
}

void Game::spawnEnemies() {
    enemies.clear();

    // G³ówna mapa
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(800.f, 440.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(650.f, 440.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(1500.f, 440.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(2100.f, 440.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(3600.f, 440.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(4250.f, 440.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(4800.f, 440.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(7500.f, 440.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(11000.f, 440.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(12500.f, 440.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(14000.f, 440.f)));

    // Podziemia
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(900.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(1100.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(1700.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(2500.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(2700.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(3400.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(3600.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Goomba>(goombaTexture, sf::Vector2f(4300.f, 2940.f)));
    enemies.emplace_back(std::make_unique<Troopa>(troopaTexture, sf::Vector2f(4600.f, 2940.f)));
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


void Game::saveScore(int newScore) {
    if (newScore <= 0) return;

    loadScores();
    highScores.push_back(newScore);

    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
    if (highScores.size() > 5) highScores.resize(5);

    std::ofstream file("wyniki.txt");
    for (int s : highScores) {
        file << "Wynik gracza Mario to: " << s << " pkt.\n";
    }
}

void Game::loadScores() {
    highScores.clear();
    highScoreTexts.clear();

    std::ifstream file("wyniki.txt");
    std::string line;

    std::regex pattern(R"((\d+))");
    std::smatch match; 

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, pattern)) {
            int s = std::stoi(match.str(1));
            highScores.push_back(s);
        }
    }

    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
    if (highScores.size() > 5) highScores.resize(5);

    float startY = 210.f;
    for (size_t i = 0; i < highScores.size(); ++i) {
        highScoreTexts.emplace_back(settingsFont);
        highScoreTexts.back().setString(std::to_string(i + 1) + ".    " + std::to_string(highScores[i]) + " PKT");
        highScoreTexts.back().setCharacterSize(40);
        highScoreTexts.back().setFillColor(sf::Color::Yellow);
        highScoreTexts.back().setPosition({ 280.f, startY + (i * 30.f) });
    }
}