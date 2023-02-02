#include "Functions.h"

int main() {
    vector<pair<float,float>> dataSet = Functions::readFile("data/test.csv");
    Functions::createModel(dataSet);

    return 0;
}
