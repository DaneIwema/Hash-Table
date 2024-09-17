// Implementation file for the Dictionary class
// Stores data in a basic binary search tree
// By Mary Elaine Califf

#include "Dictionary.h"

Dictionary& Dictionary::operator=(const Dictionary& rhs)
{
    if (this != &rhs)
    {
        clear();
        copy(rhs);
    }
    return *this;
}

void Dictionary::addEntry(Entry* anEntry)
{
    // call private recursive insert method
    insert(anEntry, root);
}

Entry* Dictionary::findEntry(string key) const
{
    Node* curNode = root;
    while (curNode && curNode->data->getKey() != key)
    {
        if (curNode->data->getKey() > key)
        {
            curNode = curNode->left;
        }
        else
        {
            curNode = curNode->right;
        }
    }
    if (curNode)
        return curNode->data;
    else
        return nullptr;
}

void Dictionary::printDictionaryInOrder(ostream& outputStream) const
{
    if (root)
        printInOrder(outputStream, root);
}

void Dictionary::printDictionaryKeys(ostream& outputStream) const
{
    if (root)
        printTree(outputStream, root, 0);
}

// this is doing a postOrder traversal of the tree, deleting the Entry and then Node in each node of the tree
// the Dictionary is taking responsibility for the Entry objects, because they have to be dynamically allocated
// and only the tree has them all
void Dictionary::clear(Node* node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node->data;
        delete node;
    }
}

// this is doing a postOrder traversal of the original tree, making a copy of each node
Dictionary::Node* Dictionary::copy(Dictionary::Node* origNode)
{
    if (origNode)
    {
        // recursively copy the left and right subtrees
        Node* newLeft = copy(origNode->left);
        Node* newRight = copy(origNode->right);

        Entry* newData = new Entry(*(origNode->data)); // copies the Entry from the original node

        Node* node = new Node(newData);
        node->left = newLeft;
        node->right = newRight;

        return node;
    }
    else
    {
        return nullptr;
    }
}

// if we get here, curNode exists
// recursive insert 
void Dictionary::insert(Entry* value, Node*& curPtr)
{
    if (!curPtr) // this is where the item goes
        curPtr = new Node(value);
    else if (value->getKey() < curPtr->data->getKey()) // heading left
        insert(value, curPtr->left);
    else // heading right
        insert(value, curPtr->right);
    
    balance(curPtr);
}

// this is doing an inOrder traversal of the tree, calling printEntry on each entry in the tree
void Dictionary::printInOrder(ostream& outputStream, Node* curNode) const
{
    if (curNode->left)
        printInOrder(outputStream, curNode->left);
    curNode->data->printEntry(outputStream);
    if (curNode->right)
        printInOrder(outputStream, curNode->right);
}

// this is doing a preOrder traversal of the tree, printing it out in a way that shows the structure
void Dictionary::printTree(ostream& outputStream, Node* curNode, int depth) const
{
    for (int i = 0; i < depth; i++)
    {
        outputStream << "  ";
    }
    outputStream << curNode->data->getKey() << "\n";
    if (curNode->left)
    {
        printTree(outputStream, curNode->left, depth + 1);
    }
    if (curNode->right)
    {
        printTree(outputStream, curNode->right, depth + 1);
    }
}

// method for balancing the node
void Dictionary::balance(Node*& node) {
    if (node == nullptr)
        return;

    if(height(node->left) - height(node->right) > 1)
        if(height(node->left->left) >= height(node->left->right))
            rotateLeftChild(node);
        else
            doubleLeftChild(node);
    else if (height(node->right) - height(node->left) > 1)
        if(height(node->right->right) >= height(node->right->left))
            rotateRightChild(node);
        else
            doubleRightChild(node);

    node->height = max(height(node->left), height(node->right)) + 1;
}

// single left rotation
void Dictionary::rotateLeftChild(Node*& node2) {
    Node* node1 = node2->left;
    node2->left = node1->right;
    node1->right = node2;
    node2->height = max( height(node2->left), height(node2->right)) + 1;
    node1->height = max( height(node1->left), height(node1->right)) + 1;
    node2 = node1;
}

// double left rotation
void Dictionary::doubleLeftChild(Node*& node3) {
    rotateRightChild(node3->left);
    rotateLeftChild(node3);
}

//single right rotation
void Dictionary::rotateRightChild(Node*& node2) {
    Node* node1 = node2->right;
    node2->right = node1->left;
    node1->left = node2;
    node2->height = max( height(node2->left), height(node2->right)) + 1;
    node1->height = max( height(node1->left), height(node1->right)) + 1;
    node2 = node1;
}

// double right rotation
void Dictionary::doubleRightChild(Node*& node3) {
    rotateLeftChild(node3->right);
    rotateRightChild(node3);
}