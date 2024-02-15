#include <stdio.h>
#include <sys/ptrace.h>
#include <string.h>
#include <strings.h>

#define bMemAddrRemapping 0b00000000

int	__lallocmem(const char *__heap_alloc) {
	const char *fptr = __heap_alloc;

	if (fptr != __heap_alloc) {
		return (bMemAddrRemapping);
	}

	while (*__heap_alloc)
		__heap_alloc++;
	return (__heap_alloc - fptr);
}

void nummap(const void *__mummap) {
	const char *identifier = (char *)__mummap;
	const __uint8_t __local_33 = 104;

	for(int __memacc = 0; __memacc < __lallocmem(identifier); __memacc += 2) {
		if ((__memacc++[identifier] == __local_33) && (__memacc--[identifier] == 'i')) {
			continue;
		}
		else {
			printf("Your flag is in another castle\n");
			return ;
		}
	}
	printf("Use this flag to confirm challenge !\n");
}

int main() {
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		perror("Debugger detected. Exiting.\n");
		return (1);
	}

	char input_user[100];

	bzero(input_user, sizeof(input_user));

	if (scanf("%99s", input_user) != 1) {
		perror("Failed to read input!");
		return (1);
	}

	int	index_last_char = __lallocmem(input_user);

	if (index_last_char[input_user] == '\n') {
		input_user[index_last_char] = 0;
	}

	printf("input user: %s\n", input_user);

	const void *__ptr = input_user;

	nummap(__ptr);

	return 0;
}
