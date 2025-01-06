dll: dll.c
#	gcc -o dll -fsanitize=address -Wall -Wextra -pedantic dll.c
	gcc -o dll -Wall -Wextra -pedantic dll.c
