// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;


// add the elf information to the map and adjust counters
void addElfInfo(unordered_map<string, int>& elfMap, int& calorieCount, int& elfCount)
{
    string elfName = "elf" + std::to_string(elfCount);
    elfCount++;
    elfMap[elfName] = calorieCount;
    calorieCount = 0;
}

void printMap(unordered_map<string, int> umap)
{
    string maxValueKey = "";
    int maxValue = -1;
    for (auto x : umap)
    {
        string key = x.first;
        int value = x.second;
        cout << key << " : " << value << endl;

        // Quick and diry way to get the max value
        if (value > maxValue && value < 70613 && value < 68330 && value < 66862)
        {
            maxValue = value;
            maxValueKey = key;
        }
    }

    //70613
    cout << "Elf " << maxValueKey << " has the largest calorie count with " << maxValue << " calories!!" << endl;

}

int main()
{
    string filePath = "aoc_day1.txt";

    ifstream inputFile(filePath);
    string line;

    unordered_map<string, int> elfMap;

    int calorieCount = 0;
    int elfCount = 1;

    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);
            if (line.empty())
            {
                addElfInfo(elfMap, calorieCount, elfCount);
                
            }
            else
            {
                calorieCount += stoi(line);
            }
        }

        // Once we finish iterating, then we do a final add
        addElfInfo(elfMap, calorieCount, elfCount);
        // close our file
        inputFile.close();
    }

    printMap(elfMap);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
