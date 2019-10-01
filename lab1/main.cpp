#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>
#include <ctime>

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
    virtual bool kill_rekurs(T data)=0;

};


template<typename T>
Node<T> *find(Node<T>* const, T);

template<typename T>
void delete_rekurs(Node<T>*);

template<typename T>
bool kill_binary(Node<T>*, T);

template<typename T>
bool remove_binary(Node<T>*, Node<T>*, int);

template<typename T>
bool kill_rekursive(Node<T>*, T);

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
            vartree_print_rekurs(root->right, depth); // тут зміни (not depth + 1)
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
    // син зі своїми братами стає на місце видаленого батька
    // сини синів залишаються зі своїми зв'язками
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

    //видалення рівня починаючи зі знайденого елементу
    bool kill_rekurs(T key) override {
        Node<T>* pkey = find(root, key);
        Node<T>* current;
        if(!pkey)
            return false;

        if(pkey->dad->left == pkey) {
            pkey->dad->left = nullptr;
        }
        else {
            current = pkey->dad->left;
            while(current->right != pkey)
                current = current->right;
            current->right = nullptr;
            pkey->dad->left = nullptr;
        }
        delete_rekurs(pkey);
        return true;
    }
};


template<typename T>
class BinTree: public Tree<T> {
private:
    Node<T>* root;

public:
    BinTree(T first_data) {
        root = new Node<T>(first_data);//формування першого елемента дерева
    }

    ~BinTree() {
        delete_rekurs(root);
    }
    void print() override{
        root->tree_print();
    }

    //--------------------------------------------------------
    //додавання елементів в кінець дерева 2, 3, ..., nn
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
            // тут зміни відносно попереднього current
            Node<T> *el = new Node<T>(data, current, nullptr, nullptr);
            current->left = el;
        }
        else {
            Node<T> *el = new Node<T>(data, current, nullptr, nullptr);
            current->right = el;
        }
    }


//	//-------------------------------------------------------
//	//вилучення елемента
    bool kill(T key) override {
       return kill_binary(root, key);
    }

    // вилучення елемента за вказівником на батька та індексом
    bool remove(Node<T>* father, int index) override {
       return remove_binary(root, father, index);
    }

    //рекурсивне видалення всього починаючи зі знайденого елементу
    bool kill_rekurs(T key) override {
        return kill_rekursive_binary(root, key);
    }
};

template<typename T>
class SearchTree: public Tree<T> {
private:
    Node<T>* root;

public:
    SearchTree(T first_data) {
        root = new Node<T>(first_data);//формування першого елемента дерева
    }

    ~SearchTree() {
        delete_rekurs(root);
    }
    void print() override{
        root->tree_print();
    }


    void add(T data) override{
        if(find(root, data))
            return;
        Node<T>* current = root;
        Node<T>* prev = root;
        while(current) {
            prev = current;
            if(data < current->data)
                current = current->left;
            else
            if(data > current->data)
                current = current->right;
        }
        if(data < prev->data) {
            Node<T> *el = new Node<T>(data, prev, nullptr, nullptr);
            prev->left = el;
        }
        if(data > prev->data) {
            Node<T> *el = new Node<T>(data, prev, nullptr, nullptr);
            prev->right = el;
        }
    }


//	//-------------------------------------------------------
//	//вилучення елемента
    bool kill(T key) override {
        return kill_binary(root, key);
    }

    // вилучення елемента за вказівником на батька та індексом
    bool remove(Node<T>* father, int index) override {
        return remove_binary(root, father, index);
    }

    //рекурсивне видалення всього починаючи зі знайденого елементу
    bool kill_rekurs(T key) override {
        return kill_rekursive_binary(root, key);
    }
};




//-------------------------
//-------------------------
//-------------------------

// PART 2

//-------------------------
//-------------------------
//-------------------------

using std::tm;
using std::time_t;






class Date {
private:
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
public:
    Date(int y = 1900, int m = 1, int d = 1, int h = 0, int i = 0, int s = 0)  {
        year = y;
        month = m;
        day = d;
        hours = h;
        minutes = i;
        seconds = s;
    }

    // This is automatically called when '+' is used with
    // between two Complex objects
    Date operator - (Date &obj) {
        time_t time1 = std::mktime(make_tm());
        time_t time2 = std::mktime(obj.make_tm());
        time_t difference = (time1 - time2);
        struct tm *tminfo;
        tminfo = localtime ( &difference );
        Date res = make_date(tminfo);
        return res;
    }

