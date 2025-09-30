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
} Room;

typedef struct Stack
{
    char roomName[MAX_ROOM][STRING_MAX];
    int top;

}Stack;

struct Room *createRoom();
void buildMap();

void clearTerminal();
void clearInput();
void gameLogic();

void initializeStack(Stack *s);
int stackIsFull(Stack *s);
int stackIsEmpty(Stack *s);
void push(Stack *s, char new[]);     // add new element to top
void pop(Stack *s, char *removed); // remove top element
void showStack(Stack *s);

int roomIndex = 0;
char name[MAX_ROOM][20] = {"Hall de entrada", "Cozinha", "Biblioteca", "Quarto de Hospede", "Sotao", "Suite", "Lavanderia"};
struct Room *saguao = NULL; // iniciando head como global

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
    if(r->left != NULL)
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

    while (flag)
    {
        push(&roomPassedBy, r->name);
        if (r->left == NULL && r->right == NULL)
        {
            printf("Voce chegou ao final\n");
            showStack(&roomPassedBy);
        }

        switch (menu(r))
        {
        case 100:
            if (r->right == NULL)
            {
                printf("Esta porta esta fechada\n");
            }
            else
            {
                r = r->right;
            }
            break;
        case 101:
            if (r->left == NULL)
            {
                printf("Esta porta esta trancada\n");
            } else {
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
}

struct Room *createRoom()
{
    struct Room *r;
    r = malloc(sizeof(Room));
    r->left = NULL;
    r->right = NULL;
    strcpy(r->name, name[roomIndex]);
    roomIndex++;

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


// {

//     if (saguao == NULL)
//     {
//         saguao = createRoom();
//         r = saguao;
//     }

//     while (MAX_ROOM > roomIndex)
//     {

//         if (strcmp(r->name, name[roomIndex]) > 0)
//         {
//             if (r->right == NULL)
//             {
//                 r->right = createRoom();
//             }
//             else
//             {
//                 buildMap(r->right);
//             }
//         }
//         else if (strcmp(r->name, name[roomIndex]) < 0)
//         {
//             if (r->left == NULL)
//             {
//                 r->left = createRoom();
//             }
//             else
//             {
//                 buildMap(r->left);
//             }
//         }
//     }
// }

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


void initializeStack(Stack *s){
    s->top = -1;
}
int stackIsFull(Stack *s){
    return s->top == MAX_ROOM -1;
}
int stackIsEmpty(Stack *s){
    return s->top == -1;
}
void push(Stack *s, char new[]){// add new element to top
    if(stackIsFull(s)){
        return;
    }

    s->top++;
    strcpy(s->roomName[s->top], new);
   // printf("%s foi colocado em %s\n", new, s->roomName[s->top]);
}     
void pop(Stack *s, char *removed){
    if(stackIsEmpty(s)){
        return;
    }

    removed = s->roomName[s->top];
    s->top--;
} // remove top element
void showStack(Stack *s){
    printf("Salas percorridas: \n");

    for (int i = 0; i < s->top ; i++)
    {
        printf("%s -> ",s->roomName[i]);
    }
    printf("%s\n",s->roomName[s->top]);
    
}