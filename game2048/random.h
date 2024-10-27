#include <random>
class Random {
    std::random_device rd;  // Обеспечивает случайное зерно для генератора
    std::mt19937 gen;       // Создаем генератор Mersenne Twister
public:
    Random();  // Инициализируем генератор случайным значением от random_device
    int get_random_int(int min, int max);
    float get_random_float(float min, float max);
};