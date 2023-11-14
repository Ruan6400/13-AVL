#include <iostream>
#include <cstdio>
using namespace std;

// definicao de tipo
struct NO {
	int valor;
	NO* esq;
	NO* dir;
	int altura; // usada para balanceamento
};

NO* raiz = NULL;
int AlturaDir=0;
int AlturaEsq=0;
int AlturaCalculada=0;
// headers
// estrutura principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();



// funcoes auxiliares Arvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int elementosArvore(NO* no);
void exibirElementosArvore(NO* no, int qtespacos);
void buscarElementoArvore(NO* no, int valor);
void ExibeArvore(NO* no,int nivel);
//--------------------------

// funcoes auxiliares balaceamento
int alturaNo(NO* no);
void Altura(NO* no,int nivel,NO* galho);
void DefineAlturas(NO* no);
int fatorBalanceamento(NO* no);
int max(int a, int b);
NO* girarDireita(NO* no);
NO* girarEsquerda(NO* no);
//--------------------------


int main()
{
	menu();
}

void menu()
{
	int op = 0;
	while (op != 6) {
	    DefineAlturas(raiz);
		system("clear"); // somente no windows
		cout << "Menu Arvore";
		cout << endl << endl;
		cout << "1 - Inicializar Arvore \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Inserir elemento \n";
		cout << "4 - Exibir elementos \n";
		cout << "5 - Buscar elemento \n";
		cout << "6 - Sair \n";

		cout << "Opcao: ";
		cin >> op;

		switch (op)
		{
		case 1: inicializar();
			break;
		case 2:exibirQuantidade();
			break;
		case 3: inserir();
			break;
		case 4: exibir();
			break;
		case 5: buscar();
			break;
		default:
			break;
		}

		getchar(); // somente no windows
	}
}

void inicializar()
{
	raiz = NULL;
	cout << "Arvore inicializada \n";
}


void inserir()
{
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	raiz = insereArvore(raiz, valor);
}

void exibirQuantidade() {
	cout << "Quantidade de elementos: " << elementosArvore(raiz) << endl;

}

void exibir() {
	ExibeArvore(raiz, 0);
	getchar();
}

void buscar() {
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	buscarElementoArvore(raiz, valor);
}


NO* criaNO(int valor)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL)
	{
		return NULL;
	}
	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->altura = 0;
	return novo;
}

void Altura(NO* no,int nivel,NO* galho){
    if(no==NULL){
        if(nivel>AlturaCalculada){
            AlturaCalculada=nivel-1;
        }
        galho->altura=AlturaCalculada;
        return;
    }
    Altura(no->dir,nivel+1,galho);
    Altura(no->esq,nivel+1,galho);
}
int alturaNo(NO* no)
{
	if (no == NULL) {
		return -1;
	}
	else {
		return no->altura;
	}
}

void DefineAlturas(NO* no){
    if(no==NULL){
        return;
    }
    AlturaCalculada=0;
    Altura(no,0,no);
    DefineAlturas(no->dir);
    DefineAlturas(no->esq);
}

int fatorBalanceamento(NO* no)
{
	if (no == NULL) {
		return 0;
	}
	return alturaNo(no->esq) - alturaNo(no->dir);
}


int max(int a, int b)
{
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}


NO* insereArvore(NO* no, int valor)
{

	if (no == NULL) {
		// arvore vazia
		return criaNO(valor);
	}
	else{
	    if (valor < no->valor) {
	        // insere na subarvore esquerda
	        no->esq = insereArvore(no->esq, valor);
	    }
	    else{
	        if (valor > no->valor) {
	            // insere na subarvore direita
	            no->dir = insereArvore(no->dir, valor);
	        }
	        else{
	            return no;
	        }
	    }
	}

	// atualiza a altura do no (lembre-se que esta � fun��o recursiva)

	no->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;

	// calcula o fator de balanceamento
	int fator = fatorBalanceamento(no);

	// verifica se precisa balancear
	if (fator > 1 && valor < no->esq->valor) {
		return girarDireita(no);
	}
	if (fator < -1 && valor > no->dir->valor) {
		return girarEsquerda(no);
	}
	if (fator > 1 && valor > no->esq->valor) {
		no->esq = girarEsquerda(no->esq);
		return girarDireita(no);
	}
	if (fator < -1 && valor < no->dir->valor) {
		no->dir = girarDireita(no->dir);
		return girarEsquerda(no);
	}
	return no;

}

NO* girarDireita(NO* no)
{
	// sua implementa��o vai aqui
	NO* GalhoLateral = no;
	no=no->esq;
	NO* Ponta = no;
	while(Ponta->dir!=NULL){
	    Ponta=Ponta->dir;
	}
	Ponta->dir=GalhoLateral;
	GalhoLateral->esq=NULL;
	return no;
}

NO* girarEsquerda(NO* no)
{
	// sua implementa��o vai aqui
	NO* GalhoLateral = no;
	no=no->dir;
	NO* Ponta=no;
	while(Ponta->esq!=NULL){
	    Ponta = Ponta->esq;
	}
	Ponta->esq=GalhoLateral;
	GalhoLateral->dir=NULL;
	return no;
}

int elementosArvore(NO* no)
{
	if (no == NULL) {
		return 0;
	}

	return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}


// simula a hierarquia da arvore usando espacos e exibe os elementos 
// horizontalmente 
void exibirElementosArvore(NO* no, int qtEspacos)
{
	const int espaco = 4;

	if (no == NULL) {
		return;
	}
	qtEspacos += espaco;

	//exibe a subarvore da direita
	exibirElementosArvore(no->dir, qtEspacos);
	cout << endl;

	for (int i = espaco; i < qtEspacos; i++)
		cout << " ";

	// exibir o no atual
	cout << no->valor << endl;

	//exibe a subarvore da esquerda
	exibirElementosArvore(no->esq, qtEspacos);

}

void buscarElementoArvore(NO* no, int valor)
{
	if (no == NULL) {
		cout << "Elemento nao encontrado \n";
		return;
	}

	if (no->valor == valor) {
		cout << "Elemento encontrado \n";
		return;
	}

	if (valor < no->valor) {
		buscarElementoArvore(no->esq, valor);
	}
	else {
		buscarElementoArvore(no->dir, valor);
	}
}


// versao nao recursiva
NO* buscarElementoArvoreComPai(NO* no, int valor, NO*& pai)
{
	NO* atual = no;
	pai = NULL;
	while (atual != NULL) {
		if (valor == atual->valor) {
			return atual;
		}
		else {
			pai = atual;

			if (valor < atual->valor) {
				atual = atual->esq;
			}
			else {
				atual = atual->dir;
			}
		}
	}
	return NULL;
}

void ExibeArvore(NO* no,int nivel){
    if(no==NULL){return;}
    for(int i=0;i<nivel;i++){
        cout<<" - ";
    }
    cout<<no->valor<<"("<<no->altura<<")\n";
    ExibeArvore(no->dir,nivel+1);
    ExibeArvore(no->esq,nivel+1);
}




