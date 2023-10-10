/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

bool greater_abs(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_size()>i2->get_size()) {
        return true;
    }
    else if (i1->get_size()<i2->get_size()) {
        return false;
    }
    else {
        for (int i=0;i<i1->get_size();i++) {
            if ((*(i1->get_array()+i))>(*(i2->get_array()+i))) {
                return true;
            }
            else if ((*(i1->get_array()+i))<(*(i2->get_array()+i))) {
                return false;
            }
            else {
            }
        }
        return false;
    }
}

UnlimitedInt* helper_gcd(UnlimitedInt* p, UnlimitedInt* q) {
    UnlimitedInt* xero=new UnlimitedInt(0);
    while (greater_abs(p,xero) && greater_abs(q,xero)) {
        if (greater_abs(p,q)) {
            p=p->mod(p,q);
        }
        else {
            q=q->mod(q,p);
        }
    }
    if (p == xero) {
        delete xero;
        return q;
    }
    delete xero;
    return p;
}

UnlimitedRational::UnlimitedRational() {
    p=new UnlimitedInt();
    q=new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    UnlimitedInt* gcd=helper_gcd(num,den);
    p=UnlimitedInt::div(num,gcd);
    q=UnlimitedInt::div(den,gcd);
    delete gcd;
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    string ans="";
    ans=p->to_string();
    return ans;
}

string UnlimitedRational::get_q_str() {
    string ans="";
    ans=q->to_string();
    return ans;
}

string UnlimitedRational::get_frac_str() {
    string num=get_p_str();
    string den=get_q_str();
    string ans=num+"/"+den;
    return ans;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str()=="0/0") {
        return i1;
    }

    if (i2->get_frac_str()=="0/0") {
        return i2;
    }

    UnlimitedInt* temp1=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* temp2=UnlimitedInt::mul(i2->get_p(),i1->get_q());
    UnlimitedInt* numerator=UnlimitedInt::add(temp1,temp2);

    UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_q());

    delete temp1;
    delete temp2;

    UnlimitedRational* ans=new UnlimitedRational(numerator,denominator);
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str()=="0/0") {
        return i1;
    }

    if (i2->get_frac_str()=="0/0") {
        return i2;
    }

    UnlimitedInt* temp1=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* temp2=UnlimitedInt::mul(i2->get_p(),i1->get_q());
    UnlimitedInt* numerator=UnlimitedInt::sub(temp1,temp2);

    UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_q());

    delete temp1;
    delete temp2;

    UnlimitedRational* ans=new UnlimitedRational(numerator,denominator);
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str()=="0/0") {
        return i1;
    }

    if (i2->get_frac_str()=="0/0") {
        return i2;
    }

    UnlimitedInt* numerator=UnlimitedInt::mul(i1->get_p(),i2->get_p());
    UnlimitedInt* denominator=UnlimitedInt::mul(i2->get_q(),i1->get_q());

    UnlimitedRational* ans=new UnlimitedRational(numerator,denominator);
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {

    if (i1->get_frac_str()=="0/0") {
        return i1;
    }

    if (i2->get_frac_str()=="0/0") {
        return i2;
    }

    UnlimitedInt* numerator=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* denominator=UnlimitedInt::mul(i2->get_p(),i1->get_q());

    UnlimitedRational* ans=new UnlimitedRational(numerator,denominator);
    return ans;
}