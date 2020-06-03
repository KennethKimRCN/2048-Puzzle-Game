#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
	int data;
	int node_index;
	struct Node *up;
	struct Node *down;
	struct Node *left;
	struct Node *right;
}Node;

void traverse(Node* head);
void traverse2(Node* head);

Node* shift_right(Node* ptr, Node* head);
Node* merge_check_r(Node* ptr, Node* head);
Node* merge_right(Node* head);

Node* shift_left(Node* ptr, Node* head);
Node* merge_check_l(Node* ptr, Node* head);
Node* merge_left(Node* head);

Node* shift_up(Node* ptr, Node* head);
Node* merge_check_u(Node* ptr, Node* head);
Node* merge_up(Node* head);

Node* shift_down(Node* ptr, Node* head);
Node* merge_check_d(Node* ptr, Node* head);
Node* merge_down(Node* head);

Node* insert(Node* board, int placement);
Node* new_Num(Node* board);
int rng();
Node* set_Board();

int main(){
	int gameover = 0, turn = 0;
	srand(time(NULL));

	//Set up 4x4 board
	struct Node* board = set_Board();

	//Introduction
	printf("WELCOME TO KEN'S 2048\n");
	printf("INSTRUCTIONS:\n");
	printf("PRESS: l TO SHIFT LEFT\n");
	printf("PRESS: r TO SHIFT RIGHT\n");
	printf("PRESS: u TO SHIFT UP\n");
	printf("PRESS: d TO SHIFT DOWN\n");
	printf("PRESS: q TO QUIT\n");
	
	//Initial two 2's
	new_Num(board);
	new_Num(board);

	char input;

	while(gameover != 1){
		traverse2(board);
		printf("ENTER INPUT:\t");
		scanf(" %c",&input);
		printf("\n");

		switch (input){
			case 'r':
				printf("YOUR INPUT:\tRIGHT\n");
				turn++;
				printf("TURN:\t%d\n", turn);
				merge_right(board);
				new_Num(board);
				break;
			case 'l':
				printf("YOUR INPUT:\tLEFT\n");
				turn++;
				printf("TURN:\t%d\n", turn);
				merge_left(board);
				new_Num(board);
				break;
			case 'u':
				printf("YOUR INPUT:\tUP\n");
				turn++;
				printf("TURN:\t%d\n", turn);
				merge_up(board);
				new_Num(board);
				break;
			case 'd':
				printf("YOUR INPUT:\tDOWN\n");
				turn++;
				printf("TURN:\t%d\n", turn);
				merge_down(board);
				new_Num(board);
				break;
			case 'q':
				printf("GAME TERMINATED\n");
				printf("THANK YOU FOR PLAYING\n");
				gameover = 1;
				break;
			default:
				printf("INPUT ERROR\n");
				break;
		}
	}

	return 0;
}

void traverse(Node* head){
	int output;
	if(head != NULL){
		if(head->data != 0)
			output = 1<<head->data;
		else
			output = 0;
		printf("[%d]\t", output);
		head = head->right;
		traverse(head);
	}
}

void traverse2(Node* head){
	traverse(head);
	printf("\n");
	if(head != NULL){
		head = head->down;
		traverse2(head);
	}
}

//Right Merge
Node* shift_right(Node* ptr, Node* head){
	if(head->data == 0){
		if(ptr->data != 0){
			head->data = ptr->data;
			ptr->data=0;
			if(head->left != NULL)
				shift_right(head->left, head);
		}
		else if(ptr->data == 0)
			if(ptr->left != NULL)
				shift_right(ptr->left,head);
	}
	else if(head->data != 0){
		head = head->left;
		if(head->left != NULL)
			shift_right(head->left, head);
	}
	return head;
}

Node* merge_check_r(Node* ptr, Node* head){
	if((head->data == ptr->data)&&(head->data != 0)){
		head->data++;
		ptr->data = 0;
		head = head->left;
		if(head->left != NULL)
			merge_check_r(head->left, head);
	}
	else if(ptr->data == 0){
		if(ptr->left != NULL)
			ptr = ptr->left;
		if(ptr->left != NULL)
			merge_check_r(ptr, head);
		else if(ptr->data != 0)
			merge_check_r(ptr, head);
	}
	else if(ptr->data != head->data){
		head = head->left;
		if(ptr->left != NULL)
			merge_check_r(head->left, head);
	}
	return head;
}

Node* merge_right(Node* head){
	while(head->right != NULL)
		head = head->right;
	merge_check_r(head->left,head);
	while(head->right != NULL)
		head = head->right;
	shift_right(head->left,head);
	if(head->down != NULL)
		merge_right(head->down);
	return head;
}

