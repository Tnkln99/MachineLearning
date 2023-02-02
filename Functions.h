#ifndef MACHINELEARNING_FUNCTIONS_H
#define MACHINELEARNING_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <valarray>

using namespace std;

class Functions {
public:
    static vector<pair<float, float>> readFile(const string & fileName)
    {
        vector<pair<float, float>> result;
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file (fileName, ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();

                std::stringstream str(line);

                while(getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        }
        else
            cout<<"Could not open the file\n";

        for(auto & i : content)
        {
            try{
                pair<float,float> x_y;
                x_y.first = stof(i[0]);
                x_y.second = stof(i[1]);
                result.push_back(x_y);
            }
            catch(...){

            }
        }

        for(auto & pair : result)
        {
            cout << pair.first << " : " << pair.second << endl;
        }

        return result;
    };

    static double hx(double x, double q0, double q1)
    {
          return q0 + (q1 * x);
    };

    static double cost(double q0, double q1, const vector<pair<float, float>>& dataSet)
    {
        int sizeOfDataSet = dataSet.size();
        double som = 0;
        for(auto & pair : dataSet){
            double h_x = hx(pair.first, q0, q1);
            double y_i = pair.second;
            som += pow(h_x - y_i, 2);
        }
        return som / (2*sizeOfDataSet);
    };

    static pair<double, double> gradient(double q0, double q1, const vector<pair<float, float>>& dataSet)
    {
        double somQ0 = 0;
        double somQ1 = 0;
        for(auto & x_y : dataSet)
        {
            somQ0 += hx(x_y.first, q0, q1) - x_y.second;
            somQ1 += (hx(x_y.first, q0, q1) - x_y.second) * x_y.first;
        }

        pair<double, double> result;
        double alpha = 0.00001f;
        int sizeOfDataSet = dataSet.size();

        result.first = q0 - (alpha*1/sizeOfDataSet * somQ0);
        result.second = q1 - (alpha*1/sizeOfDataSet * somQ1);
        return result;
    };

    static void createModel(const vector<pair<float, float>>& dataSet)
    {
        double lastCost = Functions::cost(0,0,dataSet);
        pair<double, double> newThetas = Functions::gradient(0,0,dataSet);
        double newCost = Functions::cost(newThetas.first, newThetas.second, dataSet);

        int iterCount = 0;
        while(lastCost - newCost > 0.00001f)
        {
            lastCost = newCost;
            newThetas = Functions::gradient(newThetas.first, newThetas.second, dataSet);
            newCost = Functions::cost(newThetas.first, newThetas.second, dataSet);
            iterCount++;
        }
        cout << "Iteration: " << iterCount << endl;
        cout << "equation is " << newThetas.first << " + " << newThetas.second << "x"<< endl;
    };
};


#endif //MACHINELEARNING_FUNCTIONS_H
