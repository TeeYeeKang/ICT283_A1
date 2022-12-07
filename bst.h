//bst pointer

#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T info;
    Node<T> *lLink;
    Node<T> *rLink;
};

template <class T>
class binaryTreePointer
{

public:
    typedef void (*funcP)(T &);
    void insert(const T& insertItem);
    bool search(const T& searchItem) const;
    void destroyTree();
    void inorderTraversal(funcP fp) const;
    void preorderTraversal(funcP fp) const;
    void postorderTraversal(funcP fp) const;
    binaryTreePointer();
    ~binaryTreePointer();
    binaryTreePointer(const binaryTreePointer<T>& otherTree);
    //mix and max

protected:
    Node<T> *root;

private:
    void copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot);
    void destroy(Node<T>* &p);
    void inorder(funcP fp, Node<T> *p) const;
    void preorder(funcP fp, Node<T> *p) const;
    void postorder(funcP fp ,Node<T> *p) const;
    bool searchElement(Node<T>* nd, const T& item) const;
    void insertElement(Node<T>*& nd, T item);
};

template <class T>
binaryTreePointer<T>::binaryTreePointer()
{
    root = nullptr;
}

//copy constructor
template<class T>
binaryTreePointer<T>::binaryTreePointer(const binaryTreePointer<T>& otherTree)
{
    if(otherTree.root==nullptr)
    {
        root = nullptr;
    }
    else
    {
        copyTree(root, otherTree.root);
    }
}

template<class T>
void binaryTreePointer<T>::copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot)
{
    if(otherTreeRoot==nullptr)
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new Node<T>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

template<class T>
binaryTreePointer<T>::~binaryTreePointer()
{
    destroy(root);
}

template <class T>
void binaryTreePointer<T>::inorderTraversal(funcP fp) const
{
    inorder(fp, root);
}

template <class T>
void binaryTreePointer<T>::preorderTraversal(funcP fp) const
{
    preorder(fp, root);
}

template <class T>
void binaryTreePointer<T>::postorderTraversal(funcP fp) const
{
    postorder(fp, root);
}

template <class T>
void binaryTreePointer<T>::inorder(funcP fp, Node<T> *p) const
{
    if(p!=nullptr)
    {
        inorder(fp, p->lLink);
        (fp)(p->info);
        //cout<<p->info<<" ";
        inorder(fp, p->rLink);
    }
}

template <class T>
void binaryTreePointer<T>::preorder(funcP fp, Node<T> *p) const
{
    if(p!=nullptr)
    {
        (fp)(p->info);
        //cout<<p->info<<" ";
        preorder(fp, p->lLink);
        preorder(fp, p->rLink);
    }
}

template <class T>
void binaryTreePointer<T>::postorder(funcP fp, Node<T> *p) const
{
    if(p!=nullptr)
    {
        postorder(fp, p->lLink);
        postorder(fp, p->rLink);
        //cout<<p->info<<" ";
        (fp)(p->info);
    }
}

template<class T>
void binaryTreePointer<T>::destroy(Node<T>* &p)
{
    if(p!=nullptr)
    {
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p=nullptr;
    }
}

template<class T>
void binaryTreePointer<T>::destroyTree()
{
    destroy(root);
}

template<typename T>
bool binaryTreePointer<T>::search(const T& searchItem) const
{
    if(searchElement(root, searchItem))
        return true;
    else
        return false;
}

template<typename T>
bool binaryTreePointer<T>::searchElement(Node<T>* nd, const T& item) const
{
    //base case
    if(nd == nullptr)
        return false;
    if(nd->info == item)
        return true;

    //recursive case
    if(item > nd->info)
        return searchElement(nd->rLink, item);
    else
        return searchElement(nd->lLink, item);
}

template<typename T>
void binaryTreePointer<T>::insert(const T& insertItem)
{
    insertElement(root, insertItem);
}

template<typename T>
void binaryTreePointer<T>::insertElement(Node<T>*& nd, T item)
{
    if(nd == nullptr) // you are the root or you reached the end of a tree
    {
        nd = new Node<T>;
        nd->info = item;
        nd->lLink = nullptr;
        nd->rLink = nullptr;
    }
    else
    {
        if(item < nd->info)
        {
            insertElement(nd->lLink, item);
        }
        else
        {
            insertElement(nd->rLink, item);
        }
    }
}





#endif // BST_H

