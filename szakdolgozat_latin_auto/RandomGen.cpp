#include "RandomGen.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <streambuf>
#include <string>

using namespace std;

void RandomGen::Getrandom(vector<int>& rvector, int inputhossz)
{
    cout << "GENERATING RANDOM NUMBERS" << endl;
    unsigned int seed = 0;
    
    ifstream infile("seed.txt");
    string input((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    seed = stoi(input);
    infile.close();


    //Randomszámok generálása vectorba
    srand(seed);
    rvector.clear();
    for (int i = 0; i < inputhossz * 4; i++)
    {
        rvector.push_back(rand() % 15);
    }
}