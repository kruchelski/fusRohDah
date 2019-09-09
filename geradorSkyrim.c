#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criaHeap(int *vetor, int i, int f)
{	
	int a;
	int auxiliar = vetor[i];
	int j = i * 2 + 1;
	while (j <= f)
	{
		if (j < f)
		{
			if(vetor[j] < vetor[j + 1])
			{
				j = j + 1;
			}
		}
		if(auxiliar < vetor[j])
		{
			vetor[i] = vetor[j];
			i = j;
			j = 2 * i + 1;
		} 
		else
		{
			j = f + 1;
		}
	}
	vetor[i] = auxiliar;
}

void heapSort(int *vetorOrigem, int tamanho)
{
	int a, tmp;
	int i, contador;

	for (i = (tamanho / 2); i >= 0; i--)
	{
		criaHeap(vetorOrigem, i, tamanho - 1);
		contador++;
	}

	for (i = tamanho - 1; i >= 1; i--)
	{
		tmp = vetorOrigem[0];
		vetorOrigem[0] = vetorOrigem[i];
		vetorOrigem[i] = tmp;
		criaHeap(vetorOrigem, 0, i-1);
		contador++;
	}

	return;
}

void preencher(FILE *arq, int linhas)
{
	int cont, tempo;
	int hora, minuto, segundo;
	char* cidades[10] = {"Whiterun", "Solitude", "Winterhold", "Windhelm", "Riften", "Dawnstar", "Markarth", "Morthal", "Falkreath", "Ivarstead"};
	char* conteudo[linhas];
	int identificador[linhas];
	for (cont = 0; cont < linhas; cont++)
	{
		identificador[cont] = rand() % (24 * 60 * 60);
	}
	heapSort(identificador, linhas);

	for (cont = 0; cont < linhas; cont++)
	{	
		tempo = identificador[cont];

		hora = tempo / (60 * 60);
		minuto = (tempo - (hora * 60 * 60)) / 60;
		segundo = (tempo - (hora * 60 * 60) - (minuto * 60));

		fprintf(arq, "%02d", hora );
		fprintf(arq, "%c", ' ');
		fprintf(arq, "%02d", minuto );
		fprintf(arq, "%c", ' ');
		fprintf(arq, "%02d", segundo );
		fprintf(arq, "%c", ' ');
		fprintf(arq, "%s", cidades[ rand() % 10 ]);
		fprintf(arq, "%c", '\n');
	}	
}

int main (int argc, char **argv)
{
	FILE *arq;
	int linhas;
	srand( (unsigned) time(NULL));	
	linhas = atoi(argv[1]);		
	arq = fopen("horaCarrocas.txt","w");
	preencher(arq, linhas);
	fclose(arq);
	printf("\nArquivo criado com sucesso!!!\n\n");
	return 0;
}