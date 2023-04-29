#include <iostream>
#include <stack>
#include <math.h>
#include <string>
using namespace std;

struct node {
    string data;
    node * left;
    node * right;
};

struct tree{
    node * root = nullptr;
};

node * init_data (string val){
    node * tempNode = new node;
    tempNode -> data = val;
    tempNode -> left = nullptr;
    tempNode -> right = nullptr;
    return tempNode;
}

int getPriority(string s){
    if (s == "(") return 0;
    if (s == "+" || s == "-") return 1;
    if (s == "*" || s == "/") return 2;
    if (s == "^") return 3;
}

void process(tree &myTree, stack <node*> &node_stack, stack <string> &operator_stack, int index, int size, string s){
    if (index == size - 1){
        while (!operator_stack.empty()){
            node * x = init_data(operator_stack.top());
            operator_stack.pop();
            myTree.root = x;
            if (x -> right == nullptr){
                x -> right = node_stack.top();
                node_stack.pop();
            }
            if (x -> left == nullptr){
                x -> left = node_stack.top();
                node_stack.pop();
            }
            if (x -> left != nullptr && x -> right != nullptr){
                node_stack.push(x);
                if (operator_stack.top() == "(")
                    operator_stack.pop();
            }
        }
    }
    else {
        node * x = init_data(operator_stack.top());
        operator_stack.pop();
        myTree.root = x;
        if (x -> right == nullptr){
            x -> right = node_stack.top();
            node_stack.pop();
        }
        if (x -> left == nullptr){
            x -> left = node_stack.top();
            node_stack.pop();
        }
        if (x -> left != nullptr && x -> right != nullptr){
            node_stack.push(x);
            if (s != ")") operator_stack.push(s);
            if (operator_stack.top() == "(") operator_stack.pop();
        }

    }
}


void traversal(node * x){
    if (x == nullptr) return;
    traversal(x -> left);
    traversal(x -> right);
    cout << x -> data << " ";
}


int main() {
    stack <node*> node_stack;
    stack <string> operator_stack;
    string str, tempStr;
    cin >> str;
    tempStr = str;
    str = '(' + str + ')';
    string s[str.size()];
    int i = 0, j = 0;
    tree myTree;
    int n = str.size();
    while(i <= n - 1){
        if (str[i] >= 48 && str[i] <= 57){
            while (str[i] >= 48 && str[i] <= 57){
                s[j] = s[j] + str[i];
                i++;
            }
            j++;
        }
        else{
            s[j] = str[i];
            j++;
            i++;
        }
    }
    int priorityArr[j];
    for (int i = 0; i < j; i++){
        if (s[i] == "(" || s[i] == ")" || s[i] == "+" || s[i] == "-" || s[i] == "*" || s[i] == "/" || s[i] == "^"){
            if (operator_stack.empty()) operator_stack.push(s[i]);
            else if (s[i] == "(" || (s[i] == "+" && getPriority(s[i]) > getPriority(operator_stack.top()))||
                     (s[i] == "-" && getPriority(s[i]) > getPriority(operator_stack.top()))||
                     (s[i] == "+" && getPriority(s[i]) > getPriority(operator_stack.top()))||
                     (s[i] == "*" && getPriority(s[i]) > getPriority(operator_stack.top()))||
                     (s[i] == "/" && getPriority(s[i]) > getPriority(operator_stack.top()))||
                     (s[i] == "^" && getPriority(s[i]) > getPriority(operator_stack.top()))){
                operator_stack.push(s[i]);
            }
            else process(myTree, node_stack, operator_stack, i, j, s[i]);
        }
        else {
            node * temp;
            temp = init_data(s[i]);
            node_stack.push(temp);
        }
    }

    node * temp = myTree.root;
    cout << "Infix: " << tempStr<< endl;
    cout << "Postfix: ";
    traversal(temp);
    return 0;
}