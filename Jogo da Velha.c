#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>

#define EMPATE 'E'
#define CARACTERE_BRANCO ' '
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER 13

void inicializando_Tabuleiro(char tabuleiro[3][3]){
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

void imprimeTabuleiro(char tabuleiro[3][3]){
    int i=0, j=0;

    printf("\n\t\t   0      1      2\n\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(j == 0){
                printf("\t\t");
            }
            printf("  %c  ", tabuleiro[i][j]);
            if(j < 2){
                printf(" | ");
            }
            if(j == 2){
                printf("     %d", i);
            }            
        }
        printf("\n");
        if(i < 2){
            printf("\t\t------+-------+------\n");
        }
    }
}

int main(){
    setlocale(LC_ALL,"Portuguese");

    char tabuleiro[3][3];
    char nome1[100], nome2[100];
    char player_atual[100];
    int winner = EMPATE;
    int linha = 3, coluna = 3;
    int num_jogadas = 0;
    int tam_tabuleiro = 9;
    int opcao = 1, tecla, contador_jogador1 = 0, contador_jogador2 = 0;
    bool continuar = true;

    while(continuar){
        printf("\t  ========== JOGO DA VELHA ==========\n\n");
        printf("\t\t    Player vs Player %s\n", opcao == 1 ? "<--" : " ");
        printf("\t\t          Sair %s\n\n", opcao == 2 ? "<--" : " ");
        printf("\t  ========== ============= ==========\n\n");
        tecla = getch();

        if(tecla == 224){
            tecla = getch();
            
            switch(tecla){
                case UP_ARROW:
                    if(opcao > 1){
                        opcao--;
                    }
                    break;
                case DOWN_ARROW:
                    if(opcao < 2){
                        opcao++;
                    }
                    break;
            }
        } else if(tecla == ENTER){
            switch(opcao){
                case 1:
                    continuar = false;
                    break;
                case 2: 
                    exit(0);
                    break;
            }
        }
        system("cls");
    }

    inicializando_Tabuleiro(tabuleiro);

    if(opcao == 1){
        printf("\t========== JOGO DA VELHA ==========\n\n");
        
        printf("Informe o nome do Jogador 1: ");
        fgets(nome1, 100, stdin);
        nome1[strcspn(nome1, "\n")] = '\0';
        printf("Informe o nome do Jogador 2: ");
        fgets(nome2, 100, stdin);
        nome2[strcspn(nome2, "\n")] = '\0';
        strcpy(player_atual, nome1);

        continuar = true;
        system("cls");

        while(continuar){
            printf("\t========== JOGO DA VELHA ==========\n\n");
            printf("\tA partida será em uma:\n\n");
            printf("1 - MD1 %s\n", opcao == 1 ? "<--" : " ");
            printf("2 - MD3 %s\n", opcao == 2 ? "<--" : " ");
            
            tecla = getch();

            if(tecla == 224){
                tecla = getch();
            
                switch(tecla){
                    case UP_ARROW:
                        if(opcao > 1){
                            opcao--;
                        }
                        break;
                    case DOWN_ARROW:
                        if(opcao < 3){
                            opcao++;
                        }
                        break;
                }
            } else if(tecla == ENTER){
                switch(opcao){
                    case 1:
                        continuar = false;
                        break;
                    case 2:
                        continuar = false;
                        break;
                }
            }
        system("cls");
        }

        if(opcao == 2){
            while(1){
                inicializando_Tabuleiro(tabuleiro);
                while (contador_jogador1 != 2 && contador_jogador2 != 2){
                    printf("\t ========== JOGO DA VELHA ==========\n");
                    printf("\t    ======== Melhor de 3 ========\n\n");
                    printf("\t\t %s %d  x  %s %d\n", nome1, contador_jogador1, nome2, contador_jogador2);
                    imprimeTabuleiro(tabuleiro);
                    printf("\n___________________________________________________");
                    printf("\n\t%s sua vez de jogar!\n\n", player_atual);

                    printf("Escolha a linha: ");
                    scanf("%d", &linha);
                    if(!(linha >= 0 && linha <= 2)){
                        system("cls");
                        printf("\nA linha deve ser entre 0 e 2. Digite novamente!\n");
                        continue;
                    }

                    printf("Escolha a coluna: ");
                    scanf("%d", &coluna);
                    if(!(coluna >= 0 && coluna <= 2)){
                        system("cls");
                        printf("\nA coluna deve ser entre 0 e 2. Digite novamente!\n");
                        continue;
                    }

                    if(num_jogadas % 2 == 0){
                        strcpy(player_atual, nome1);
                        if(tabuleiro[linha][coluna] == CARACTERE_BRANCO){
                            tabuleiro[linha][coluna] = 'X';
                        }
                        else{
                            system("cls");
                            printf("\nPOSICAO OCUPADA. DIGITE NOVAMENTE!!!\n");
                            continue; 
                        }
                    }
                    else{
                        strcpy(player_atual, nome2);
                        if(tabuleiro[linha][coluna] == CARACTERE_BRANCO){
                            tabuleiro[linha][coluna] = 'O';
                        }
                        else{
                            system("cls");
                            printf("\nPOSICAO OCUPADA. DIGITE NOVAMENTE!!!\n");
                            continue; 
                        }
                    } 
                    system("cls");
                    for(linha = 0; linha < 3; linha += 1){
                        winner = player_atual[0];

                        for(coluna = 1; coluna < 3; coluna += 1){
                            if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha][coluna - 1]){
                                winner = EMPATE;
                                break;
                            }
                        }

                        if(winner != EMPATE){
                            break;
                        }
                    }

                    if(winner == EMPATE){
                        for(coluna = 0; coluna < 3; coluna += 1){
                            winner = player_atual[0];

                            for(linha = 1; linha < 3; linha += 1){
                                if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha - 1][coluna]){
                                    winner = EMPATE;
                                    break;
                                }
                            }

                            if (winner != EMPATE){
                                break;
                            }
                        }
                    }

                    if(winner == EMPATE){
                        winner = player_atual[0];

                        for(linha = 1; linha < 3; linha++){     
                            if(tabuleiro[linha][linha] == CARACTERE_BRANCO || tabuleiro[linha][linha] != tabuleiro[linha - 1][linha - 1]){
                                winner = EMPATE;
                                break;
                            }
                        }
                    }

                    if(winner == EMPATE){
                        winner = player_atual[0];

                        coluna = 3 - 2;

                        for(linha = 1; linha < 3 && coluna >= 0; linha += 1){
                            if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha - 1][coluna + 1]){
                                winner = EMPATE;
                                break;
                            }

                            coluna -= 1;
                        }
                    }

                    num_jogadas += 1;

                    if(winner != EMPATE || num_jogadas == tam_tabuleiro){
                        if(winner != EMPATE){
                            printf("\t========== JOGO DA VELHA ==========\n");
                            printf("\t   ======== Melhor de 3 ========\n\n");
                            printf("\t\t %s %d  x  %s %d\n", nome1, contador_jogador1, nome2, contador_jogador2);
                            imprimeTabuleiro(tabuleiro);
                            printf("\n\n\t====%s Venceu a partida!====\n\n", player_atual);
                            if (strcmp(player_atual, nome1) == 0) {
                                contador_jogador1++;
                            } else {
                                contador_jogador2++;
                            }
                        }
                        else{
                            imprimeTabuleiro(tabuleiro);
                            printf("\n\n\t==== Partida Empatada!\n\n");
                        }

                        if(contador_jogador1 == 2 || contador_jogador2 == 2){
                            if(contador_jogador1 == 2){
                                system("cls");
                                printf("\t========== JOGO DA VELHA ==========\n");
                                printf("\t   ======== Melhor de 3 ========\n\n");
                                printf("\t\t %s %d  x  %s %d\n", nome1, contador_jogador1, nome2, contador_jogador2);
                                imprimeTabuleiro(tabuleiro);
                                printf("\n\n\t %s É O VENCEDOR DA MELHOR DE 3\n\n", nome1);
                            } else {
                                system("cls");
                                printf("\t========== JOGO DA VELHA ==========\n");
                                printf("\t   ======== Melhor de 3 ========\n\n");
                                printf("\t\t %s %d  x  %s %d\n", nome1, contador_jogador1, nome2, contador_jogador2);
                                imprimeTabuleiro(tabuleiro);
                                printf("\n\n\t %s É O VENCEDOR DA MELHOR DE 3\n\n", nome2);
                            }
                            break;
                        } else{
                            printf("Aperte qualquer tecla para continuar a próxima rodada!");
                            getch();
                            system("cls");
                            printf("\t========== JOGO DA VELHA ==========\n");
                            printf("\t   ======== Melhor de 3 ========\n\n");
                            printf("\n\n\t   ==== PRÓXIMA PARTIDA ====\n\n");
                            sleep(1.5);
                            system("cls");
                            inicializando_Tabuleiro(tabuleiro);
                            num_jogadas = 0;
                        }
                    }

                    if(num_jogadas % 2 == 0){
                        strcpy(player_atual, nome1);
                    }
                    else{
                        strcpy(player_atual, nome2);
                    }
                }
            }

        } else if(opcao == 1){
            while(1){
                printf("\t ========== JOGO DA VELHA ==========\n");
                printf("\t    ======== Melhor de 1 ========\n\n");
                imprimeTabuleiro(tabuleiro);
                printf("\n___________________________________________________");
                printf("\n\t%s sua vez de jogar!\n\n", player_atual);

                printf("Escolha a linha: ");
                scanf("%d", &linha);
                if(!(linha >= 0 && linha <= 2)){
                    printf("\nA linha deve ser entre 0 e 2. Digite novamente!");
                    continue;
                }

                printf("Escolha a coluna: ");
                scanf("%d", &coluna);
                if(!(coluna >= 0 && coluna <= 2)){
                    printf("\nA coluna deve ser entre 0 e 2. Digite novamente!");
                    continue;
                }

                if(num_jogadas % 2 == 0){
                    strcpy(player_atual, nome1);
                    if(tabuleiro[linha][coluna] == CARACTERE_BRANCO){
                        tabuleiro[linha][coluna] = 'X';
                    }
                    else{
                        system("cls");
                        printf("POSICAO OCUPADA. DIGITE NOVAMENTE!!!\n\n");
                        continue; 
                    }
                }
                else{
                    strcpy(player_atual, nome2);
                    if(tabuleiro[linha][coluna] == CARACTERE_BRANCO){
                        tabuleiro[linha][coluna] = 'O';
                    }
                    else{
                        system("cls");
                        printf("POSICAO OCUPADA. DIGITE NOVAMENTE!!!\n\n");
                        continue; 
                    }
                } 
                system("cls");
                for(linha = 0; linha < 3; linha += 1){
                    winner = player_atual[0];

                    for(coluna = 1; coluna < 3; coluna += 1){
                        if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha][coluna - 1]){
                            winner = EMPATE;
                            break;
                        }
                    }

                    if(winner != EMPATE){
                        break;
                    }
                }

                if(winner == EMPATE){
                    for(coluna = 0; coluna < 3; coluna += 1){
                        winner = player_atual[0];

                        for(linha = 1; linha < 3; linha += 1){
                            if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha - 1][coluna]){
                                winner = EMPATE;
                                break;
                            }
                        }

                        if (winner != EMPATE){
                            break;
                        }
                    }
                }

                if(winner == EMPATE){
                    winner = player_atual[0];

                    for(linha = 1; linha < 3; linha++){     
                        if(tabuleiro[linha][linha] == CARACTERE_BRANCO || tabuleiro[linha][linha] != tabuleiro[linha - 1][linha - 1]){
                            winner = EMPATE;
                            break;
                        }
                    }
                }

                if(winner == EMPATE){
                    winner = player_atual[0];

                    coluna = 3 - 2;

                    for(linha = 1; linha < 3 && coluna >= 0; linha += 1){
                        if(tabuleiro[linha][coluna] == CARACTERE_BRANCO || tabuleiro[linha][coluna] != tabuleiro[linha - 1][coluna + 1]){
                            winner = EMPATE;
                            break;
                        }

                        coluna -= 1;
                    }
                }

                num_jogadas += 1;

                if(winner != EMPATE || num_jogadas == tam_tabuleiro){
                    break;
                }

                if(num_jogadas % 2 == 0){
                    strcpy(player_atual, nome1);
                }
                else{
                    strcpy(player_atual, nome2);
                }
            }

            printf("\t ========== JOGO DA VELHA ==========\n");
            printf("\t    ======== Melhor de 1 ========\n\n");
            imprimeTabuleiro(tabuleiro);

            if(winner != EMPATE){
                printf("\n\n\t\t %s Venceu a partida! \n\n", player_atual);
            }
            else{
                printf("\n\n\t\t Partida Empatada! \n\n");
            }

        } 
    }
    return 0;
}