#ifndef SRC_S21_RAND_GENERATOR_H_
#define SRC_S21_RAND_GENERATOR_H_
#include <random>

namespace s21 {

class RandomNumberGenerator {
 public:
  RandomNumberGenerator() : gen_(rd_()){};
  int GenerateRandomInt(int lower_bound, int upper_bound) {
    std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
    return distrib(gen_);
  }
  double GenerateRandomDouble(int lower_bound, int upper_bound) {
    std::uniform_real_distribution<double> distrib(lower_bound, upper_bound);
    return distrib(gen_);
  }
  void SetSeed(std::uint_least32_t seed) {
    std::seed_seq seed_s{seed << 1, ~seed,     seed,      ~(seed << 4),
                         seed >> 1, seed & 16, seed << 5, seed | (seed << 5)};
    gen_ = std::mt19937(seed);
  }

 private:
  std::random_device rd_;
  std::mt19937 gen_;
};
}  // namespace s21
#endif  // SRC_S21_RAND_GENERATOR_H_