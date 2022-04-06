#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <cstdio>

using namespace std;


struct Node
{
    long key;
    Node *left;
    Node *right;
    Node *parent;
};

void add(Node *&root, int key);
void findMin(Node *root);
void findMax(Node *root);
void inOrder(Node *root);
void preOrder(Node *root);
void transplant(Node *root, Node *u, Node *v);
void deleteElement(Node *root, int key);
void deletePostOrder(Node *root);
void partPreOrder(Node *root, int key);
void createAVL(Node *&root, int arr[], int s, int e);

void heapsort(int T[], int size);
void maxHeapify(int* T, int i, int heapSize);
void buildMaxHeap(int* T, int heapSize);
int cinInt();
void generateRandomArray(int size, int t[]);
void deletePostOrder2(Node *root);

void transplant(Node *root, Node *u, Node *v);
void deleteElement(Node *root, int key);
void leftRotate(Node *&root, Node *x);
void rightRotate(Node *&root, Node *x);
int log2 (int x);
void DSW(Node *&root);



int main()
{
    Node *root;
    root = nullptr;
    int key, del, arrSize, randomBSTv;
    long randomBST;
    double sortTime;
    int *pdel;

    ///////////////
    cout << "\t\t\t\tMENU:\n\n";
    cout << "l - wygeneruj losowe drzewo\tA - stworz drzewo AVL\ta - dodaj element do drzewa\n";
    cout << "d - usun elementy drzewa\tD - usun cale drzewo\tr - rownowaz drzewo\n";
    cout << "m - wyswietl minimum\t\tM - wyswietl maksimum\ti - wyswietl in-order\n";
    cout << "p - wyswietl pre-order\t\tP - fragment pre-order\t\n";///t - przejdz do menu testow
    cout << "x - zakoncz program\n\n";


    while(1)
    {
        char o;
        cout << "Wybierz operacje: ";
        cin.clear();
        cin.sync();
        cin >> o;
        switch(o)
        {
        case 'r':
            if(root == nullptr)
            {
                cout << "\nStworz drzewo aby je zrownowazyc\n" << endl;
            }
            else
            {
                cout << "\nPorzadek pre-order przed rownowazeniem:" << endl;
                preOrder(root);
                DSW(root);
                cout << "\nDrzewo zostalo zrownowazone.\nPorzadek pre-order po zrownowazeniu:\n";
                preOrder(root);
                cout << "\n\n";
            }
            break;
        case 'x':
            cout << "\nProgram zakonczony" << endl;
            break;
        case 'a'://
            cout << "\nPodaj klucz: ";
            //cin >> key;
            key = cinInt();
            add(root, key);
            cout << "Dodano element.\n" << endl;
            break;
        case 'm'://
            if(root != nullptr)
            {
                cout << "\nSciezka poszukiwania: " << endl;
                findMin(root);
                cout << endl;
            }
            else
                cout << "\nDrzewo jest puste, wprowadz dane aby wyswietlic wartosc minimalna.\n\n";
            break;
        case 'M'://
            if(root != nullptr)
            {
                cout << "\nSciezka poszukiwania: " << endl;
                findMax(root);
                cout << endl;
            }
            else
                cout << "\nDrzewo jest puste, wprowadz dane aby wyswietlic wartosc maksymalna.\n\n";
            break;
        case 'l'://
            if(root != nullptr)
            {
                cout << "\nJuz stworzyles drzewo, aby utworzyc nowe drzewo aktualne zostanie usuniete.\nCzy chcesz kontynuowac? y/n\t(d - dodaj na koniec)\n";
                cin.clear();
                cin.sync();
                cin >> o;
                while(o != 'y' && o != 'n' && o != 'd')
                {
                    cout << "Wprowadzono nieobslugiwana komende\ny - tak\tn - nie\td - dodaj do istniejacego drzewa\n";
                    cin.clear();
                    cin.sync();
                    cin >> o;
                }
                if(o == 'y')
                {
                    deletePostOrder2(root);
                    root = nullptr;
                }
                else if(o == 'd')
                {
                }
                else
                    break;
            }
            cout << "\nwygenerowac dane wejsciowe czy wczytac z klawiatury?\nw - wygeneruj\tk - wczytaj z klawiatury\n";
            cin.clear();
            cin.sync();
            cin >> o;
            while(o != 'w' && o != 'k')
            {
                cout << "Wprowadzono nieobslugiwana komende\nw - wygeneruj\tk - wczytaj z klawiatury\n";
                cin.clear();
                cin.sync();
                cin >> o;
            }
            srand(time(nullptr));
            cout << "Podaj rozmiar losowego drzewa BST: ";

            randomBST = cinInt();
            if(o == 'w')
            {
                clock_t start, stop;
                start = clock();
                for(int i=0; i<randomBST; i++)
                {
                    add(root, rand()%(randomBST*10));
                }
                stop = clock();
                sortTime = (stop - start)/(double)CLOCKS_PER_SEC;
                cout << "\nCzas sortowania drzewa: " << sortTime << endl;
            }
            else
            {
                cout << "Podaj dane:\n";
                for(int i=0; i<randomBST; i++)
                {
                    randomBSTv = cinInt();

                    add(root, randomBSTv);
                }
            }

            cout << "\nWygenerowano losowe drzewo BST.\n" << endl;
            break;
        case 'd'://
            cout << "Ile elementow chcesz usunac? ";
            del = cinInt();
            pdel = new int [del];
            cout << "Wartosci elementow do usuniecia:" <<endl;
            for(int i=0; i<del; i++)
            {
                pdel[i] = cinInt();
            }
            for(int i=0; i<del; i++)
            {
                deleteElement(root, pdel[i]);
            }
            cout << "Usuwanie zakonczone.\n" << endl;
            break;
        case 'D'://
            cout << "\nKolejno usuniete elementy:\n";
            deletePostOrder(root);
            cout << "\n\n";
            root = nullptr;
            break;

        case 'i'://
            if(root != nullptr)
            {
                cout << "\nIn-order:" << endl;
                inOrder(root);
                cout << "\n\n";
            }
            else
                cout << "\nDrzewo jest puste, wprowadz dane aby je wyswietlic in-order.\n" << endl;
            break;
        case 'p'://
            if(root != nullptr)
            {
                cout << "\nPre-order:" << endl;
                preOrder(root);
                cout << "\n\n";
            }
            else
                cout << "\nDrzewo jest puste, wprowadz dane aby je wyswietlic pre-order.\n" << endl;
            break;
        case 'P'://
            cout << "\nPodaj klucz: ";
            cin.clear();
            cin.sync();
            key = cinInt();
            partPreOrder(root, key);
            cout << "\n\n";
            break;
        case 'A'://
            if(root != nullptr)///
            {
                cout << "\nJuz stworzyles drzewo, aby utworzyc nowe drzewo aktualne zostanie usuniete.\nCzy chcesz kontynuowac? y/n\t(d - dodaj na koniec)\n";
                cin.clear();
                cin.sync();
                cin >> o;
                while(o != 'y' && o != 'n')
                {
                    cout << "Wprowadzono nieobslugiwana komende\ny - tak\tn - nie\n";
                    cin.clear();
                    cin.sync();
                    cin >> o;
                }
                if(o == 'y')
                {
                    deletePostOrder2(root);
                    root = nullptr;
                }
                else
                    break;
            }///
            cout << "\nwygenerowac dane wejsciowe czy wczytac z klawiatury?\nw - wygeneruj\tk - wczytaj z klawiatury\n";
            cin >> o;
            while(o != 'w' && o != 'k')
            {
                cout << "Wprowadzono nieobslugiwana komende\nw - wygeneruj\tk - wczytaj z klawiatury\n";
                cin.clear();
                cin.sync();
                cin >> o;
            }
            if(o != 'w' && o != 'k')
            {
                cout << "Wprowadzono nieobslugiwana komende\nw - wygeneruj\tk - wczytaj z klawiatury\n";
                cin.clear();
                cin.sync();
                cin >> o;
            }
            cout << "Podaj rozmiar drzewa AVL: ";
            arrSize = cinInt();
            int *arr;
            arr = new int [arrSize];
            if(o == 'w')
            {
                generateRandomArray(arrSize, arr);
            }
            else
            {
                cout << "Podaj dane: " << endl;
                for(int i=0; i<arrSize; i++)
                {
                    cin >> arr[i];
                }
            }
            clock_t start, stop;
            start = clock();
            heapsort(arr, arrSize);
            createAVL(root, arr, 0, arrSize-1);
            stop = clock();
            sortTime = (stop - start)/(double)CLOCKS_PER_SEC;
            cout << "\nUtworzono drzewo AVL.\nCzas tworzenia drzewa: " << sortTime << "\n\n";
            break;
        ///case 't':
            ///tu wpisz testy//////////////////////////
            ///break;
        default:
            cout << "\nProgram nie obsluguje danej komendy, \nwprowadz komende dostepna w menu:\n" << endl;
            break;
        }


        if(o == 'x')
        {
            break;
        }
    }


    delete root;
    return 0;
}


