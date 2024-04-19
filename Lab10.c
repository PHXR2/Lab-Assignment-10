#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    int count; // to store the number of occurrences of a word
    struct TrieNode *children[ALPHABET_SIZE];
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Function to create a new trie node
struct TrieNode *createNode(void) {
    struct TrieNode *pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    pNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
    }
    return pNode;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->root = createNode();
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *pCrawl = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    pCrawl->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *pCrawl = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!pCrawl->children[index]) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    return pCrawl->count;
}

// Deallocate the trie structure
void deallocateNodes(struct TrieNode *node) {
    if (node == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateNodes(node->children[i]);
    }
    free(node);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    deallocateNodes(pTrie->root); 
    free(pTrie);
    return NULL;
}


// This function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    // Implementation depends on file reading logic
    // Placeholder for compilation
    return 0;
}

int main(void) {
    char *inWords[256];
    
    // Read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    // Parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
