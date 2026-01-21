#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>

#include "Node.h"
#include "NoSuchItemException.h"

template<class T>
class DefaultBalanceCondition {
public:
    bool operator()(int current, int ideal) const {
        // Default BST: NEVER triggers rebalancing
        return true;
    }
};


template<class T,
         typename BalanceCondition = DefaultBalanceCondition<T>,
         typename Comparator = std::less<T> >
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const std::list<T> &sortedList);
    BinarySearchTree(const BinarySearchTree &obj);
    ~BinarySearchTree();

    BinarySearchTree &operator=(const BinarySearchTree &rhs);

    bool insert(const T &element);
    bool remove(const T &element);
    void removeAllNodes();

    bool isEmpty() const;
    int getHeight() const;
    int getSize() const;

    const T &get(const T &element) const;
    const T &getMin() const;
    const T &getMax() const;
    const T &getNext(const T &element) const;
    const T &getCeiling(const T &element) const;
    const T &getFloor(const T &element) const;

    std::list<Node<T> *> find(const T &low, const T &high) const;

    void toCompleteBST();

    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;
    void printPretty() const;


    void print(std::ostream &out) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    void print(Node<T> *t, std::ostream &out) const;
    void printTraversal(Node<T> *node, int type) const;



private:
    Node<T> *root;
    int numNodes;
    Comparator isLessThan;
    BalanceCondition isBalancedFunctor;

private:

    //Helper for destructor
    void destroy(Node<T>* node);

    // Helper to calculate left subtree size for complete BST
    int getLeftSubtreeSize(int n) const;

    // Helper for Constructor
    Node<T>* buildFromList(typename std::list<T>::const_iterator &itr, int n);

    // Helpers for toCompleteBST
    void flattenTree(Node<T>* node, Node<T>*& prev);
    Node<T>* buildFromChain(Node<T>*& currentChainNode, int n);
    
    Node<T>* printPreorderHelper( Node<T> * root) const;
    Node<T>* printPostorderHelper( Node<T> * root) const;
    Node<T>* printInorderHelper( Node<T> * root) const;
    
    Node<T>* copyRec(const Node<T>* root);
    
    const T& helpergetMin(const Node<T>* root) const;
    const T& helpergetMax(const Node<T>* root) const;
    
    const Node<T>* getNext(const Node<T>* root, const T &key) const;
    
    Node<T>* buildComplete(const T* arr, int l, int r);
    
    void metadataUpdate(Node<T>* root);
    
    bool add(Node<T>*&root, const T &element);
    
    Node<T>* insertHelper(Node<T> *node, const T &element, bool &inserted);
    Node<T>* removeHelper(Node<T> *node, const T &element, bool &removed); 
    
    Node<T>* helperComplete(std::vector<Node<T>*> &nodes, int start, int end);
    
    void collectInorder(Node<T> *node, std::vector<Node<T>*> &nodes);
    
    Node<T>* findMin(Node<T> *node) const;
    
    void findHelper(Node<T>* node, const T& low, const T& high, std::list<Node<T>*>& result) const;


};


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::destroy(Node<T>* node) {
    
    if (node != NULL) {
        destroy(node->left);   
        destroy(node->right);  
        delete node;          
    }
    
}



