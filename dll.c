#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum {
	WARN,
	ERROR 
};

typedef struct node_t{
	char* item;
	struct node_t* next;	
	struct node_t* prev;
} node_t;

typedef struct list {
	node_t *head;
	node_t *tail;
}list;

char* hstring(const char text[]) {
	size_t capacity = strlen(text) + 1;
	char *str = malloc(capacity);
	if (str == NULL) {
		printf("WARNING: unable to allocate memory.");
		return NULL;
	}
	strncpy(str, text, capacity);
	str[capacity - 1] = '\0';
	return str;
}

void report(int level, const char error[]) {
	switch(level) {
		case WARN:	
			printf("WARNING: %s\n", error);
			break;
		case ERROR:
			printf("ERROR: %s\n", error);
			break;
		default:
			printf("%s\n", error);
			break;
	}
}

list* new_list() {
	list* l = (list*) malloc(sizeof(list));
	if (l == NULL) {
		report(WARN, "Unable to allocate memory for the list.");
	}
	l->head = NULL;
	l->tail = NULL;
	return l;
}

int empty(list*list) {
	return list->tail == NULL;
}

void append(list* list, const char text[]) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->item = hstring(text);
	node->prev = list->tail;
	node->next = NULL;
	if (empty(list)) {
		list->head = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
}

void print(list*list) {
	node_t* head = list->head;
	while(head != NULL) {
		printf("%s ", head->item);
		head = head->next;
	}
	printf("\n");
}

node_t * get(list *list, const char text[]) {
	node_t *head = list->head;
	while(head != NULL) {
		if(strcmp(head->item, text) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

node_t* delete (list *list, const char text[]) {
	node_t *head = list->head;
	while(head != NULL) {
		if (strcmp(head->item, text) == 0) {
			if (head->prev != NULL){
				head->prev->next = head->next;
			}	
			if (head->next != NULL) {
				head->next->prev = head->prev;
			}
			return head;
		}
		head = head->next;
	}
	return NULL;
}

void print_node(node_t* node) {
	if (node == NULL) {
		printf("∅\n");
	} else {
		printf("Node[item=%s]\n", node->item);
	}
}

int main() {
	list* l = new_list();
	append(l, "hello");
	append(l, "world");
	append(l, "I'm");
	append(l, "David");

	printf("List before: ");
	print(l);

	node_t *found = get(l, "I'm");
	printf("Found: ");
	print_node(found);
	node_t *not_found = get(l, "WWW");
	printf("Not Found: ");
	print_node(not_found);

	node_t* deleted = delete(l, "David");
	printf("Deleted: ");
	print_node(deleted);
	node_t* not_deleted = delete(l, "Mario");
	printf("Not Deleted: ");
	print_node(not_deleted);

	printf("List after: ");
	print(l);
}
