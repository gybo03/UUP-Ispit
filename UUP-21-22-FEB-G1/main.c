#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

//<editor-fold desc="Prvi i drugi zad">
int n = 5, m = 6;

void printM(int a[n][m]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int daLiSeponoviloPoRedu(int a[n][m], int i, int k) {
    for (int j = 0; j < k; ++j) {
        if (a[i][k] == a[i][j]) {
            return -1;
        }
    }
    return 0;
}

int daLiSeponoviloPoKoloni(int a[n][m], int j, int l) {
    for (int i = 0; i < l; ++i) {
        if (a[l][j] == a[i][j]) {
            return -1;
        }
    }
    return 0;
}

int brzajednickihCifara(int a[n][m], int i, int j) {
    int br = 0;
    for (int k = 0; k < m; ++k) {
        for (int l = 0; l < n; ++l) {
            int ik = a[i][k];
            int lj = a[l][j];
            if (a[i][k] == a[l][j]) {
                if (daLiSeponoviloPoRedu(a, i, k) || daLiSeponoviloPoKoloni(a, j, l)) {
                    continue;
                }
                br++;
            }
        }
    }
    return br;
}

void umanjiRedZaB(int a[n][m], int i, int b) {
    for (int j = 0; j < m; ++j) {
        a[i][j] = abs(a[i][j] + 10 - b) % 10;
    }
}

void uvecajKolonuZaB(int a[n][m], int j, int b) {
    for (int i = 0; i < n; ++i) {
        a[i][j] = abs(a[i][j] + b) % 10;
    }
}

void zad1(int a[n][m]) {
    int trenutnoPoklapanje = 0;
    int maksPoklapanje = 0;
    int minI = -1;
    int maxRed, maxKolona;
    int trenutniRed, trenutnaKolona;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            trenutnoPoklapanje = brzajednickihCifara(a, i, j);
            if (trenutnoPoklapanje > maksPoklapanje) {
                maksPoklapanje = trenutnoPoklapanje;
                trenutnoPoklapanje = 0;
                maxRed = i;
                maxKolona = j;
            }
        }
    }
    umanjiRedZaB(a, maxRed, maksPoklapanje);
    uvecajKolonuZaB(a, maxKolona, maksPoklapanje);
    printM(a);
}

int sledeciSpejs(char str[], int i) {
    while (str[i] != ' '&&str[i]!=0) {
        i++;
    }
    return i;
}

int brUzvicnika(char str[], int i) {
    int br = 0;
    int krajReci = sledeciSpejs(str, i);
    for (int j = i; j < krajReci; ++j) {
        if (str[j] == '!') {
            br++;
        }
    }
    return br;
}

int sledeciuzvicnik(char str[], int i) {
    while (str[i] != '!') {
        i++;
    }
    return i;
}

void shiftuj(char str[], int i) {
    char temp = str[i];
    int uzvicnik = sledeciuzvicnik(str, i);
    for (int j = i; j < uzvicnik - 1; ++j) {
        str[j] = str[j + 1];
    }
    str[uzvicnik - 1] = temp;
}

void uvecajSlova(char str[], int i) {
    int spejs = sledeciSpejs(str, i);
    for (int j = 0; j < spejs; ++j) {
        if (str[j] > 96) {
            str[j] -= 32;
        }
    }
}

void shiftujLevo(char str[], int i) {
    for (int j = i; j < strlen(str); ++j) {
        str[j] = str[j + 1];
    }
    str[strlen(str)] = 0;
}

int poslednjePonavljanje(char str[], int i) {
    int br=0;
    int prviUzvicnik = sledeciuzvicnik(str, i);
    int drugiUzvicnik = sledeciuzvicnik(str, prviUzvicnik + 1);
    for (int j = drugiUzvicnik - 1; j > prviUzvicnik; --j) {
        for (int k = j-1; k > prviUzvicnik; --k) {
            if (str[j] == str[k]) {
                br++;
                shiftujLevo(str, k);
            }
        }
    }
    return br;
}

void zad2(char str[]) {
    int pocetakReci = 0;
    int spejs = sledeciSpejs(str, pocetakReci);
    while (spejs <= strlen(str)) {
        int br= brUzvicnika(str,pocetakReci);
        if (br== 0) {
            uvecajSlova(str, pocetakReci);
        } else if (br == 1) {
            shiftuj(str, pocetakReci);
        } else {
            spejs-=poslednjePonavljanje(str, pocetakReci);
        }
        pocetakReci = spejs + 1;
        spejs = sledeciSpejs(str, pocetakReci);
    }
    printf("%s", str);
}
//</editor-fold>