void add(Node *&root, int key)
{
    Node *n = new Node;
    n->key = key;
    Node *ptr;
    ptr = root;
    //cout << "X";
    if(ptr != nullptr)
    {
        while(ptr != nullptr)
        {
            if(key < ptr->key)
            {
                //cout << "D";
                if(ptr->left == nullptr)
                {
                    ptr->left = n;
                    n->parent = ptr;
                    n->left = nullptr;
                    n->right = nullptr;
                    break;
                }
                else
                    ptr = ptr->left;
            }
            else
            {
                if(ptr->right == nullptr)
                {
                    ptr->right = n;
                    n->parent = ptr;
                    n->left = nullptr;
                    n->right = nullptr;
                    break;
                }
                else
                    ptr = ptr->right;
            }
        }
        //cout << ".";
    }
    else
    {
        //cout << "Drzewo puste" << endl;
        n->left = root;
        n->right = root;
        n->parent = nullptr;/// /////////////////////////////////////////////?
        root = n;

        //ptr->left = nullptr;
        //ptr->right = nullptr;
    }
}

/*void add(Node *&root, int key)
{
    Node *n = new Node;
    n->key = key;
    Node *ptr, *y;
    ptr = root;
    y = nullptr;
    while(ptr != nullptr)
    {
        y = ptr;
        if(n->key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    n->parent = y;
    if(y == nullptr)
    {
        root = n;
    }
    else if(n->key < y->key)
    {
        y->left = n;
    }
    else
    {
        y->right = n;
    }
}*/

