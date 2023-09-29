#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52

typedef struct
{
    int val;
    char * naipe;
    char cor;
}
carta;

typedef struct node_l
{
    carta select;
    struct node_l * next;
}
node;

void distribuirCartas (node ** pilhas_jogo);
void setarMesa (node ** pilhas_jogo, node ** pilhas_stack, node ** pilhas_deck);
void displayCards (node * pilhas);
void freeStack (node ** pilhas_jogo, node ** pilhas_stack, node ** pilhas_deck);

int main()
{
    node * pilhas_jogo[8];
    node * pilhas_stack[4];
    node * pilhas_deck[4];

    srand(time(NULL));

    distribuirCartas(pilhas_jogo);

    for (int i = 0; i < 4; i++)
    {
        pilhas_stack[i] = NULL;
        pilhas_deck[i] = NULL;
    }

    char start;

    printf("\033[1;34m\t\t\t!!! FREECELL !!!\n\n\033[0m");
    printf("Como jogar:\n\nDigite a coluna da qual deseja tirar uma carta. Depois, digite para qual coluna deseja enviar a carta\n"
           "O objetivo e empilhar todas as cartas de cada naipe, em ordem crescente, nas colunas de empilhamento\n"
           "Pilhas auxiliares podem segurar uma carta por vez\n"
           "Apenas cartas de cores alternadas e valores imediatamente inferiores podem ser empilhadas nas colunas de jogo\n\n"
           "Obs: Colunas 1-8 = Colunas do jogo (Pilhas principais)\n"
           "     Colunas 9-12 = Colunas auxiliares (Pilhas do canto superior esquerdo)\n"
           "     Colunas 13-16 = Colunas de empilhamento (Pilhas do canto superior direito)\n"
           "\nAperte enter para iniciar o jogo\n");

    scanf("%c", &start);

    int cartasDeck = 0, isValid = 1;
    int pegarCarta, jogarCarta, takeTracker, playTracker;

    node * temp;

    while (cartasDeck < 52)
    {
        if (isValid == 1)
            setarMesa (pilhas_jogo, pilhas_stack, pilhas_deck);
        else
            printf("\nJogada invalida\n\n");

        isValid = 0;

        printf("Digite de qual pilha deseja tirar a carta:\n");
        scanf("%d", &pegarCarta);

        if (pegarCarta == 0)
            break;

        if (pegarCarta < 1 || pegarCarta > 12)
            isValid = 1;

        printf("Digite em qual pilha deseja jogar a carta:\n");
        scanf("%d", &jogarCarta);

        if (jogarCarta == 0)
            break;

        if (jogarCarta < 1 || jogarCarta > 16 || jogarCarta == pegarCarta)
            isValid = 1;

        if (isValid == 0)
        {
            if (pegarCarta > 8)
            {
                takeTracker = pegarCarta - 9;

                if (pilhas_stack[takeTracker])
                {
                    if (jogarCarta < 9)
                    {
                        playTracker = jogarCarta - 1;

                        if (pilhas_jogo[playTracker])
                        {
                            temp = pilhas_jogo[playTracker];

                            while (temp->next)
                                temp = temp->next;

                            if (pilhas_stack[takeTracker]->select.val == temp->select.val - 1)
                            {
                                if (pilhas_stack[takeTracker]->select.cor != temp->select.cor)
                                {
                                    temp->next = pilhas_stack[takeTracker];
                                    pilhas_stack[takeTracker] = NULL;
                                    isValid = 1;
                                }
                            }
                        }
                        else
                        {
                            pilhas_jogo[playTracker] = pilhas_stack[takeTracker];
                            pilhas_stack[takeTracker] = NULL;
                            isValid = 1;
                        }
                    }
                    else if (jogarCarta < 13)
                    {
                        playTracker = jogarCarta - 9;

                        if (!pilhas_stack[playTracker])
                        {
                            pilhas_stack[playTracker] = pilhas_stack[takeTracker];
                            pilhas_stack[takeTracker] = NULL;
                            isValid = 1;
                        }
                    }
                    else
                    {
                        playTracker = jogarCarta - 13;

                        if (pilhas_deck[playTracker])
                        {
                            temp = pilhas_deck[playTracker];

                            if (pilhas_stack[takeTracker]->select.val == temp->select.val + 1 && pilhas_stack[takeTracker]->select.naipe[0] == temp->select.naipe[0])
                            {
                                pilhas_deck[playTracker] = pilhas_stack[takeTracker];
                                free (temp);
                                cartasDeck++;
                                pilhas_stack[takeTracker] = NULL;
                                isValid = 1;
                            }
                        }
                        else
                        {
                            if (pilhas_stack[takeTracker]->select.val == 1)
                            {
                                pilhas_deck[playTracker] = pilhas_stack[takeTracker];
                                cartasDeck++;
                                pilhas_stack[takeTracker] = NULL;
                                isValid = 1;
                            }
                        }
                    }
                }
            }
            else
            {
                takeTracker = pegarCarta - 1;

                if (pilhas_jogo[takeTracker])
                {
                    node * last = pilhas_jogo[takeTracker];
                    temp = last;

                    while (last->next)
                    {
                        temp = last;
                        last = last->next;
                    }

                    if (jogarCarta < 9)
                    {
                        playTracker = jogarCarta - 1;

                        if (pilhas_jogo[playTracker])
                        {
                            node * tempPlay = pilhas_jogo[playTracker];

                            while (tempPlay->next)
                                tempPlay = tempPlay->next;

                            if (last->select.val == tempPlay->select.val - 1)
                            {
                                if (last->select.cor != tempPlay->select.cor)
                                {
                                    tempPlay->next = last;

                                    if (temp->next)
                                        temp->next = NULL;
                                    else
                                        pilhas_jogo[takeTracker] = NULL;

                                    isValid = 1;
                                }
                            }
                        }
                        else
                        {
                            pilhas_jogo[playTracker] = last;

                            if (temp->next)
                                temp->next = NULL;
                            else
                                pilhas_jogo[takeTracker] = NULL;

                            isValid = 1;
                        }
                    }
                    else if (jogarCarta < 13)
                    {
                        playTracker = jogarCarta - 9;

                        if (!pilhas_stack[playTracker])
                        {
                            pilhas_stack[playTracker] = last;

                            if (temp->next)
                                temp->next = NULL;
                            else
                                pilhas_jogo[takeTracker] = NULL;

                            isValid = 1;
                        }
                    }
                    else
                    {
                        playTracker = jogarCarta - 13;

                        if (pilhas_deck[playTracker])
                        {
                            node * tempPlay = pilhas_deck[playTracker];

                            if (last->select.val == tempPlay->select.val + 1)
                            {
                                if (last->select.naipe[0] == tempPlay->select.naipe[0])
                                {
                                    pilhas_deck[playTracker] = last;
                                    free (tempPlay);
                                    cartasDeck++;

                                    if (temp->next)
                                        temp->next = NULL;
                                    else
                                        pilhas_jogo[takeTracker] = NULL;

                                    isValid = 1;
                                }
                            }
                        }
                        else
                        {
                            if (last->select.val == 1)
                            {
                                pilhas_deck[playTracker] = last;
                                cartasDeck++;

                                if (temp->next)
                                    temp->next = NULL;
                                else
                                    pilhas_jogo[takeTracker] = NULL;

                                isValid = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (cartasDeck < 52)
        printf("\nDERROTA!\n\n");
    else
        printf("\nGANHOU!\n\n");

    freeStack (pilhas_jogo, pilhas_stack, pilhas_deck);

    return 0;
}

void distribuirCartas (node ** pilhas_jogo)
{
    carta baralho[TOTAL_CARTAS];

    char * naipes[4] = {"Copas", "Ouros", "Espadas", "Paus"};

    char cores[2] = {'V', 'P'};

    for (int cartas = 0; cartas < TOTAL_CARTAS; cartas++)
    {
        baralho[cartas].val = (cartas % 13) + 1;
        baralho[cartas].naipe = naipes[cartas / 13];
        baralho[cartas].cor = cores[cartas / 26];
    }

    int total_cartas = TOTAL_CARTAS;
    int random;

    for (int i = 0; i < 8; i++)
    {
        random = rand() % total_cartas--;

        pilhas_jogo[i] = malloc(sizeof(node));

        pilhas_jogo[i]->select = baralho[random];
        pilhas_jogo[i]->next = NULL;

        while (random < total_cartas)
        {
            baralho[random] = baralho[random + 1];
            random++;
        }
    }

    node * temp;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8 && total_cartas > 0; j++)
        {
            random = rand() % total_cartas--;

            temp = pilhas_jogo[j];

            while (temp->next)
                temp = temp->next;

            temp->next = malloc(sizeof(node));
            temp = temp->next;

            temp->select = baralho[random];
            temp->next = NULL;

            while (random < total_cartas)
            {
                baralho[random] = baralho[random + 1];
                random++;
            }
        }
    }
}

void setarMesa (node ** pilhas_jogo, node ** pilhas_stack, node ** pilhas_deck)
{
    node * print_temp[8];

    printf("\n\n");

    for (int i = 0; i < 4; i++)
    {
        if (pilhas_stack[i])
            displayCards (pilhas_stack[i]);
        else
            printf("[]\t\t");
    }

    for (int i = 0; i < 4; i++)
    {
        if (pilhas_deck[i])
            displayCards (pilhas_deck[i]);
        else
            printf("[]\t\t");
    }

    printf("\n\n");

    int pilhas_NULL = 0;
    int endedArray[8];

    for (int i = 0; i < 8; i++)
    {
        endedArray[i] = 0;

        if (pilhas_jogo[i])
        {
            displayCards (pilhas_jogo[i]);
            print_temp[i] = pilhas_jogo[i]->next;
        }
        else
        {
            printf ("[]\t\t");
            endedArray[i] = 1;
            pilhas_NULL++;
            print_temp[i] = NULL;
        }
    }

    printf("\n");

    while (pilhas_NULL < 8)
    {
        for (int i = 0; i < 8; i++)
        {
            if (endedArray[i] == 0)
            {
                if (print_temp[i])
                {
                    displayCards (print_temp[i]);
                    print_temp[i] = print_temp[i]->next;
                }
                else
                {
                    printf("\t\t");
                    endedArray[i] = 1;
                    pilhas_NULL++;
                }
            }
            else
                printf("\t\t");
        }
        printf("\n");
    }
    printf("\n");
}

void displayCards (node * pilhas)
{
    if (pilhas->select.cor == 'V')
        printf("\033[1;31m");
    else
        printf("\033[1;30m");

    switch(pilhas->select.val)
    {
        case 1: printf("A - %s\t", pilhas->select.naipe);
            break;

        case 11: printf("J - %s\t", pilhas->select.naipe);
            break;

        case 12: printf("Q - %s\t", pilhas->select.naipe);
            break;

        case 13: printf("K - %s\t", pilhas->select.naipe);
            break;

        default: printf("%i - %s\t", pilhas->select.val, pilhas->select.naipe);
    }

    printf("\033[0m");
}

void freeStack (node ** pilhas_jogo, node ** pilhas_stack, node ** pilhas_deck)
{
    node * temp;

    for (int i = 0; i < 4; i++)
    {
        if (pilhas_stack[i])
            free (pilhas_stack[i]);

        if (pilhas_deck[i])
            free (pilhas_deck[i]);

        while (pilhas_jogo[i])
        {
            temp = pilhas_jogo[i];
            pilhas_jogo[i] = pilhas_jogo[i]->next;
            free (temp);
        }

        while (pilhas_jogo[i + 4])
        {
            temp = pilhas_jogo[i + 4];
            pilhas_jogo[i + 4] = pilhas_jogo[i + 4]->next;
            free (temp);
        }
    }
}
