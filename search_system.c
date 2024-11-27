#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ALPHABET_SIZE 256 // Extended ASCII size to include special characters, numbers, and spaces
#define MAX_WORD_LENGTH 100
#define MAX_SUGGESTIONS 10

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool is_end_of_word;
};

// Function to create a new Trie node
struct TrieNode *create_node() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->is_end_of_word = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Function to insert a word or phrase into the Trie
void insert(struct TrieNode *root, const char *input) {
    struct TrieNode *node = root;
    while (*input) {
        unsigned char index = (unsigned char)*input; // Handle extended ASCII
        if (!node->children[index]) {
            node->children[index] = create_node();
        }
        node = node->children[index];
        input++;
    }
    node->is_end_of_word = true;
}

// Function to load words or phrases from a file
void load_words_from_file(struct TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char input[MAX_WORD_LENGTH];
    while (fgets(input, sizeof(input), file)) {
        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';
        insert(root, input);
    }

    fclose(file);
}

// Function to find all suggestions with the given prefix
void find_all_suggestions(struct TrieNode *node, char *prefix, int depth,
                           char suggestions[][MAX_WORD_LENGTH], int *count) {
    if (*count >= MAX_SUGGESTIONS) return;
    if (node->is_end_of_word) {
        strcpy(suggestions[*count], prefix);
        (*count)++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[depth] = (char)i;
            prefix[depth + 1] = '\0';
            find_all_suggestions(node->children[i], prefix, depth + 1, suggestions, count);
        }
    }
    prefix[depth] = '\0'; // Reset prefix to avoid overwriting
}

// Function to get autocomplete suggestions
void autocomplete(struct TrieNode *root, const char *prefix, char suggestions[][MAX_WORD_LENGTH], int *count) {
    struct TrieNode *node = root;
    while (*prefix) {
        unsigned char index = (unsigned char)*prefix; // Handle extended ASCII
        if (!node->children[index]) {
            return; // No words or phrases with this prefix
        }
        node = node->children[index];
        prefix++;
    }
    find_all_suggestions(node, (char *)prefix, strlen(prefix), suggestions, count);
}

// Function to free the memory of the Trie
void free_trie(struct TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free_trie(node->children[i]);
    }
    free(node);
}

// Main function to demonstrate usage
int main() {
    struct TrieNode *root = create_node();
    const char *filename = "words.txt"; // The file containing words or phrases
    load_words_from_file(root, filename);

    char prefix[MAX_WORD_LENGTH];
    char suggestions[MAX_SUGGESTIONS][MAX_WORD_LENGTH];
    int ch = 0;

    do {
        int count = 0;
        printf("Enter search prefix: ");
        fgets(prefix, sizeof(prefix), stdin);
        prefix[strcspn(prefix, "\n")] = '\0'; // Remove trailing newline

        autocomplete(root, prefix, suggestions, &count);

        printf("---------------------------------------------------------------\n");
        if (count == 0) {
            printf("No suggestions found for '%s'.\n", prefix);
        } else {
            printf("Autocomplete suggestions for '%s':\n", prefix);
            for (int i = 0; i < count; i++) {
                printf("%s\n", suggestions[i]);
            }
        }
        printf("---------------------------------------------------------------\n");

        char choice[10];
        printf("Enter 1 if you want to search again, or any other key to exit: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0'; // Remove trailing newline
        ch = atoi(choice);

    } while (ch == 1);

    // Free memory
    free_trie(root);
    return 0;
}