//Left Merge
Node* shift_left(Node* ptr, Node* head){
	if(head->data == 0){
		if(ptr->data != 0){
			head->data = ptr->data;
			ptr->data=0;
			if(head->right != NULL)
				shift_left(head->right, head);
		}
		else if(ptr->data == 0)
			if(ptr->right != NULL)
				shift_left(ptr->right,head);
	}
	else if(head->data != 0){
		head = head->right;
		if(head->right != NULL)
			shift_left(head->right, head);
	}
	return head;
}

Node* merge_check_l(Node* ptr, Node* head){
	if((head->data == ptr->data)&&(head->data != 0)){
		head->data++;
		ptr->data = 0;
		head = head->right;
		if(head->right != NULL)
			merge_check_l(head->right, head);
	}
	else if(ptr->data == 0){
		if(ptr->right != NULL)
			ptr = ptr->right;
		if(ptr->right != NULL)
			merge_check_l(ptr, head);
		else if(ptr->data != 0)
			merge_check_l(ptr, head);
	}
	else if(ptr->data != head->data){
		head = head->right;
		if(ptr->right != NULL)
			merge_check_l(head->right, head);
	}
	return head;
}

Node* merge_left(Node* head){
	while(head->left != NULL)
		head = head->left;
	merge_check_l(head->right,head);
	while(head->left != NULL)
		head = head->left;
	shift_left(head->right,head);
	if(head->down != NULL)
		merge_left(head->down);
	return head;
}

//Up Merge
Node* shift_up(Node* ptr, Node* head){
	if(head->data == 0){
		if(ptr->data != 0){
			head->data = ptr->data;
			ptr->data=0;
			if(head->down != NULL)
				shift_up(head->down, head);
		}
		else if(ptr->data == 0)
			if(ptr->down != NULL)
				shift_up(ptr->down,head);
	}
	else if(head->data != 0){
		head = head->down;
		if(head->down != NULL)
			shift_up(head->down, head);
	}
	return head;
}

Node* merge_check_u(Node* ptr, Node* head){
	if((head->data == ptr->data)&&(head->data != 0)){
		head->data++;
		ptr->data = 0;
		head = head->down;
		if(head->down != NULL)
			merge_check_u(head->down, head);
	}
	else if(ptr->data == 0){
		if(ptr->down != NULL)
			ptr = ptr->down;
		if(ptr->down != NULL)
			merge_check_u(ptr, head);
		else if(ptr->data != 0)
			merge_check_u(ptr, head);
	}
	else if(ptr->data != head->data){
		head = head->down;
		if(ptr->down != NULL)
			merge_check_u(head->down, head);
	}
	return head;
}

Node* merge_up(Node* head){
	while(head->up != NULL)
		head = head->up;
	merge_check_u(head->down,head);
	while(head->up != NULL)
		head = head->up;
	shift_up(head->down,head);
	if(head->right != NULL)
		merge_up(head->right);
	return head;
}

//Down Merge
Node* shift_down(Node* ptr, Node* head){
	if(head->data == 0){
		if(ptr->data != 0){
			head->data = ptr->data;
			ptr->data=0;
			if(head->up != NULL)
				shift_down(head->up, head);
		}
		else if(ptr->data == 0)
			if(ptr->up != NULL)
				shift_down(ptr->up,head);
	}
	else if(head->data != 0){
		head = head->up;
		if(head->up != NULL)
			shift_down(head->up, head);
	}
	return head;
}

Node* merge_check_d(Node* ptr, Node* head){
	if((head->data == ptr->data)&&(head->data != 0)){
		head->data++;
		ptr->data = 0;
		head = head->up;
		if(head->up != NULL)
			merge_check_d(head->up, head);
	}
	else if(ptr->data == 0){
		if(ptr->up != NULL)
			ptr = ptr->up;
		if(ptr->up != NULL)
			merge_check_d(ptr, head);
		else if(ptr->data != 0)
			merge_check_d(ptr, head);
	}
	else if(ptr->data != head->data){
		head = head->up;
		if(ptr->up != NULL)
			merge_check_d(head->up, head);
	}
	return head;
}

Node* merge_down(Node* head){
	while(head->down != NULL)
		head = head->down;
	merge_check_d(head->up,head);
	while(head->down != NULL)
		head = head->down;
	shift_down(head->up,head);
	if(head->right != NULL)
		merge_down(head->right);
	return head;
}

