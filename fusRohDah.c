/* Estruturas de dados 2
*  Atividade 02
*  Alunos:
*  André Klingenfus Antunes
*  Cassiano Kruchelski Vidal
*  Julio do Lago Muller
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHOQUE 21
#define TAMANHO 86400

typedef struct _t_time {
	int hora, minuto, segundo;
} t_time;

typedef struct _t_timetable {
	t_time chave;
	char valor[NHOQUE];
	struct _t_timetable *link;
} t_timetable;

t_timetable *table[TAMANHO];


int hashzinho(t_time t) {
	return (t.hora * 3600) + (t.minuto * 60) + t.segundo;
}

void initTimetable(t_timetable *t[]) {
	for (int i = 0; i < TAMANHO; i++) {
		t[i] = NULL;
	}
}

t_timetable* criaTimetable() {
	t_timetable *novo;

	novo = (t_timetable *)malloc(sizeof(t_timetable));
	if (!novo) {
		printf("\nDeu problemas na alocacao :(\n");
		exit(0);
	}
	return novo;
}

void put(t_time key, char* valor) {
	int index = hashzinho(key);
	t_timetable *nuevo, *aux;
	nuevo = criaTimetable();
	nuevo->chave = key;
	strcpy(nuevo->valor, valor);
	nuevo->link = NULL;
	if (table[index] == NULL) {
		table[index] = nuevo;
	} else {
		aux = table[index];
		while (aux->link != NULL) {
			aux = aux->link;
		}
		aux->link = nuevo;
	}
}

char* get(t_time key) {
	int i = 0, index = hashzinho(key);
	t_timetable *aux;
	aux = table[index];
	if (aux == NULL) return "Vazio";
	while (aux != NULL) {
		i++;
		aux = aux->link;
	}
	aux = NULL;
	char* msg;
	char msgaux[NHOQUE];
	msg = (char*)malloc(sizeof(char) * (NHOQUE + 5) * i);
	aux = table[index];
	while (aux != NULL){
		strcpy(msgaux, aux->valor);
		strcat(msg, " - ");
		strcat(msg, msgaux);
		aux = aux->link;
	}
	return msg;
}

int main(int argc, char* argv[]) {
	FILE *arq = fopen("horaCarrocas.txt", "r");
	char temp[NHOQUE], opc;
	int h, m, s;
	t_time t;
	initTimetable(table);
	while (!feof(arq)) {
		fscanf(arq,"%d %d %d %s", &t.hora, &t.minuto, &t.segundo, &temp);
		put(t, temp);
	}
	fseek(arq, 0, SEEK_SET);
	printf("Puts realizados!\n");
	printf("Pressione 1 para listar toda a tabela ou 2 para buscar por horário\n");
	scanf("%c", &opc);
	switch(opc) {
		case('1'):
			printf("%c - Pressione alguma coisa pra iniciar os gets\n\n", opc);
			getchar();
			for (int hr = 0; hr < 24; hr++) {
				for (int min = 0; min < 60; min++) {
					for (int seg = 0; seg < 60; seg++) {
						t.hora = hr,
						t.minuto = min;
						t.segundo = seg;
						printf("%2d:%2d:%2d %s\n", t.hora, t.minuto, t.segundo, get(t));
					}
				}
			}
		break;

		case('2'):
			printf("Digite o tempo para buscar\n");
			printf("No formato H M S\n");
			printf("Qualquer valor negativo encerra\n");
			while (1) {
				scanf("%d %d %d", &t.hora, &t.minuto, &t.segundo);
				if ((t.hora < 0) && (t.minuto < 0) & (t.segundo < 0)) exit(0);
				printf("%d:%d:%d %s\n", t.hora, t.minuto, t.segundo, get(t));
			}
		break;

		default:
			printf("Opcao inválida.\n");
	}
	fclose(arq);
	return 0;
}