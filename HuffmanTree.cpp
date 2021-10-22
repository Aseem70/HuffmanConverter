//Justin Delgado

#include "HuffmanTree.hpp"
#include "TestStrings.hpp"

HuffmanTree::~HuffmanTree()
{

}

//Create a frequency map of each character in the string
std::map<char, freq> HuffmanTree::mapFrequencies(std::string input)  //freq == int
{
    std::map<char, freq> frequencyMap;

    for(char &c : input)
    {
        if(frequencyMap.find(c) != frequencyMap.end())
        {
            frequencyMap[c]++;
        }
        else
        {
            frequencyMap[c] = 1;
        }
    }

    return frequencyMap;

}


HeapQueue <HuffmanNode*, HuffmanNode::Compare>  HuffmanTree::priorityFrequency(std::map<char, freq> freqMap)
{   
    
    HeapQueue <HuffmanNode*, HuffmanNode::Compare> priorityQueue;

    std::map<char, freq>::iterator it = freqMap.begin();

    
    while(it != freqMap.end())
    {
        HuffmanNode* insertNode = new HuffmanNode(it->first, it->second);
        priorityQueue.insert(insertNode);
        it++;
    }
    
    return priorityQueue;

}


HuffmanNode* HuffmanTree::constructTree(HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue)
{
    while (priorityQueue.size() != 1)
    {
        //pop top two nodes
        HuffmanNode* leftChild = priorityQueue.min();
        priorityQueue.removeMin();
        HuffmanNode* rightChild = priorityQueue.min();
        priorityQueue.removeMin();

        //Add together their frequencies
        int combinedFrequency = leftChild->getFrequency() + rightChild->getFrequency();

        //Link the new nodes together
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFrequency, nullptr, leftChild, rightChild); 
        //Tilde is for internal nodes only
        
        priorityQueue.insert(newNode);
    }

    

    //return new root node
    return priorityQueue.min();
}

void HuffmanTree::createCharCode(HuffmanNode* root, std::map<char, code>& huffMap, std::string huffCode)
{
    if (root == NULL)
    {
        return;
    }
    if(root->getCharacter() != '\0')
    {
        huffMap[root->getCharacter()] = huffCode;
    }
    
    createCharCode(root->left, huffMap, huffCode + '0');
    createCharCode(root->right, huffMap, huffCode + '1');
}

std::string HuffmanTree::convertString(std::string stringToConvert, std::map<char, code> huffMap)
{
    std::string convertedString;

    for(char &c : stringToConvert)
    {
        convertedString += huffMap[c];
    }

    return convertedString;

}

//reference operator allows me to build on the same string
//constant because SerializeTree() is constant
void HuffmanTree::serialVisit(HuffmanNode* root, std::string& serializeString) const 
{
    if (root == NULL)
    {
        return;
    }
    if(root->isBranch())
    {
        serialVisit(root->left, serializeString);
    }
    if(root->isBranch())
    {
        serialVisit(root->right, serializeString);
    }

    if(root->isBranch())
    {   
        serializeString += 'B';
    }
    if(root->isLeaf())
    {
        serializeString += "L";
        serializeString += root->getCharacter();
    }
}

HuffmanNode* HuffmanTree::deserializeTree(std::string serialized)
{
    std::stack<HuffmanNode*> stack;
    HuffmanNode* newNode;
    HuffmanNode* rightChild;
    HuffmanNode* leftChild;

    for(long long unsigned int i = 0; i < serialized.length(); i++)
    {
        if (serialized[i] != '\\')
        {
            if((serialized[i] == 'B' && serialized[i-1] != 'L') || (serialized[i] == 'B' && serialized[i-1] == 'L' && serialized[i - 2] == 'L'))
            {
                rightChild = stack.top();
                stack.pop();
                leftChild = stack.top();
                stack.pop();
                newNode = new HuffmanNode('\0', 0, nullptr, leftChild, rightChild);
                stack.push(newNode); 
            }
            else if(serialized[i-1] == 'L')
             {
            if (!(serialized[i] == 'B' && serialized[i - 1] == 'L' && serialized[i-2] == 'L'))
            {
                newNode = new HuffmanNode(serialized[i], 0);
                stack.push(newNode);
            }

            }
        }
    } //end for loop

   

    return stack.top();
}

std::string HuffmanTree::convertCompressed(std::string compressed, HuffmanNode* root)
{
    HuffmanNode* traversalNode = root;
    std::string translatedString;

    

    for(char x: compressed)
    {

        if(x == '0')
        {
            traversalNode = traversalNode->left;
        }
        if(x == '1') 
        {
            traversalNode = traversalNode->right;
        }

        if(traversalNode->isLeaf())
        {
            translatedString += traversalNode->getCharacter();
            traversalNode = root;
        }

    } // end for loop

    return translatedString;

}

std::string HuffmanTree::compress(const std::string inputStr)
{
    std::map<char, int> frequencyMap = mapFrequencies(inputStr);
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue = priorityFrequency(frequencyMap);
    setRootNode(constructTree(priorityQueue));
    std::map<char, code> huffMap;
    createCharCode(getRootNode(), huffMap, "");
    return convertString(inputStr, huffMap);
    
}

std::string HuffmanTree::serializeTree() const
{
    std::string returnString;

    serialVisit(root, returnString);
    
    return returnString;
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree)
{
    //will take that funky string and re-create the tree
    //using the inputString, we'll keep running through the tree to reconstruct the message
    HuffmanNode* newRoot;
    newRoot = deserializeTree(serializedTree);
    return convertCompressed(inputCode, newRoot);

}