void findMin(Node *root)
{
    Node *ptr = root;

    while(ptr != nullptr)
    {
        if(ptr->left == nullptr)
        {
            cout << ptr->key << "\nmin: " << ptr->key << endl;
        }
        else
        {
            cout << ptr->key << " -> ";
        }
        ptr = ptr->left;
    }
}

Node *treeMin(Node *root)
{
    Node *ptr = root;

    while(ptr->left != nullptr)
    {
        ptr = ptr->left;
    }
    return ptr;
}

void findMax(Node *root)
{
    Node *ptr = root;

    while(ptr != nullptr)
    {
        if(ptr->right == nullptr)
        {
            cout << ptr->key << "\nmax: " << ptr->key << endl;
        }
        else
        {
            cout << ptr->key << " -> ";
        }
        ptr = ptr->right;
    }
}

Node *treeMax(Node *root)
{
    Node *ptr = root;

    while(ptr->right != nullptr)
    {
        ptr = ptr->right;
    }
    return ptr;
}

void inOrder(Node *root)
{
    Node *ptr = root;
    if(ptr != nullptr)
    {
        inOrder(ptr->left);
        cout << ptr->key << ", ";
        inOrder(ptr->right);
    }
}

void preOrder(Node *root)
{
    Node *ptr = root;
    if(ptr != nullptr)
    {
        cout << ptr->key << ", ";
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

void deletePostOrder(Node *root)
{
    Node *ptr = root;

    if(ptr != nullptr)
    {
        deletePostOrder(ptr->left);
        deletePostOrder(ptr->right);
        cout << ptr->key << ",";
        free(ptr);
    }
}

void partPreOrder(Node *root, int key)
{
    Node *ptr = root;

    while(ptr != nullptr && ptr->key != key)
    {
        if(key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    if(ptr == nullptr)
        cout << "\nDrzewo nie zawiera podanego klucza.\n";
    preOrder(ptr);
}

void createAVL(Node *&root, int arr[], int s, int e)
{
    int median = s+(e+1-s)/2;
    add(root, arr[median]);

    if(s < e)
    {
        createAVL(root, arr, s, median-1);
        if(s+1 < e)
        {
            createAVL(root, arr, median+1, e);
        }
    }
}


void heapsort(int T[], int size)
{
    int heapSize = size-1;
    buildMaxHeap(T, heapSize);
    for(int i=heapSize; i>0; i--)
    {
        int tmp = T[0];
        T[0] = T[i];
        T[i] = tmp;
        heapSize--;
        maxHeapify(T, 0, heapSize);
    }
}

void maxHeapify(int* T, int i, int heapSize)
{
    int l = (i+1)*2-1;
    int r = (i+1)*2;
    int least;
    if(l <= heapSize && T[l] > T[i])
    {
        least = l;
    }
    else
    {
        least = i;
    }
    if(r <= heapSize && T[r] > T[least])
    {
        least = r;
    }
    if(least != i)
    {
        int tmp = T[i];
        T[i] = T[least];
        T[least] = tmp;
        maxHeapify(T, least, heapSize);
    }
}

void buildMaxHeap(int* T, int heapSize)
{
    for(int i=heapSize/2; i>-1; i--)
    {
        maxHeapify(T, i, heapSize);
    }
}

int cinInt()
{
    int x;
    while(!(cin >> x))
    {
        cin.clear();
        cin.sync();
        cout << "Podaj liczbe: ";
    }
    return x;
}

void generateRandomArray(int size, int t[])
{
    time_t x;
    srand((unsigned) time(&x));
    for(int i=0; i<size; i++)
    {
        t[i] = rand()%(10*size);
    }
}

void deletePostOrder2(Node *root)
{
    Node *ptr = root;

    if(ptr != nullptr)
    {
        deletePostOrder2(ptr->left);
        deletePostOrder2(ptr->right);
        free(ptr);
    }
}

void deleteElement(Node *root, int key)
{
    Node *ptr = root;

    while(ptr != nullptr && ptr->key != key)
    {
        if(key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    if(ptr == nullptr)
    {
        cout << "Drzewo nie zawiera elementu o kluczu " << key << endl;
    }
    else if(ptr->left == nullptr)
    {
        transplant(root, ptr, ptr->right);
    }
    else if(ptr->right == nullptr)
    {
        transplant(root, ptr, ptr->left);
    }
    else
    {
        Node *y = treeMin(ptr->right);
        if(y->parent != ptr)
        {
            transplant(root, y, y->right);
            y->right = ptr->right;
            y->right->parent = y;
        }
        transplant(root, ptr, y);
        y->left = ptr->left;
        y->left->parent = y;
    }
}

void transplant(Node *root, Node *u, Node *v)
{
    if(u->parent == nullptr)
    {
        root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if(v != nullptr)
    {
        v->parent = u->parent;
    }
}

void leftRotate(Node *&root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if(y->left != nullptr)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nullptr)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(Node *&root, Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if(y->right != nullptr)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nullptr)
    {
        root = y;
    }
    else if(x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

int log2 (int x)
{
    int y = 1;

    while( ( x >>= 1 ) > 0 )
        y <<= 1;

    return y;
}

void DSW(Node *&root)
{
    int n=0,s=0,i=0;
    Node* p = root;
    while(p)
    {
        if(p->left != nullptr)
        {
            rightRotate(root,p);
            p = p->parent;
        }
        else
        {
            n++;
            p = p->right;
        }
    }

    s = n + 1 - log2 (n + 1);

    p = root;
    for(i=0; i<s; i++)
    {
        leftRotate(root, p);
        p = p->parent->right;
    }

    n -= s;

    while(n > 1)
    {
        n >>= 1;
        p = root;
        for(i=0; i<n; i++)
        {
            leftRotate(root, p);
            p = p->parent->right;
        }
    }
}
