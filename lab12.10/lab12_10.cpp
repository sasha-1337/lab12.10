#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
    Node* left,
        * right;
    int info;
};

void create(char* fname);
void read(char* fname, Node*& root);
void print(Node* root, int level);
void Min(Node* root, int& min);
void average(Node* root, int& S, int& k);
void count(Node* root, int& r, int min, double avr);
void scan(Node* root, int min, double aver, int& rootinfo);
int Height(Node* root);
int BFactor(Node* root);
Node* Delete(Node* p, int value);
Node* Insert(Node* p, int value);
Node* findMin(Node* root);
Node* rightRotation(Node* r);
Node* leftRotation(Node* r);
Node* balanceHeight(Node* r);
Node* deleteMin(Node* p);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[61];
    int choice;
    int min = 0;
    int S = 0;
    int k = 0;
    int r = 0;
    int rootinfo = 0;
    double avr = 0.0;
    Node* root = NULL;
    do
    {
        cout << "Будь ласка, оберіть команду:" << endl << endl;
        cout << " [1] - Записати значення вузлів у бінарний файл" << endl;
        cout << " [2] - Створити бінарне дерево" << endl;
        cout << " [3] - Вивести бінарне дерево на екран" << endl;
        cout << " [4] - Видалити всі вузли, які знаходяться між мінімальним та середнім значенням" << endl;
        cout << " [0] - Вийти із програми" << endl << endl;
        cout << "Введіть номер обраної команди: "; cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
            create(fname);
            break;
        case 2:
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
            read(fname, root);
            break;
        case 3:
            print(root, 0);
            cout << endl;
            break;
        case 4:
            Min(root, min);
            average(root, S, k);
            avr = S * 1.0 / k;
            count(root, r, min, avr);
            for (int i = 0; i < r; i++)
            {
                scan(root, min, avr, rootinfo);
                root = Delete(root, rootinfo);
            }
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели неправильний номер команди." << endl;
        }
    } while (choice != 0);

    return 0;
}

void create(char* fname)
{
    ofstream fout(fname, ios::binary);
    if (!fout)
    {
        cerr << "Не вдалося відкрити файл '" << fname << "'" << endl;
        return;
    }
    int value, N;
    cout << "Введіть кількість вузлів бінарного дерева: "; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cout << "Значення вузла: "; cin >> value;
        fout.write((char*)&value, sizeof(value));
    }
    cout << endl;
}

void read(char* fname, Node*& root)
{
    ifstream fin(fname, ios::binary);
    if (!fin)
    {
        cerr << "Не вдалося відкрити файл '" << fname << "'" << endl;
        return;
    }
    int value;
    while (fin.read((char*)&value, sizeof(value)))
    {
        root = Insert(root, value);
    }
}

void print(Node* root, int level)
{
    if (root != NULL)
    {
        print(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "   ";
        cout << root->info << endl;
        print(root->left, level + 1);
    }
}

void Min(Node* root, int& min)
{
    if (root != NULL)
    {
        Min(root->right, min);
        if (root->info < min)
            min = root->info;
        Min(root->left, min);
    }
}


void average(Node* root, int& S, int& k)
{
    if (root != NULL)
    {
        average(root->right, S, k);
        S += root->info;
        k++;
        average(root->left, S, k);
    }
}

void count(Node* root, int& r, int min, double avr)
{
    if (root != NULL)
    {
        count(root->right, r, min, avr);
        if ((root->info >= min) && (root->info <= avr))
            r++;
        count(root->left, r, min, avr);
    }
}

void scan(Node* root, int min, double avr, int& rootinfo)
{
    if (root != NULL)
    {
        scan(root->right, min, avr, rootinfo);
        if ((root->info >= min) && (root->info <= avr))
            rootinfo = root->info;
        scan(root->left, min, avr, rootinfo);
    }
}

int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

Node* findMin(Node* root)
{
    if (root->left != NULL)
        return findMin(root->left);
    else
        return root;
}

Node* rightRotation(Node* p)
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

Node* leftRotation(Node* q)
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    return p;
}

Node* balanceHeight(Node* p)
{
    if (BFactor(p) == 2)
    {
        if (BFactor(p->right) < 0)
            p->right = rightRotation(p->right);
        return leftRotation(p);
    }
    if (BFactor(p) == -2)
    {
        if (BFactor(p->left) > 0)
            p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    return p;
}

Node* Insert(Node* p, int value)
{
    if (!p)
    {
        p = new Node;
        p->info = value;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    if (value < p->info)
        p->left = Insert(p->left, value);
    else
        if (value > p->info)
            p->right = Insert(p->right, value);
    return balanceHeight(p);
}

Node* deleteMin(Node* p)
{
    if (p->left == 0)
        return p->right;
    p->left = deleteMin(p->left);
    return balanceHeight(p);
}

Node* Delete(Node* p, int value)
{
    if (!p)
        return 0;
    if (value < p->info)
        p->left = Delete(p->left, value);
    else if (value > p->info)
        p->right = Delete(p->right, value);
    else
    {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r)
            return q;
        Node* min = findMin(r);
        min->right = deleteMin(r);
        min->left = q;
        return balanceHeight(min);
    }
    return balanceHeight(p);
}