template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getLeftSubtreeSize(int n) const {
    
    int h=0;
    while( (int)std::pow(2,h+1)-1 <= n ) {
        h++;
        }
    
    int nodes_in_full_h=(int)std::pow(2,h)-1;
    
    int last_level_nodes=n-nodes_in_full_h;
    
    int max_last_level=(int)std::pow(2,h);
    
    int left_last=std::min(last_level_nodes,max_last_level/2);
    
    int left_full=(int)std::pow(2,h-1)-1;
    
    int lcount=left_full+left_last;
    
    return lcount;

}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::metadataUpdate(Node<T>* node){
    
    if(node==NULL) {return;}
    int lh;
    int rh;
    int ls;
    int rs;
    if(node->left!=NULL) {
        lh=node->left->height;
        ls=node->left->subsize;
    }
    else{
        lh=-1;
        ls=0;
    }
    if(node->right!=NULL) {
        rh=node->right->height;
        rs=node->right->subsize;
    }
    else{
        rh=-1;
        rs=0;
    }
    node->height=std::max(lh,rh)+1;
    node->subsize=ls+rs+1;
    
}


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::copyRec(const Node<T>* root){
    if(root==NULL) {return NULL;}
    
    Node<T>* newnode = new Node<T>();
    newnode->element = root->element;
    newnode->left = copyRec(root->left);
    newnode->right = copyRec(root->right);
    newnode->height = root->height;
    newnode->subsize = root->subsize;
    return newnode;
    
}


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::buildComplete(const T* arr, int l, int r) {
    
    if(l>r) {return NULL;}
    int n=r-l+1;
    int lcount=getLeftSubtreeSize(n);

    int rootIndex = l + lcount; 
    Node<T>* node = new Node<T>(arr[rootIndex], NULL, NULL, 0, 1);

    node->left  = buildComplete(arr, l, rootIndex - 1);
    node->right = buildComplete(arr, rootIndex + 1, r);
    metadataUpdate(node);
    return node;    
    
}



/////////////////////////////////////////////////////////////
///////////  CONSTRUCTORS / DESTRUCTOR  /////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree() {
    //TODO
    root = NULL;
    numNodes = 0;
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const std::list<T> &sortedList)
{
  //TODO
  
    numNodes=sortedList.size();
    if(numNodes==0) {
        root=NULL;
        return;
    }
    
    T* arr=new T[numNodes];
    typename std::list<T>::const_iterator it = sortedList.begin();

    for (int i = 0; i < (int)numNodes; i++) {
        arr[i] = *it;
        ++it;
    }
  
    root=buildComplete(arr,0,numNodes-1);
    delete [] arr;
    
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const BinarySearchTree &obj)
{
    //TODO
    root = copyRec(obj.root);
    numNodes = obj.numNodes;
    isLessThan = obj.isLessThan;
    isBalancedFunctor = obj.isBalancedFunctor;
}



