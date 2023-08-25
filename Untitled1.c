#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

typedef struct Node {
	struct Node *next;
	struct Node *prev;

	int value;
} Node;

Node *head = NULL;
Node *tail = NULL;

int list_count = 0;

void input_list(const char *);
void delete_from_list(const char *);
void search_in_list(int);
void print_list();
void print_list_size();
void exit_program();

void wait_until_key_pressed();

int main(int argc, char *argv[]) {
	char input[256];

	printf("TDA Listas Ordenadas＞ ");

	while (strcmp(fgets(input, sizeof(input), stdin), "F\n")) {
		char *token = strtok(input, " ");

		char command[2] = "\0";
		char arg[254] = "\0";

		int i = 0;

		bool isValidInput = true;

		if (strlen(input) == 2) {
			memset(command, input[0], 1);
		} else {
			while (token != NULL) {
				char *pos;

				if ((pos = strchr(token, '\n'))) {
					*pos = '\0';
				}

				if (!i && strlen(token) == 1) {
					strcpy(command, token);
				} else if (i == 1) {
					strcpy(arg, token);
				} else if (i > 1) {
					isValidInput = false;
					break;
				}

				token = strtok(NULL, " ");
				i++;
			}
		}

		if (isValidInput) {
			int value = -1;

			switch (command[0]) {
				case 'I':
					input_list(arg);
					break;
				case 'E':
					delete_from_list(arg);
					break;
				case 'B':
					if (atoi(arg)) {
						value = atoi(arg);
					} else {
						if (!strcmp(arg, "0")) {
							value = 0;
						} else {
							break;
						}
					}

					search_in_list(value);
					wait_until_key_pressed();

					break;
				case 'L':
					print_list();
					wait_until_key_pressed();
					break;
				case 'T':
					print_list_size();
					wait_until_key_pressed();
					break;
			}
		}

		printf("TDA Listas Ordenadas＞ ");
	}

	exit_program();

	return 0;
}

int get_values_from_file(const char *file_name, int *values) {
	FILE *fp = fopen(file_name, "r");

	if (!fp) {
		perror("Error");
		return -1;
	}

	int i = 0;
	int value;

	char s[256];

	while (fgets(s, 256, fp))  {
		if ((value = atoi(s))) {
			values[i++] = value;
		} else {
			if (!strcmp(s, "0\n")) {
				values[i++] = 0;
			}
		}
	}

	fclose(fp);

	return i;
}

int compare_func(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

void input_list(const char *file_name) {
	int *values = (int *)malloc(256 * sizeof(int));

	if (!values) {
		return;
	}

	int n = get_values_from_file(file_name, values);

	if (n > 0) {
		qsort(values, n, sizeof(int), compare_func);

		for (int i = 0; i < n; i++) {
			Node *new = (Node *)malloc(sizeof(Node));

			if (!new) {
				return;
			}

			new->value = values[i];

			if (!i) {
				head = new;
				tail = new;

				head->next = NULL;
				head->prev = NULL;

				tail->next = NULL;
				tail->prev = NULL;
			} else {
				new->prev = tail;
				new->next = NULL;

				tail->next = new;
				tail = new;
			}

			if (i == 1) {
				head->next = tail;
				tail->prev = head;
			}

			list_count++;
		}
	}

	free(values);
	values = NULL;
}

void delete_from_list(const char *file_name) {
	int *values = (int *)malloc(256 * sizeof(int));

	if (!values) {
		return;
	}

	int n = get_values_from_file(file_name, values);

	if (n > 0) {
		for (int i = 0; i < n; i++) {
			Node *current = head;

			while (current) {
				if (values[i] == current->value) {
					if (current->prev) {
						current->prev->next = current->next;

						if (current->next) {
							current->next->prev = current->prev;
						}
					}

					if (current == head) {
						head = current->next;
					}

					if (current == tail) {
						tail = current->prev;
					}

					list_count--;

					free(current);
				}

				current = current->next;
			}
		}
	}

	free(values);
	values = NULL;
}

void search_in_list(int value) {
	Node *current = head;

	size_t n = sizeof(int);

	int *positions = (int *)malloc(n);

	if (!positions) {
		return;
	}

	int *p = positions;
	int c = 0;

	for (int i = 0; current; i++) {
		if (current->value == value) {
			if ((c * 4) + sizeof(int) > n) {
				positions = realloc(positions, (n += sizeof(int)));
			}

			*p++ = i;
			c++;
		}

		current = current->next;
	}

	int buffer_size = n * 3;
	char *buffer = (char *)malloc(buffer_size * sizeof(char));

	if (!buffer) {
		return;
	}

	for (int i = 0; i < c; i++) {
		int last_size = snprintf(NULL, 0, "%d", positions[i]) + 3;

		if (last_size + strlen(buffer) > buffer_size) {
			buffer = realloc(buffer, (buffer_size += last_size));
		}

		char tmp_buffer[last_size];
		sprintf(tmp_buffer, " %d", positions[i]);
		strcat(buffer, tmp_buffer);

		if (i < c - 1) {
			strcat(buffer, ", ");
		} else {
			strcat(buffer, "\n");
			break;
		}
	}

	if (c) {
		printf((c > 1 ? "\nPosiciones:%s" : "\nPosición:%s"), buffer);
	} else {
		printf("\nNo se encontró elemento en la lista\n");
	}

	printf("\nPresione una tecla para continuar...\n");

	free(positions);
	free(buffer);

	positions = NULL;
	buffer = NULL;
}

void print_list() {
	Node *current = head;

	int buffer_size = (list_count * 4) - 1;
	char *buffer = (char *)malloc(buffer_size * sizeof(char));

	if (!buffer) {
		return;
	}

	while (current) {
		int last_size = snprintf(NULL, 0, "%d", current->value) + 4;

		if (last_size + strlen(buffer) > buffer_size) {
			buffer = realloc(buffer, (buffer_size += last_size));
		}

		char tmp_buffer[last_size];
		sprintf(tmp_buffer, " %d", current->value);
		strcat(buffer, tmp_buffer);

		if (current->next != NULL) {
			strcat(buffer, " ＞");
		} else {
			strcat(buffer, "\n");
		}

		current = current->next;
	}

	printf("\nP:%s", buffer);
	printf("\nPresione una tecla para continuar...\n");

	free(buffer);
	buffer = NULL;
}

void print_list_size() {
	printf("\nList size: %d bytes\n", list_count * (int)sizeof(int));
	printf("\nPresione una tecla para continuar...\n");
}

void exit_program() {
	exit(EXIT_SUCCESS);
}

void wait_until_key_pressed() {
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while (!getchar()) {}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
