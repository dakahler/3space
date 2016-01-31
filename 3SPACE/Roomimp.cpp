#include <fstream>  // File I/O header
#include <stdio.h>

using namespace std;

// Polygon Linked List
struct PolyDef {
	double x,y,z,num;
	PolyDef *next;
};
PolyDef *first;
PolyDef *last;

// Collision Detection Linked List
struct LineEq {
	double p1x,p1y,p2x,p2y,m;
	LineEq *next;
};
LineEq *first_l;
LineEq *last_l;

// Function importRoom(char filename[50])
// Parameter Description: 50 char max string filename
// Return Type: void
void importRoom(char filename[50])
{
	char string[10],temp[10];
	int end=0,i=0;
	ifstream file_ptr;
	first=new PolyDef;
	last=first;
	first_l=new LineEq;
	last_l=first_l;
	int k=0;

	file_ptr.open(filename,ios::in);
	if (file_ptr) {
		while (!file_ptr.eof()) {
			file_ptr.getline(string,50);
			sscanf(string,"%s %d",&temp,&i);
			LineEq  *templine=new LineEq;
			while (i>=1) {
				PolyDef *temppoly=new PolyDef;
			
				file_ptr >> temppoly->x;
				file_ptr >> temppoly->y;
				file_ptr >> temppoly->z;
				temppoly->num=i;
				if (i==4) {
					templine->p1x=temppoly->x;
					templine->p1y=temppoly->z;
				}
				if (i==3) {
					templine->p2x=temppoly->x;
					templine->p2y=temppoly->z;
					if (templine->p2x!=templine->p1x)
						templine->m=(templine->p2y-templine->p1y)/
									(templine->p2x-templine->p1x);
					else templine->m=1000;
					last_l->next=templine;
					last_l=templine;
				}
				last->next=temppoly;
				last=temppoly;
				i--;
			}
			k++;
		}
	}
	else {
		printf("File Error.");
	}
	file_ptr.close();
	last->next=NULL;
	last_l->next=NULL;
}

