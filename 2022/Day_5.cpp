// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;


void GenerateStacks(unordered_map<int, stack<char>>& stacks)
{
    // Stack in reverse as we want last character to be on top
    vector<string> stackStrings;
    stackStrings.push_back("RSLFQ");
    stackStrings.push_back("NZQGPT");
    stackStrings.push_back("SMQB");
    stackStrings.push_back("TGZJHCBQ");
    stackStrings.push_back("PHMBNFS");
    stackStrings.push_back("PCQNSLVG");
    stackStrings.push_back("WCF");
    stackStrings.push_back("QHGZWVPM");
    stackStrings.push_back("GZDLCNR");

    for (int i = 0; i < stackStrings.size(); i++)
    {
        stack<char> stack;
        string stringStack = stackStrings.at(i);
        for (int j = 0; j < stringStack.length(); j++)
        {
            stack.push(stringStack[j]);
        }

        stacks[i + 1] = stack;
    }
}
// move X from A to B
void getTransactionInfo(const string& instruction, int& quantity, int& fromStack, int& toStack)
{
    stringstream ss;
    ss << instruction;

    int count = 0;
    string temp;
    int number;
    while (!ss.eof())
    {
        ss >> temp;
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> number)
        {
            switch (count) {
            case 0:
                quantity = number;
                count++;
                break;
            case 1:
                fromStack = number;
                count++;
                break;
            case 2: 
                toStack = number;
                count++;
                break;
            default:
                break;
            }

        }
    }
}


void getStackString(stack<char> stack, string& stackString)
{
    while (!stack.empty())
    {
        char item = stack.top();
        stack.pop();
        stackString.push_back(item);
    }

}

void printStacks(const unordered_map<int, stack<char>>& stacks)
{
    for (const auto& element : stacks)
    {
        string stackString;
        getStackString(element.second, stackString);
        std::cout << "Stack " << element.first << ": " << stackString << endl;
    }
}

void executeTransaction(unordered_map<int, stack<char>>& stacks, const int& quantity, const int& fromStackNum, const int& toStackNum)
{
    stack<char> fromStack = stacks[fromStackNum];
    stack<char> toStack = stacks[toStackNum];
    stack<char> tempStack;

    for (int i = 0; i < quantity; i++)
    {
        if (!fromStack.empty())
        {
            char item = fromStack.top();
            tempStack.push(item);
            fromStack.pop();
        } 
    }
    while (!tempStack.empty())
    {
        char item = tempStack.top();
        toStack.push(item);
        tempStack.pop();
    }


    stacks[fromStackNum] = fromStack;
    stacks[toStackNum] = toStack;
}

int main()
{
    string filePath = "aoc_day5.txt";
    ifstream inputFile(filePath);
    string line;

    unordered_map<int, stack<char>> stacks;
    GenerateStacks(stacks);
    std::cout << "Original Stacks" << endl;
    printStacks(stacks);
    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);

            if (!line.empty())
            {
                int quantity;
                int fromStackNumber;
                int toStackNumber;

                getTransactionInfo(line,quantity, fromStackNumber, toStackNumber);
                executeTransaction(stacks, quantity, fromStackNumber, toStackNumber);
            }

        }

        // close our file
        inputFile.close();
        std::cout << "Final stacks" << endl;
        printStacks(stacks);
    }

}