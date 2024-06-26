#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <math.h>
#include <stdbool.h>

struct tree{
    int id;
    struct tree *leftmostchild;
    struct tree *rightsibling;
    struct tree *parent;
};
typedef struct tree node;

node *root1;

node *makenode(int id){
    node *new=(node*)malloc(sizeof(node));
    new->id=id;
    new->leftmostchild=NULL;
    new->rightsibling=NULL;
    new->parent=NULL;
    return new;
}

node *find(node *r,int u){
    if (r==NULL) return NULL;
    if (r->id==u) return r;
    node *p=r->leftmostchild;
    while (p!=NULL){
        node *q=find(p,u);
        if (q!=NULL) return q;
        p=p->rightsibling; 
    }
    return NULL;
}

void insert(node *r,int u,int v){
    node *p=find(r,v);
    if (p==NULL) return;
    node *q=makenode(u);
    if (p->leftmostchild==NULL){
        p->leftmostchild=q;
        q->parent=p;
        return;
    }
    node *h=p->leftmostchild;
    while (h->rightsibling!=NULL) h=h->rightsibling;
    h->rightsibling=q;
    q->parent=p;
}

int countleaves(node *r){
    int count=0;
    if (r->leftmostchild==NULL) {
        count++;
        return count;
    }
    else{
        node *p=r->leftmostchild;
        while (p!=NULL){
            count+=countleaves(p);
            p=p->rightsibling;
        }
    }
    return count;
}

int countnode(node *r){
    int count=0;
    node *p=r->leftmostchild;
    if (p==NULL) {
        return count;
    }
    else {
        while(p!=NULL){
            count+=countnode(p)+1;
            p=p->rightsibling;
        }
    }
    return count;
}

int countchildren(node *r){
    int count=0;
    node *p=r->leftmostchild;
    if (p==NULL) return 0;
    else{
        while (p!=NULL){
            count++;
            p=p->rightsibling;
        }
    }
    return count;
}

int countkchildren(node *r,int k){
    int count=0;
    node *p=r->leftmostchild;
    if (countchildren(r)==k) count++;
    while (p!=NULL){
        count+=countkchildren(p,k);
        p=p->rightsibling;
    }
    return count;
}


int main(){
	char command[100];
	int ans[10000];
	int count=0;
	while (1){
		scanf("%s",command);
		if (strcmp(command,"*")==0) break;
		else
		if (strcmp(command,"MakeRoot")==0) {
			int u;
			scanf("%d",&u);
			root1=makenode(u);
		}
		else
		if (strcmp(command,"Insert")==0) {
			int u;
			int v;
			scanf("%d %d",&u,&v);
			insert(root1,u,v);
		}
        else
        if (strcmp(command,"CountLeaves")==0){
            int u;
            scanf("%d",&u);
            ans[count++]=countleaves(find(root1,u));
        }
        if (strcmp(command,"CountKChildren")==0){
            int u;
            int k;
            scanf("%d %d",&u,&k);
             ans[count++]=countkchildren(find(root1,u),k);
           // ans[count++]=countnode(find(root1,u));
        }

    }
    for (int i=0;i<count;i++) printf("%d\n",ans[i]);
}