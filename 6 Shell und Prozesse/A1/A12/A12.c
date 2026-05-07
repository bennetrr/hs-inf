#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc, const char *argv[]) {
	if (argc != 2) {
		printf("Too few arguments\n");
		return 1;
	}

	const int nameCount = atoi(argv[1]);
	char **names = malloc(nameCount * sizeof(char *));

	for (int i = 0; i < nameCount; i++) {
		printf("%d: ", i);
		size_t len = 0;
		names[i] = NULL;
		getline(&names[i], &len, stdin);
		names[i][strcspn(names[i], "\n")] = '\0';
	}

	for (int i = nameCount - 1; i >= 0; i--) {
		printf("%s\n", names[i]);
	}

	for (int i = 0; i < nameCount; i++) {
		free(names[i]);
	}
	free(names);

	return 0;
}
