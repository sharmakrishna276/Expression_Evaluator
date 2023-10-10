/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
    type="";
    val=new UnlimitedRational();
    evaluated_value=new UnlimitedRational();
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    type=t;
    UnlimitedInt* den=new UnlimitedInt(1);
    val=new UnlimitedRational(v,den);
    evaluated_value=new UnlimitedRational(v,den);
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    type=t;
    val=v;
    evaluated_value=v;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
}