#include "Dekodolo.h"
#include "RandomGen.h"
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <conio.h>
#include <fstream>
#include <streambuf>

using namespace std;



void Dekodolo::GetDekodoltSzoveg(string coded)
{
	cout << "DECODING IN PROGRESS" << endl;
	vector<int> randszamok;
	RandomGen randomgen;
	string output;

	randomgen.Getrandom(randszamok, coded.length()); ////Randomgenerátor meghívása
	Dekodolo::GetDekodoloMx();		//Dekódolómátrix meghívása
	output = Dekodolo::Visszafejtes(coded, randszamok);		//Visszafejtesi algoritmus

	ofstream decodedfile("decoded.txt");
	decodedfile << output;
	decodedfile.close();

}


//Visszafejtesi algoritmus
string Dekodolo::Visszafejtes(string input, vector<int> randszamok)
{
	//Bekért input bináris stringgé alakítása
	string binary_input;
	for (unsigned int i = 0; i < input.size();i++)
	{
		bitset<8> b(input.c_str()[i]);
		binary_input += b.to_string();
	}


	//4 bites szeletekre vágás és a szeletek integerré alakítása
	vector <unsigned int> binarytoint;
	for (unsigned int i = 0; i < binary_input.size() / 4;i++)
	{
		string chunk = "";
		for (int j = 0; j < 4;j++)
		{
			chunk.push_back(binary_input[(i * 4) + j]);
		}

		binarytoint.push_back(stoi(chunk, 0, 2));
	}


	//Dekódolási eljárás
	for (unsigned int i = 0;i < 4;i++) //Hányszor fut le a kódolás
	{
		for (unsigned int j = 0;j < binarytoint.size();j++) //Hány elemre fut a kódolás
		{
			binarytoint[j] = decoder[randszamok[((j * 2) + 1)]][binarytoint[j]];
			binarytoint[j] = decoder[randszamok[(j * 2)]][binarytoint[j]];
		}
	}


	//Dekódolt értékek egybefüggõ bináris stringgé alakítása
	string crypto_binary = "";
	for (unsigned int i = 0;i < binarytoint.size();i++)
	{
		crypto_binary.append(bitset<4>(binarytoint[i]).to_string());
	}


	//Dekódolt bináris string szöveges formára hozása
	string output = "";
	for (unsigned int i = 0;i < crypto_binary.size() / 8;i++)
	{
		bitset<8> b1(crypto_binary, i * 8, 8);
		output += static_cast<unsigned char>(stoi(b1.to_string(), nullptr, 2));
	}
	return output;
}

//Dekódolómátrix meghívása
void Dekodolo::GetDekodoloMx()
{
	for (int x = 0;x < 16;x++)
	{
		for (int y = 0;y < 16;y++)
		{
			decoder[x][coder[x][y]] = y;
		}
	}
}