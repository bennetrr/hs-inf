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
	size_t res = getline(buffer, &len, fp);
	(*buffer)[strcspn(*buffer, "\n")] = '\0';
	return res;
}

int main(void) {
	struct Item *head = nullptr;
	struct Item *tail = nullptr;

	FILE *rfile = fopen("quelle", "r");
	if (!rfile) {
		printf("Error opening file\n");
		return 1;
	}

	while (true) {
		char *name = nullptr;
		if (get_input(&name, rfile) == -1) {
			break;
		}

		char *surname = nullptr;
		if (get_input(&surname, rfile) == -1) {
			free(surname);
			break;
		}

		if (!head) {
			head = (struct Item *) malloc(sizeof(struct Item));
			tail = head;

			head->name = name;
			head->surname = surname;
			head->next = nullptr;
			head->prev = nullptr;
		} else {
			struct Item *oldTail = tail;
			tail = (struct Item *) malloc(sizeof(struct Item));

			tail->name = name;
			tail->surname = surname;
			tail->next = nullptr;
			tail->prev = oldTail;
		}
	}

	{
		FILE *wfile = fopen("umgekehrte-reihenfolge", "w");
		if (!wfile) {
			printf("Error opening file\n");
			return 1;
		}

		struct Item *current = tail;
		do {
			fprintf(wfile, "%s %s\n", current->name, current->surname);
			current = current->prev;
		} while (current);
	}

	{
		struct Item *current = tail;
		do {
			struct Item *next = current->prev;
			free(current->name);
			free(current->surname);
			free(current);
			current = next;
		} while (current);
	}

	return 0;
}
