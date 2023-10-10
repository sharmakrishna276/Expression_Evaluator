/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt() {
    size=65;
    sign=0;
    capacity=65;
    unlimited_int=new int[capacity];
}

UnlimitedInt::UnlimitedInt(string str) {
    int sz=str.size();
    if (sz==1) {
        if (str[0]=='0') {
            size=1;
            sign=0;
            capacity=1;
            unlimited_int=new int[capacity];
            *(unlimited_int+size-1)=0;
        }
    }
    else {
        if (str[0]=='-') {
            size=sz-1;
            sign=-1;
            capacity=sz-1;
            unlimited_int=new int[capacity];
            for (int i=0;i<size;i++) {
                int x=str[i+1];
                *(unlimited_int+i)=x;
            }         
        }
        else {
            size=sz;
            sign=1;
            capacity=sz;
            unlimited_int=new int[capacity];
            for (int i=0;i<size;i++) {
                int x=str[i];
                *(unlimited_int+i)=x;
            }         
        }
    }
}

UnlimitedInt::UnlimitedInt(int i) {
    if (i==0) {
        size=1;
        sign=0;
        capacity=1;
        unlimited_int=new int[capacity];
        *(unlimited_int+size-1)=0;
    }
    else {
        if (i<0) {
            sign=-1;
            int temp=-1*i;
            while (temp>0) {
                size++;
                capacity++;
                temp/=10;
            }
            unlimited_int=new int[capacity];
            int temp2=-1*i;
            int j=size-1;
            while (temp2>0) {
                *(unlimited_int+j)=temp2%10;
                temp2/=10;
                j--;
            }
        }
        else {
            sign=1;
            int temp=i;
            while (temp>0) {
                size++;
                capacity++;
                temp/=10;
            }
            unlimited_int=new int[capacity];
            int temp2=i;
            int j=size-1;
            while (temp2>0) {
                *(unlimited_int+j)=temp2%10;
                temp2/=10;
                j--;
            }
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    size=sz;
    capacity=cap;
    sign=sgn;
    unlimited_int=ulimited_int;
}

UnlimitedInt::~UnlimitedInt() {
    delete [] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

UnlimitedInt* compare_abs(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_size()>i2->get_size()) {
        return i1;
    }
    else if (i1->get_size()<i2->get_size()) {
        return i2;
    }
    else {
        for (int i=0;i<i1->get_size();i++) {
            if ((*(i1->get_array()+i))>(*(i2->get_array()+i))) {
                return i1;
            }
            else if ((*(i1->get_array()+i))<(*(i2->get_array()+i))) {
                return i2;
            }
            else {
            }
        }
        return i1;
    }
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign()==i2->get_sign()) {
        if (i1->get_sign()==0) {
            return i1;
        }
        else if (i1->get_sign()==1) {
            int cap=max(i1->get_capacity(),i2->get_capacity())+1;
            int* number=new int[cap];
            *(number+0)=0;
            int idx=min(i1->get_size(),i2->get_size());
            int j=1;
            while (j<=idx) {
                *(number+cap-j)=(*(i1->get_array()+i1->get_size()-j))+(*(i2->get_array()+i2->get_size()-j));
                j++;
            }
            while (j<cap) {
                if (i1->get_size()>i2->get_size()) {
                    *(number+cap-j)=(*(i1->get_array()+i1->get_size()-j));
                    j++;
                }
                else {
                    *(number+cap-j)=(*(i2->get_array()+i2->get_size()-j));
                    j++;        
                }
            }
            for (int k=(cap-1);k>0;k--) {
                (*(number+k-1))+=(*(number+k))/10;
                (*(number+k))%=10;
            }
            if (*(number+0)==0) {
                int* num2=new int[cap-1];
                for (int i=0;i<(cap-1);i++) {
                    *(num2+i)=*(number+i+1);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-1,1,cap-1);
                return ans;
            }
            UnlimitedInt* ans=new UnlimitedInt(number,cap,1,cap);
            return ans;
        }
        else {
            int cap=max(i1->get_capacity(),i2->get_capacity())+1;
            int* number=new int[cap];
            *(number+0)=0;
            int idx=min(i1->get_size(),i2->get_size());
            int j=1;
            while (j<=idx) {
                *(number+cap-j)=(*(i1->get_array()+i1->get_size()-j))+(*(i2->get_array()+i2->get_size()-j));
                j++;
            }
            while (j<cap) {
                if (i1->get_size()>i2->get_size()) {
                    *(number+cap-j)=(*(i1->get_array()+i1->get_size()-j));
                    j++;
                }
                else {
                    *(number+cap-j)=(*(i2->get_array()+i2->get_size()-j));
                    j++;        
                }
            }
            for (int k=(cap-1);k>0;k--) {
                (*(number+k-1))+=(*(number+k))/10;
                (*(number+k))%=10;
            }
            if (*(number+0)==0) {
                int* num2=new int[cap-1];
                for (int i=0;i<(cap-1);i++) {
                    *(num2+i)=*(number+i+1);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-1,-1,cap-1);
                return ans;
            }
            UnlimitedInt* ans=new UnlimitedInt(number,cap,-1,cap);
            return ans;
        }
    }
    else {
        if (i1->get_sign()==0) {
            return i2;
        }
        else if (i2->get_sign()==0) {
            return i1;
        }
        else if (i1->get_sign()>0) {
            UnlimitedInt* big=compare_abs(i1,i2);
            if (big==i1) {
                int cap=i1->get_capacity();
                int* number=new int[cap];
                int idx=i2->get_capacity();
                int j=cap-idx;
                for (int i=0;i<j;i++) {
                    *(number+i)=(*(i1->get_array()+i));
                }
                for (int i=j;i<cap;i++) {
                    if (*(i1->get_array()+i)>=*(i2->get_array()+i-j)) {
                        *(number+i)=(*(i1->get_array()+i))-(*(i2->get_array()+i-j));
                    }
                    else {
                        *(number+i-1)-=1;
                        *(number+i)=(*(i1->get_array()+i))-(*(i2->get_array()+i-j))+10;
                    }
                }
                int n=0;
                for (int k=0;k<cap;k++) {
                    if (*(number+k)!=0) {
                        n=k;
                        break;
                    }
                }
                int* num2=new int[cap-n];
                for (int i=0;i<(cap-n);i++) {
                    *(num2+i)=*(number+i+n);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,1,cap-n);
                return ans;
            }
            else {
                int cap=i2->get_capacity();
                int* number=new int[cap];
                int idx=i1->get_capacity();
                int j=cap-idx;
                for (int i=0;i<j;i++) {
                    *(number+i)=(*(i2->get_array()+i));
                }
                for (int i=j;i<cap;i++) {
                    if (*(i2->get_array()+i)>=*(i1->get_array()+i-j)) {
                        *(number+i)=(*(i2->get_array()+i))-(*(i1->get_array()+i-j));
                    }
                    else {
                        *(number+i-1)-=1;
                        *(number+i)=(*(i2->get_array()+i))-(*(i1->get_array()+i-j))+10;
                    }
                }
                int n=0;
                for (int k=0;k<cap;k++) {
                    if (*(number+k)!=0) {
                        n=k;
                        break;
                    }
                }
                int* num2=new int[cap-n];
                for (int i=0;i<(cap-n);i++) {
                    *(num2+i)=*(number+i+n);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,-1,cap-n);
                return ans; 
            }
        }
        else {
            UnlimitedInt* big=compare_abs(i1,i2);
            if (big==i1) {
                int cap=i1->get_capacity();
                int* number=new int[cap];
                int idx=i2->get_capacity();
                int j=cap-idx;
                for (int i=0;i<j;i++) {
                    *(number+i)=(*(i1->get_array()+i));
                }
                for (int i=j;i<cap;i++) {
                    if (*(i1->get_array()+i)>=*(i2->get_array()+i-j)) {
                        *(number+i)=(*(i1->get_array()+i))-(*(i2->get_array()+i-j));
                    }
                    else {
                        *(number+i-1)-=1;
                        *(number+i)=(*(i1->get_array()+i))-(*(i2->get_array()+i-j))+10;
                    }
                }
                int n=0;
                bool tp=false;
                for (int k=0;k<cap;k++) {
                    if (*(number+k)!=0) {
                        n=k;
                        tp=true;
                        break;
                    }
                }
                if (!tp) {
                    delete [] number;
                    int* nuum=new int[1];
                    *(nuum+0)=0;
                    UnlimitedInt* ans=new UnlimitedInt(nuum,1,0,1);
                    return ans;
                }
                int* num2=new int[cap-n];
                for (int i=0;i<(cap-n);i++) {
                    *(num2+i)=*(number+i+n);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,-1,cap-n);
                return ans;
            }
            else {
                int cap=i2->get_capacity();
                int* number=new int[cap];
                int idx=i1->get_capacity();
                int j=cap-idx;
                for (int i=0;i<j;i++) {
                    *(number+i)=(*(i2->get_array()+i));
                }
                for (int i=j;i<cap;i++) {
                    if (*(i2->get_array()+i)>=*(i1->get_array()+i-j)) {
                        *(number+i)=(*(i2->get_array()+i))-(*(i1->get_array()+i-j));
                    }
                    else {
                        *(number+i-1)-=1;
                        *(number+i)=(*(i2->get_array()+i))-(*(i1->get_array()+i-j))+10;
                    }
                }
                int n=0;
                bool tp=false;
                for (int k=0;k<cap;k++) {
                    if (*(number+k)!=0) {
                        n=k;
                        tp=true;
                        break;
                    }
                }
                if (!tp) {
                    delete [] number;
                    int* nuum=new int[1];
                    *(nuum+0)=0;
                    UnlimitedInt* ans=new UnlimitedInt(nuum,1,0,1);
                    return ans;
                }
                int* num2=new int[cap-n];
                for (int i=0;i<(cap-n);i++) {
                    *(num2+i)=*(number+i+n);
                }
                delete [] number;
                UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,1,cap-n);
                return ans;
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i2->get_sign()==0) {
        return i1;
    }
    else if (i2->get_sign()==1) {
        UnlimitedInt* temp=new UnlimitedInt(i2->get_array(),i2->get_size(),-1,i2->get_size());
        UnlimitedInt* ans=add(i1,temp);
        delete temp;
        return ans;
    }
    else {
        UnlimitedInt* temp=new UnlimitedInt(i2->get_array(),i2->get_size(),1,i2->get_size());
        UnlimitedInt* ans=add(i1,temp);
        delete temp;
        return ans;  
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign()==0) {
        return i1;
    }
    else if (i2->get_sign()==0) {
        return i2;
    }
    else {
        int cap=(i1->get_capacity())+(i2->get_capacity());
        int* number=new int[cap];
        for (int i=0;i<cap;i++) {
            *(number+i)=0;
        }
        for (int i=i1->get_size()-1;i>=0;i--) {
            for (int j=i2->get_size()-1;j>=0;j--) {
                *(number+i+j)+=(*(i1->get_array()+i))*(*(i2->get_array()+j));
            }
        }
        for (int i=cap-1;i>0;i--) {
            *(number+i-1)+=(*(number+i)/10);
            *(number+i)%=10;
        }
        int n=0;
        for (int k=0;k<cap;k++) {
            if (*(number+k)!=0) {
                n=k;
                break;
            }
        }
        int* num2=new int[cap-n];
        for (int i=0;i<(cap-n);i++) {
            *(num2+i)=*(number+i+n);
        }
        delete [] number;
        if (i1->get_sign()==i2->get_sign()) {
            UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,1,cap-n);
            return ans;
        }
        else {
            UnlimitedInt* ans=new UnlimitedInt(num2,cap-n,-1,cap-n);
            return ans;
        }
    }
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* ans=NULL;
    return ans;   
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* temp=div(i1,i2);
    UnlimitedInt* temp2=mul(temp,i2);
    UnlimitedInt* ans=sub(i1,temp2);
    delete temp;
    delete temp2;
    return ans;
}

string UnlimitedInt::to_string() {
    string ans="";
    if (sign<0) {
        ans+="-";
    }
    for (int i=0;i<size;i++) {
        ans+=*(unlimited_int+i);
    }
    return ans;
}