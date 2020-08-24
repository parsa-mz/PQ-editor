#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

/**
    @Auther Parsa Mazaheri
    @Version 2.1
*/

struct Node
{
    char ch = 0;
    Node * prev = NULL, * next = NULL;
    Node (char _ch = 0, Node * _prev = NULL, Node * _next = NULL)
    {
        ch = _ch;
        prev = _prev;
        next = _next;
    }
};
struct LinkedList
{
    Node * start = NULL, * finish = NULL;
    Node * now = start;
    LinkedList(){
        Node * tobe = new Node;
        tobe->ch = 13;
        tobe->prev = tobe->next = NULL;
        start = finish = now = tobe;
    }
    void Insert(char ch) {

        Node * tobe = new Node;
        tobe->ch = ch;
        tobe->prev = tobe->next = NULL;
        if (now->next == NULL) {
            now->next = tobe;
            tobe->prev = now;
            finish = tobe;
        }
        else {
            now->next->prev = tobe;
            tobe->next = now->next;
            tobe->prev = now;
            now->next = tobe;
        }
        now = tobe;
    }
    void Delete()
    {
        if (now == start)
            return ;
        if (now->next == NULL) {
            now->prev->next = NULL;
            finish = now->prev;
            now = now->prev;
        }
        else {
            now->next->prev = now->prev;
            now->prev->next = now->next;
            now = now->prev;
        }
    }

    int Order_of_node(Node * a){
        int order = 0;
        while (a->ch != 13){
            a = a->prev;
            order ++;
        }
        return (order);
    }
    void GoBack() {
        if (now->prev == NULL)
            return ;
        now = now->prev;
    }
    void GoForward() {
        if (now->next == NULL)
            return ;
        now = now->next;
    }
    void GoUp() {
        Node * last = now;
        int order = Order_of_node(now);
        while (last->ch != 13)
            last = last->prev;
        if (last == start)
            return ;
        last = last->prev;
        int diff = Order_of_node(last) - order;
        while (diff > 0) {
            last = last->prev;
            diff --;
        }
        now = last;
    }
    void GoDown() {
        Node * last = now;
        int order = Order_of_node(now);
        while (last != NULL && last->ch != 13)
            last = last->next;
        if (last == NULL)
            return ;
        int order2 = 0;
        while (order2 < order && last->next != NULL) {
            last = last->next;
            order2 ++;
        }
        now = last;
    }

    string Get(Node * cur, int k = 0) {
        string ret = "";
        while (k && cur != NULL) {
            ret += cur->ch;
            cur = cur->next;
            k --;
        }
        while (k --)
            ret += (char)(0);
        return (ret);
    }

    Node * Find_first(string input, Node * nw) {
        while (nw != NULL)
        {
            if (Get(nw, (int)input.size()) == input)
                return (nw);
            nw = nw->next;
        }
        return (NULL);
    }

    vector < pair < int , int > > Find(string t) {
        int line = 0, i = 1;
        Node * cur = start->next;
        vector < pair < int , int > > V;
        while (cur != NULL) {
            if (cur->ch == 13)
                i = 0, line ++;
            string s = Get(cur, (int)t.size());
            if (s == t)
                V.push_back({line, i});
            i ++; cur = cur->next;
        }
        return (V);
    }
};
LinkedList A;
// ===============================
// Main Functions
void erase_last_char() {

    cout << '\b';
    cout << (char)(' ');
    cout << '\b';
}

ofstream out;
void Display(bool is_file = 0) {
    if (is_file == 0)
        system("cls");
    cout << "\t\t --- PQ Editor ---\n";
    cout << "=====================================================\n\n";
    char curser = '\'';
    Node * _now = A.start->next;
    if (A.now == A.start && is_file == 0)
        cout << curser;
    while (_now != NULL) {
        if (_now->ch != 13) {
            if (is_file)
                out << _now->ch;
            else
                cout << _now->ch;
        }
        else {
            if (is_file)
                out << '\n';
            else
                cout << '\n';
        }
        if (_now == A.now && is_file == 0)
            cout << curser;
        _now = _now->next;
    }
    return ;
}

