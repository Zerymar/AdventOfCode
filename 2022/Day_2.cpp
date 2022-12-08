// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;

/*
A  Rock         1
B  Paper        2
C  Scissors     3

X  Lose
Y  Tie
Z  Win

Score:
Loss   0
    - A : Z
    - B : X
    - C : Y
Tie    3
    - A : X
    - B : Y
    - C : Z
Win    6
    - A : Y
    - B : Z
    - C : X

*/


string getOpponentString(string line)
{
    string delimiter = " ";
    string opponent = line.substr(0, line.find(delimiter));
    return opponent;
}

int main()
{
    string filePath = "C:/Users/cesar/OneDrive/Documents/GitHub/AdventOfCode/2022/Files/aoc_day2.txt";
    ifstream inputFile(filePath);
    string line;

    set<string> tieSet;
    tieSet.insert("A X");
    tieSet.insert("B Y");
    tieSet.insert("C Z");

    set<string> winSet;
    winSet.insert("A Y");
    winSet.insert("B Z");
    winSet.insert("C X");


    unordered_map<string, string> lossMap;
    lossMap["A"] = "C";
    lossMap["B"] = "A";
    lossMap["C"] = "B";

    unordered_map<string, string> winMap;
    winMap["A"] = "B";
    winMap["B"] = "C";
    winMap["C"] = "A";

    unordered_map<string, int> pointMap;
    pointMap["A"] = 1;
    pointMap["B"] = 2;
    pointMap["C"] = 3;

    int totalScore = 0;

    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);

            string opponentPlay = getOpponentString(line);
            string myPlay;
            if (line.find("X") != string::npos)
            {
                myPlay = lossMap[opponentPlay];
                totalScore += pointMap[myPlay];
            }
            else if (line.find("Y") != string::npos)
            {
                totalScore += 3;
                totalScore += pointMap[opponentPlay];
            }
            else if (line.find("Z") != string::npos)
            {
                myPlay = winMap[opponentPlay];
                totalScore += 6;
                totalScore += pointMap[myPlay];
            }
        }

        cout << "Total score is " << totalScore << endl;
        // close our file
        inputFile.close();
    }

}