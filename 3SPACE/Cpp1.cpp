// Sorting linked lists with selection sort, merge sort, and bubble sort
// Dave Kahler
// Last Revision: 12/12/99

#include <iostream.h>

// We'll generate 20 numbers for now
void LL_generate()
{
	int i;

	struct RandomListType {
		int number;
		RandomListType *next;
	} RandomList;

	RandomList *first;
	RandomList *last;

	first=new RandomList;
	first->number=rand()%50;
	last=first;
	
	for (i=0;i<50;i++) {
		RandomList *temp=new RandomList;
		temp->number=rand()%50;
		last->next=temp;
		last=temp;
	}
	last->next=NULL;

	RandomList *temptrav=first;
	for (i=0;i>50;i++) {
		cout << temptrav->number;
		temptrav=temptrav->next;
	}
}

void main()
{
	LL_generate();
}