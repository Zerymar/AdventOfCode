// CPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;

struct tree
{
    tree* north;
    tree* south;
    tree* east;
    tree* west;
    int scenicScore;
    int key;
};

bool isVisibleNorth(tree* current, int originalKey)
{
    bool visible = true;
    if (current->north)
    {
        // if true, keep going else, just return false
        visible = originalKey > current->north->key;
        if (visible)
        {
            visible = isVisibleNorth(current->north, originalKey);
        }
    }

    return visible;
}

bool isVisibleSouth(tree* current, int originalKey)
{
    bool visible = true;
    if (current->south)
    {
        // if true, keep going else, just return false
        visible = originalKey > current->south->key;
        if (visible)
        {
            visible = isVisibleSouth(current->south, originalKey);
        }
    }
    return visible;
}

bool isVisibleEast(tree* current, int originalKey)
{
    bool visible = true;
    if (current->east)
    {
        // if true, keep going else, just return false
        visible = originalKey > current->east->key;
        if (visible)
        {
            visible = isVisibleEast(current->east, originalKey);
        }
    }
    return visible;
}

bool isVisibleWest(tree* current, int originalKey)
{
    bool visible = true;
    if (current->west)
    {
        // if true, keep going else, just return false
        visible = originalKey > current->west->key;
        if (visible)
        {
            visible = isVisibleWest(current->west, originalKey);
        }
    }
    return visible;
}

bool isTreeVisible(tree& current)
{
    int originalKey = current.key;

    tree* ptr = &current;

    bool visible =  isVisibleEast(ptr, originalKey) || isVisibleNorth(ptr, originalKey) ||
        isVisibleWest(ptr, originalKey) || isVisibleSouth(ptr, originalKey);

    return visible;
}

tree* newTree(int key)
{
    tree* newTree = new tree;
    newTree->key = key;
    newTree->scenicScore = 0;

    // we dont care about surrounding trees when making a new one
    newTree->north = nullptr;
    newTree->south = nullptr;
    newTree->east = nullptr;
    newTree->west = nullptr;
    return newTree;
}

void setWestTree(tree& current, tree& west)
{
    current.west = &west;
    west.east = &current;
}

void setNorthTree(tree& current, tree& north)
{
    current.north = &north;
    north.south = &current;
}

void createGrid(string filePath, vector<vector<tree*>>& grid)
{
    ifstream inputFile(filePath);
    int row = 0;
    if (inputFile.is_open())
    {
        while (inputFile)
        {
            tree* northTree = nullptr;
            string line;
            std::getline(inputFile, line);
            if (!line.empty())
            {
                tree* westTree = nullptr;
                vector<tree*> columns;
                for (int i = 0; i < line.length(); i++)
                {
                    int treeKey = int(line[i] - '0');
                    tree* tree = newTree(treeKey);
                    if (westTree)
                    {
                        setWestTree(*tree, *westTree);
                    }

                    // get the tree in the north
                    if (row > 0)
                    {
                        northTree = grid[row - 1][i];
                        setNorthTree(*tree, *northTree);
                    }

                    columns.push_back(tree);
                    westTree = tree;
                }
                grid.push_back(columns);
            }

            row++;
        }

        inputFile.close();
    }
}

void printGrid(vector<vector<tree*>> grid)
{
    for (auto& row : grid)
    {
        for (auto& tree : row)
        {
            cout << tree->key;
        }
        cout << endl;
    }
}

void northScenic(tree* current, int& count, int originalKey)
{
    tree* adjacentTree = current->north;
    if (adjacentTree)
    {
        count++;
        int adjacentKey = adjacentTree->key;

        if (originalKey > adjacentKey)
        {
            northScenic(adjacentTree, count, originalKey);
        }
    }
}
void southScenic(tree* current, int& count, int originalKey)
{
    tree* adjacentTree = current->south;
    if (adjacentTree)
    {
        count++;
        int adjacentKey = adjacentTree->key;

        if (originalKey > adjacentKey)
        {
            southScenic(adjacentTree, count, originalKey);
        }
    }
}
void westScenic(tree* current, int& count, int originalKey)
{
    // current->key = 5;
    // west-> key = 5;
    tree* adjacentTree = current->west;
    if (adjacentTree)
    {
        count++;
        int adjacentKey = adjacentTree->key;

        if (originalKey > adjacentKey)
        {
            westScenic(adjacentTree, count, originalKey);
        }
    }
}
void eastScenic(tree* current, int& count, int originalKey)
{
    tree* adjacentTree = current->east;
    if (adjacentTree)
    {
        count++;
        int adjacentKey = adjacentTree->key;

        if (originalKey > adjacentKey)
        {
            eastScenic(adjacentTree, count, originalKey);
        }
    }
}



void calculateScenicScore(tree& current)
{
    int northCount = 0;
    int southCount = 0;
    int eastCount = 0;
    int westCount = 0;
    tree* ptr = &current;
    int originalKey = current.key;
    northScenic(ptr, northCount, originalKey);
    southScenic(ptr, southCount, originalKey);
    eastScenic(ptr, eastCount, originalKey);
    westScenic(ptr, westCount, originalKey);
    int totalScenic = (northCount * southCount * eastCount * westCount);
    current.scenicScore = totalScenic;

}

int main()
{
    string filePath = "aoc_day8.txt";
    ifstream inputFile(filePath);
    string line;

    vector<vector<tree*>> grid;
    // Width and Height are both grid.size() wide
    // Subtract four not to double count corners

    createGrid(filePath, grid);
    int visibleTreeCount = (grid.size() * 4) - 4;
    // we already counted the edges
    int startRowIndex = 1;
    int endRowIndex = grid.size() - 2; 

    int startColumnIndex = 1;
    int endColumnIndex = grid[endRowIndex].size() - 2;

    int maxScenicScore = -1;

    /*
    * PART 1*/
    for (int row = startRowIndex; row <= endRowIndex; row++)
    {
        for (int column = startColumnIndex; column <= endColumnIndex; column++)
        {
            tree* currentTree = grid[row][column];
            //cout << "Current tree is " << currentTree->key << endl;
            bool treeVisible = isTreeVisible(*currentTree);
            if (treeVisible)
            {
                visibleTreeCount++;
            }
        }
    }

    /* PART 2*/
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            tree* tree = grid[i][j];
            calculateScenicScore(*tree);
            if (tree->scenicScore > maxScenicScore)
            {
                maxScenicScore = tree->scenicScore;
            }     
        }
    }

    cout << "All visible trees: " << visibleTreeCount << endl;
    cout << "A tree has a scenic score of " << maxScenicScore << "!" << endl;
}