#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.
#define STRING_MAX 30
#define MAX_ROOM 7

typedef struct Room
{
    struct Room *left;
    struct Room *right;
    char name[STRING_MAX];
    char clueDescription[STRING_MAX];
} Room;

typedef struct Stack
{
    char roomName[MAX_ROOM][STRING_MAX];
    int top;

} Stack;

typedef struct Clue
{
    char clueDescription[STRING_MAX];
    struct Clue *left;
    struct Clue *right;
} Clue;

struct Room *createRoom();
void buildMap();

void clearTerminal();
void clearInput();
void gameLogic();

void initializeStack(Stack *s);
int stackIsFull(Stack *s);
int stackIsEmpty(Stack *s);
void push(Stack *s, char new[]);   // add new element to top
void pop(Stack *s, char *removed); // remove top element
void showStack(Stack *s);

// struct Clue* createClue(char *clueDescription);
struct Clue *addClueTree(Clue *r, char clueDescription[]);
void inOrder(struct Clue *r);

void freeTree(Room *r);
void freeClueTree(Clue *r);

int roomIndex = 0;
char name[MAX_ROOM][STRING_MAX] = {"Hall de entrada", "Cozinha", "Biblioteca", "Quarto de Hospede", "Sotao", "Suite", "Lavanderia"};
struct Room *saguao = NULL; // iniciando head como global

int clueIndex = 0;
char clueDescription[MAX_ROOM][STRING_MAX] = {"Sangue", "Punhal", "Lenco sujo", "Envelope", "bengala", "fuzil", "revolver"};
Clue *head = NULL; // inicia pista

int main()
{

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    gameLogic();

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

int menu(Room *r)
{

    char response;
    printf("Voce esta no: %s\n", r->name);
    printf("Para onde voce quer ir?\n");
    if (r->right != NULL)
    {
        printf("\n(d). Direita\n");
    }
    if (r->left != NULL)
    {
        printf("(e). Esquerda\n");
    }
    printf("(s). Sair\n");
    scanf("%c", &response);
    clearInput();

    return response;
}

void gameLogic()
{
    Room *r = NULL;
    buildMap();
    r = saguao;
    int flag = 1;
    Stack roomPassedBy;
    initializeStack(&roomPassedBy);
    Clue *c = NULL;

    while (flag)
    {
        push(&roomPassedBy, r->name);
        c = addClueTree(c, r->clueDescription);
        if (r->left == NULL && r->right == NULL)
        {
            printf("\n\n --- Voce chegou ao final ---\n");
            showStack(&roomPassedBy);
            printf("\n\n---PISTAS---\n");
            inOrder(c);
            printf("\n\n");
        }

        switch (menu(r))
        {
        case 'd':
            if (r->right == NULL)
            {
                printf("Esta porta esta fechada\n");
            }
            else
            {
                r = r->right;
            }
            break;
        case 'e':
            if (r->left == NULL)
            {
                printf("Esta porta esta trancada\n");
            }
            else
            {
                r = r->left;
            }
            break;
        case 0:
            flag = 0;
            break;

        default:
            flag = 0;
            break;
        }

        clearTerminal();
    }
    freeTree(saguao);
    freeClueTree(head);
    head = NULL;
    saguao = NULL;
    // free(r);
}

struct Room *createRoom()
{
    struct Room *r;
    r = malloc(sizeof(Room));
    r->left = NULL;
    r->right = NULL;
    strcpy(r->name, name[roomIndex]);
    roomIndex++;
    strcpy(r->clueDescription, clueDescription[clueIndex]);
    clueIndex++;

    return r;
}

void buildMap()
{
    saguao = createRoom();
    saguao->right = createRoom();
    saguao->right->right = createRoom();
    saguao->right->left = createRoom();
    saguao->left = createRoom();
    saguao->left->right = createRoom();
    saguao->left->left = createRoom();
}

struct Clue *createClue(char *clueDescription)
{
    struct Clue *new = (struct Clue *)malloc(sizeof(struct Clue));
    strcpy(new->clueDescription, clueDescription);
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct Clue *addClueTree(Clue *r, char clueDescription[])
{
    if (r == NULL)
    {
        r = createClue(clueDescription);
    }

    if (strcmp(r->clueDescription, clueDescription) > 0)
    {

        r->right = addClueTree(r->right, clueDescription);
    }
    else if (strcmp(r->clueDescription, clueDescription) < 0)
    {
        r->left = addClueTree(r->left, clueDescription);
    }
    return r;
}

void inOrder(struct Clue *r)
{
    // printf("aqui\n");
    if (r != NULL)
    {
        inOrder(r->right);
        printf("%s ", r->clueDescription);
        inOrder(r->left);
    }
}

void clearTerminal()
{
    for (int i = 0; i < 30; i++)
    {
        printf("\n");
    }
}

void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void initializeStack(Stack *s)
{
    s->top = -1;
}
int stackIsFull(Stack *s)
{
    return s->top == MAX_ROOM - 1;
}
int stackIsEmpty(Stack *s)
{
    return s->top == -1;
}
void push(Stack *s, char new[])
{ // add new element to top
    if (stackIsFull(s))
    {
        return;
    }

    s->top++;
    strcpy(s->roomName[s->top], new);
    // printf("%s foi colocado em %s\n", new, s->roomName[s->top]);
}
void pop(Stack *s, char *removed)
{
    if (stackIsEmpty(s))
    {
        return;
    }

    removed = s->roomName[s->top];
    s->top--;
} // remove top element
void showStack(Stack *s)
{
    printf("Salas percorridas: \n");

    for (int i = 0; i < s->top; i++)
    {
        printf("%s -> ", s->roomName[i]);
    }
    printf("%s\n", s->roomName[s->top]);
}

void freeTree(Room *r)
{

    if (r == NULL)
        return;

    freeTree(r->right);
    freeTree(r->left);
    free(r);
}

void freeClueTree(Clue *c)
{

    if (c == NULL)
        return;

    freeClueTree(c->right);
    freeClueTree(c->left);
    free(c);
}