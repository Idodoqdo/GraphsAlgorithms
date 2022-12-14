#ifndef SRC_S21_RAND_GENERATOR_H_
#define SRC_S21_RAND_GENERATOR_H_
#include <random>

namespace s21 {

class RandomNumberGenerator {
    public:
    RandomNumberGenerator() : gen_(rd_()) {};
    int GenerateRandomValue(size_t range) {
       std::uniform_int_distribution<> distrib(0, static_cast<int>(range));
       return distrib(gen_);
    }
    double GenerateRandomChance() {
       std::uniform_real_distribution<double> distrib (0, 1);
       return distrib(gen_);
    } 
    private:
    std::random_device rd_;
    std::mt19937 gen_;
 };
}
#endif  // SRC_S21_RAND_GENERATOR_H_