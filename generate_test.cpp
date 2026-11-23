#include <fstream>
#include <iostream>
#include <random>

constexpr int NUM_REF_STR = 50;
constexpr int REF_STR_LEN= 30;
constexpr int NUM_PAGES = 8;
constexpr int FRAME_SIZE = 3;     

int main() {
    std::ofstream out("TestingData.txt");

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> pd(0, NUM_PAGES - 1);

    for (int i = 0; i < NUM_REF_STR; i++) {
        for (int pos = 0; pos < REF_STR_LEN; pos++) {
            out << pd(generator);
        }
        out << '\n';
    }

    out.close();

    // std::cout << "TestingData.txt generated successfully.\n";
    std::cout << "Reference strings: " << NUM_REF_STR << '\n';
    std::cout << "String length: " << REF_STR_LEN << '\n';
    std::cout << "Number of pages: " << NUM_PAGES << '\n';
    std::cout << "Configured frame size: " << FRAME_SIZE << '\n';

    return 0;
}
