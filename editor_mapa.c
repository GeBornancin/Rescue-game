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
#define PASSOU     	4


typedef struct{
    int map[ALT][LAR];
} save_Map;

int main() {

	save_Map salvar;
   
   FILE *txt, *bin; 


	int mapa[ALT][LAR];
	int lin, col, final, px, py; 
	int flag_animal=0, flag_inicio=0, flag_final=0, erro=0,mapa_aux[ALT][LAR],sinal;
	char jogada, *nome=malloc(99*sizeof(char));

	
	
	// INICIALIZA O MAPA COM PAREDES
	for(lin=0; lin<ALT; lin++) {
		for(col=0; col<LAR; col++) {
			mapa[lin][col] = PAREDE;
		}
	}

	// EDITOR DE MAPAS - USUARIO MONTA O MAPA A SER USADO NO JOGO
	final = 0;
	px = py = 1;
	while(final == 0) {

		COR_BRANCO
		system("clear");
		printf("\t\t  EDITOR DE MAPAS - GAME RESGATE\n");
		for(lin=0; lin<ALT; lin++) {
			// printf("");
			for(col=0; col<LAR; col++) {

				if(lin == px && col == py) {
					COR_VERMELHO					
					printf("_");
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
					COR_AZUL
					printf("☻");
				}
				else if(mapa[lin][col] == ANIMAL) {
					COR_LARANJA
					printf("♞");
				} 
			}
			printf("\n");
		}
	
		COR_BRANCO
		if(erro==1){
			COR_BRANCO
			printf("    (C: Caminho)(P: Parede)(I: Início)(A: Animal)(O: OK)");
			COR_VERMELHO
			printf("\n\t\t[ERRO] Não há animal e/ou início");	
			erro=0;	
		}
		else if(erro == 2){
			COR_BRANCO
			printf("    (C: Caminho)(P: Parede)(I: Início)(A: Animal)(O: OK)");
			COR_VERMELHO
			printf("\n\t\t[ERRO] Não há caminho possivel");	
			erro=0;	
		}
		else{
			COR_BRANCO
			printf("    (C: Caminho)(P: Parede)(I: Início)(A: Animal)(O: OK)");
		
		}

		// CAPTURA TECLA
		jogada = getch();

		// TECLA ESPECIAL
		if(jogada == 27) {
			jogada = getch(); 

			if(jogada == 91) {      
				jogada = getch();
				
				// CIMA
				if(jogada == 65) {
					if(px > 0) {
						px--;
					}
				}		
	  			// BAIXO
				else if(jogada == 66) {
		    			if(px < ALT-1) {
						px++;
					}
				}
				// DIREITA
				else if(jogada == 67) {
					if(py < LAR-1) {
						py++;
					}
			    	}
				// ESQUERDA
				else if(jogada == 68) {
					if(py > 0) {
						py--;
					}
				}
			}
		}
		// PAREDE
		else if(jogada == 'P' || jogada == 'p') {		
		
			if(px != 0 && px != ALT-1 && py != 0 && py != LAR-1){
				if(px != 0 && px != ALT-1 && py != 0 && py != LAR-1){	
					
						if(mapa[px][py] == ANIMAL){
							flag_animal = 0;
					}
						if(mapa[px][py] == INICIO){
							flag_inicio = 0;
					}
					
					mapa[px][py] = PAREDE;
				}
			}
		}
		// CAMINHO
		else if(jogada == 'C' || jogada == 'c') {		
			
			if(px != 0 && px != ALT-1 && py != 0 && py != LAR-1){
					if(mapa[px][py] == ANIMAL){
						flag_animal = 0;
				}
					if(mapa[px][py] == INICIO){
						flag_inicio = 0;
				}
				
				mapa[px][py] = CAMINHO;
			}
		}
		// INICIO
		else if(jogada == 'I' || jogada == 'i' && flag_inicio == 0) {
			
			if(px != 0 && px != ALT-1 && py != 0 && py != LAR-1){
				
				if(mapa[px][py] == ANIMAL){
					flag_animal = 0;
			 	}
				flag_inicio=1;
				mapa[px][py] = INICIO;
			}	
		}
		// ANIMAL
		else if(jogada == 'A' || jogada == 'a' && flag_animal == 0) {		
			
			if(px != 0 && px != ALT-1 && py != 0 && py != LAR-1){
				if(mapa[px][py] == INICIO){
					flag_inicio = 0;
				}
				
				flag_animal=1;
				mapa[px][py] = ANIMAL;
			}
		}
		// OK - SAIR
			else if(jogada == 'O' || jogada == 'o') {

				if(flag_animal != 1 || flag_inicio != 1){
					erro = 1;
				}
 
				else if(flag_animal == 1 && flag_inicio == 1){	
					final = 1;
					flag_final=1;
				}
			}

			for(lin=0; lin<ALT; lin++){
				for(col=0; col<LAR; col++){
					mapa_aux[lin][col] = mapa[lin][col];
				}
			}
			
			
			//VALIDAÇÃO DO CAMINHO
			//VERIFICANDO SE HÁ CAMINHO
			while(final == 1){



				sinal = 0;

				for(lin=0; lin<ALT; lin++){
					for(col=0; col<LAR; col++){
						
						// VERIFICANDO POSIÇÃO DO INICIO
						if(mapa_aux[lin][col] == INICIO){
							
							// VERIFICANDO SE ENCONTROU ANIMAL
							if(mapa[lin][col-1]==ANIMAL || mapa_aux[lin][col+1]==ANIMAL || mapa_aux[lin-1][col]==ANIMAL || mapa_aux[lin+1][col]==ANIMAL){

								lin = ALT; // SAINDO DO FOR
								col = LAR; // SAINDO DO FOR
								sinal = 2; // EXISTE CAMINHO POSSIVEL 
							}

							//BAIXO
							if(mapa_aux[lin+1][col] == CAMINHO){ 
								mapa_aux[lin+1][col] = INICIO; 
								sinal = 1; 

							}

							//CIMA
							if(mapa_aux[lin-1][col] == CAMINHO){ 
								mapa_aux[lin-1][col] = INICIO; 
								sinal = 1;
							}

							//DIREITA
							if(mapa_aux[lin][col+1] == CAMINHO){ 
								mapa_aux[lin][col+1] = INICIO; 
								sinal = 1;
							}

							//ESQUERDA
							if(mapa_aux[lin][col-1] == CAMINHO){ 
								mapa_aux[lin][col-1] = INICIO;
								sinal = 1;
							}
							
							mapa_aux[lin][col] = PASSOU; // MARCA POR ONDE JA FOI PASSADO

						}
					}
				}

				// NÃO EXISTE CAMINHO POSSIVEL
				if(sinal == 0){
					erro = 2;
					final = 0;
				
				}

				// EXISTE CAMINHO POSSIVEL
				else if(sinal == 2){
					final = 3;
				}
			}
		}
	

	
  	bin = fopen("mapas.bin", "a+");
    txt = fopen("mapas.txt", "a+");



    if(bin != NULL){

        system("clear");
        printf("\n- Digite um nome para salvar o mapa: ");
        gets(nome);
        fputs(nome, txt);
        fputs("\n", txt);

        for(lin=0; lin<ALT; lin++){
            for(col=0; col<LAR; col++){
                salvar.map[lin][col] = mapa[lin][col]; 
            }
        }
        fwrite(salvar.map, sizeof(save_Map), 1, bin);
        printf("\n- [OK] O cenário [%s] foi salvo com sucesso", nome);

    }
    fclose(bin);
    fclose(txt);

	printf("\n");
	return 0;
}

