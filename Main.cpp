#include "Functions.h"

int main() {
    vector<pair<float,float>> dataSet = Functions::readFile("data/train.csv");
    Functions::createModel(dataSet);

    return 0;
}
