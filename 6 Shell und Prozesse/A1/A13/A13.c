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

void get_input(char **buffer) {
	size_t len = 0;
	getline(buffer, &len, stdin);
	(*buffer)[strcspn(*buffer, "\n")] = '\0';
}

int main(void) {
	struct Item *head = NULL;
	struct Item *tail = NULL;

	printf("Usage: Write '<NAME>\\n<SURNAME>\\n' or 'exit'\n");

	while (true) {
		char *name = NULL;
		get_input(&name);

		if (strcmp(name, "exit") == 0) {
			free(name);
			break;
		}

		char *surname = NULL;
		get_input(&surname);

		if (strcmp(surname, "exit") == 0) {
			free(name);
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
		const struct Item *current = tail;
		while (current) {
			printf("%s %s\n", current->name, current->surname);
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
