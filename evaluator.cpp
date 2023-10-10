/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator() {
    symtable=new SymbolTable();
}

Evaluator::~Evaluator() {
    int size=expr_trees.size();
    for (int i=0;i<size;i++) {
        delete expr_trees[i];
    }
    delete symtable;
}

void Evaluator::parse(vector<string> code) {

    ExprTreeNode* root=new ExprTreeNode();
    expr_trees.push_back(root);
    root->id=code[1];
    root->left=new ExprTreeNode();
    root->left->type="VAR";
    root->left->id=code[0];
    ExprTreeNode* curr=new ExprTreeNode();
    root->right=curr;
    vector<ExprTreeNode*> v;
    v.push_back(curr);
    for (int i=2;i<code.size();i++) {
        if (code[i]=="(") {
            curr->left=new ExprTreeNode();
            v.push_back(curr->left);
            curr=curr->left;
        }
        else if (code[i]=="+") {
            curr->type="ADD";
            curr->right=new ExprTreeNode();
            v.push_back(curr->right);
            curr=curr->right;
        }
        else if (code[i]=="-") {
            curr->type="SUB";
            curr->right=new ExprTreeNode();
            v.push_back(curr->right);
            curr=curr->right;
        }
        else if (code[i]=="*") {
            curr->type="MUL";
            curr->right=new ExprTreeNode();
            v.push_back(curr->right);
            curr=curr->right;
        }
        else if (code[i]=="/") {
            curr->type="DIV";
            curr->right=new ExprTreeNode();
            v.push_back(curr->right);
            curr=curr->right;
        }
        else if (code[i]==")") {
            v.pop_back();
            if (v.size()>=1) {
                curr=v[v.size()-1];
            }
        }
        else if (code[i][0]=='0' || code[i][0]=='1' || code[i][0]=='2' || code[i][0]=='3' || code[i][0]=='4' || code[i][0]=='5' || code[i][0]=='6' || code[i][0]=='7' || code[i][0]=='8' || code[i][0]=='9') {
            UnlimitedInt* num=new UnlimitedInt(code[i]);
            UnlimitedInt* den=new UnlimitedInt(1);
            curr->type="VAL";
            curr->val=new UnlimitedRational(num,den);
            v.pop_back();
            if (v.size()>=1) {
                curr=v[v.size()-1];
            }         
        }
        else {
            curr->type="VAR";
            curr->id=code[i];
            v.pop_back();
            if (v.size()>=1) {
                curr=v[v.size()-1];
            }
        }
    }
}

void Evaluate(ExprTreeNode* root) {
    if (root->left==NULL && root->right==NULL) {
        if (root->type=="VAL") {
            root->evaluated_value=root->val;
            return;
        }
        else {
            
        }
    }
}

void Evaluator::eval() {
    ExprTreeNode* root=expr_trees[expr_trees.size()-1];
    if (root->left->type=="VAL" && root->right->type=="VAL") {
        if (root->type=="ADD") {
            root->evaluated_value=UnlimitedRational::add(root->left->val,root->right->val);
        }
        else if (root->type=="SUB") {
            root->evaluated_value=UnlimitedRational::sub(root->left->val,root->right->val);
        }
        else if (root->type=="MUL") {
            root->evaluated_value=UnlimitedRational::mul(root->left->val,root->right->val);
        }
        else if (root->type=="DIV") {
            root->evaluated_value=UnlimitedRational::div(root->left->val,root->right->val);
        }
        else {
        }
    }
}