Node* insert(Node* board, int placement){
	if(board->node_index != placement){
		if(board->right != NULL){
			board = board->right;
			insert(board, placement);
		}
		else{
			while(board->left != NULL)
				board = board->left;
			if(board->down != NULL)
				insert(board->down, placement);
		}
	}
	else{
		if(board->data == 0)
			board->data++;
		else{
			while(board->left != NULL)
				board = board->left;
			while(board->up != NULL)
				board = board->up;
			new_Num(board);
		}
	}
	return board;
}

Node* new_Num(Node* board){
	int placement = rand()%16;
	insert(board, placement);
	return board;
}

Node* set_Board(){
	struct Node* node0 = NULL;
	struct Node* node1 = NULL;
	struct Node* node2 = NULL;
	struct Node* node3 = NULL;
	struct Node* node4 = NULL;
	struct Node* node5 = NULL;
	struct Node* node6 = NULL;
	struct Node* node7 = NULL;
	struct Node* node8 = NULL;
	struct Node* node9 = NULL;
	struct Node* node10 = NULL;
	struct Node* node11 = NULL;
	struct Node* node12 = NULL;
	struct Node* node13 = NULL;
	struct Node* node14 = NULL;
	struct Node* node15 = NULL;

	node0 = (struct Node*)malloc(sizeof(struct Node));
	node1 = (struct Node*)malloc(sizeof(struct Node));
	node2 = (struct Node*)malloc(sizeof(struct Node));
	node3 = (struct Node*)malloc(sizeof(struct Node));
	node4 = (struct Node*)malloc(sizeof(struct Node));
	node5 = (struct Node*)malloc(sizeof(struct Node));
	node6 = (struct Node*)malloc(sizeof(struct Node));
	node7 = (struct Node*)malloc(sizeof(struct Node));
	node8 = (struct Node*)malloc(sizeof(struct Node));
	node9 = (struct Node*)malloc(sizeof(struct Node));
	node10 = (struct Node*)malloc(sizeof(struct Node));
	node11 = (struct Node*)malloc(sizeof(struct Node));
	node12 = (struct Node*)malloc(sizeof(struct Node));
	node13 = (struct Node*)malloc(sizeof(struct Node));
	node14 = (struct Node*)malloc(sizeof(struct Node));
	node15 = (struct Node*)malloc(sizeof(struct Node));

	node0->data = 0;
	node1->data = 0;
	node2->data = 0;
	node3->data = 0;
	node4->data = 0;
	node5->data = 0;
	node6->data = 0;
	node7->data = 0;
	node8->data = 0;
	node9->data = 0;
	node10->data = 0;
	node11->data = 0;
	node12->data = 0;
	node13->data = 0;
	node14->data = 0;
	node15->data = 0;

	node0->node_index = 0;
	node1->node_index = 1;
	node2->node_index = 2;
	node3->node_index = 3;
	node4->node_index = 4;
	node5->node_index = 5;
	node6->node_index = 6;
	node7->node_index = 7;
	node8->node_index = 8;
	node9->node_index = 9;
	node10->node_index = 10;
	node11->node_index = 11;
	node12->node_index = 12;
	node13->node_index = 13;
	node14->node_index = 14;
	node15->node_index = 15;

	node0->left = NULL;
	node1->left = node0;
	node2->left = node1;
	node3->left = node2;
	node4->left = NULL;
	node5->left = node4;
	node6->left = node5;
	node7->left = node6;
	node8->left = NULL;
	node9->left = node8;
	node10->left = node9;
	node11->left = node10;
	node12->left = NULL;
	node13->left = node12;
	node14->left = node13;
	node15->left = node14;

	node0->right = node1;
	node1->right = node2;
	node2->right = node3;
	node3->right = NULL;
	node4->right = node5;
	node5->right = node6;
	node6->right = node7;
	node7->right = NULL;
	node8->right = node9;
	node9->right = node10;
	node10->right = node11;
	node11->right = NULL;
	node12->right = node13;
	node13->right = node14;
	node14->right = node15;
	node15->right = NULL;

	node0->up = NULL;
	node1->up = NULL;
	node2->up = NULL;
	node3->up = NULL;
	node4->up = node0;
	node5->up = node1;
	node6->up = node2;
	node7->up = node3;
	node8->up = node4;
	node9->up = node5;
	node10->up = node6;
	node11->up = node7;
	node12->up = node8;
	node13->up = node9;
	node14->up = node10;
	node15->up = node11;

	node0->down = node4;
	node1->down = node5;
	node2->down = node6;
	node3->down = node7;
	node4->down = node8;
	node5->down = node9;
	node6->down = node10;
	node7->down = node11;
	node8->down = node12;
	node9->down = node13;
	node10->down = node14;
	node11->down = node15;
	node12->down = NULL;
	node13->down = NULL;
	node14->down = NULL;
	node15->down = NULL;

	return node0;
}
