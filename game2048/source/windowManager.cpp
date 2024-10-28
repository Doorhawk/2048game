#include "windowManager.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace sf;

WindowManager::WindowManager() {

    pressedKey = 0;

    tileSize = 80;
    
    gameDifficult = 3;

    changeSize(0);

    gameSizeX = game.get_size()[0];
    gameSizeY = game.get_size()[1];

    width = tileSize* (gameSizeX+2);
    height = tileSize * (gameSizeY + 2);

    createWindow(width, height);

    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("resources/arialmt.ttf")) {
        std::cout << "font not founded";
    }


}

void WindowManager::updateWindow() {


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            controlButtons(event);
        }

        drawFrame();

    }
}
void WindowManager::changeSize(int change) {
    gameDifficult += change;
    if (gameDifficult < 0 || gameDifficult > 5) {
        gameDifficult = 0;
    }
    
        switch (gameDifficult)
        {
        
        case 0:
            game.setNewSize(2, 2);
            break;
        case 1:
            game.setNewSize(4, 1);
            break;
        case 2:
            game.setNewSize(2, 4);
            break;
        case 3:
            game.setNewSize(4, 4);
            break;
        case 4:
            game.setNewSize(6, 6);
            break;
        default:
            game.setNewSize(10, 10);
            break;
        }

        gameSizeX = game.get_size()[0];
        gameSizeY = game.get_size()[1];

        width = tileSize * (gameSizeX + 2);
        height = tileSize * (gameSizeY + 2);

        createWindow(height, width);
        restartGame();
    

}


void WindowManager::drawGame() {
    

    int ramkasize = 80;
    int betwinsize = 2;
    

        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setCharacterSize(30);

        text.setString("score: " + std::to_string(game.get_score()));
        text.setPosition(40, ramkasize /20.);
        window.draw(text);

        text.setString("record: " + std::to_string(game.get_record()));
        text.setPosition(40, ramkasize *5/10.);
        window.draw(text);




        text.setCharacterSize(30);
        


        RectangleShape rec1(Vector2f((tileSize+ betwinsize)*gameSizeY+ betwinsize, (tileSize + betwinsize) * gameSizeX+ betwinsize));
        rec1.setFillColor(Color(100, 100, 100));
        rec1.setPosition(ramkasize, ramkasize);
        window.draw(rec1);

        RectangleShape rec(Vector2f(tileSize, tileSize));
        rec.setFillColor(Color(200, 200, 200));

       

        int num = 0;
        int p = 0;  // поправка для того чтобы вырввнять по центру цифры
        for (int i = 0; i < gameSizeX; i++) {
            for (int j = 0; j < gameSizeY; j++)
            {
                num = game.get_map_vol(i, j);
                text.setString(std::to_string(num));

                int k = num; // центрирование числа
                while ((k = k / 10)) {
                    p -= tileSize/8;
                }


                rec.setFillColor(get_color(num));
                rec.setPosition(j*(tileSize+ betwinsize)+ betwinsize+ ramkasize, i * (tileSize + betwinsize) + betwinsize + ramkasize);
                window.draw(rec);

                if (num) {
                    text.setPosition(j * (tileSize + betwinsize) + betwinsize + ramkasize +5*tileSize/12 +p, i * (tileSize + betwinsize) + betwinsize + ramkasize + tileSize / 4 );
                    text.setCharacterSize(30);
                    window.draw(text);
                }
                p = 0;
            }

        }

        CircleShape tr(10.f, 3), tr1(10.f, 3), tr2(10.f, 3), tr3(10.f, 3);
        tr.setPosition(30, width - 70);
        tr1.setPosition(50, width - 20);
        tr1.rotate(180);
        tr2.setPosition(65, width - 55);
        tr2.rotate(90);
        tr3.setPosition(15, width - 35);
        tr3.rotate(-90);
        Color col(170, 170, 170);
        tr.setFillColor(col);
        tr1.setFillColor(col);
        tr2.setFillColor(col);
        tr3.setFillColor(col);

        Color dark(100, 100, 100);
        switch (pressedKey)
        {
        case 0:
            break;
        case 1:
            tr3.setFillColor(Color(100, 100, 100));
            break;
        case 2:
            tr2.setFillColor(Color(100, 100, 100));
            break;
        case 3:
            tr.setFillColor(Color(100, 100, 100));
            break;
        case 4:
            tr1.setFillColor(Color(100, 100, 100));
            break;
        default:
            break;
        }

        window.draw(tr);
        window.draw(tr1);
        window.draw(tr2);
        window.draw(tr3);


        if (game.is_game_end()) {

            rec1.setFillColor(Color(200, 200, 200, 200));
            rec1.setPosition(0, 0);
            rec1.setSize(Vector2f(height, width));
            window.draw(rec1);

            text.setString("Game end\npress R");
            text.setPosition(height/4, 2*width/5);
            window.draw(text);

        }

        
}
Color WindowManager::get_color(int num) {
    Color col;
    switch (num)
    {
    case 0:
        col = Color(150, 150, 150);
        break;
    case 2:
        col = Color(200, 200, 200);
        break;
    case 4:
        col = Color(100, 200, 200);
        break;
    case 8:
        col = Color(200, 150, 200);
        break;
    case 16:
        col = Color(200, 200, 150);
        break;
    case 32:
        col = Color(150, 150, 200);
        break;
    case 64:
        col = Color(200, 150, 150);
        break;
    case 128:
        col = Color(150, 200, 150);
        break;
    default:
        col = Color(200, 200, 250);

        break;
    }
    return col;
}

void WindowManager::drawFrame() {

    window.clear(Color(200,200,200));
    drawGame();
    window.display();
}
void WindowManager::controlButtons(Event ev) {

    if (ev.type == Event::KeyPressed) {



        if (ev.key.code == Keyboard::R) {
            restartGame(); 
        }
        if (ev.key.code == Keyboard::Left) {
            game.left();
            pressedKey = 1;
        }
        if (ev.key.code == Keyboard::Right) {
            game.right();
            pressedKey = 2;
        }
        if (ev.key.code == Keyboard::Up) {
            game.up();
            pressedKey = 3;
        }
        if (ev.key.code == Keyboard::Down) {
            game.down();
            pressedKey = 4;
        }
        
        
        if (ev.key.code == Keyboard::A) {
            changeSize(-1);
        }
        if (ev.key.code == Keyboard::D) {
            changeSize(+1);
        }
    }
    
   

}
void WindowManager::createWindow(int wight, int height) {
    window.clear();
    if (wight < 1) {
        wight = 1;
    }
    if (height < 1) {
        height = 1;
    }
    window.create(VideoMode(wight, height), L"2048", Style::Default);
}

void WindowManager::restartGame() {
    
    game.restart();
    pressedKey = 0;
}