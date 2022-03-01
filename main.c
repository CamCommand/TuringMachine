#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void *malloc(size_t size);

struct tapeNode {//contains the tape info
    struct tapeNode *left;
    struct tapeNode *right;
    char content;
};
struct instruction {//keep inportant for writing directions
    char Movedirection;
    int Newstate;
    char Writeval;
};

//inserts a Node at tail of doubly linked list
void append(struct tapeNode *node, char data) {
    while (node->right != NULL) {
        node = node->right;
    }
    struct tapeNode *newNode = malloc(sizeof(struct tapeNode));
    newNode->content = data;//read the variables it makes sense
    newNode->left = node;
    newNode->right = NULL;//could be anything so set as null first b4 i get garbage
    node->right = newNode;
}

void displayTape(struct tapeNode *node) { //shows tape, do b4 and after
    do {								  //doesn't work with while using do while
        printf("%c", node->content);
        node = node->right;
    } while (node->right != NULL);
    printf("%c\n", node->content);
}

int main(int argc, char **argv) {
    struct tapeNode *mainTapeHead = malloc(sizeof(struct tapeNode));
    struct tapeNode *tempTape;
    mainTapeHead->right = NULL;
    mainTapeHead->left = NULL;		//so no crap gets in
    mainTapeHead->content = 'A';	//4 output only

    FILE *input_file;
    char arr[100];
    struct instruction **array2d;
    int startState, endState;
    int currentState;

    printf("Input file: \n");
    scanf("%s", arr);
    getchar();
    // \/ change location before submitting
    //input_file = fopen("C:\\Users\\Name\\CLionProjects\\C2019\\input.txt", "r");
    input_file = fopen(arr, "r");
    fscanf(input_file, "%s\n", arr);

    //Initializing the tape
    int in = 0;
    while (arr[in] != 0) {
        append(mainTapeHead, arr[in]);
        in++;
    }//don't change

    //Get the number of states and initialize the instruction 2d array
    fscanf(input_file, "%s\n", arr);
    array2d = malloc(sizeof(struct instruction *) * atoi(arr));
    for (int i = 0; i < 128; i++) {//convert to ints and 128 is max ascii value
        array2d[i] = malloc(sizeof(struct instruction) * 128);//size of all
    }

    //Get the start and end states
    fscanf(input_file, "%d\n", &startState);
    fscanf(input_file, "%d\n", &endState);
    //printf("%d %d\n", startState, endState);
    printf("Writing the tape...\n");
    printf("Initial tape contents: ");
    displayTape(mainTapeHead);//first tape

    //read the rest of the file and assign instructions
    while (feof(input_file) == 0) {//this is just for the insturctions dont use in final test
        fscanf(input_file, "%s\n", arr);
        array2d[atoi(&arr[1])][arr[3]].Writeval = arr[8];
        array2d[atoi(&arr[1])][arr[3]].Movedirection = arr[10];
        array2d[atoi(&arr[1])][arr[3]].Newstate = atoi(&arr[12]);
        //printf("%s\n", arr);//for the tests
    }
    //printf("%c %c %d\n", array2d[4]['A'].Writeval, array2d[4]['A'].Movedirection, array2d[4]['A'].Newstate);
    //printf("\n");
    fclose(input_file);

    tempTape = mainTapeHead;
    //write the tape
    currentState = startState;
    int united_temp_state_of_america;
    while (currentState != endState) {//the rest of the TM insturctions
        united_temp_state_of_america = currentState;
        if (array2d[currentState][tempTape->content].Movedirection == 82) {//82 is R so if Right
            currentState = array2d[currentState][tempTape->content].Newstate;
            tempTape->content = array2d[united_temp_state_of_america][tempTape->content].Writeval;
            if (tempTape->right == NULL) {//if there is nothing dont leave it use Blank
                append(tempTape, 'B');
                tempTape = tempTape->right;
            } else {//if not null
                tempTape = tempTape->right;
            }
        } else {//If L or Left
            currentState = array2d[currentState][tempTape->content].Newstate;
            tempTape->content = array2d[united_temp_state_of_america][tempTape->content].Writeval;
            tempTape = tempTape->left;
        }
    }
    printf("Final tape contents: ");
    displayTape(mainTapeHead);//final product
  
}