#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

//<editor-fold desc="prvi i drugi zad">
int n=4;
int vrednostB(int a[n][n],int i,int j){
    int min=100,max=-100;
    for (int k = i-1; k <= i+1; ++k) {
        for (int l = j-1; l <= j+1; ++l) {
            if(k==i&&l==j){
                continue;
            }
            int row=k,col=l;
            if(k<0){
                row=n-1;
            }
            if(l<0){
                col=n-1;
            }
            if(k==n){
                row=0;
            }
            if(l==n){
                col=0;
            }
            if(a[row][col]>max){
                max=a[row][col];
            }
            if(a[row][col]<min){
                min=a[row][col];
            }
        }
    }
    //printf("min=%d,max=%d\n",min,max);
    return abs(min-max);
}
void printM(int a[n][n]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void zad1(int a[n][n],int b[n][n]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //printf("%d\n", vrednostB(a,i,j));
            b[i][j]= vrednostB(a,i,j);
        }
    }
    printM(b);
}
int brojSamoglasnika(char tok[],int begin,int end){
    int br=0;
    for (int i = begin; i < end; ++i) {
        if(tok[i]=='a'||tok[i]=='A'||tok[i]=='e'||tok[i]=='E'||tok[i]=='i'||tok[i]=='I'||tok[i]=='o'||tok[i]=='O'||tok[i]=='u'||tok[i]=='U'){
            br++;
        }
    }
    return br;
}
int nextSpace(char str[],int i){
    while(str[i]!=' '&&str[i]!=0){
        i++;
    }
    return i;
}
void toUpper(char str[],int begin,int end){
    for (int i = begin; i < end; ++i) {
        if(str[i]>96){
            str[i]-=32;
        }
    }
}
void toLower(char str[],int begin,int end){
    for (int i = begin; i < end; ++i) {
        if(str[i]<91){
            str[i]+=32;
        }
    }
}
void zad2(char str[]){
    int prevspace=0;
    int nextspace= nextSpace(str, prevspace);
    while(nextspace <= strlen(str)){
        int brSamoglasnika= brojSamoglasnika(str, prevspace, nextspace);
        if(brSamoglasnika%2==0){
            toLower(str, prevspace, nextspace);
        }else{
            toUpper(str, prevspace, nextspace);
        }
        prevspace= nextspace + 1;
        nextspace=nextSpace(str, prevspace);
    }
    printf("%s",str);
}
//</editor-fold>

typedef struct{
    char ime[50];
    int visina;
    int tezina;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(char* ime,int visina,int tezina){
    Node* n=(Node*)malloc(sizeof(Node));
    strcpy(n->ime,ime);
    n->visina=visina;
    n->tezina=tezina;
    n->left=NULL;
    n->right=NULL;
    return n;
}

Node* addNode(Node* root,char* ime,int visina,int tezina){
    if(root){
        if(strcmp(root->ime,ime)>=0){
            root->left=addNode(root->left,ime,visina,tezina);
        }else{
           root->right=addNode(root->right,ime,visina,tezina);
        }
        return root;
    }else{
        Node* new= createNode(ime,visina,tezina);
        return new;
    }
}

int strToInt(char* tok){
    int br=0;
    for (int i = 0; i < strlen(tok); ++i) {
        br=br*10+tok[i]-48;
    }
    return br;
}

void printTree(Node* root){
    if(root){
        printTree(root->left);
        printf("%s,%d,%d\n",root->ime,root->visina,root->tezina);
        printTree(root->right);
    }
}

void najvisaInajnizaOsoba(Node* root,Node* najvisaOsoba,Node* najnizaOsoba){
    if(root){
        if(root->visina>najvisaOsoba->visina){
            strcpy(najvisaOsoba->ime,root->ime);
            najvisaOsoba->visina=root->visina;
            najvisaOsoba->tezina=root->tezina;
        }
        if(root->visina<najnizaOsoba->visina){
            strcpy(najnizaOsoba->ime,root->ime);
            najnizaOsoba->visina=root->visina;
            najnizaOsoba->tezina=root->tezina;
        }
        najvisaInajnizaOsoba(root->left,najvisaOsoba,najnizaOsoba);
        najvisaInajnizaOsoba(root->right,najvisaOsoba,najnizaOsoba);
    }
}

void nadjinajvisuINajnizuOsobu(Node* root){
    Node* najvisaOsoba= createNode("",0,0);
    Node* najnizaOsoba= createNode("",300,0);
    najvisaInajnizaOsoba(root,najvisaOsoba,najnizaOsoba);
    printf("najvisa osoba je %s visine %d i tezine %d\n",najvisaOsoba->ime,najvisaOsoba->visina,najvisaOsoba->tezina);
    printf("najniza osoba je %s visine %d i tezine %d\n",najnizaOsoba->ime,najnizaOsoba->visina,najnizaOsoba->tezina);
}

void ispisOsobaLakseOdOdredjeneTezine(Node* root,int tezina){
    if(root){
        if(root->tezina<tezina){
            printf("%s,%d,%d\n",root->ime,root->visina,root->tezina);
        }
        ispisOsobaLakseOdOdredjeneTezine(root->left,tezina);
        ispisOsobaLakseOdOdredjeneTezine(root->right,tezina);
    }
}

void freeTree(Node* root){
    if(root==NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    /*int a[][4]={{2, 1, 4, 7},{5, 3, 8, 2},{6, 1, 7, 9},{3, 0, 4, 2}};
    int b[4][4];
    zad1(a,b);
    char str[]="Inat je zao zanat ";
    zad2(str);*/

    Node* root=NULL;
    FILE* file= fopen("..\\Podaci\\UUP-21-22-JAN-G2-Z3 fajl.txt","r");
    if(file){
        char buffer[100];
        while (fgets(buffer, 100, file) != NULL) {
            char* tok= strtok(buffer,",");
            char* ime;
            strcpy(ime,tok);
            tok= strtok(NULL,",");
            int visina= strToInt(tok);
            tok= strtok(NULL,"\n");
            int tezina= strToInt(tok);
            root= addNode(root,ime,visina,tezina);
            //printf("%s", buffer);
        }
    }else{
        printf("greska");
    }
    printTree(root);

    nadjinajvisuINajnizuOsobu(root);

    ispisOsobaLakseOdOdredjeneTezine(root,70);

    freeTree(root);

    return 0;
}
