#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include "gea.h"

#define LAR 		62
#define ALT 		18
#define CAMINHO 	0
#define PAREDE 		1
#define INICIO 		2
#define ANIMAL		3
#define PASSOU		4
#define MOVIMENTO 	5

typedef struct{
    int map[ALT][LAR];
} save_Map;

int main(){

    save_Map save;

	FILE *bin, *txt;

    int mapa[ALT][LAR];
	int lin, col, final, px, py, cont, ab_mapa, l=1, gamemode, flag_init,  a=0, b=0, b2=0, po, fim=2,flag_final;
	char nome_mapa[99], jogada;

	//VARIAVEIS TIMER
	int inicial, Tfinal, total, min, seg;	

	bin = fopen("mapas.bin", "a+");
    txt = fopen("mapas.txt", "a+");

	 // SELEÇÃO DE MAPA
    system("clear");
	COR_VERMELHO
    printf("\t\t\tGAME RESCUE\n");
	COR_AGUA
    printf("\n- Escolha um dos cenários a seguir:\n");
    while(fgets(nome_mapa, 100, txt) != NULL){
		COR_ROXO
        printf("\t(%i) %s", l, nome_mapa);
        l++;
    }
    printf("\t> ");
    scanf("%i", &ab_mapa);

	
	// SELECIONA MAPA ESCOLHIDO PELO USUÁRIO
    for(cont = 0; cont < ab_mapa; cont++){
        fread(mapa, sizeof(save_Map), 1, bin);
    }
        
    fclose(bin);
    fclose(txt);
    COR_AGUA    
    printf("[OK] Cenário carregado!");
    __fpurge(stdin);
    getchar();

 	// SELEÇÃO MODO DE JOGO
    system("clear");
	COR_VERMELHO
    printf("\n\tGAME RESCUE\n");
	COR_AGUA
    printf("\n- Escolha uma das opções de jogo:");
	COR_ROXO
    printf("\n\t(1) Manual \n\t(2) Automático \n\t> ");
    scanf("%i", &gamemode);
    system("clear");

	flag_init = 0;
	final = 0;
	min = 0;

	inicial = time(NULL);
		
	switch(gamemode) {

		case 1:
			while(final == 0) {

				COR_BRANCO
				system("clear");
				COR_VERMELHO
				printf("\t\t\tGAME RESGATE\n");
				for(lin=0; lin<ALT; lin++) {
					// printf("");
					for(col=0; col<LAR; col++) {

						if(mapa[lin][col] == INICIO && flag_init == 0){
							px = lin;
							py = col;
							flag_init=1;
						}

						else if(lin == px && col == py) {
							COR_AZUL				
							printf("☻");
						}
						else if(mapa[lin][col] == CAMINHO) {
							COR_BRANCO
							printf(" ");
						}
						else if(mapa[lin][col] == PAREDE) {
							COR_BRANCO
							printf("#");
						}
						else if(mapa[lin][col] == INICIO) {
							
							printf(" ");
						}
						else if(mapa[lin][col] == ANIMAL) {
							COR_LARANJA
							printf("♞");
						} 
					}
					printf("\n");
				}

				COR_BRANCO //MUDA A COR

				//ATUALIZA O CONTADOR DE TEMPO
					
				Tfinal = time(NULL);
				total = Tfinal - inicial;
				min = total/60;
				seg = total%60;
		
				if(seg<10 && min<10){
					printf("[TEMPO] 0%i:0%i",min,seg);
				}
				else if(min<10 && seg>10){
					printf("[TEMPO] 0%i:%i",min,seg);
				}
				else if(min>10 && seg<10){
					printf("[TEMPO] %i:0%i",min,seg);
				}
				else {
					printf("[TEMPO] %i:%i",min,seg);
				}
						
				COR_BRANCO
		
				// CAPTURA TECLA
				jogada = getch();

				// TECLA ESPECIAL
				if(jogada == 27) {
					jogada = getch(); 

					if(jogada == 91) {      
						jogada = getch();
							
						// CIMA
						if(jogada == 65) {
							if(px > 0 && mapa[px-1][py]!=PAREDE) {
								px--;
							}
						}		
						// BAIXO
						else if(jogada == 66) {
								if(px < ALT-1 && mapa[px+1][py]!=PAREDE) {
								px++;
							}
						}
						// DIREITA
						else if(jogada == 67) {
							if(py < LAR-1 && mapa[px][py+1]!=PAREDE) {
								py++;
							}
						}
						// ESQUERDA
						else if(jogada == 68) {
							if(py > 0 && mapa[px][py-1]!=PAREDE) {
								py--;
							}
						}

						//USUARIO RESGATOU ANIMAL
						if(mapa[px][py]==ANIMAL){

							final = 1;
							po=1;
						
						}
					}
				}
			}
		break;
		Tfinal=time(NULL);

		//MODO AUTOMATICO
		case 2:
			//INICIA O CONTADOR DE TEMPO
			inicial = time(NULL);
			while(final==0){

				fflush(stdout); 
				usleep(300000); //TEMPO DE ANIMAÇÃO
				fflush(stdout); 

				COR_BRANCO //MUDA A COR
				system("clear"); //LIMPA O TERMINAL
				COR_LARANJA
				printf("\t\t\t RESGATE AUTOMÁTICO\n");

				//IMPRIME O MAPA
				for(lin=0; lin<ALT; lin++) {
					
					for(col=0; col<LAR; col++) {

						if(mapa[lin][col] == CAMINHO || mapa[lin][col] == PASSOU ) {
							COR_BRANCO //MUDA A COR
							printf(" "); //IMPRIME O CAMINHO/PASSOU
						}

						else if(mapa[lin][col] == PAREDE) {
							COR_BRANCO //MUDA A COR
							printf("#"); //IMPRIME A PAREDE
						}
											
						else if(mapa[lin][col] == ANIMAL) {
							COR_LARANJA //MUDA A COR
							printf("♞"); //IMPRIME O ANIMAL
						}

						else if (mapa[lin][col] == INICIO) {
							COR_AZUL //MUDA A COR
							printf("☻"); //IMPRIME O INÍCIO
						}
					}
					printf("\n");
				}  

				if(fim==2){
						
					COR_BRANCO  //MUDA A COR
					
					//ATUALIZA O CONTADOR DE TEMPO  
					total = Tfinal - inicial;
					min = total/60;
					seg = total%60;

					//IMPRIME O CONTADOR DE TEMPO
					if(seg<=9 && min<=9){
							COR_VERDE
							printf("\n\t\t[Tempo de jogo:"); 
							COR_BRANCO
							printf("0%i:0%i]",min,seg);
					}
					else if(min<=9 && seg>=10){
							COR_VERDE
							printf("\n\t\t[Tempo de jogo:"); 
							COR_BRANCO
							printf("0%i:%i]",min,seg);
					}
					else if(min>=10 && seg<=9){
							COR_VERDE
							printf("\n\t\t[Tempo de jogo:"); 
							COR_BRANCO
							printf("%i:0%i]",min,seg);
					}
					else if(min>=10 && seg>=10){
							COR_VERDE
							printf("\n\t\t[Tempo de jogo:"); 
							COR_BRANCO
							printf("%i:%i]",min,seg);
					}

				}

				fim=2; //O CONTADOR DE TEMPO PODE INICIAR NA TELA   
						
				//FAZENDO A MOVIMENTAÇÃO
				for(lin=0; lin<ALT; lin++) {
					for(col=0; col<LAR; col++) {

						//ENCONTRANDO O INÍCIO
						if( mapa[lin][col] == INICIO ){
														
							//BAIXO
							if(mapa[lin+1][col] == CAMINHO){ //VERIFICA SE HÁ CAMINHO
								mapa[lin+1][col] = MOVIMENTO; //COLOCA-SE MOVIMENTO ONDE HÁ CAMINHO
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
							
							}
							else if (mapa[lin+1][col] == ANIMAL){
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
								lin = ALT; //SAI DO LAÇO  FOR                        
								col = LAR; //SAI DO LAÇO FOR
								final = 3; //ACHOU O ANIMAL - SAI DO LAÇO WHILE
							}

							//CIMA
							if(mapa[lin-1][col] == CAMINHO){//VERIFICA SE HÁ CAMINHO
								mapa[lin-1][col] = MOVIMENTO; //COLOCA-SE MOVIMENTO ONDE HÁ CAMINHO
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
						
							}
							else if (mapa[lin-1][col] == ANIMAL){
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
								lin = ALT; //SAI DO LAÇO  FOR                        
								col = LAR; //SAI DO LAÇO FOR
								final = 3; //ACHOU O ANIMAL - SAI DO LAÇO WHILE
							}

							//DIREITA
							if(mapa[lin][col+1] == CAMINHO){//VERIFICA SE HÁ CAMINHO
								mapa[lin][col+1] = MOVIMENTO; //COLOCA-SE MOVIMENTO ONDE HÁ CAMINHO
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
						
							}
							else if (mapa[lin][col+1] == ANIMAL){
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
								lin = ALT; //SAI DO LAÇO  FOR                        
								col = LAR; //SAI DO LAÇO FOR
								final = 3; //ACHOU O ANIMAL - SAI DO LAÇO WHILE
							}

							//ESQUERDA
							if(mapa[lin][col-1] == CAMINHO){//VERIFICA SE HÁ CAMINHO
								mapa[lin][col-1] = MOVIMENTO; //COLOCA-SE MOVIMENTO ONDE HÁ CAMINHO
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
				
							}
							else if (mapa[lin][col-1] == ANIMAL){
								mapa[lin][col] = PASSOU; //COLOCA-SE PASSOU NO LUGAR DO INÍCIO
								lin = ALT; //SAI DO LAÇO  FOR                        
								col = LAR; //SAI DO LAÇO FOR
								final = 3; //ACHOU O ANIMAL - SAI DO LAÇO WHILE
							}
						}
					}
				}

				//TRANSFORMA O MOVIMENTO EM INICIO
				for(lin=0; lin<ALT; lin++) {
					for(col=0; col<LAR; col++) {
						if(mapa[lin][col]==MOVIMENTO){
							mapa[lin][col]=INICIO;
						}
					}
				}

				Tfinal=time(NULL);	
			}
		for(a=0; a<10; a++){

                fflush(stdout); 
		        usleep(500000); // TEMPO DE ANIMAÇÃO - SUSPENDE A EXECUÇÃO POR MICROSEGUNDOS
		        fflush(stdout);

                system("clear");
                //IMPRIME O MAPA
                for(lin=0; lin<ALT; lin++) {
                    for(col=0; col<LAR; col++) {

                        if(mapa[lin][col] == CAMINHO || mapa[lin][col] == PASSOU) {
                            COR_BRANCO
                            printf(" "); 
                        }

                        else if(mapa[lin][col] == PAREDE) {
                            if(a % 2 == 0){ // MUDA A COR DAS PAREDES
                                COR_LARANJA
                                printf("#"); 
                            }
                            else{
                                COR_AGUA
                                printf("#");
                            }
                        }
                                                            
                        else if(mapa[lin][col] == ANIMAL) {
                            if(a % 2 == 0){ // ALTERNA ENTRE ANIMAL E INICIO 
                                COR_AZUL 
                                printf("♞");
                            }
                            else{
                                COR_LARANJA
                                printf("☻"); 
                            }
                            
                        }

                        else if (mapa[lin][col] == INICIO) {
                            COR_AZUL 
                            printf(" "); 
                        }
                    }
                    printf("\n");
                }

                COR_VERDE
                printf("\n\nPARABENS! RESGATE CONCLUÍDO COM SUCESSO ");
                COR_VERDE

                // IMPRIME TIMER
                if(seg < 10){
                    if(min < 10){
                        printf("[Tempo de Jogo: 0%i:0%i]", min, seg);
                    }
                    else{
                        printf("[Tempo de Jogo: %i:0%i]", min, seg);
                    }
                }
                else{
                    if(min < 10){
                        printf("[Tempo de Jogo: 0%i:%i]", min, seg);
                    }
                    else{
                        printf("[Tempo de Jogo: %i:%i]", min, seg);
                    }
                }  
        }
		
	}


		
    return 0;
}