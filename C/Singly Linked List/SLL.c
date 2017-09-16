#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Node {
    char *phoneme;
    struct Node *next;
}Word;

typedef struct SentenceNode {
    Word *word;
    struct SentenceNode *next;
}Sentence;
//pasted
void playPhoneme(char *phoneme)
{
    char command[64];
    // create command to execute playback
    sprintf(command, "aplay -c 1 -q -t wav Phonemes/%s.snd", phoneme);
    // play soundfile for phoneme
    if (system(command) != 0)
    {
        printf("Error while trying to execute command: %s\n", command);
    }
}

/*
* This function plays a word. The function requires a pointer to a Word struct defined above.
*/
void playWord(Word *head)
{
    Word *tail = head;
    while(tail -> next != NULL){
        tail = tail -> next;
        playPhoneme(tail->phoneme);
        sleep(0.005);
    }
    
}

void playSentence(Sentence *head)
{
    Sentence *tail = head;
    while(tail -> next != NULL){
        tail = tail -> next;
        playWord(tail->word);
    }
}
//pasted


void add(Word *head, char *phoneme)
{
    Word *tail = head;
    while(tail -> next != NULL)
    {
        tail = tail -> next;
    }
    Word *node = malloc(sizeof(Word));
    node -> phoneme = phoneme;
    node -> next = NULL;
    tail -> next = node;
}

void printList(Word *head)
{
    Word *tail = head;
    while(tail -> next != NULL){
        tail = tail -> next;
        printf("%s", tail -> phoneme);
    }
}

void printSentence(Sentence *head)
{
    Sentence *tail = head;
    while(tail -> next != NULL){
        tail = tail -> next;
        printList(tail->word);
        printf(" ");
    }
}

void freeword(Sentence *head)
{
    Sentence *tail = head;
    while(tail -> next != NULL){
        Sentence *tmp = tail;
        tail = tail -> next;
        free(tmp);
    }
    free(tail);
    
}

void addSentence(Sentence *head, Word *word)
{
    Sentence *tail = head;
    while(tail -> next != NULL)
    {
        tail = tail -> next;
    }
    Sentence *node = malloc(sizeof(Sentence));
    node ->word = word;
    node -> next = NULL;
    tail -> next = node;
}

int main(int argc, const char* argv[])
{
    printf("\nAlles werkt nog\n");

    Word *head = malloc(sizeof(Word));
    head->phoneme = NULL;
    head -> next = NULL;
    
    Word *head1 = malloc(sizeof(Word));
    head1->phoneme = NULL;
    head1 -> next = NULL;



    Sentence *sHead = malloc(sizeof(Sentence));
    sHead->word = NULL;
    sHead->next = NULL;
    
    add(head, "J");
    add(head, "M");
    add(head, "AA");
    
    add(head1, "HH");
    add(head1, "HH");
    add(head1, "HH");

    addSentence(sHead, head);
    addSentence(sHead, head1);
    printSentence(sHead);
    //printList(head);

    playSentence(sHead);

    return 0;
}

