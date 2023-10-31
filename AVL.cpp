#include <iostream> 
#include <cstdio>
using namespace std; 
  
struct NO{
    int valor; 
    NO* esq;
    NO* dir;
};

NO* raiz=NULL;
  
void menu(); 
void inserir(); 
void exibir();
void excluir();
void equilibrar(NO* no,NO* anterior,bool& falha);

void ProcuraDeleta(NO* no, int numero,NO* anterior);
NO* LinhaReta(NO* no,bool Esq);
void ExibirArvore(NO* no,int nivel,string posicao);
void InserirArvore(NO* atual,NO* novo,NO* anterior);
void Altura(NO* no,int alt,bool Dir);
int AlturaArvoreDir=0;
int AlturaArvoreEsq=0;
int main(){ 
    menu(); 
} 
  
void menu(){ 
    int op=0; 
    while(op!=4){ 
       system("clear"); 
       cout<<"Estrutura Arvore \n\n"; 
       cout<<"1 - inserir\n"; 
       cout<<"2 - exibir\n"; 
       cout<<"3 - excluir\n";
       cout<<"4 - sair\n";
       cout<<"digite a opcao: \n"; 
       cin>>op; 
       switch(op){ 
           case 1: inserir(); 
                   break; 
           case 2: exibir(); 
                   break; 
           case 3: excluir();
                   break;
           case 4: return;
           default: break; 
       } 
       getchar(); 
    } 
} 
  
void inserir(){ 
     int Num; 
     cout<<"Digite um valor: "; 
     cin>>Num; 
     NO* novo = (NO*)malloc(sizeof(NO)); 
     novo->valor = Num; 
     novo->dir=NULL; 
     novo->esq=NULL; 
     if(raiz==NULL){ 
         raiz=novo; 
     }
     else{
         InserirArvore(raiz,novo,NULL);
     }
     cout<<"Valor inserido"<<endl;
     bool falha = false;
     do{
         equilibrar(raiz,NULL,falha);
     }while(falha);
     getchar();
}

void exibir(){
     if(raiz!=NULL){
         ExibirArvore(raiz,0,"raiz");
     }
     else{cout<<"Árvore vazia"<<endl;}
     getchar();
}
void excluir(){
    if(raiz==NULL){
        cout<<"Arvore vazia \n";
        getchar();
        return;
    }
    else{
        int numero;
        cout<<"Digite o elemento: \n";
        cin>>numero;
        if(raiz->valor==numero){
            NO* paraExcluir=raiz;
            if(raiz->dir!=NULL){
                if(raiz->esq!=NULL){
                    NO* PontaSolta = LinhaReta(raiz->dir,true);
                    PontaSolta->esq=raiz->esq;
                }
                raiz=raiz->dir;
            }
            else{
                if(raiz->esq!=NULL){
                    raiz=raiz->esq;
                }
                else{
                    raiz=NULL;
                }
            }
            free(paraExcluir);
            cout<<"Valor deletado\n";
            getchar();
        }
        else{
            ProcuraDeleta(raiz,numero,NULL);
        }
        bool falha = false;
        do{
            equilibrar(raiz,NULL,falha);
        }while(falha);
    }
}
void equilibrar(NO* no,NO* anterior,bool& falha){
    if(no==NULL){return;}
    AlturaArvoreEsq=0;
    AlturaArvoreDir=0;
    Altura(no->dir,1,true);
    Altura(no->esq,1,false);
    int Peso=AlturaArvoreDir - AlturaArvoreEsq;
    if(Peso>1){
        falha=true;
        if(no==raiz){
            raiz=raiz->dir;
            NO* PontaSolta = LinhaReta(raiz,true);
            PontaSolta->esq=no;
            no->dir=NULL;
        }
        else{
            anterior->dir=no->dir;
            NO* PontaSolta = LinhaReta(anterior->dir,true);
            PontaSolta->esq=no;
            no->dir=NULL;
        }
    }
    else{
        if(Peso<-1){
            falha=true;
            if(no==raiz){
                raiz=raiz->esq;
                NO* PontaSolta = LinhaReta(raiz,false);
                PontaSolta->dir=no;
                no->esq=NULL;
            }
            else{
                anterior->esq=no->esq;
                NO* PontaSolta = LinhaReta(anterior->esq,false);
                PontaSolta->dir=no;
                no->esq=NULL;
            }
        }
        else{
            falha=false;
            equilibrar(no->dir,no,falha);
            equilibrar(no->esq,no,falha);
        }
    }
}

void ProcuraDeleta(NO* no,int numero,NO* anterior){
    if(no==NULL){
        cout<<"Valor nao encontrado.";
        getchar();
        return;
    }
    if(no->valor==numero){
        if(no->dir!=NULL){
            if(no->dir->valor>anterior->valor){anterior->dir=no->dir;}
            else{anterior->esq=no->dir;}
            if(no->esq!=NULL){
                NO* PontaSolta = LinhaReta(no->dir,true);
                PontaSolta->esq=no->esq;
            }
        }
        else{
            if(no->esq!=NULL){
                if(no->esq->valor>anterior->valor){anterior->dir=no->esq;}
                else{anterior->esq=no->esq;}
            }
            else{
                if(no->valor>anterior->valor){anterior->dir=NULL;}
                else{anterior->esq=NULL;}
            }
        }
        free(no);
        cout<<"Valor deletado"<<endl;
        getchar();
        return;
    }
    if(numero>no->valor){ProcuraDeleta(no->dir,numero,no);}
    else{ProcuraDeleta(no->esq,numero,no);}
}

NO* LinhaReta(NO* no, bool Esq){
    if(Esq){
        if(no->esq==NULL){ return no;}
        else{ return LinhaReta(no->esq,true);}
    }
    else{
        if(no->dir==NULL){ return no;}
        else{ return LinhaReta(no->dir,false);}
    }
}
 
void InserirArvore(NO* atual,NO* novo,NO* anterior){
     if(atual==NULL){
         if(novo->valor>anterior->valor){
             anterior->dir=novo;
         }
         else{
             anterior->esq=novo;
         }
     }
     else{
         if(novo->valor>atual->valor){
             InserirArvore(atual->dir,novo,atual);
         }
         else{
             InserirArvore(atual->esq,novo,atual);
         }
     }
}
 
void ExibirArvore(NO* no,int nivel,string posicao){
     if(no==NULL){
         return;
     }
     for(int i=0;i<nivel;i++){
        cout<<" - ";
     }
     cout<<"nivel "<<nivel<<" "<<posicao<<" : "<<no->valor<<endl;
     if(no->dir!=NULL){ExibirArvore(no->dir,nivel+1,"dir");}
     if(no->esq!=NULL){ExibirArvore(no->esq,nivel+1,"esq");}
}

void Altura(NO* no,int alt,bool Dir){
    if(no==NULL){
        if(Dir){
            if(alt>AlturaArvoreDir){AlturaArvoreDir=alt-1;}
        }
        else{
            if(alt>AlturaArvoreEsq){AlturaArvoreEsq=alt-1;}
        }
        return;
    }
    Altura(no->dir,alt+1,Dir);
    Altura(no->esq,alt+1,Dir);
}
