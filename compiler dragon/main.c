#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"

main(){
	int choice;
	char buffer[32];
	node_t *head=NULL;
	node_t *tmp=NULL;

	fprintf(stderr, "0.search 1.insert\n");
	while(1){
		scanf("%d",&choice);
		switch(choice){
			case 0:
				scanf("%s",buffer);
				head=node_search(head,buffer);
				if(tmp!=NULL){
					fprintf(stderr, "FOUND[%s]\n",tmp->name);
				}else{
					fprintf(stderr, "NOT FOUND[%s]\n",tmp->name);
				}
				break;
			case 1:
				scanf("%s",buffer);
				head=node_insert(head,buffer);
				break;
		}
	}
}