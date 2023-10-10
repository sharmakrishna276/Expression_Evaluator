/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry() {
    key="";
    val=new UnlimitedRational();
    left=NULL;
    right=NULL;
}

SymEntry::SymEntry(string k, UnlimitedRational* v) {
    key=k;
    val=v;
    left=NULL;
    right=NULL;
}

SymEntry::~SymEntry() {
    delete val;
}