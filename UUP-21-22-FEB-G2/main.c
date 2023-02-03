#include <stdio.h>
#include <string.h>
#include <malloc.h>

//<editor-fold desc="prvi i drugi">
int n = 4;

void popuniNulama(int a[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 0;
        }
    }
}

void printM(int a[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void zad1(int a[n][n]) {
    popuniNulama(a);
    int rotiraj;
    scanf("%d", &rotiraj);
    int zapravoRotiraj = rotiraj % 4;
    int i = 1;
    int row, col;
    int hor, ver;
    switch (zapravoRotiraj) {
        case 0:
            hor = 1;
            ver = 0;
            row = 0;
            col = 0;
            break;
        case 1:
            ver = 1;
            hor = 0;
            row = 0;
            col = n - 1;
            break;
        case 2:
            hor = -1;
            ver = 0;
            row = n - 1;
            col = n - 1;
            break;
        case 3:
            hor = 0;
            ver = -1;
            row = n - 1;
            col = 0;
            break;
    }
    while (i <= n * n) {
        a[row][col] = i++;
        if (col == n - 1 && hor == 1) {
            hor = 0;
            ver = 1;
        }
        if (row == n - 1 && ver == 1) {
            hor = -1;
            ver = 0;
        }
        if (col == 0 && hor == -1) {
            hor = 0;
            ver = -1;
        }
        if (row == 0 && ver == -1) {
            hor = 1;
            ver = 0;
        }
        row += ver;
        col += hor;
        if (a[row][col]) {
            row -= ver;
            col -= hor;
            if (hor == 1) {
                hor = 0;
                ver = 1;
            } else if (ver == 1) {
                hor = -1;
                ver = 0;
            } else if (hor == -1) {
                hor = 0;
                ver = -1;
            } else if (ver == -1) {
                hor = 1;
                ver = 0;
            }
            row += ver;
            col += hor;
        }
    }
    printM(a);
}

void zad2(char P[], char S[]) {
    int trenutniBrPonavljanjaSlova = 0;
    int maksBrPonavljanjaSlova = 0;
    for (int i = 0; i < strlen(S); ++i) {
        trenutniBrPonavljanjaSlova = 0;
        for (int j = 0; j < strlen(P); ++j) {
            if (S[i] == P[j]) {
                trenutniBrPonavljanjaSlova++;
            }
        }
        if (trenutniBrPonavljanjaSlova > maksBrPonavljanjaSlova) {
            maksBrPonavljanjaSlova = trenutniBrPonavljanjaSlova;
        }
    }

    printf("%d ", maksBrPonavljanjaSlova);
    for (int i = 0; i < strlen(S); ++i) {
        trenutniBrPonavljanjaSlova = 0;
        for (int j = 0; j < strlen(P); ++j) {
            if (S[i] == P[j]) {
                trenutniBrPonavljanjaSlova++;
            }
        }
        if (trenutniBrPonavljanjaSlova == maksBrPonavljanjaSlova) {
            printf("%c ", S[i]);
        }
    }
}
//</editor-fold>


typedef struct Node {
    char maxi[5];
    char idea[5];
    char proizvod[50];
    int cenaMaxi;
    int cenaIdea;
    struct Node *sledeci;
} Node;

int menu() {
    printf("\nOdaberite jednu od sledecih opcija:\n");
    printf("\t1: ucitavanje radova iz fajla\n");
    printf("\t2: ispis radova na konzolu\n");
    printf("\t3: ispis svih teretana sa spravama \n");
    printf("\t4: ispis svih teretana u odredjenoj opstini\n");
    printf("\t5: brisanje podataka iz memorije i izlaz iz programa\n");
    printf("\nVasa opcija: ");
    int n;
    scanf("%d", &n);
    return n;
}

Node *createNode(char prodavnica[], char proizvod[], int cena) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (strcmp(prodavnica, "maxi") == 0) {
        strcpy(n->maxi, prodavnica);
        strcpy(n->idea, "    ");
        n->cenaMaxi = cena;
        n->cenaIdea = 0;
    } else {
        strcpy(n->idea, prodavnica);
        strcpy(n->maxi, "    ");
        n->cenaIdea = cena;
        n->cenaMaxi = 0;
    }
    strcpy(n->proizvod, proizvod);
    n->sledeci=NULL;
    return n;
}

Node *addNode(Node *root, char prodavnica[], char proizvod[], int cena) {
    if (root == NULL) {
        root = createNode(prodavnica, proizvod, cena);
        return root;
    }
    if (strcmp(root->proizvod, proizvod) == 0) {
        if (strcmp(prodavnica, "maxi") == 0) {
            strcpy(root->maxi, prodavnica);
            root->cenaMaxi = cena;
        } else {
            strcpy(root->idea, prodavnica);
            root->cenaIdea = cena;
        }
    } else {
        if (root->sledeci == NULL) {
            root->sledeci = createNode(prodavnica, proizvod, cena);
        } else {
            root->sledeci = addNode(root->sledeci, prodavnica, proizvod, cena);
        }
    }
    return root;
}

void printList(Node *root) {
    if (root) {
        printf("%s,%s,%s,%d,%d\n", root->maxi, root->idea, root->proizvod, root->cenaMaxi, root->cenaIdea);
        printList(root->sledeci);
    }
}

int strToInt(char* tok){
    int br=0;
    for (int i = 0; i < strlen(tok); ++i) {
        br=br*10+tok[i]-48;
    }
    return br;
}

Node* ucitajListu(Node* root,char* path){
    FILE* file= fopen(path,"r");
    if(file){
        char buffer[100];
        char prodavnica[5];
        char proizvod[50];
        int cena;
        while(fgets(buffer,100,file)!=NULL){
            char* tok= strtok(buffer,",");
            strcpy(prodavnica,tok);
            tok= strtok(NULL,",");
            strcpy(proizvod,tok);
            tok= strtok(NULL,"\n");
            cena= strToInt(tok);
            root= addNode(root,prodavnica,proizvod,cena);
        }
    }else{
        printf("greska");
    }
    return root;

}

int cenaArtiklaUMaksiju(Node* root,char* proizvod){
    if(root){
        if(strcmp(root->proizvod,proizvod)==0&& strcmp(root->maxi,"maxi")==0){
            return root->cenaMaxi;
        }else{
            cenaArtiklaUMaksiju(root->sledeci,proizvod);
        }
    }else{
        return 0;
    }

}
int cenaArtiklaUIdeji(Node* root,char* proizvod){
    if(root){
        if(strcmp(root->proizvod,proizvod)==0&& strcmp(root->idea,"idea")==0){
            return root->cenaIdea;
        }else{
            cenaArtiklaUIdeji(root->sledeci,proizvod);
        }
    }else{
        return 0;
    }
}

void najjeftinijaProdavnica(Node* root){
    char spisak[500];
    scanf("%s",spisak);
    int sumaMaxi=0,sumaIdea=0;
    int kolikonemaProizvodaUMaksiju=0;
    int kolikonemaProizvodaUIdeji=0;
    int jefitinijejeU=-1;
    char* proizvod= strtok(spisak,",");

    do {
        //printf("%s",proizvod);
        sumaMaxi+= cenaArtiklaUMaksiju(root,proizvod);
        sumaIdea+= cenaArtiklaUIdeji(root,proizvod);
        if(cenaArtiklaUIdeji(root,proizvod)==0){
            kolikonemaProizvodaUIdeji++;
        }

        if(cenaArtiklaUMaksiju(root,proizvod)==0){
            kolikonemaProizvodaUMaksiju++;
        }
        if(kolikonemaProizvodaUIdeji>0&&kolikonemaProizvodaUMaksiju>0){
            jefitinijejeU=-1;
            break;
        }
        if(kolikonemaProizvodaUMaksiju>0){
            jefitinijejeU=1;
        }
        if(kolikonemaProizvodaUIdeji){
            jefitinijejeU=0;
        }
        proizvod= strtok(NULL,",");
        if(sumaIdea!=0||sumaMaxi!=0){
            //printf("cena u maksiju=%d cena u ideji=%d\n",sumaMaxi,sumaIdea);
        }
    }while(proizvod!=NULL);
    if(jefitinijejeU==1){
        printf("jeftinije je u ideji");
    }else if(jefitinijejeU==0){
        printf("jeftinije je u maksiju");
    }else{
        printf("Nije moguce pronaci sve artikle u jednoj prodavnici");
    }
}


int main() {
    /*int a[4][4];
    zad1(a);
    char P[]="abccjggkkkklmm";
    char S[]="cbjm";
    zad2(P,S);*/
    Node *root = NULL;
    int m;
    /*do{
        m=menu();
        switch (m) {
            case 1:
                root= ucitajListu(root,"..\\podaci\\UUP-21-22-FEB-G2.txt");
                break;
            case 2:
                printList(root);
                break;
            case 3:
                najjeftinijaProdavnica(root);
                break;
        }
    }while(m!=5);*/
    root= ucitajListu(root,"..\\podaci\\UUP-21-22-FEB-G2.txt");
    printList(root);
    najjeftinijaProdavnica(root);
    
    
    return 0;
}
