#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    int *next;
    int val;
};

struct LinkedList *LinkedList_create(int val)
{
	struct LinkedList *list = malloc(sizeof(struct LinkedList));
	assert(list != NULL);
	
	list->next = NULL;
	list->val = val

	return list;
}

void LinkedList_destroy(struct LinkedList *list)
{
	assert(list != NULL);
	
	free(list);
}

void LinkedList_print(struct LinkedList list);
	do {
		
	} while();
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
