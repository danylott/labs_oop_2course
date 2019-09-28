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

template<typename T>
class Node {
public:
    T data;
    // son for tree with any count of children
    Node* left;
    // brother for tree with any count of children
    Node* right;

    //--------------------------------------------------------
    //формування першого елемента дерева
    Node(T data) {
        //TODO: pass by const ref
        this->data = data;
        left = nullptr;
        right = nullptr;
    }

    Node(T data, Node<T>* left, Node<T>* right) {
        this->data = data;
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
        Node *root = this;
        tree_print_rekurs(root);
    }

private:
    void tree_print_rekurs(Node *root, int depth = 1) {
        if (root != nullptr)
        {
            printBinTree(root->prev, depth + 1);
            for(int i = 0; i < depth; i++)
                cout << " --";
            cout << root->data << "\n";
            printBinTree(root->next, depth + 1);
        }
    }

};

template<typename T>
class Tree {
public:
    virtual void print()=0;
    virtual void add(T data)=0;
    virtual bool remove(Node<T> father, int index)=0;
    virtual bool kill(T data)=0;

};


template<typename T>
Node<T> *find(Node<T> * const, T);

template<typename T>
class DoublyLinkedList: public List<T> {
private:
    Node<T>* begin;
    Node<T>* end;
public:
    DoublyLinkedList(T first_data) {
        begin = new Node<T>(first_data);//формування першого елемента дерева
        end = begin;	//список складаєтьсчя з одного елемента

    }

    ~DoublyLinkedList() {
        Node<T> *current=begin, *to_delete;
        while (current) {
            to_delete = current;
            current = current->next;
            delete to_delete;
        }
    }
    void print() override {
        begin->list_print();
    }

    //--------------------------------------------------------
    //додавання елементів в кінець дерева 2, 3, ..., nn
    void add(T data) override{
        Node<T> *pv = new Node<T>(data, end, nullptr);

        end->next = pv;
        end = pv;
    }

    //-------------------------------------------------------
    //вставка елемента
    bool insert(T key, T data) override {
        if (Node<T> *pkey = find(begin, key)) {

            //зв`язок нового вузла з наступним
            //зв`язок нового вузла з попереднім
            Node<T> *pv = new Node<T>(data, pkey, pkey->next);

            pkey->next = pv;  //зв`язок попереднього з новим вузлом
            //зв`язок наступного з новим вузлом
            if (pkey != end)
                (pv->next)->prev = pv;
            else
                end = pv; //якщо вузол стає останнім, змінюємо покажчик на кінець
            return true;
        }
        return false;  //місце для вставки не було знайдено
        //можна було б реалізовувати іншу обробку
        //наприклад, вставку в кінець дерева,
        //передбачивши можливу порожність дерева
    }

    //-------------------------------------------------------
    //вилучення елемента
    bool remove(T key) override {
        if (Node<T> *pkey = find(begin, key)) {
            if (pkey == begin) {
                begin = begin->next;
                begin->prev = nullptr;
            } else if (pkey == end) {
                end = end->prev;
                end->next = nullptr;
            } else {
                (pkey->prev)->next = pkey->next;
                (pkey->next)->prev = pkey->prev;
            }
            delete pkey;
            return true;
        }
        return false;
    }
};


template<typename T>
class ArrayList: public List<T> {
private:
    int size;
    int capacity;
    T* items;
    const int INITIAL_CAPACITY = 4;

    void grow_capacity() {
        capacity *=2;
        T* new_items = new T[capacity];
        for(int i=0; i<size;i++) {
            new_items[i] = items[i];
        }
        delete [] items;
        items = new_items;
    }

    int find(T key) {
        for(int i=0;i<size;i++) {
            if (items[i] == key) {
                return i;
            }
        }
        return -1;
    }

public:
    ArrayList(T first_data) {
        items = new T[INITIAL_CAPACITY];
        items[0] = first_data;
        capacity = INITIAL_CAPACITY;
        size = 1;
    }

