#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <stack>
//#include <iostream>


typedef int freq;
typedef std::string code;

class HuffmanTree : public HuffmanTreeBase {
    public:

        HuffmanTree(): root(nullptr) {};

        //Constructor for Tree with a root
        HuffmanTree(HuffmanNode* r) : root(r) {};
        ~HuffmanTree();

        //Functions we have to implement
        virtual std::string compress(const std::string inputStr);
        virtual std::string serializeTree() const;
        virtual std::string decompress(const std::string inputCode, const std::string serializedTree);

        //modify root node
        void setRootNode(HuffmanNode* node) {this->root = node;};

        //get root node
        HuffmanNode* getRootNode(){return root;};

        // Methods for compression

        //convert string of chars into a map of char frequencies
        std::map<char, freq> mapFrequencies(std::string input);

        //convert map of char frequencies into a priority queue
        HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityFrequency(std::map<char, freq> freqMap);

        //Create a Huffman Tree using the priority queue
        //Will return the root node of the finished Tree!!
        HuffmanNode* constructTree(HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue);

        //gotta start at the root and iterate through the tree
        //Will produce a map that has the different characters and their respective Huffman Code
        void createCharCode(HuffmanNode* root, std::map<char, code>& huffMap, std::string huffCode);

        //converts the string into its characters. Can probably remove this because it's short
        std::string convertString(std::string stringToConvert, std::map<char, code> huffMap);

        //for visiting each node in the tree recursively
        void serialVisit(HuffmanNode* root, std::string& serializeString) const;

        //turn the serialized code back into a tree
        HuffmanNode* deserializeTree(std::string serialized);

        //convert the compressed text back into its original text
        std::string convertCompressed(std::string compressed, HuffmanNode* root);

    private:
        //root of the Huffman Tree
        //might not need these depending on how I construct this

        //initially set to nothin
        HuffmanNode* root = nullptr;

};

#endif /* HUFFMAN_H */