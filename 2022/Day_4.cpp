// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    string filePath = "aoc_day4.txt";
    ifstream inputFile(filePath);
    string line;

    int subsetcount = 0;
    int overlapcount = 0;
    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);

            if (!line.empty())
            {
                string firstHalf = line.substr(0, line.find(","));
                string secondHalf = line.substr(line.find(",") + 1);

                int aStart = stoi(firstHalf.substr(0, firstHalf.find("-")));
                int aEnd = stoi(firstHalf.substr(firstHalf.find("-") + 1));

                int bStart = stoi(secondHalf.substr(0, secondHalf.find("-")));
                int bEnd = stoi(secondHalf.substr(secondHalf.find("-") + 1));

                if (aStart <= bStart && aEnd >= bEnd || bStart <= aStart && bEnd >= aEnd)
                {
                    subsetcount++;
                }
                if ( aStart <= bEnd && bStart <= aEnd)
                {
                    overlapcount++;
                }
            }

        }

        // close our file
        inputFile.close();
    }

    cout << "Final subset count is " << subsetcount << endl;
    cout << "Final overlap count is " << overlapcount << endl;

}