#pragma once

template <typename T>
BinaryTree<T>::BinaryTree(TreeType type) : root_(nullptr), treeType_(type) {}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    destroy(root_);
}

template <typename T>
void BinaryTree<T>::destroy(Node *node)
{
    if (!node)
    {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// case handler for insert depending on type of tree
template <typename T>
void BinaryTree<T>::insert(const T &item)
{
    if (treeType_ == TreeType::BST)
        root_ = insertBST(root_, item);
    else
    {
        root_ = insertLLRB(root_, item);
        root_->red = false;                 //root can never be red
    }
}

template <typename T>
int BinaryTree<T>::getHeight() const
{
    return height(root_);
}

// Find and return value associated with
// minimum key for both BST and LLRB
template <typename T>
const T *BinaryTree<T>::findMin() const
{
    if(root_ == nullptr)    //case empty
        return(nullptr);

    Node *min = findMinNode(root_); 
    return &(min->value);
}

// FindMinNode helper to find and return pointer to node with
// minimum key for both BST and LLRB
template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::findMinNode(Node *node) const
{
    if(!node)    //case empty
        return(nullptr);

    while(node->left != nullptr) //stop if reaches node with no left child
        node = node->left; 
    return (node); 
}

template <typename T>
int BinaryTree<T>::height(Node *node) const
{
    if (!node)
    {
        return 0;
    }
    const int left = height(node->left);
    const int right = height(node->right);
    return 1 + std::max(left, right);
}

// uses recursive approach to locate area to add node, insert there
template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertBST(Node *node, const T &item)
{
    if (!node)
    {
        return new Node(item, false);
    }
    if (item < node->value)
    {
        node->left = insertBST(node->left, item);
    }
    else if (node->value < item)
    {
        node->right = insertBST(node->right, item);
    }
    else
    {
        node->value = item;
    }
    return node;
}

// insert item for LLRB while maintaining LLRB properties
template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertLLRB(Node *node, const T &item)
{
    if(!node)   //case empty
        return new Node(item, true);

    //recursive insertion
    if(item < node->value)
    {
        node->left = insertLLRB(node->left, item);
    }
    else if (node->value < item)
    {
        node->right = insertLLRB(node->right, item);
    }
    else
        node->value = item; 

    //conditions rebalancing
    if(isRed(node->right) && !isRed(node->left))
        node = rotateLeft(node);
    if(isRed(node->left) && isRed(node->left->left))
        node = rotateRight(node);
    if(isRed(node->left) && isRed(node->right))
        flipColors(node);

    return(node);
}

// check if a node is red (for LLRB)
template <typename T>
bool BinaryTree<T>::isRed(Node *node) const
{
    if(!node)    //case empty
        return(false);

    return (node->red);
}

// implement leftwards rotation, given pointer to parent node that needs to rotate
template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::rotateLeft(Node *node) 
{
    Node* rightChild = node->right;
    Node* rightChildLeft = rightChild->left; 

    rightChild->left = node;
    node->right = rightChildLeft;

    bool tempColor = node->red;
    node->red = rightChild->red;      
    rightChild->red = tempColor; 

    return(rightChild); //return new root of subtree
}

// when two reds on left, rotate right
template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::rotateRight(Node *node)
{
    Node* leftChild = node->left; 
    Node* leftChildRight = node->left->right;
    
    leftChild->right = node;
    node->left = leftChildRight;

    bool tempColor = node->red;
    node->red = leftChild->red;
    leftChild->red = tempColor;

    return(leftChild);
}

//flip color when node has two red children
template <typename T>
void BinaryTree<T>::flipColors(Node *node)
{
    Node* leftChild = node->left;
    Node* rightChild = node->right;

    leftChild->red = false;
    rightChild->red = false;
    node->red = true;
}