    Date operator + (Date &obj) {
        time_t time1 = std::mktime(make_tm());
        time_t time2 = std::mktime(obj.make_tm());
        time_t difference = (time1 + time2);
        struct tm *tminfo;
        tminfo = localtime ( &difference );
        Date res = make_date(tminfo);
        return res;
    }

    bool operator < (Date &obj) {
        time_t time1 = std::mktime(make_tm());
        time_t time2 = std::mktime(obj.make_tm());
        return (time1 < time2);
    }

    bool operator == (Date &obj) {
        time_t time1 = std::mktime(make_tm());
        time_t time2 = std::mktime(obj.make_tm());
        return (time1 == time2);
    }

    bool operator > (Date &obj) {
        time_t time1 = std::mktime(make_tm());
        time_t time2 = std::mktime(obj.make_tm());
        return (time1 > time2);
    }

    // Тут також виводиться день тижня, тому це найкращий вивід
    void print() {
        time_t time1 = std::mktime(make_tm());
        std::cout << asctime (localtime(&time1));
    }


    // Звичайний вивід
    void simple_print() {
        std::cout << year << "-" << month << "-" << day << " " << hours << ":" << minutes << ":" << seconds;
    }

    tm* make_tm()
    {
        tm* tm = new struct tm;
        tm->tm_year = year - 1900;
        tm->tm_mon = month - 1;
        tm->tm_mday = day;
        tm->tm_hour = hours;
        tm->tm_min = minutes;
        tm->tm_sec = seconds;
        return tm;
    }
    Date make_date(tm* tminfo)
    {
        Date res;
        res.year = tminfo->tm_year + 1900;
        res.month = tminfo->tm_mon + 1;
        res.day = tminfo->tm_mday;
        res.hours = tminfo->tm_hour;
        res.minutes = tminfo->tm_min;
        res.seconds = tminfo->tm_sec;
        return res;
    }

    bool check_date() {
        cout << std::mktime(make_tm());
        if (std::mktime(make_tm()) == -1)
            return false;
        return true;
    }
};

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

std::ostream& operator<<(std::ostream& os, Date& date) {
    time_t time1 = std::mktime(date.make_tm());
    os << asctime(localtime(&time1));
    return os;
}



template<typename T>
T get_test_data(int index) {
    return T{index};
}

template<>
double get_test_data<double>(int index) {
    return index+0.1;
}

template<>
Date get_test_data<Date>(int index) {
    return Date{1970+index, index % 12 + 1,  index % 28 + 1, index % 24, index % 60, index % 60};
}



template<typename T>
void test_tree(Tree<T>* tree) {
    cout<<"Any tree"<<endl;
    int nn;
    T  k, m, l;
    //визначаємось з кількістю елементів
    cout << "Number = ";
    //cin >> nn;
    nn = 7;
    cout << nn << endl;
    //BinTree<double> tree { 0.1 };

    for (int i = 2; i <= nn; i++)
        tree->add(get_test_data<T>(i));
    tree->print();
    //вставка елемента k після елемента m
    cout << "Insert = ";
    //cin >> k;
    k = get_test_data<T>(10);
    cout << k << endl;
    tree->add(k);
    tree->print();  //виведення дерева
    //вилучення елемента k
    cout << "Delete = ";
    //cin >> k;
    k = get_test_data<T>(5);
    cout << k << endl;
    if (!tree->kill(k))
        cout << "no find " << endl;
    tree->print();
    cout << "Delete rekurs = ";
    l = get_test_data<T>(6);
    cout << l << endl;
    tree->kill_rekurs(l);
    tree->print();  //виведення дерева
}

