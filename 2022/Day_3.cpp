// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


void iterateThroughAlphabet(const string& albet, unordered_map<string, int>& map, int& priorityValue)
{
    for (int i = 0; i < albet.length(); i++)
    {
        char packageLetter = albet[i];
        string charString;
        charString.push_back(packageLetter);
        map[charString] = priorityValue;
        priorityValue++;
    }
}

void generatePriorityMap(unordered_map<string, int> &map)
{
    const string albet_lower{ "abcdefghijklmnopqrstuvwxyz" };
    const string albet_upper{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    // start at one
    int priorityValue = 1;
    iterateThroughAlphabet(albet_lower, map, priorityValue);
    iterateThroughAlphabet(albet_upper, map, priorityValue);

}

void findBadgeItem(vector<string> elfGroup, string &commonItem)
{
    // can always assume we have 3 elements
    string firstGroup = elfGroup.at(0);
    string secondGroup = elfGroup.at(1);
    string thirdGroup = elfGroup.at(2);

    for (int i = 0; i < firstGroup.length(); i++)
    {
        char item = firstGroup[i];
        if (secondGroup.find(item) != string::npos && thirdGroup.find(item) != string::npos)
        {
            commonItem.push_back(item);
            break;
        }
    }
}


void findCommonPackage(const string& compartment, string &commonPackage, bool noDupe)
{
    string firstHalf = compartment.substr(0, compartment.length() / 2);
    string secondHalf = compartment.substr(compartment.length() / 2);
    for (int i = 0; i < firstHalf.length(); i++)
    {
        char packageChar = firstHalf[i];
        if (secondHalf.find(packageChar) != string::npos)
        {
            commonPackage.push_back(packageChar);
            if (noDupe)
            {
                break;
            }
        }
    }
}


int main()
{
    string filePath = "aoc_day3.txt";
    ifstream inputFile(filePath);
    string line;

    unordered_map<string, int> priorityValueUM;
    vector <string> elfGroup;
    generatePriorityMap(priorityValueUM);

    int sum = 0;
    int elfCount = 1;
    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);
            string commonItem;
            if (elfCount % 3 == 0)
            {
                elfGroup.push_back(line);
                // do sum check here
                findBadgeItem(elfGroup, commonItem);
                sum += priorityValueUM[commonItem];
                cout << "Badge found: " << commonItem << endl;
                // clear elf group
                elfGroup.clear();
            }
            else
            {
                elfGroup.push_back(line);
            }
            elfCount++;
        }

        // close our file
        inputFile.close();
    }

    cout << "Final sum is " << sum << endl;

}