int strToInt(char* tok){
    int br=0;
    for (int i = 0; i < strlen(tok); ++i) {
        br=br*10+tok[i]-48;
    }
    return br;
}

typedef struct Node{
    char teretana[100];
    char opstina[100];
    int brSprava;
    int brSpravaZaKardio;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(char* teretana,char* opstina,int brSparava,int brSpravaZaKardio){
    Node* n=(Node*)malloc(sizeof(Node));
    strcpy(n->teretana,teretana);
    strcpy(n->opstina,opstina);

    n->brSprava=brSparava;
    n->brSpravaZaKardio=brSpravaZaKardio;

    n->right=NULL;
    n->left=NULL;
    return n;
}

Node* addNode(Node* root,char* opstina,char* teretana,int brSprava,int brSpravaZaKardio){
    if(root){
        if(strcmp(root->opstina,opstina)<=0){
            root->right= addNode(root->right,opstina,teretana,brSprava,brSpravaZaKardio);
        }else{
            root->left=addNode(root->left,opstina,teretana,brSprava,brSpravaZaKardio);
        }
        return root;
    }else{
        Node* new= createNode(teretana,opstina,brSprava,brSpravaZaKardio);
        return new;
    }
}

void printTree(Node* root){
    if(root){
        printTree(root->left);
        printTree(root->right);
        printf("%s-%s-%d-%d\n",root->opstina,root->teretana,root->brSprava,root->brSpravaZaKardio);
    }
}

void ispisTeretanaSaSpravama(Node* root,int brSprava){
    if(root){
        if(root->brSprava-root->brSpravaZaKardio>brSprava){
            printf("%s-%s-%d-%d\n",root->opstina,root->teretana,root->brSprava,root->brSpravaZaKardio);
        }
        ispisTeretanaSaSpravama(root->right,brSprava);
        ispisTeretanaSaSpravama(root->left,brSprava);
    }
}

void ispisSvihTeretanaSaZadatimPodstringomZaOpstinu(Node* root,char* str){
    if(root){
        if(strstr(root->opstina,str)){
            printf("%s-%s-%d-%d\n",root->opstina,root->teretana,root->brSprava,root->brSpravaZaKardio);
        }
        ispisSvihTeretanaSaZadatimPodstringomZaOpstinu(root->right,str);
        ispisSvihTeretanaSaZadatimPodstringomZaOpstinu(root->left,str);
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
Node* ucitaj(Node* root,char* path){
    FILE* file= fopen(path,"r");
    if(file){
        char buffer[200];
        while (fgets(buffer, 200, file) != NULL) {
            char* tok= strtok(buffer,"-");
            char opstina[100];
            strcpy(opstina,tok);
            tok= strtok(NULL,"-");
            char teretana[100];
            strcpy(teretana,tok);
            tok= strtok(NULL,"-");
            int brSprava= strToInt(tok);
            tok= strtok(NULL,"\n");
            int brSpravaZaKardio= strToInt(tok);
            root= addNode(root,opstina,teretana,brSprava,brSpravaZaKardio);
            //printf("%s", buffer);
        }
    }else{
        printf("greska");
    }
    return root;
}
int main() {
    /*int a[][6]={{1, 2, 3, 5, 3, 1},{5, 4, 8, 4, 2, 7},{7, 5, 7, 3, 1, 5},{8, 1, 1, 2, 2, 4},{3, 6, 2, 7, 5, 1}};
    zad1(a);
    char str[] = "Nano p!andan! Anan!asu b!ana!no";
    zad2(str);*/

    Node* root=NULL;
    int brSprava;
    char opstina[100];
    do{
        n = menu();
        switch (n) {
            case 1:
                root = ucitaj(root,"..\\podaci\\UUP-21-22-FEB-G1-ulaz3.txt"); break;
            case 2:
                printTree(root); break;
            case 3:
                printf("unesite zeljenu kolicinu sprava\t");
                scanf("%d",&brSprava);
                ispisTeretanaSaSpravama(root,brSprava); break;
            case 4:
                printf("unesite zeljenu opstsinu\t");
                scanf("%s",opstina);
                ispisSvihTeretanaSaZadatimPodstringomZaOpstinu(root,opstina); break;
            case 5:
                freeTree(root); return 0;
        }
    }while(n!=5);

    return 0;
}
