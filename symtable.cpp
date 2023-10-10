/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable() {
    size=0;
    root=NULL;
}

void deleteSymbolTable(SymEntry* root) {
    if (root==NULL) {
        return;
    }
    deleteSymbolTable(root->left);
    deleteSymbolTable(root->right);
    delete root;
}

SymbolTable::~SymbolTable() {
    deleteSymbolTable(root);
}

void SymbolTable::insert(string k, UnlimitedRational* v) {
    SymEntry* node = new SymEntry(k,v);
    if (root==NULL) {
        root=node;
        size++;
    }
    SymEntry* a=root;
    SymEntry* b=NULL;
    while (a!=NULL) {
        if ((a->key)>k) {
            b=a;
            a=a->left;
        }
        else if (a->key==k) {
            a->val=v;
            break;
        }
        else {
            b=a;
            a=a->right;
        }
    }
    if (a==NULL) {
        a=node;
        size++;
    }
    return;
}

void SymbolTable::remove(string k) {
    SymEntry* temp=root;
    SymEntry* parent=NULL;
    while (temp->key!=k) {
        if ((temp->key)>k) {
            parent=temp;
            temp=temp->left;
        }
        else {
            parent=temp;
            temp=temp->right;
        }
    }
    if (temp->left==NULL && temp->right==NULL) {
        delete temp;
        size--;
    }
    else if (temp->left==NULL) {
        parent->right=temp->right;
        delete temp;
        size--;
    }
    else if (temp->right==NULL) {
        parent->left=temp->left;
        delete temp;
        size--;
    }
    else {
        SymEntry* parent2=parent;
        SymEntry* temp2=NULL;
        parent=temp;
        temp=temp->right;
        while (temp->left) {
            temp2=temp;
            temp=temp->left;
        }
        if (temp2==NULL) {
            if (parent2->left==parent) {
                parent2->left=temp;
                temp->left=parent->left;
                delete parent;
                size--;
            }
            else {
                parent2->right=temp;
                temp->left=parent->left;
                delete parent;
                size--;
            }
        }
        else {
            if (parent2->left==parent) {
                parent2->left=temp;
                temp->left=parent->left;
                temp->right=parent->right;
                temp2->left=NULL;
                delete parent;
                size--;
            }
            else {
                parent2->right=temp;
                temp->left=parent->left;
                temp->right=parent->right;
                temp2->left=NULL;
                delete parent;
                size--;
            }       
        }
    }
    return;
}

SymEntry* Search(SymEntry* root, string k) {
    if (root->key==k) {
        return root;
    }
    else if ((root->key)>k) {
        root=root->left;
        return Search(root,k);
    }
    else {
        root=root->right;
        return Search(root,k);
    }
}

UnlimitedRational* SymbolTable::search(string k) {
    SymEntry* ans=Search(root,k);
    return ans->val;
}

int SymbolTable::get_size() {
    return size;
}

SymEntry* SymbolTable::get_root() {
    return root;
}