/*
Trabalho 1 - Estruturas de Dados Avançadas - INF1010
Alunos
João Ricardo Malta - 2112714
Vinícius Machado - 2111343

*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funções e structs exercício 1
struct lista {
  int num;
  struct lista *prox;
};

typedef struct lista Lista;

Lista *lst_cria(void);
void lst_insere(Lista **l, int n);
void lst_imprime(Lista *lst);
Lista *concatenaLista(Lista *list1, Lista *list2);

// Structs e Função exercício 2

#define N 50

typedef struct elemento Elemento;
typedef struct pilha Pilha;

struct elemento {
  float info;
  Elemento *prox;
};

struct pilha {
  Elemento *topo;
};

Pilha *pilhaCria(void);
int pilhaVazia(Pilha *p);
void pilhaPush(Pilha *p, float valor);
float pilhaPop(Pilha *p);
void pilhaLibera(Pilha *p);
double calculadora(char operacao, double num1, double num2);

int main(void) {
  // Exercício 1

  Lista *l1, *l2, *l3;

  srand(time(0));

  l1 = lst_cria();
  l2 = lst_cria();
  l3 = lst_cria();

  for (int i = 0; i < 10; i++) {
    int numero1 = rand() % 100 + 1;
    int numero2 = rand() % 100 + 1;
    lst_insere(&l1, numero1);
    lst_insere(&l2, numero2);
  }

  printf("\nLista 1\n");
  lst_imprime(l1);

  printf("\nLista 2\n");
  lst_imprime(l2);

  printf("\nLista 3\n");
  l3 = concatenaLista(l1, l2);
  lst_imprime(l3);

  // Exercício 2
  Pilha *p = pilhaCria();
  char operacao[N];
  printf("\nDigite a expressão pósfixa separada por espaços: ");
  scanf(" %[^\n]", operacao);
  char *caracter = strtok(operacao, " ");
  while (caracter != NULL) {
    if (isdigit(caracter[0])) {
      float num = atof(caracter);
      pilhaPush(p, num);
    } else {
      if (strchr("+-*/^", caracter[0])) {
        float num2 = pilhaPop(p);
        float num1 = pilhaPop(p);
        float resultado = calculadora(caracter[0], num1, num2);
        pilhaPush(p, resultado);
      } else {
        printf("caracter inválido: %s\n", caracter);
        exit(1);
      }
    }
    caracter = strtok(NULL, " ");
  }
  if (!pilhaVazia(p)) {
    float resultado = pilhaPop(p);
    printf("O resultado da expressão é: %.2f\n", resultado);
  } else {
    printf("Expressão vazia.\n");
  }
  pilhaLibera(p);
  return 0;
}

// Funções exercício 1
Lista *lst_cria(void) { return NULL; }

void lst_imprime(Lista *lst) {
  Lista *p;
  for (p = lst; p != NULL; p = p->prox)
    printf("num = %d\n", p->num);
}

void lst_insere(Lista **l, int n) {
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  if (novo == NULL) {
    printf("erro ao alocar novo no");
    exit(1);
  }
  novo->num = n;
  if ((*l) == NULL || n < (*l)->num) {
    novo->prox = (*l);
    (*l) = novo;
  } else {
    Lista *aux = *l;
    while (aux->prox != NULL && aux->prox->num < n) {
      aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
  }
}

Lista *concatenaLista(Lista *list1, Lista *list2) {
  Lista *resultado = NULL;

  while (list1 != NULL || list2 != NULL) {
    if (list1 != NULL && (list2 == NULL || list1->num < list2->num)) {
      if (resultado == NULL || resultado->num != list1->num) {
        lst_insere(&resultado, list1->num);
      }
      list1 = list1->prox;
    } else if (list2 != NULL && (list1 == NULL || list2->num < list1->num)) {
      if (resultado == NULL || resultado->num != list2->num) {
        lst_insere(&resultado, list2->num);
      }
      list2 = list2->prox;
    } else {

      if (resultado == NULL || resultado->num != list1->num) {
        lst_insere(&resultado, list1->num);
      }
      list1 = list1->prox;
      list2 = list2->prox;
    }
  }
  return resultado;
}

// Funções Exercício 2

Pilha *pilhaCria(void) {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL) {
    printf("Sem memória criar a pilha.\n");
    exit(1);
  }
  p->topo = NULL;
  return p;
}

int pilhaVazia(Pilha *p) { return p->topo == NULL; }

void pilhaPush(Pilha *p, float valor) {
  Elemento *n = (Elemento *)malloc(sizeof(Elemento));
  if (n == NULL) {
    printf("Sem memória para alocar o elemento.\n");
    exit(1);
  }

  n->info = valor;
  n->prox = p->topo;
  p->topo = n;
}

float pilhaPop(Pilha *p) {
  Elemento *t;
  float v;
  if (pilhaVazia(p)) {
    printf("Pilha vazia.\n");
    exit(1);
  }
  t = p->topo;
  v = t->info;
  p->topo = t->prox;
  free(t);
  return v;
}

void pilhaLibera(Pilha *p) {
  Elemento *t, *q;
  q = p->topo;
  while (q != NULL) {
    t = q->prox;
    free(q);
    q = t;
  }
  free(p);
}

double calculadora(char operacao, double num1, double num2) {
  switch (operacao) {
  case '+':
    return num1 + num2;
  case '-':
    return num1 - num2;
  case '*':
    return num1 * num2;
  case '/':
    if (num2 == 0) {
      printf("Erro ao dividir por zero.\n");
      exit(1);
    }
    return num1 / num2;
  case '^':
    return pow(num1, num2);
  default:
    printf("Operação desconhecida: %c\n", operacao);
    exit(1);
  }
}
