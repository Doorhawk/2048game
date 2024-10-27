#include "random.h"
#include <vector>

class Game2048 : Random {

private:

    int n;
    int m;


    std::vector<std::vector<int>> map;       // карта игры 4х4 клетки
    int score;       // счет игрока
    int record;      // максимальный счет за сессию
    bool map_change; // изменилась ли карта после нажатия кнопки
    int turn_counter;


    void spawn_random_cell();
    void after_move();

public:
    
    Game2048();
    void restart();
    void fullrestart();

    void up();
    void down();
    void left();
    void right();

    std::vector<int> get_size();

    void setNewSize(int, int);

    int get_map_vol(int i, int j);

    bool is_game_end();
    int get_turn_count();
    int get_score();
    int get_record();
    
    bool get_map_change();
};