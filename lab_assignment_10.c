#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct TrieNode {
    struct TrieNode *children[26]; 
    int isEndOfWord; 
};

// Creates a new Trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    int i;
    
    if (node) {
        node->isEndOfWord = 0;
        for (i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    int i;
    
    for (i = 0; i < strlen(word); i++) {
        if (word[i] < 'a' || word[i] > 'z') {
            return; 
        }
        int index = word[i] - 'a'; 
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
            if (current->children[index] == NULL) {
                return; 
            }
        }
        current = current->children[index];
    }
    current->isEndOfWord++; 
}

int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    int i;
    
    for (i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; 
        }
        current = current->children[index];
    }
    return current->isEndOfWord; 
}


void deallocateTrie(struct TrieNode *root) {
    if (!root) {
        return;
    }
    int i;
    
    for (i = 0; i < 26; i++) {
        if (root->children[i]) {
            deallocateTrie(root->children[i]);
            root->children[i] = NULL; 
        }
    }
    free(root);
}



int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }
    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        if (pInWords[numWords] == NULL) {
            printf("Memory allocation failed for word %s.\n", word);
            return 0;
        }
        numWords++;
    }
    fclose(file);
    return numWords;
}


int main(void) {
    char *inWords[256];
    int i;
    
    int numWords = readDictionary("dictionary-1.txt", inWords);
    for (i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    
    struct TrieNode *root = createTrieNode();
    for (i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (i = 0; i < 5; i++) {
        printf("%s %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    
    deallocateTrie(root);
    root = NULL;
    if (root != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}

