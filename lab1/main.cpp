/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(0, max);

    return int(dist(gen));
}

int const COUNT = 10000; // max count of elements

template<typename T>
class Node {
public:
    T data;
    Node* dad;
    // son for tree with any count of children
    Node* left;
    // brother for tree with any count of children
    Node* right;

    //--------------------------------------------------------
    //формування першого елемента дерева
    Node(T data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
        dad = nullptr;
    }

    Node(T data, Node<T>* dad, Node<T>* left, Node<T>* right) {
        this->data = data;
        this->dad = dad;
        this->left = left;
        this->right = right;
    }

    //-------------------------------------------------------
    //знищення дерева
    ~Node() {
    }

    //-------------------------------------------------------
    //виведення дерева
    void tree_print() {
        Node<T> *root = this;
        tree_print_rekurs(root);
    }

private:
    void tree_print_rekurs(Node<T> *root, int depth = 1) {
        if (root != nullptr)
        {
            tree_print_rekurs(root->left, depth + 1);
            for(int i = 0; i < depth; i++)
                cout << " --";
            cout << root->data << "\n";
            tree_print_rekurs(root->right, depth + 1);
        }
    }

};

template<typename T>
class Tree {
public:
    virtual void print()=0;
    virtual void add(T data)=0;
    virtual bool kill(T data)=0;
    virtual bool remove(Node<T>* father, int index)=0;

};


template<typename T>
Node<T> *find(Node<T>* const, T);

template<typename T>
void delete_rekurs(Node<T>*);

template<typename T>
class VariableSonTree: public Tree<T> {
private:
    Node<T>* root;

    void vartree_print_rekurs(Node<T> *root, int depth = 1) {
        if (root != nullptr)
        {
            vartree_print_rekurs(root->left, depth + 1);
            for(int i = 0; i < depth; i++)
                cout << " --";
            cout << root->data << "\n";
            vartree_print_rekurs(root->right, depth); // changes here (not depth + 1)
        }
    }

public:
    VariableSonTree(T first_data) {
        root = new Node<T>(first_data);//формування першого елемента дерева
    }

    ~VariableSonTree() {
        delete_rekurs(root);
    }
    void print() override {
        vartree_print_rekurs(root);
    }

    //--------------------------------------------------------
    /*  Додавання елементів відбувається для дерева з довільною кількістю
     *  дітей рандомно, тобто на кожному кроці обираємо куди піти - до брата, чи до сина
     *  та відповідно переміщаємось, поки не потрапимо до листа, туди й додаємо - теж рандомно:
     *  або як сина, або як брата
     */
    void add(T data) override{
            int rand;
            Node<T>* current = root;

            // виключаємо можливість додавання однакових данних у дерево
            // ця умова створена для глобалізації задачі, так як у пошуковому дереві відсутні
            // однакові елементи
            if(find(root, data))
                return;
            while(current->left || current->right) {

                if(current->left && current->right) {
                    rand = rand_num(2);
                    if(rand) {
                        current = current->right;
                    }
                    else {
                        current = current->left;
                    }
                }
                else
                if(current->left){
                    current = current->left;
                }
                else
                if(current->right){
                    current = current->right;
                }

            }


        rand = rand_num(2);
            if(current == root)
                rand = 1;
        if(rand) {
            Node<T> *el = new Node<T>(data, current, nullptr, nullptr);
            current->left = el;
        }
        else {
            Node<T> *el = new Node<T>(data, current->dad, nullptr, nullptr);
            current->right = el;
        }
    }


    //-------------------------------------------------------
    //вилучення елемента
    bool kill(T key) override {
        Node<T>* current;
        Node<T>* down_current;
        if (Node<T> *pkey = find(root, key)) {
            if (pkey == root) {
                root = root->left;
                root->dad = nullptr;
            } else if (!pkey->right && !pkey->left) { // вузол - лист
                if ((pkey->dad)->left == pkey) {
                    (pkey->dad)->left = nullptr;
                } else {
                    current = (pkey->dad)->left;
                    while (current->right != pkey)
                        current = current->right;
                    current->right = nullptr;
                }

            } else if (!pkey->left) { // вузол не має синів
                if((pkey->dad)->left == pkey) {
                    (pkey->dad)->left = pkey->right;
                }
                else {
                    current = (pkey->dad)->left;
                    while(current->right!= pkey)
                        current = current->right;
                    current->right = pkey->right;
                }

            } else if (!pkey->right) { // вузол не має братів
                if((pkey->dad)->left == pkey) {
                    (pkey->dad)->left = pkey->left;
                    (pkey->left)->dad = pkey->dad;
                }
                else {
                    current = (pkey->dad)->left;
                    while(current->right != pkey)
                        current = current->right;
                    current->right = pkey->left;
                    (pkey->left)->dad = pkey->dad;
                }
            }
            else { // вузол має все
                if((pkey->dad)->left == pkey) {
                    (pkey->dad)->left = pkey->left;
                    (pkey->left)->dad = pkey->dad;
                    current = pkey->left;
                    while(current->right) {
                        current = current->right;
                        current->dad = pkey->dad;
                    }
                    current->right = pkey->right;
                }
                else {
                    current = (pkey->dad)->left;
                    while(current->right != pkey)
                        current = current->right;
                    current->right = pkey->left;

                    down_current = pkey->left;
                    down_current->dad = pkey->dad;
                    while(down_current->right) {
                        down_current = down_current->right;
                        down_current->dad = pkey->dad;
                    }
                    down_current->right = pkey->right;
                }
            }
            delete pkey;
            return true;
        }
        return false;
    }

