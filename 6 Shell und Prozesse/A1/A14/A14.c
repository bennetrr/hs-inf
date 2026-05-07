#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
	char *name;
	char *surname;
	struct Item *next;
	struct Item *prev;
};

size_t get_input(char **buffer, FILE *fp) {
	size_t len = 0;
	const size_t res = getline(buffer, &len, fp);
	(*buffer)[strcspn(*buffer, "\n")] = '\0';
	return res;
}

int main(void) {
	struct Item *head = NULL;
	struct Item *tail = NULL;

	FILE *rfile = fopen("quelle", "r");
	if (!rfile) {
		printf("Error opening file\n");
		return 1;
	}

	while (true) {
		char *name = NULL;
		if (get_input(&name, rfile) == -1) {
			break;
		}

		char *surname = NULL;
		if (get_input(&surname, rfile) == -1) {
			free(surname);
			break;
		}

		if (!head) {
			head = (struct Item *) malloc(sizeof(struct Item));
			tail = head;

			head->name = name;
			head->surname = surname;
			head->next = NULL;
			head->prev = NULL;
		} else {
			struct Item *oldTail = tail;
			tail = (struct Item *) malloc(sizeof(struct Item));

			tail->name = name;
			tail->surname = surname;
			tail->next = NULL;
			tail->prev = oldTail;
			oldTail->next = tail;
		}
	}

	{
		FILE *wfile = fopen("umgekehrte-reihenfolge", "w");
		if (!wfile) {
			printf("Error opening file\n");
			return 1;
		}

		const struct Item *current = tail;
		while (current) {
			fprintf(wfile, "%s %s\n", current->name, current->surname);
			current = current->prev;
		}
	}

	{
		struct Item *current = tail;
		while (current) {
			struct Item *next = current->prev;
			free(current->name);
			free(current->surname);
			free(current);
			current = next;
		}
	}

	return 0;
}
