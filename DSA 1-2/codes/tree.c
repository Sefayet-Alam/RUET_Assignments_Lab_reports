#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *ll;
    struct node *rl;
};

 struct node *h,*q,*p,*ax[50];
 int n;

void create();
void display();
int main()
{
    create();
    display();
    return 0;
}

void create(){
    FILE *fp;
    fp=fopen("tree.txt","r");
    int i,x,y,z;

    for(i=1;i<50;i++)
        ax[i]=(struct node*)malloc(sizeof(struct node));
        ax[0]=0;
    for(i=1;1<2;i++){
        fscanf(fp,"%d%d%d",&x,&y,&z);
        n=i;
        if(x==-1)
            break;
        ax[i]->data=y;
    	//ax[i]->ll=ax[z;]
        ax[i]->ll=ax[x];
        ax[i]->rl=ax[z];
    }
    fclose(fp);
}

void display(){
    int i,n=8;
for(i=1;i<n;i++)
    printf("%X\t\t%c\t%X\n",ax[i]->ll,ax[i]->data,ax[i]->rl);
}
