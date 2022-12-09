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

struct node {
    string key; //dirname
    int size; // size of gb
    vector<node*> children;
    node* parent;
};

node* newNode(string key, int size, node* parent)
{
    node* temp = new node;
    temp->key = key;
    temp->size = size;
    temp->parent = parent;
    return temp;
}


void getDirectoryTotalSize(node* root, int threshold, int& size)
{
    if (root && !root->children.empty())
    {
        if (root->size <= threshold)
        {
           // cout << "Found dir " << root->key << " with size " << root->size << endl;
            size += root->size;
        }
        for (auto& child : root->children)
        {
            getDirectoryTotalSize(child, threshold, size);
        }
    }

}

void propagateSize(node& node, int size)
{
    node.size += size;
    if (node.parent)
    {
        propagateSize(*node.parent, size);
    }
}

node* findNode(node* root, string key, bool current = false)
{
    node* foundNode = nullptr;
    if (!root)
    {
        return foundNode;
    }
    else if (root->key == key && !current)
    {
        return root;
    }
    else
    {
        for (auto& child : root->children)
        {
            node* temp = findNode(child, key);
            if (temp)
            {
                foundNode = temp;
            }
        }   
    }

    return foundNode;
}

void printSubtree(node* root, const std::string& prefix) {
    using std::cout;
    using std::endl;
    if (root->children.empty()) return;
    cout << prefix;
    size_t n_children = root->children.size();
    cout << (n_children > 1 ? "|-- " : "");

    for (size_t i = 0; i < n_children; ++i) {
        node* c = root->children[i];
        if (i < n_children - 1) {
            if (i > 0) { // added fix
                cout << prefix << "|-- "; // added fix
            } // added fix
            bool printStrand = n_children > 1 && !c->children.empty();
            std::string newPrefix = prefix + (printStrand ? "|\t" : "\t");
            std::cout << c->key << " : " << c->size << endl;
            printSubtree(c, newPrefix);
        }
        else {
            cout << (n_children > 1 ? prefix : "") << "|-- ";
            std::cout << c->key << " : " << c->size << endl;
            printSubtree(c, prefix + "\t");
        }
    }
}

void printTree(node* root) {
    using std::cout;
    std::cout << root->key << " : " << root->size << "\n";
    printSubtree(root, "");
    cout << "\n";
}

void generateTree(const string& filePath, node& root)
{
    ifstream inputFile(filePath);
    string line;
    node* currentRoot = &root;
    if (inputFile.is_open())
    {
        while (inputFile)
        {
            std::getline(inputFile, line);
            if (!line.empty())
            {
                //node* newNode;

                string cd = "$ cd ";
                string dir = "dir ";
                int cd_len = cd.length();
                int dir_len = dir.length();

                size_t cd_pos = line.find(cd);
                size_t dir_pos = line.find(dir);
                
                if (dir_pos != string::npos)
                {
                    string childNodeKey = line.substr(dir_pos + dir_len);
                    node* childNode = newNode(childNodeKey, 0, currentRoot);
                    currentRoot->children.push_back(childNode);
                }
                // create new node with digit, update parent value too
                else if (isdigit(line[0]))
                {
                    string delimiter = " ";
                    int size = stoi(line.substr(0, line.find(delimiter)));
                    string key = line.substr(line.find(delimiter) + 1);
                    node* temp = newNode(key, size, currentRoot);
                    propagateSize(*currentRoot, size);
                    currentRoot->children.push_back(temp);
                }
                
                else if (cd_pos != string::npos)
                {
                    string parentDir = line.substr(cd_pos + cd_len);
                    if (parentDir.find("..") == string::npos)
                    {
                        currentRoot = findNode(currentRoot, parentDir, true);
                    }
                    else
                    {
                        node* temp = currentRoot;
                        currentRoot = currentRoot->parent ? currentRoot->parent : &root;
                        //cout << "Going up a level from " << temp->key << " to " << currentRoot->key << endl;       
                    }
                }
            }
        }


        inputFile.close();
    }

}

void getTotalUsedSpace(node* root, int& totalSize)
{
    if (root->children.empty())
    {
        totalSize += root->size;
    }
    else
    {
        for (auto& child : root->children)
        {
            getTotalUsedSpace(child, totalSize);
        }
    }
}

void findSmallestNode(node* root, int min, int& smallestNodeSize)
{
    int currentNodeSize = root->size;

    if (currentNodeSize >= min && currentNodeSize < smallestNodeSize && !root->children.empty())
    {
        smallestNodeSize = currentNodeSize;
    }

    for (auto& child : root->children)
    {
        findSmallestNode(child, min, smallestNodeSize);
    }
 
}

int main()
{
    string filePath = "\aoc_day7.txt";
    node* root = newNode("/", 0, nullptr);

    generateTree(filePath, *root);

    int maxStorage = 70000000;
    int minUnusedNeeded = 30000000;
    int totalUsed = 0;
    getTotalUsedSpace(root, totalUsed);
    
    int threshold = 100000;
    int partOneSize = 0;
    getDirectoryTotalSize(root, threshold, partOneSize);

    printTree(root);
    cout << "The sum of all directories with max size of " << threshold << " is " << partOneSize << endl;
    cout << "Total size: " << totalUsed << endl;
    
    int remainingSpace = maxStorage - totalUsed;
    int minSpaceToDelete = minUnusedNeeded - remainingSpace;

    int smallestNodeSize = maxStorage;
    findSmallestNode(root, minSpaceToDelete, smallestNodeSize);

    cout << "Remaining space: " << remainingSpace << endl;
    cout << "Need at least: " << minSpaceToDelete << endl;
    cout << "Size of dir to delete: " <<smallestNodeSize <<endl;
    bool enoughSpace = remainingSpace >= minUnusedNeeded;

    cout << "Is there enough unused space: " << enoughSpace << endl;

}