    // вилучення елемента за вказівником на батька та індексом
    bool remove(Node<T>* father, int index) override {
        if(!father)
            return false;
        if(!father->left)
            return false;
        Node<T>* current = father->left;
        int cntr = 0;
        while(current->right && cntr < index) {
            current = current->right;
            cntr++;
        }
        if(cntr == index) {
            kill(current->data); // кожен запис зустрічається лише 1 раз
            return true;
        }
        else
            return false;
    }
};


template<typename T>
class BinTree: public Tree<T> {
private:
    Node<T>* root;

public:
    BinTree(T first_data) {

    }

    ~BinTree() {
        delete [] items;
    }
    void print() override{
        for(int i=0;i<size;i++) {
            cout<<items[i]<<" ";
        }
        cout<<endl;
    }

    //--------------------------------------------------------
    //додавання елементів в кінець дерева 2, 3, ..., nn
    void add(T data) override{
        if (size == capacity) {
            grow_capacity();
        }
        items[size]=data;
        size++;
    }

    //-------------------------------------------------------
    //вставка елемента
    bool insert(T key, T data) override{
        int key_index = find(key);
        if (key_index == -1) { // not found
            return false;
        }
        if(size==capacity) {
            grow_capacity();
        }
        key_index++; //insert after this index
        for(int i = size; i>key_index;i--) {
            items[i] = items[i-1];
        }
        items[key_index] = data;
        size++;
        return true;
    }
//
//	//-------------------------------------------------------
//	//вилучення елемента
    bool remove(T key) override {
        int key_index = find(key);
        if (key_index == -1) { // not found
            return false;
        }
        for(int i=key_index;i<size-1;i++) {
            items[i]=items[i+1];
        }
        return true;
    }
};

template<typename T>
T get_test_data(int index) {
    return T{index};
}

template<>
double get_test_data<double>(int index) {
    return index+0.1;
}