template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::~BinarySearchTree() {
    //TODO
    removeAllNodes();
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C> &
BinarySearchTree<T,B,C>::operator=(const BinarySearchTree &rhs)
{
    //TODO
    if ( this != &rhs){
        removeAllNodes();
        root = copyRec(rhs.root);
        numNodes = rhs.numNodes;
        isLessThan = rhs.isLessThan;
        isBalancedFunctor = rhs.isBalancedFunctor;
        
    }
    
    return *this;
}



template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::removeAllNodes()
{
    //TODO
    
    destroy(root);

    root = NULL;
    numNodes = 0;
}

/////////////////////////////////////////////////////////////
//////////////////// GETTERS ////////////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::isEmpty() const {
    //TODO
    return (root == NULL);
 }

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getHeight() const {
    //TODO
    if (root==NULL){
        return -1;
    }
    return root->height;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getSize() const {
    //TODO
    return numNodes;
 }


/////////////////////////////////////////////////////////////
////////////////////// FIND NODE ////////////////////////////
/////////////////////////////////////////////////////////////


template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::get(const T &element) const
{
    //TODO
    
    Node<T>* current = root;
    
    while(current != NULL){
        if(isLessThan(element, current->element)){
            current =current->left;
        }
        
        else if(isLessThan(current->element, element)){
            current =current->right;
        }
        
        else{
            return current->element;
        }
        
    }
    
    throw NoSuchItemException();
    
}

/////////////////////////////////////////////////////////////
//////////////////// INSERT / REMOVE ////////////////////////
/////////////////////////////////////////////////////////////

/*
template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::add(Node<T>*&node, const T &element){
    if(node==NULL){
        node = new Node<T>();
        node->element = element;
        node->subsize = 1;
    }

    bool result;
    
    else if(isLessThan(element, node->element)){
        result = add(node->left, element);
        
        if(result){
            metadataUpdate(node);
        
            int h = 0;
            int temp = node->subsize;
            while (temp > 1) {
                temp = temp / 2;  
                h++;
            }
        
            int idealHeight = h;
            if (!isBalancedFunctor(node->height, idealHeight)) {
                std::vector<Node<T>*> nodes;
                collectInorder(node, nodes);
                node = helperComplete(nodes, 0, nodes.size() - 1);
            }

        }
        
    }
    
    else if(isLessThan(node->element, element)){
        result = add(node->right, element);

        if(result){
            metadataUpdate(node);
        
            int h = 0;
            int temp = node->subsize;
            while (temp > 1) {
                temp = temp / 2;  
                h++;
            }
            
            int idealHeight = h;
            if (!isBalancedFunctor(node->height, idealHeight)) {
                std::vector<Node<T>*> nodes;
                collectInorder(node, nodes);
                node = helperComplete(nodes, 0, nodes.size() - 1);
            }
            

        }
        
    }
    
    else{
        node->element = element;
        return false;
    }
    
    return result;
    
}*/


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::insertHelper(Node<T> *node, const T &element, bool &inserted) {
    if (!node) {
        inserted = true;
        numNodes++;
        Node<T> * newnode = new Node<T>();
        newnode->element = element;
        newnode->subsize = 1;
        return newnode;
    }
    
    if (isLessThan(element, node->element)) {
        node->left = insertHelper(node->left, element, inserted);
    } 
    else if (isLessThan(node->element, element)) {
        node->right = insertHelper(node->right, element, inserted);
    } 
    else {
        node->element = element;
        inserted = false;
        return node;
    }
    
    metadataUpdate(node);
    
    int h = 0;
        int temp = node->subsize;
        while (temp > 1) {
            temp = temp / 2;  
            h++;
        }
    
    int idealHeight = h;
    if (!isBalancedFunctor(node->height, idealHeight)) {
        std::vector<Node<T>*> nodes;
        collectInorder(node, nodes);
        node = helperComplete(nodes, 0, nodes.size() - 1);
    }
    
    return node;
}
  

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insert(const T &element)
{
    //TODO
    
    bool inserted = false;
    root = insertHelper(root, element, inserted);
    return inserted;
    
    /*
    bool result = add(root, element);
    if(result) numNodes++;
    return result;
    */
    
}


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::findMin(Node<T> *node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::removeHelper(Node<T> *node, const T &element, bool &removed) {
    if (!node) {
        removed = false;
        return NULL;
    }
    
    if (isLessThan(element, node->element)) {
        node->left = removeHelper(node->left, element, removed);
    } else if (isLessThan(node->element, element)) {
        node->right = removeHelper(node->right, element, removed);
    } else {
        removed = true;
        numNodes--;
        
        if (!node->left && !node->right) {
            delete node;
            return NULL;
        } else if (!node->left) {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        } else {
            Node<T> *successor = findMin(node->right);
            node->element = successor->element;
            node->right = removeHelper(node->right, successor->element, removed);
        }
    }
    
    metadataUpdate(node);
    
    int h = 0;
        int temp = node->subsize;
        while (temp > 1) {
            temp = temp / 2;  
            h++;
        }
    
    int idealHeight = h;
    if (!isBalancedFunctor(node->height, idealHeight)) {
        std::vector<Node<T>*> nodes;
        collectInorder(node, nodes);
        node = helperComplete(nodes, 0, nodes.size() - 1);
    }
    
    return node;
}



template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::remove(const T &element) {
    //TODO
    
    bool removed = false;
    root = removeHelper(root, element, removed);
    return removed;
    
}

/////////////////////////////////////////////////////////////
//////////////////// MIN/MAX/NEXT ///////////////////////////
/////////////////////////////////////////////////////////////



template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMin() const {
    //TODO
    
    if(root==NULL) throw NoSuchItemException();

    Node<T>* curr = root;
    while(curr->left != NULL){
        curr = curr->left;
    }
    return curr->element;
    
}

/*
template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::helpergetMin(const Node<T>* node) const {
    //TODO
    
    if(node == NULL){
        throw NoSuchItemException();
    }
    while(node->left != NULL){
        node = node->left;
    }
    return node->element;
    
}
*/


template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMax() const {
    //TODO
    
    if(root == NULL){
        throw NoSuchItemException();
    }
    return helpergetMax(root);
    
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::helpergetMax(const Node<T>* root) const {
    //TODO
    
    if(root->right == NULL){
        return root->element;
    }
    else{
        return helpergetMax(root->right);
    }
    
}


template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getNext(const T &key) const {
    //TODO
    
    Node<T>* current = root;
    Node<T>* bestptr = NULL;
    
    while(current!=NULL){
        
        if(isLessThan(key, current->element)){
            bestptr = current;
            current = current->left;
        }
        
        else{
            current = current->right;
        }
        
    }
    
    if(bestptr == NULL) throw NoSuchItemException();
    
    return bestptr->element;
    
    /*
    if(root==NULL){
        throw NoSuchItemException();
    }
    
    const Node<T>* resultptr = getNext(root,key);
    
    if( resultptr == NULL ){
        throw NoSuchItemException();
    }
    return resultptr->element;
    */
    
}

/*
template<class T, typename B, typename C>
const Node<T>* BinarySearchTree<T,B,C>::getNext(const Node<T>* node, const T &key) const {
    //TODO
    
    if (node == NULL) {
        return NULL;
    }
    
    if(isLessThan(key, node->element)) {
        const Node<T>* leftresult = getNext(node->left, key);
        
        if(leftresult == NULL){
            return node;
        }
        else{
            return leftresult;
        }
        
    }
    
    else {
        return getNext(node->right, key);
    }
    
    
}
*/

/////////////////////////////////////////////////////////////
//////////////// CEILING & FLOOR ////////////////////////////
/////////////////////////////////////////////////////////////


template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getFloor(const T &key) const {
    //TODO
    /*
    Node > Key: This node is too big. The floor must be in the left subtree.

    Node < Key: This node is a potential answer! Save it as bestptr, but go right to see if you can find a larger number that is still smaller than the key.

    Node == Key: This is the best possible floor. Return it immediately.
    */
    
    Node<T>* current = root;
    Node<T>* bestptr = NULL;
    
    while(current!=NULL){
        if(isLessThan(current->element, key)){
            bestptr = current;
            current = current->right;
            
        }
        
        else if(isLessThan(key, current->element)){
            current = current->left;
        }
        
        else{
            return current->element;
        }
    }
    
    if(bestptr == NULL) throw NoSuchItemException();
    
    return bestptr->element;
    
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getCeiling(const T &key) const {
    //TODO
    
    Node<T>* current = root;
    Node<T>* bestptr = NULL;
    
    while(current!=NULL){
        if(isLessThan(current->element, key)){
            current = current->right;
        }
        
        else if(isLessThan(key, current->element)){
            bestptr = current;
            current = current->left;
        }
        
        else {
            return current->element;
        }
    }
    
    if(bestptr == NULL) throw NoSuchItemException();
    
    return bestptr->element;
    
}
/////////////////////////////////////////////////////////////
/////////////////////// RANGE FIND //////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::findHelper(Node<T>* node, const T& low, const T& high, std::list<Node<T>*>& result) const{
    
    if(node == NULL) return;
    
    if(node->element > low){
        findHelper(node->left, low, high, result);
    }
    
    if(node->element >= low && node->element<=high ){
        result.push_back(node);
    }
    
    if(node->element < high){
        findHelper(node->right, low, high, result);
    }
    
}


template<class T, typename B, typename C>
std::list<Node<T> *> BinarySearchTree<T,B,C>::find(const T &low, const T &high) const
{
    //TODO
    std::list<Node<T> *> result;
    findHelper(root, low, high, result);
    return result;
    
}

/////////////////////////////////////////////////////////////
//////////////////// COMPLETE BST ///////////////////////////
/////////////////////////////////////////////////////////////


template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::helperComplete(std::vector<Node<T>*> &nodes, int start, int end) {
    if (start > end) return NULL;
    
    int n = end - start + 1;
    int leftSize = getLeftSubtreeSize(n);
    int rootIndex = start + leftSize;
    
    Node<T> *rootNode = nodes[rootIndex];
    rootNode->left = helperComplete(nodes, start, rootIndex - 1);
    rootNode->right = helperComplete(nodes, rootIndex + 1, end);
    
    metadataUpdate(rootNode);
    
    return rootNode;
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST()
{
    //TODO
    
    if (!root) return;
    
    std::vector<Node<T>*> nodes;
    collectInorder(root, nodes);
    root = helperComplete(nodes, 0, nodes.size() - 1);
    
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::collectInorder(Node<T> *node, std::vector<Node<T>*> &nodes) {
    if (!node) return;
    collectInorder(node->left, nodes);
    nodes.push_back(node);
    collectInorder(node->right, nodes);
}



/////////////////////////////////////////////////////////////
//////////////////////// PRINTS /////////////////////////////
/////////////////////////////////////////////////////////////

// === PREORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPreorder() const {
    std::cout << "BST_preorder{" << std::endl;
    printTraversal(root, 0);
    std::cout << std::endl << "}" << std::endl;
}

// === INORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printInorder() const {
    std::cout << "BST_inorder{" << std::endl;
    printTraversal(root, 1);
    std::cout << std::endl << "}" << std::endl;
}

// === POSTORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPostorder() const {
    std::cout << "BST_postorder{" << std::endl;
    printTraversal(root, 2);
    std::cout << std::endl << "}" << std::endl;
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printTraversal(Node<T> *node, int type) const
{

    // --- Collect traversal into arr ---
 // TODO you can use stack  std::stack
    std::vector<T> arr;
    std::stack<Node<T>*> s1;

    if (type == 1) { 
        // inorder
        // TODO 
        
        Node<T>* curr = node;
        while(curr != NULL || !s1.empty() ){
            while(curr!=NULL){
                s1.push(curr);
                curr = curr->left;
            }
            
            curr = s1.top();
            s1.pop();
            arr.push_back(curr->element);
            curr = curr->right;
            
        }
        
        
        
    }
    else if (type == 0) {
        // preorder
        // TODO 
        
        Node<T>* x;
        if(node != NULL) s1.push(node);
        
        while(!s1.empty()){
            x = s1.top();
            s1.pop();
            arr.push_back(x->element);
            if(x->right != NULL) s1.push(x->right);
            if(x->left != NULL) s1.push(x->left);
        }
        
    }
    else {
        // postorder
        // TODO
        std::stack<Node<T>*> s2;
        Node<T>* x;
        if(node != NULL) s1.push(node);
        
        while(!s1.empty()){
            x = s1.top();
            s1.pop();
            if(x->left != NULL) s1.push(x->left);
            if(x->right != NULL) s1.push(x->right);
            s2.push(x);
        }
        
        while(!s2.empty()){
            x = s2.top();
            s2.pop();
            arr.push_back(x->element);
        }
        
    }

    // --- Now print with commas ---
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << "\t" << arr[i];
        if (i + 1 < arr.size()) std::cout << ",";
        std::cout << std::endl;
    }
}


/////////////////////////////////////////////////////////////
/////////////////////// PRETTY PRINT ////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty() const
{
        // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty(Node<T> *node,
                                                int indentLevel,
                                                bool isLeftChild) const
{
    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::print(std::ostream &out) const {
    print(root, out);
    out << "\n";
}
// Print pair<int,float> or any std::pair<K,V>
template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A,B>& p) {
    os << p.first;   // ONLY print the key
    return os;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::print(Node<T> *t, std::ostream &out) const
{
    if (!t) return;

    bool hasLeft  = (t->left  != NULL);
    bool hasRight = (t->right != NULL);

    // LEFT subtree
    if (hasLeft)
    {
        out << '[';
        print(t->left, out);
    }
    else if (hasRight)
    {
        out << '[';
    }

    // CURRENT node
    if (!hasLeft && !hasRight)
    {
        out << '(' << t->element << ')';
    }
    else
    {
        out << '{' << t->element
            << ",H" << t->height
            << ",S" << t->subsize
            << '}';
    }

    // RIGHT subtree
    if (hasRight)
    {
        print(t->right, out);
        out << ']';
    }
    else if (hasLeft)
    {
        out << ']';
    }
}




#endif // BINARY_SEARCH_TREE_H
