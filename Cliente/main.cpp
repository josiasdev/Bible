#include "user.h"
#include <iostream>

int main() {
    User user;
    std::string verse, translation;

    std::cout << "Digite o versículo que deseja procurar: ";
    std::getline(std::cin, verse);
    std::cout << "Digite a tradução da Bíblia: ";
    std::getline(std::cin, translation);

    user.searchVerse(verse, translation);

    return 0;
}
