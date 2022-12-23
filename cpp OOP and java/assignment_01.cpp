#include <bits/stdc++.h>

using namespace std;


class Node {
    public:
    int c;
    int power;
    Node *next_node;
};


void create(Node **prev,int coeff,int pow){
   Node *curr,*temp;
   temp=*prev;
    if(temp==NULL){
        curr=new Node();
        curr->c=coeff;
        curr->power=pow;
        *prev=curr;
        curr->next_node=new Node();
        curr=curr->next_node;
        curr->next_node=NULL;
    }
    else{
        curr->c=coeff;
        curr->power=pow;
        curr->next_node=new Node();
        curr=curr->next_node;
        curr->next_node=NULL;

    }
}

void linked_list_traverse(Node *node){

    while (node->next_node != NULL) {
         if(node->c!=0) cout<<node->c;
        if(node->power!=0) cout<<"x"<<node->power;
        node = node->next_node;

        if (node->next_node != NULL) cout<<"+";

    }
    cout<<endl;
}

void add(Node **e1,Node **e2){
    Node *tmp,*prev,*tmp1,*tmp2;
    tmp=NULL;
    tmp=new Node();

     tmp1=NULL;
    tmp1=new Node();
    tmp1=*e1;

     tmp2=NULL;
    tmp2=new Node();
    tmp2=*e2;

     prev=NULL;
    prev=new Node();
     if(tmp1->power > tmp2->power){
            prev=tmp1;
            tmp1=tmp1->next_node;
        }
        else if(tmp1->power<tmp2->power){
            prev=tmp2;
            tmp2=tmp2->next_node;
        }
        else{
            prev=tmp1;
            tmp1->c=tmp1->c+tmp2->c;
            tmp1=tmp1->next_node;
            tmp2=tmp2->next_node;

        }
        *e1=prev;
    while(tmp1!=NULL && tmp2!=NULL){
        if(tmp1->power > tmp2->power){
            prev->next_node=tmp1;
            prev=tmp1;
            tmp1=tmp1->next_node;
        }
        else if(tmp1->power<tmp2->power){
            prev->next_node=tmp2;
            prev=tmp2;
            tmp2=tmp2->next_node;
        }
        else{
            prev->next_node=tmp1;
            prev=tmp1;
            tmp1->c=tmp1->c+tmp2->c;
            tmp1=tmp1->next_node;
            tmp2=tmp2->next_node;

        }
    }
     while(tmp1!=NULL || tmp2!=NULL){
        if(tmp1->power > tmp2->power){
            prev->next_node=tmp1;
            prev=tmp1;
            tmp1=tmp1->next_node;
        }
        else if(tmp1->power<tmp2->power){
            prev->next_node=tmp2;
            prev=tmp2;
            tmp2=tmp2->next_node;
        }
        else{
            prev->next_node=tmp1;
            prev=tmp1;
            tmp1->c=tmp1->c+tmp2->c;
            tmp1=tmp1->next_node;
            tmp2=tmp2->next_node;

        }
    }
    //cout<<endl;
}

vector<int>coeffs,pows;
int stringtoint(string number){
    int newNumber;
    for ( int i = number.length() -1 ; i >= 0 ; i-- ) {
    int power = number.length() - i -1;
    newNumber += (pow( 10,  power) * (number[i] - '0'));
    }
    return newNumber;
}
void inputstr(string eq){
    //cout<<eq<<endl;
    int n=eq.size();
    int l=0,r=0,k=0;
    string co="",po="";

    for(int i=0; i<n; i++)
    {
        if(eq[i]=='x')
        {

           // cout<<l<<" "<<i<<" ";
            if(l==i-1)
            {
                //case: 1x4+4sx5
                co="";
                co+=eq[l];
            }
            else if(l==i)
            {
                //case: +x3
                co="1";
            }
            else{
                co="";
                for(int j=l;j<i;j++){
                    co+=eq[j];
                }
                //cout<<" "<<co;
            }
            //cout<<endl;
           k=stringtoint(co);
            coeffs.push_back(k);
            r=i+1;

        }
        else if(eq[i]=='+' || eq[i]=='-')
        {
            if(r==i-1)
            {
                po="";
                po+=eq[r];
            }
            else if(r==i)
            {
                po="0";
            }
            else{
                po="";
                for(int j=r;j<i;j++){
                    po+=eq[j];
                }
                //cout<<" "<<po;
            }
              k=stringtoint(po);
            pows.push_back(k);

            l=i+1;
        }
    }
    bool tru=0;
    for(int i=eq.size()-1;i>=0;i--){
        if(eq[i]=='+'){
            tru=1;
            break;
        }
        else if(eq[i]=='x'){
            break;
        }
    }
    if(tru==1){
        co="";
        for(int j=l;j<n;j++){
        co+=eq[j];
        }

        k=stringtoint(co);
        coeffs.push_back(k);
        r=n;
    }
    if(r==n-1)
    {
        po="";
        po+=eq[r];
    }
    else if(r==n)
    {
        po="0";
    }
    else{
        po="";
       for(int j=r;j<n;j++){
       po+=eq[j];
        }
    }

    k=stringtoint(po);
    pows.push_back(k);

}
int main()
{

    Node *eqn1 = NULL, *eqn2 = NULL,*finaleqn=NULL;
    string firsteqn,secondeqn;
    cout<<"Input: \np1= ";
    cin>>firsteqn;//example: 13x8+7x5+32x2+54
    inputstr(firsteqn);
    for(int i=0;i<pows.size();i++){
        int a,b;
        a=coeffs[i];
        b=pows[i];
        create(&eqn1,a,b);
    }
    coeffs.clear();
    pows.clear();

    cout<<"\np2= ";
    cin>>secondeqn; // example: 3x12+17x5+3x3+98
    inputstr(secondeqn);

     for(int i=0;i<pows.size();i++){
        int a,b;
        a=coeffs[i];
        b=pows[i];
        create(&eqn2,a,b);
    }


//    cout<<"p1= ";
//     linked_list_traverse(eqn1);


//     cout<<"p2= ";
//     linked_list_traverse(eqn2);

     cout<<"\n\nOutput p1: ";
    add(&eqn1,&eqn2);
    linked_list_traverse(eqn1);
    return 0;
}
