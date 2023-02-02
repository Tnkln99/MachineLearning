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

        for(int i=0;i<content.size();i++)
        {
            try{
                pair<float,float> x_y;
                x_y.first = stof(content[i][0]);
                x_y.second = stof(content[i][1]);
                result.push_back(x_y);
            }
            catch(...){

            }
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
            som += pow(h_x , y_i);
        }
        return som / (2*sizeOfDataSet);
    };

    static pair<double, double> gradient(double q0, double q1)
    {
        pair<double, double> result;
        return result;
    };

    static void createModel(const vector<pair<float, float>>& dataSet)
    {
        double lastCost = Functions::cost(0,0,dataSet);
        pair<double, double> newThetas = Functions::gradient(0,0);
        double newCost = Functions::cost(newThetas.first, newThetas.second, dataSet);
        while(newCost - lastCost > 0.0001f)
        {
            lastCost = newCost;
            newThetas = Functions::gradient(newThetas.first, newThetas.second);
            newCost = Functions::cost(newThetas.first, newThetas.second, dataSet);
        }
    };
};


#endif //MACHINELEARNING_FUNCTIONS_H
