#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

struct Node {
    char value;
    int number;
    Node* left;
    Node* right;
    bool var;
    bool optr;

    Node(string value) : var{false}, optr{false},
        left{nullptr}, right{nullptr} {
        if (value[0] > 64) {
            var = true;
            this->value = value[0];
        } else {
            number = stoi(value);
            this->value = ' ';
        }
    }
    Node(char value) : var{false}, value{value},
        optr{true}, left{nullptr}, right{nullptr} {
    }
    void setLeft (Node* left) {
        this->left = left;
    }
    void setRight (Node* right) {
        this->right = right;
    }
};

class Solver {
    Node* root;
    vector<Node*> nodes;
    //vector <char> optr = {'-','+','*'};
    stack <char> sop;
    map <char,int> optr = {{'-',1},{'+',1},{'*',2},{'/',2},{'^',3},{'(',0},{')',0}};
public:
    Solver(string expresion) : root{nullptr} {
        expresion+='#';
        string str = "";
        for (auto i : expresion) {
            if (optr.count(i) || i == 35) {
                addVnode(' ',str);
                str = "";
                eOper(i);
            } else
                str += i;
        }
        while (!sop.empty()) {
            addVnode(sop.top());
            sop.pop();
        }
        buildTree();
    }
    void eOper(char oper) {
        if (oper == 35) return;
        if (oper > 41){
            while (!sop.empty() && optr.at(sop.top()) > optr.at(oper) && sop.top() != 40) {
                addVnode(sop.top());
                sop.pop();
            }
            sop.push(oper);
        } else if (oper == 41) {
            while (!sop.empty() && sop.top() != 40) {
                addVnode(sop.top());
                sop.pop();
            }
            sop.pop();
        } else if (oper == 40) {
            sop.push(oper);
        }
    }
    void addVnode(char ch=' ',string str = "") {
        if (str == "" && ch == ' ') return;
        Node* temp = nullptr;
        if (str != "") temp = new Node(str);
        else temp = new Node(ch);
        nodes.push_back(temp);
    }
    void buildTree() {

    }
    void printn() {
        for (auto x : nodes)
            cout << x->value << " ";
    }
};