//-------------------------
int main() {

//    Date date1 = Date{2012,4,2, 10, 30, 30};
//    Date date2 = Date{2003,20,2, 50, 28, 30};
//
//    date1.print();
//    date2.print();
//
//    Date date3 = date1 - date2;
//    date3.print();
//
//    Date date4 = date1 + date3;
//    date4.simple_print();


//// Structures representing the two dates
//    tm tm1 = make_tm(2012,4,2, 10, 30, 30);    // April 2nd, 2012
//    tm tm2 = make_tm(2003,2,2, 10, 28, 30);    // February 2nd, 2003
//    tm tm3 = make_tm(2004,2,2, 10, 28, 30);
//// Arithmetic time values.
//// On a posix system, these are seconds since 1970-01-01 00:00:00 UTC
//    time_t time1 = std::mktime(&tm1);
//    time_t time2 = std::mktime(&tm2);
//    time_t time3 = std::mktime(&tm2);
//
//// Divide by the number of seconds in a day
//    const int seconds_per_day = 60*60*24;
//    time_t difference = (time1 - time2);
//    time_t sum = (time3 + difference);
//
//// To be fully portable, we shouldn't assume that these are Unix time;
//// instead, we should use "difftime" to give the difference in seconds:
//    cout << asctime(localtime(&sum));
//
////    cout << portable_difference;
////    cout << difference;
//    struct tm *tminfo;
//
//    tminfo = localtime ( &difference );
//    cout << asctime(tminfo);



    using std::vector;

    cout << endl << "Working with Variable Tree:" << endl;
    Tree<vector<int>>* tree1 = new VariableSonTree<vector<int>>({1,2});
    test_tree(tree1);

    cout << endl << "Working with Binary Tree:" << endl;
    BinTree<double>* tree2 = new BinTree<double>(0.1);
    test_tree(tree2);

    cout << endl << "Working with Search Tree:" << endl;
    Tree<Date>* tree3 = new SearchTree<Date>{1};
    test_tree(tree3);
    return 0;
}

//--------------------------------------------------------
//пошук елемента за ключем
template<typename T>
Node<T> *find(Node<T> * const root, T data) {
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

template<typename T>
bool kill_binary(Node<T>* root, T key) {
    Node<T>* current;
    Node<T>* down_current;
    if (Node<T> *pkey = find(root, key)) {
        if (pkey == root) {
            root = root->left;
            current = root;
            while(current->right)
                current = current->right;
            root->dad = nullptr;
            current->right = pkey->right;
        } else if (!pkey->right && !pkey->left) { // вузол - лист

            if ((pkey->dad)->left == pkey) {
                (pkey->dad)->left = nullptr;
            } else {
                if ((pkey->dad)->right == pkey) {
                    (pkey->dad)->right = nullptr;
                }
            }

        } else if (!pkey->left) { // вузол не має лівого сина
            if((pkey->dad)->left == pkey) {
                (pkey->dad)->left = pkey->right;
                (pkey->right)->dad = pkey->dad;
            }
            if((pkey->dad)->right == pkey) {
                (pkey->dad)->right = pkey->right;
                (pkey->right)->dad = pkey->dad;
            }

        } else if (!pkey->right) { // вузол не має правого сина
            if((pkey->dad)->left == pkey) {
                (pkey->dad)->left = pkey->left;
                (pkey->left)->dad = pkey->dad;
            }
            if((pkey->dad)->right == pkey) {
                (pkey->dad)->right = pkey->left;
                (pkey->left)->dad = pkey->dad;
            }
        }
        else { // вузол має обох синів
            if((pkey->dad)->left == pkey) {
                (pkey->dad)->left = pkey->left;
                (pkey->left)->dad = pkey->dad;
                current = pkey->left;
                while(current->right)
                    current = current->right;
                current->right = pkey->right;
                (pkey->right)->dad = current;
            }
            else {
                if((pkey->dad)->right == pkey) {
                    (pkey->dad)->right = pkey->left;
                    (pkey->left)->dad = pkey->dad;
                    current = pkey->left;
                    while(current->right)
                        current = current->right;
                    current->right = pkey->right;
                    (pkey->right)->dad = current;
                }
            }
        }
        delete pkey;
        return true;
    }
    return false;
}

template<typename T>
bool remove_binary(Node<T>* root, Node<T>* father, int index) {
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
        kill_binary(root, current->data); // кожен запис зустрічається лише 1 раз
        return true;
    }
    else
        return false;
}

template<typename T>
bool kill_rekursive_binary(Node<T>* root, T key) {
    Node<T>* pkey = find(root, key);
    if(!pkey)
        return false;
    if(pkey->dad->left == pkey)
        pkey->dad->left = nullptr;
    if(pkey->dad->right == pkey)
        pkey->dad->right = nullptr;
    delete_rekurs(pkey);
    return true;
}

