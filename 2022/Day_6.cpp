// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <deque>
#include <set>
using namespace std;

template <typename T, int MaxLen, typename Container = std::deque<T>>
class FixedQueue : public std::queue<T, Container> {
public:
    void push(const T& value) {
        if (this->size() == MaxLen) {
            this->c.pop_front();
        }
        std::queue<T, Container>::push(value);
    }

    bool isFull()
    {
        return this->size() == MaxLen;
    }
};
void printQueue(queue<char> fixedQueue)
{
    string queueString;
    while (!fixedQueue.empty())
    {
        queueString.push_back(fixedQueue.front());
        fixedQueue.pop();
    }
    cout << queueString << endl;
}

bool hasUniqueElements(FixedQueue<char, 14> fixedQueue)
{
    queue<char> tempQueue = queue<char>(fixedQueue);
    set<char> charSet;
    bool unique = true;
    while (!tempQueue.empty())
    {
        charSet.insert(tempQueue.front());
        tempQueue.pop();
    }
    return charSet.size() == 14;

}

int main()
{
    string filePath = "aoc_day6.txt";
    ifstream inputFile(filePath);
    string line;

    // Fixed queue of size 14
    FixedQueue<char, 14> fixedQueue;
    if (inputFile.is_open())
    {

        while (inputFile)
        {
            std::getline(inputFile, line);

            if (!line.empty())
            {
                for (int i = 0; i < line.length(); i++)
                {
                    char ch = line[i];
                    fixedQueue.push(ch);
                    if (fixedQueue.isFull() && hasUniqueElements(fixedQueue))
                    {
                        printQueue(fixedQueue);
                        cout << "Mark begins at " << i + 1 << endl;
                    }
                }
            }

        }

        // close our file
        inputFile.close();

    }

}