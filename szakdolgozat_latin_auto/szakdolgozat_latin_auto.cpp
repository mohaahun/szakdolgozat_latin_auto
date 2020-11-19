// szakdolgozat_latin_auto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Kodolo.h"
#include "Dekodolo.h"
#include <string>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <streambuf>

using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now(); //start timer

    ifstream infile("input.txt");
    string input((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());

    Kodolo k;
    k.GetTitkosSzoveg(input);
    infile.close();

    auto stop = chrono::high_resolution_clock::now(); //stop timer
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Total Runtime: " << duration.count() << "microseconds" << endl;
    _getch();
    return 0;
}
