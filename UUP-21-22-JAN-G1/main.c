#include <stdio.h>
#include <string.h>
#include <malloc.h>

int n = 5;

void printM(int a[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
struct linked_list{
    char name[500];
    int numerator;
    int denominator;
    struct linked_list* next;
};

typedef struct linked_list list;
list* make_node(){
    list* node = (list*)malloc(sizeof(list));
    node->numerator = 0;
    node->denominator = 0;
    node->next = NULL;
    return node;
}


typedef struct Node {
    char *ime;
    char *dijeta;
    int brKila;
    struct Node *left, *right;
} Node;

list* find_avarege(Node* root, list* head){

    if (root){
        
        if (head){
            list* temp = head;
            int bool_ = 0;
            list* prev = temp;
            while (temp && !bool_)
            {
                if (strcmp(root->dijeta, temp->name) == 0){
                    bool_ = 1;   
                    temp->numerator += root->brKila;
                    temp->denominator ++;
                    
                }   
                prev = temp;
                temp = temp->next;
            }

            if (bool_ == 0){
                list* new = make_node();
                strcpy(new->name, root->dijeta);
                new->numerator = root->brKila;
                new->denominator = 1;
                new->next = NULL;
                prev->next = new;

            }
            
        }

        else
        {
            head = make_node();
            strcpy(head->name, root->dijeta);
            head->numerator = root->brKila;
            head->denominator ++;
            
        }
                
        find_avarege(root->left, head);
        find_avarege(root->right, head);
        return head;
        

    }


}
    

    
    
char* find_best(list* head){
    char diet[500];
    float result = 0.0;
    if (head){
        list* temp = head;
        if((temp->numerator)/temp->denominator > result){
            result = (temp->numerator)/temp->denominator;
            strcpy(diet,temp->name);
        }

    }
    else{
        printf("The list does not have a head/root element!");
    }
    char* ans = malloc(sizeof(diet));
    strcpy(ans,diet);
    return ans;
}



int maxDijagonala(int a[n][n], int i, int j) {
    int oI = i, oJ = j;
    int max = -1;
    //gore levo
    i--;
    j--;
    while (i >= 0 && j >= 0) {
        if (max < a[i][j]) {
            max = a[i][j];
        }
        i--;
        j--;
    }
    i = oI;
    j = oJ;
    //gore desno
    i--;
    j++;
    while (i >= 0 && j < n) {
        if (max < a[i][j]) {
            max = a[i][j];
        }
        i--;
        j++;
    }
    i = oI;
    j = oJ;
    //dole levo
    i++;
    j--;
    while (i < n && j >= 0) {
        if (max < a[i][j]) {
            max = a[i][j];
        }
        i++;
        j--;
    }
    i = oI;
    j = oJ;
    //dole desno
    i++;
    j++;
    while (i < n && j < n) {
        if (max < a[i][j]) {
            max = a[i][j];
        }
        i++;
        j++;
    }
    return max;
}

void zad1(int a[n][n], int b[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i][j] = maxDijagonala(a, i, j);
        }
    }
    printM(b);
}

void shiftujStrLevo(char S[], int i) {
    for (int j = i; j < strlen(S); ++j) {
        S[j] = S[j + 1];
    }
    S[strlen(S)] = 0;
}

void shiftujStrDesno(char S[], int i) {
    for (int j = strlen(S) + 1; j >= i; --j) {
        S[j + 1] = S[j];
    }
    S[strlen(S) + 2] = 0;
}

void dodajChar(char S[], int i, int brPonavljanja) {

}

void zad2(char P[], char S[]) {
    for (int i = 0; i < strlen(S); ++i) {
        int brPonavljanjaUP = 0;
        for (int j = 0; j < strlen(P); ++j) {
            if (S[i] == P[j]) {
                brPonavljanjaUP++;
            }
        }
        if (brPonavljanjaUP == 0) {
            shiftujStrLevo(S, i);
            i--;
        } else {
            for (int j = 0; j < brPonavljanjaUP - 1; ++j) {
                shiftujStrDesno(S, i);
                i++;
            }
        }
    }
    printf("%s", S);
}


Node *createNode(char *ime, char *dijeta, int brKila) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->ime = (char *) malloc(strlen(ime) + 1);
    strcpy(n->ime, ime);
    n->dijeta = (char *) malloc(strlen(dijeta) + 1);
    strcpy(n->dijeta, dijeta);
    n->brKila = brKila;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void printNode(Node *n) {
    printf("ime=%s dijeta=%s brKila=%d\n", n->ime, n->dijeta, n->brKila);
}

Node *addNode(Node *root, char *ime, char *dijeta, int brKila) {
    if (root == NULL) {
        return createNode(ime, dijeta, brKila);
    } else {
        if (strcmp(root->dijeta, dijeta) <= 0) {
            root->left = addNode(root->left, ime, dijeta, brKila);
        } else {
            root->right = addNode(root->right, ime, dijeta, brKila);
        }
        return root;
    }
}

void printTree(Node *root) {
    if (root != NULL) {
        printTree(root->left);
        printf("ime=%s dijeta=%s brKila=%d\n", root->ime, root->dijeta, root->brKila);
        printTree(root->right);
    }
}

int StrToInt(char *tok) {
    int br = 0;
    for (int i = 0; i < strlen(tok); ++i) {
        br = br * 10 + tok[i] - 48;
    }
    return br;
}

void ptrToStr(char *tok,char str[]){
    for (int i = 0; i < strlen(tok); ++i) {
        str[i]=tok[i];
    }
    str[strlen(tok)]=0;
}

int count_lines(char* filename) {
    FILE* file = fopen(filename, "r");
    int lines = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}




int main() {
    /*int a[][5] = {{1, 2, 3, 4, 5},
                  {6, 7, 8, 9, 9},
                  {1, 2, 3, 4, 5},
                  {6, 5, 8, 7, 5},
                  {2, 3, 4, 5, 6}};
    int b[5][5];
    zad1(a,b);
    char P[]="asadadio";
    char S[100]="gladansam";
    printf("%s",S);
    zad2(P,S);*/

    FILE *fp = fopen("podaci.txt", "r");
    char red[100];
    Node *root = NULL;
    int brLinija= count_lines("podaci.txt");

    char ime[100];
    char dijeta[100];
    int brKila;
    char *tok;

    if (fp != NULL) {
        for (int i = 0; i < brLinija; ++i) {
            fgets(red, (sizeof(red)/sizeof(red[0])), fp);
            tok= strtok(red, ",");
            ptrToStr(tok,ime);
            tok= strtok(NULL, ",");
            ptrToStr(tok,dijeta);
            tok=strtok(NULL, "\n");
            brKila = StrToInt(tok);
            //printf("ime=%s dijeta=%s brKila=%d\n",ime,dijeta, brKila);
            root = addNode(root, ime, dijeta, brKila);

            
        }
        fclose(fp);
    } else {
        printf("greska");
    }


    list* head=NULL;
    head=(list*)find_avarege(root,head);


    char* best_diet = find_best(head);
    printf("The best diet happens to be %s", best_diet);
    return 0;
}