//
//
//template<typename T>
//void test_list(List<T>* my_list) {
//    cout<<"Any list"<<endl;
//    int nn;
//    T  k, m;
//    //визначаємось з кількістю елементів
//    cout << "Number = ";
//    //cin >> nn;
//    nn = 7;
//    cout << nn << endl;
//    //BinTree<double> my_list { 0.1 };
//
//    for (int i = 2; i <= nn; i++)
//        my_list->add(get_test_data<T>(i));
//    my_list->print();
//    //вставка елемента k після елемента m
//    cout << "Insert = ";
//    //cin >> k;
//    k = get_test_data<T>(10);
//    cout << k << endl;
//    cout << "After = ";
//    //cin >> m;
//    m = get_test_data<T>(4);
//    cout << m << endl;
//    my_list->insert(m, k);
//    my_list->print();  //виведення дерева
//    //вилучення елемента k
//    cout << "Delete = ";
//    //cin >> k;
//    k = get_test_data<T>(5);
//    cout << k << endl;
//    if (!my_list->remove(k))
//        cout << "no find " << endl;
//    my_list->print();  //виведення дерева
//}
//
//void test_doubles() {
//    cout<<"Doubles"<<endl;
//    double nn, k, m;
//    //визначаємось з кількістю елементів
//    cout << "Number = ";
//    //cin >> nn;
//    nn = 7;
//    cout << nn << endl;
//    BinTree<double> my_list { 0.1 };
//
//    for (double i = 1.1; i <= nn; i++)
//        my_list.add(i);
//    my_list.print();
//    //вставка елемента k після елемента m
//    cout << "Insert = ";
//    //cin >> k;
//    k = 4.2;
//    cout << k << endl;
//    cout << "After = ";
//    //cin >> m;
//    m = 2.1;
//    cout << m << endl;
//    my_list.insert(m, k);
//    my_list.print();  //виведення дерева
////	//вилучення елемента k
////	cout << "Delete = ";
////	//cin >> k;
////	k = 5.1;
////	cout << k << endl;
////	if (!my_list.remove(k))
////		cout << "no find " << endl;
////	my_list.print();  //виведення дерева
//}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os<<"[";
    char sep = ' ';
    for(const T& obj : vec) {
        os<<sep<<obj;
        sep = ',';
    }
    os<<" ]";
    return os;
}
//
//void test_int_vectors() {
//    cout<<"Int vectors"<<endl;
//    using std::vector;
//    int nn;
//    vector<int> k, m;
//    //визначаємось з кількістю елементів
//    cout << "Number = ";
//    //cin >> nn;
//    nn = 7;
//    cout << nn << endl;
//    BinTree<vector<int>> my_list { { 1,4,5} };
//
//    for (int i = 2; i <= nn; i++)
//        my_list.add({i,4,5});
//    my_list.print();
//
////	//вставка елемента k після елемента m
////	cout << "Insert = ";
////	//cin >> k;
////	k = 4.2;
////	cout << k << endl;
////	cout << "After = ";
////	//cin >> m;
////	m = 2.1;
////	cout << m << endl;
////	my_list.insert(m, k);
////	my_list.print();  //виведення дерева
////	//вилучення елемента k
////	cout << "Delete = ";
////	//cin >> k;
////	k = 5.1;
////	cout << k << endl;
////	if (!my_list.remove(k))
////		cout << "no find " << endl;
////	my_list.print();  //виведення дерева
//}
//
//void test_int_vector_vectors() {
//    cout<<"Int vector vectors"<<endl;
//    using std::vector;
//    int nn;
//    vector<vector<int>> k, m;
//    //визначаємось з кількістю елементів
//    cout << "Number = ";
//    //cin >> nn;
//    nn = 7;
//    cout << nn << endl;
//    VariableSonTree<vector<vector<int>>> my_list { { { 0,1}, {1,9} } };
//
//    for (int i = 2; i <= nn; i++)
//        my_list.add({ { 0,i}, {i,9} });
//    my_list.print();
//}
//-------------------------
int main() {

    VariableSonTree<int>* tree = new VariableSonTree<int>{1};
    tree->add(3);
    tree->add(7);
    tree->add(8);
    tree->add(9);
    tree->kill(8);
    tree->print();
//    using std::vector;
//    test_doubles();
//    test_int_vectors();
//    test_int_vector_vectors();
//
//    BinTree<double>* list1 = new BinTree<double>(0.1);
//    test_list(list1);
//    List<vector<int>>* list2 = new VariableSonTree<vector<int>>({1,2});
//    test_list(list2);
//
//    int nn, k, m;
//    //визначаємось з кількістю елементів
//    cout << "Number = ";
//    //cin >> nn;
//    nn = 7;
//    cout << nn << endl;
//    BinTree<int> my_list { 1 };
//
//    //додавання елементів в кінець дерева 2, 3, ..., nn
//    for (int i = 2; i <= nn; i++)
//        my_list.add(i);
//    my_list.print();  //виведення дерева
//    //вставка елемента k після елемента m
//    cout << "Insert = ";
//    //cin >> k;
//    k = 42;
//    cout << k << endl;
//    cout << "After = ";
//    //cin >> m;
//    m = 4;
//    cout << m << endl;
//    my_list.insert(m, k);
//    my_list.print();  //виведення дерева
//    //вилучення елемента k
//    cout << "Delete = ";
//    //cin >> k;
//    k = 5;
//    cout << k << endl;
//    if (!my_list.remove(k))
//        cout << "no find " << endl;
//    my_list.print();  //виведення дерева
////
////	delete pbeg;  //знищення дерева
//    //system("pause");
    return 0;
}

//--------------------------------------------------------
//пошук елемента за ключем
template<typename T>
Node<T> *find(Node<T> * const root, T data) {
    Node<T> *pv = root;
    int head = 0;
    int tail = 1;
    Node<T>* current = nullptr;
    Node<T>* queue[COUNT];
    queue[head] = root;
    bool finded = false;
    while (head < tail) {
        current = queue[head];
        head++;
        if (current->data == data) {
            finded = true;
            break;
        }
        if(current->right) {
            queue[tail] = current->right;
            tail++;
        }
        if(current->left) {
            queue[tail] = current->left;
            tail++;
        }
    }
    if(finded)
        return current;
    else
        return nullptr;
}

template<typename T>
void delete_rekurs(Node<T>* root) {
    if(root) {
        if(root->right)
            delete_rekurs(root->right);
        if(root->left)
            delete_rekurs(root->left);
        delete root;
    }
}

