#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 30
#define TAM_CICLO 3
void *preenche_vetor(int valor);

pthread_t a, b, c;
char valores_p_inserir[TAM_CICLO] = {'A', 'B', 'C'};
char vetor_de_saida[TAM_MAX];
int pos_vetor = 0;
int flags_d_thread[TAM_CICLO] = {1,0,0}; // pelo menos uma das posicoes deve possuir valor 1

int pode_inserir(int valor){
	if (flags_d_thread[valor-1] == 1){
		return 1;
	}
	return 0;
}

void printa_saida(){
	int i;
	for(i=0; i < TAM_MAX; i++){
		printf("%c", vetor_de_saida[i]);
	}
}

void *preenche_vetor(int valor){	
	while(pos_vetor < TAM_MAX){		
		if(pode_inserir(valor)){
			flags_d_thread[valor-1] = 0;
			vetor_de_saida[pos_vetor] = valores_p_inserir[valor-1];
			pos_vetor++;

			if (valor == TAM_CICLO){
				// reinicia ciclo
				flags_d_thread[0] = 1;
			}else{
				// libera prox thread
				flags_d_thread[valor] = 1;
			}
		}
	}
	if (valor == TAM_CICLO){
		printa_saida();
	}

}

int main (){

	pthread_create(&a, NULL, preenche_vetor, 1);
	pthread_create(&b, NULL, preenche_vetor, 2);
	pthread_create(&c, NULL, preenche_vetor, 3);

	pthread_join(a, NULL);  
	pthread_join(b, NULL);  
	pthread_join(c, NULL);  
	
	return 0;
}
