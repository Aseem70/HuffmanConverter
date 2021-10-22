#ifndef HUFFMANBASE_H
#define HUFFMANBASE_H

#include <cstddef>
#include <string>
#include <iostream>

//class for each individual node
class HuffmanNode {
public:
  // intialize the node (char, frequency, node to left, node to right)
  HuffmanNode(char c, size_t f, HuffmanNode *p, HuffmanNode *l, HuffmanNode *r) : character(c), frequency(f), parent(p), left(l), right(r) {};

  //creating a leaf node with just a char and frequency
  HuffmanNode(char c, size_t f) : HuffmanNode(c, f, nullptr, nullptr, nullptr) {};

  //get the character associated with it
  char getCharacter() const;

  //get frequency of a particular node
  size_t getFrequency() const;

  //leaf node
  bool isLeaf() const;

  //branch node
  bool isBranch() const;

  //root node
  bool isRoot() const;


  class Compare {
  public:

    
    Compare(bool lessThan = true) : lessThan(lessThan) {};

    //comparing one node to another
    bool operator()(const HuffmanNode &n1, const HuffmanNode &n2) const;

    
    bool operator()(const HuffmanNode *n1, const HuffmanNode *n2) const;
  private:

    
    bool lessThan;
  };

//private and public variables
private:
  char character;
  size_t frequency;

public: 
  HuffmanNode *parent;
  HuffmanNode *left;
  HuffmanNode *right;
};



//Abstract class
class HuffmanTreeBase {
  public:
  virtual std::string compress(const std::string inputStr) = 0;
  virtual std::string serializeTree() const = 0;
  virtual std::string decompress(const std::string inputCode, const std::string serializedTree) = 0;
};

#endif /* HUFFMANBASE_H */