void move_curser()
{
    while (A.now->next != NULL)
        A.now = A.now->next;
    Display(0);
    erase_last_char();
}
// Required for saving the file.
char filename[100];
void Save() {
    move_curser();
    cout << "\n\n\nEnter the file name : ";
    int l = 0;
    char ch = 0;
    while (ch != 13){
        ch = _getch();
        if (ch != 8){
            cout << ch;
            filename[l] = ch;
            l ++;
        }
        else if (l > 0)
                erase_last_char();
    }
    filename[l-1]= 0;
    out.open(filename);
    Display(1);
    out.close();
    cout << "File saved.";
    Sleep(1000);
}

ifstream input;
bool Open() {
    move_curser();
    cout << "\n\nEnter the file's name : ";
    char ch = 0;
    int l = 0;
    while (ch != 13){
        ch = _getch();
        if (ch != 8){
            cout << ch;
            filename[l] = ch;
            l ++;
        }
        else if (l > 0)
            erase_last_char();
    }
    filename[l-1]= 0;
    input.open(filename);
    if(input.fail())
        return false;
    A = LinkedList(); // initialize

    while (input.get(ch))
        A.Insert(ch);

    input.close();
    return true;
}

void Find() {
    move_curser();
    cout << "\n\nSearch for : ";
    char ch = 0;
    string tobe = "";
    while (ch != 13) {
        ch = _getch();
        if (ch != 8) {
            cout << ch;
            if (ch != 13)
                tobe += ch;
        }
        else {
            erase_last_char();
            if ((int)tobe.size() > 1)
                tobe = tobe.substr(0, (int)tobe.size() - 1);
        }
    }
    cout << endl;
    vector < pair < int , int > > V = A.Find(tobe);
    for (auto X : V)
        cout << X.first << " " << X.second << "\n";
    system("pause");
}

void Replace()
{
    move_curser();
    cout << "\n\nSearch for : ";
    char ch = 0;
    string input = "";
    while (ch != 13) {
        ch = _getch();
        if (ch != 8) {
            cout << ch;
            if (ch != 13)
                input += ch;
        }
        else {
            erase_last_char();
            if ((int)input.size() > 1)
                input = input.substr(0, (int)input.size() - 1);
        }
    }

    string toBeStr = "";
    cout << "\n Replace with: ";
    cin >> toBeStr;
    cerr << toBeStr << endl;
    Node *nw, *last = A.start->next;
    while (true) {
        nw = A.Find_first(input, last);
        if (nw == NULL)
            break;

        A.now = nw;

        for (int i = 0; i < input.size(); i++)
        {
            A.Delete();
            A.now = A.now->next;
        }
        //break;
        A.now = A.now->prev;
        for (int i = 0; i < toBeStr.size(); i++)
        {
            A.Insert(toBeStr[i]);
        }
        last = A.now->next;
    }
    move_curser();
    Display(0);
}

void Copy()
{
    //coming soon
}

void Paste()
{
    //coming soon
}

void Help()
{
    cout << "\n\n=====================================\n";
    cout << " \t   Help Center\n\n";
    cout << "Ctrl+C : Copy\t Ctrl+V : Paste\n";
    cout << "Ctrl+O : Open\t Ctrl+S : Save\n";
    cout << "Ctrl+F : Find\t Ctrl+R : Replace\n";
    cout << "Ctrl+Q : Quit\t Ctrl+K : Help\n";
    cout << "\n=======================================\n";
    system("pause");
}

void Core() {
    Display();
    Help()
    while (1) {
        char ch = _getch();
        if (ch == -32){
            ch = _getch();
            if (ch == 72)
                A.GoUp();
            if (ch == 75)
                A.GoBack();
            if (ch == 77)
                A.GoForward();
            if (ch == 80)
                A.GoDown();
        }
        else if (ch == 6)
            Find();
        else if (ch == 15) {
            if(Open() == false){
                cout << endl << "\nFile doesn't exist!\n\n";
                system("pause");
            }
        }
        else if (ch == 17)
            exit(0);
        else if (ch == 18)
            Replace();
        else if (ch == 3)
            Copy();
        else if (ch == 22)
            Paste();
        else if (ch == 19)
            Save();
        else if (ch == 11)
            Help();
        else if (ch == 8)
            A.Delete();
        else
            A.Insert(ch);

        Display();
    }
}

void Test() {
    while (1) {
        char ch = _getch();
        printf("%d\n", (int)ch);
    }
}
// ===============================
int main()
{
    //Test();
    Core();
}
