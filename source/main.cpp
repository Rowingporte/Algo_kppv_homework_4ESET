#include "Data.h"
#include <filesystem>

int main() {
    Data test;
    test.load("../../donnees/Test/test.svm");
    test.toString();
    return 0;
}