    ~ArrayList() {
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



template<typename T>
void test_list(List<T>* my_list) {
    cout<<"Any list"<<endl;
    int nn;
    T  k, m;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    //ArrayList<double> my_list { 0.1 };

    for (int i = 2; i <= nn; i++)
        my_list->add(get_test_data<T>(i));
    my_list->print();
    //вставка елемента k після елемента m
    cout << "Insert = ";
    //cin >> k;
    k = get_test_data<T>(10);
    cout << k << endl;
    cout << "After = ";
    //cin >> m;
    m = get_test_data<T>(4);
    cout << m << endl;
    my_list->insert(m, k);
    my_list->print();  //виведення дерева
    //вилучення елемента k
    cout << "Delete = ";
    //cin >> k;
    k = get_test_data<T>(5);
    cout << k << endl;
    if (!my_list->remove(k))
        cout << "no find " << endl;
    my_list->print();  //виведення дерева
}

void test_doubles() {
    cout<<"Doubles"<<endl;
    double nn, k, m;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    ArrayList<double> my_list { 0.1 };

    for (double i = 1.1; i <= nn; i++)
        my_list.add(i);
    my_list.print();
    //вставка елемента k після елемента m
    cout << "Insert = ";
    //cin >> k;
    k = 4.2;
    cout << k << endl;
    cout << "After = ";
    //cin >> m;
    m = 2.1;
    cout << m << endl;
    my_list.insert(m, k);
    my_list.print();  //виведення дерева
//	//вилучення елемента k
//	cout << "Delete = ";
//	//cin >> k;
//	k = 5.1;
//	cout << k << endl;
//	if (!my_list.remove(k))
//		cout << "no find " << endl;
//	my_list.print();  //виведення дерева
}
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

void test_int_vectors() {
    cout<<"Int vectors"<<endl;
    using std::vector;
    int nn;
    vector<int> k, m;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    ArrayList<vector<int>> my_list { { 1,4,5} };

    for (int i = 2; i <= nn; i++)
        my_list.add({i,4,5});
    my_list.print();

//	//вставка елемента k після елемента m
//	cout << "Insert = ";
//	//cin >> k;
//	k = 4.2;
//	cout << k << endl;
//	cout << "After = ";
//	//cin >> m;
//	m = 2.1;
//	cout << m << endl;
//	my_list.insert(m, k);
//	my_list.print();  //виведення дерева
//	//вилучення елемента k
//	cout << "Delete = ";
//	//cin >> k;
//	k = 5.1;
//	cout << k << endl;
//	if (!my_list.remove(k))
//		cout << "no find " << endl;
//	my_list.print();  //виведення дерева
}

void test_int_vector_vectors() {
    cout<<"Int vector vectors"<<endl;
    using std::vector;
    int nn;
    vector<vector<int>> k, m;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    DoublyLinkedList<vector<vector<int>>> my_list { { { 0,1}, {1,9} } };

    for (int i = 2; i <= nn; i++)
        my_list.add({ { 0,i}, {i,9} });
    my_list.print();
}
//-------------------------
int main() {
    using std::vector;
    test_doubles();
    test_int_vectors();
    test_int_vector_vectors();

    ArrayList<double>* list1 = new ArrayList<double>(0.1);
    test_list(list1);
    List<vector<int>>* list2 = new DoublyLinkedList<vector<int>>({1,2});
    test_list(list2);

    int nn, k, m;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    ArrayList<int> my_list { 1 };

    //додавання елементів в кінець дерева 2, 3, ..., nn
    for (int i = 2; i <= nn; i++)
        my_list.add(i);
    my_list.print();  //виведення дерева
    //вставка елемента k після елемента m
    cout << "Insert = ";
    //cin >> k;
    k = 42;
    cout << k << endl;
    cout << "After = ";
    //cin >> m;
    m = 4;
    cout << m << endl;
    my_list.insert(m, k);
    my_list.print();  //виведення дерева
    //вилучення елемента k
    cout << "Delete = ";
    //cin >> k;
    k = 5;
    cout << k << endl;
    if (!my_list.remove(k))
        cout << "no find " << endl;
    my_list.print();  //виведення дерева
//
//	delete pbeg;  //знищення дерева
    //system("pause");
    return 0;
}

//--------------------------------------------------------
//пошук елемента за ключем
template<typename T>
Node<T> *find(Node<T> * const pbeg, T d) {
    Node<T> *pv = pbeg;
    while (pv) {
        if (pv->data == d)
            break;
        pv = pv->next;
    }
    return pv;
}

