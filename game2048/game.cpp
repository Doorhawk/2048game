
#include "game.h"





void Game2048::spawn_random_cell() {

        int sum_zero_cell = 0; // количество пустых точек

        int random_num = 2;
        if (get_random_int(1, 4) == 4) {
            random_num = 4;
        }
        // считаем
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (map[i][j] == 0)
                    sum_zero_cell++;



        // если нет пустых клеток то ничего не делаем  
        if (sum_zero_cell) {

            int random_zero_cell = get_random_int(1, sum_zero_cell);

            // ищем random_zero_cell по счету пустую клетку и заполняем ее 2
            int k = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (map[i][j] == 0)
                        k++;
                    if (k == random_zero_cell) {
                        map[i][j] = random_num;
                        break;
                    }
                }
                if (k == random_zero_cell) {
                    break;
                }
            }

        }
    }
    void Game2048::after_move() {



        turn_counter++;
        //if (map_change) {
        spawn_random_cell();
        //}
        if (record < score) {
            record = score;
        }



    }


    Game2048::Game2048() {

        

        n = 4;
        m = 4;

        map.resize(n);
        for (int i = 0; i < n; i++) {
            map[i].resize(m);
            for (int j = 0; j < n; j++) {
                map[i][j] = 0;
            }
        }



        turn_counter = 0;



        score = 0;
        record = 0;
        
        map_change = true;

        

        after_move();

    }
    void Game2048::restart() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                map[i][j] = 0;
            }
        }
        
        score = 0;
        map_change = true;
        after_move();
        turn_counter = 0;

    }
    void Game2048::fullrestart() {
        restart();
        record = 0;
        
        

    }

    void Game2048::setNewSize(int nn, int mm) {
        n = nn;
        m = mm;
        map.resize(n);
        for (int i = 0; i < n; i++) {
            map[i].resize(m, 0);
        }
        fullrestart();
    }
    std::vector<int> Game2048::get_size() {
        return { n,m };
    }
    void Game2048::up() {
        
        bool key = true;
        map_change = false;
        while (key) {
            key = false;
            for (int i = 1; i < n; i++) {

                for (int j = 0; j < m; j++) {

                    if (map[i][j] != 0) {

                        if (map[i - 1][j] == 0) {
                            map[i - 1][j] = map[i][j];
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                        else if (map[i - 1][j] == map[i][j]) {
                            score += map[i][j] * 2;
                            map[i - 1][j] *= 2;
                            map[i][j] = 0;
                            key = true;
                            map_change = true;

                        }
                    }
                }
            }
        }

        after_move();

    }
    void Game2048::down() {
        
        
        bool key = true;
        map_change = false;
        while (key) {
            key = false;
            for (int i = n - 2; i >= 0; i--) {

                for (int j = 0; j < m; j++) {

                    if (map[i][j] != 0) {

                        if (map[i + 1][j] == 0) {
                            map[i + 1][j] = map[i][j];
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                        else if (map[i + 1][j] == map[i][j]) {
                            score += map[i][j] * 2;
                            map[i + 1][j] *= 2;
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                    }
                }
            }
        }
        after_move();
    }
    void Game2048::left() {
        
        bool key = true;
        map_change = false;
        while (key) {
            key = false;
            for (int i = 0; i < n; i++) {

                for (int j = 1; j < m; j++) {

                    if (map[i][j] != 0) {

                        if (map[i][j - 1] == 0) {
                            map[i][j - 1] = map[i][j];
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                        else if (map[i][j - 1] == map[i][j]) {
                            score += map[i][j] * 2;
                            map[i][j - 1] *= 2;
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                    }
                }
            }
        }
        after_move();
    }
    void Game2048::right() {
        
        bool key = true;
        map_change = false;
        while (key) {
            key = false;
            for (int i = 0; i < n; i++) {

                for (int j = m - 2; j >= 0; j--) {

                    if (map[i][j] != 0) {

                        if (map[i][j + 1] == 0) {
                            map[i][j + 1] = map[i][j];
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                        else if (map[i][j + 1] == map[i][j]) {
                            score += map[i][j] * 2;
                            map[i][j + 1] *= 2;
                            map[i][j] = 0;
                            key = true;
                            map_change = true;
                        }
                    }
                }
            }
        }
        after_move();
    }

    int Game2048::get_map_vol(int i, int j) {
        return map[i][j];
    }

    bool Game2048::is_game_end() {
        bool have_cell_to_move = false;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {
                if (!map[i][j]) {
                    return false;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {

                if (i != n - 1) {
                    have_cell_to_move += map[i][j] == map[i + 1][j];
                }
                if (j != m - 1) {
                    have_cell_to_move += map[i][j] == map[i][j + 1];
                }
                if (i != 0) {
                    have_cell_to_move += map[i][j] == map[i - 1][j];
                }
                if (j != 0) {
                    have_cell_to_move += map[i][j] == map[i][j - 1];
                }
            }
        }
        return !have_cell_to_move;
    }

    int Game2048::get_score() {
        return score;
    }
    int Game2048::get_record() {
        return record;
    }
    int Game2048::get_turn_count() {
        return turn_counter;
    }

    bool Game2048::get_map_change() {
        return map_change;
    }

    
