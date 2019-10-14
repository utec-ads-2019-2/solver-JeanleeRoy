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
            this->value = value[0]; //' ';
        }
    }
    Node(char value) : var{false}, value{value},
        optr{true}, left{nullptr}, right{nullptr} {
    }
};

class Solver {
    Node* root;
    vector<Node*> nodes;
    stack <char> sop;
    stack <Node*> stree;
    map <char,int> vars;
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
        for (auto i : nodes) {
            if (i->var) {
                if (!vars.count(i->value)) {
                    int value;
                    cout << "El valor de '" << i->value << "' es: ";
                    cin >> value;
                    vars[i->value] = value;
                }
                i->number = vars[i->value];
            }
            if (i->optr) {
                i->right = stree.top();
                stree.pop();
                i->left = stree.top();
                stree.pop();
            }
            stree.push(i);
        }
        root = stree.top();
        stree.pop();
    }
    void printn() {
        cout << "Postfix : \n\t";
        for (auto x : nodes) {
            if(x->var) cout << x->number << " ";
            else cout << x->value << " ";
        } 
        cout << endl;
    }
    void printree() {
        cout << "Tree in-order: \n\t";
        printOrder(root);
        cout << endl;
    }
    void printOrder (Node* nodo) {
            if (nodo->left) printOrder(nodo->left);
            if(nodo->var) cout << nodo->number << " ";
            else cout << nodo->value << " ";
            if (nodo->right) printOrder(nodo->right);
        }
};