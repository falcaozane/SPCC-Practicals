#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define a structure for the Symbol Table
struct SymbolEntry {
    char symbol;        // The symbol (a character)
    void *address;      // Memory address for the symbol
    char type[40];      // Type of symbol (e.g., "identifier", "operator")
};

// Insert a new symbol into the symbol table
void insertSymbol(struct SymbolEntry symbolTable[], int *symbolCount, char newSymbol) {
    // Check for duplicate symbols
    for (int i = 0; i < *symbolCount; i++) {
        if (symbolTable[i].symbol == newSymbol) {
            printf("Duplicate Symbol. Cannot insert.\n");
            return;
        }
    }

    // Allocate memory for the new symbol
    symbolTable[*symbolCount].address = malloc(sizeof(int));
    if (symbolTable[*symbolCount].address == NULL) {
        printf("Memory allocation failed. Cannot insert.\n");
        return;
    }

    // Determine the type of the symbol (identifier or operator)
    if (isalpha(newSymbol)) {
        strcpy(symbolTable[*symbolCount].type, "identifier");
    } else {
        strcpy(symbolTable[*symbolCount].type, "operator");
    }

    // Insert the symbol into the table
    symbolTable[*symbolCount].symbol = newSymbol;
    (*symbolCount)++; // Increment the symbol count
    printf("Symbol inserted successfully.\n");
}

// Display all symbols in the symbol table
void displaySymbolTable(const struct SymbolEntry symbolTable[], int symbolCount) {
    printf("\nSymbol Table\n");
    printf("Symbol \t Address \t\t Type\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%c \t %p \t %s\n", symbolTable[i].symbol, symbolTable[i].address, symbolTable[i].type);
    }
}

// Delete a symbol from the symbol table
void deleteSymbol(struct SymbolEntry symbolTable[], int *symbolCount, char symbolToDelete) {
    int foundIndex = -1;

    // Find the symbol to delete
    for (int i = 0; i < *symbolCount; i++) {
        if (symbolTable[i].symbol == symbolToDelete) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Symbol not found. Cannot delete.\n");
        return;
    }

    // Free the memory for the symbol
    free(symbolTable[foundIndex].address);

    // Shift the symbols to remove the deleted symbol
    for (int i = foundIndex; i < *symbolCount - 1; i++) {
        symbolTable[i] = symbolTable[i + 1];
    }

    // Decrement the symbol count
    (*symbolCount)--;
    printf("Symbol deleted successfully.\n");
}

// Search and display a symbol's information
void searchAndDisplaySymbol(const struct SymbolEntry symbolTable[], int symbolCount, char symbolToSearch) {
    int foundIndex = -1;

    // Find the symbol to search for
    for (int i = 0; i < symbolCount; i++) {
        if (symbolTable[i].symbol == symbolToSearch) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Symbol not found. Cannot display.\n");
    } else {
        // Display the symbol's information
        printf("\nSymbol Information\n");
        printf("Symbol: %c\n", symbolTable[foundIndex].symbol);
        printf("Address: %p\n", symbolTable[foundIndex].address);
        printf("Type: %s\n", symbolTable[foundIndex].type);
    }
}

// Modify a symbol in the symbol table
void modifySymbol(struct SymbolEntry symbolTable[], int symbolCount, char symbolToModify) {
    int foundIndex = -1;

    // Find the symbol to modify
    for (int i = 0; i < symbolCount; i++) {
        if (symbolTable[i].symbol == symbolToModify) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Symbol not found. Cannot modify.\n");
        return;
    }

    // Modify the type of the symbol
    printf("Symbol found. Modifying symbol type.\n");
    strcpy(symbolTable[foundIndex].type, "modified");
    printf("Symbol modified. New type: %s\n", symbolTable[foundIndex].type);
}

// Main program
int main() {
    struct SymbolEntry symbolTable[50]; // Symbol table with a capacity of 50 symbols
    int symbolCount = 0;                // Count of symbols in the table
    int choice;                         // User's choice for the menu
    char newSymbol;                     // Variable to hold input symbols

    // Main loop for user interaction
    do {
        // Display menu for user interaction
        printf("\nSymbol Table Operations\n");
        printf("1. Insert Symbol\n");
        printf("2. Display Symbol Table\n");
        printf("3. Delete Symbol\n");
        printf("4. Search Symbol\n");
        printf("5. Modify Symbol\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform the operation based on the user's choice
        switch (choice) {
            case 1:
                printf("Enter symbol to insert: ");
                scanf(" %c", &newSymbol); // Insert a symbol
                insertSymbol(symbolTable, &symbolCount, newSymbol);
                break;

            case 2:
                displaySymbolTable(symbolTable, symbolCount); // Display the entire symbol table
                break;

            case 3:
                printf("Enter symbol to delete: ");
                scanf(" %c", &newSymbol); // Delete a symbol
                deleteSymbol(symbolTable, &symbolCount, newSymbol);
                break;

            case 4:
                printf("Enter symbol to search: ");
                scanf(" %c", &newSymbol); // Search and display a symbol
                searchAndDisplaySymbol(symbolTable, symbolCount, newSymbol);
                break;

            case 5:
                printf("Enter symbol to modify: ");
                scanf(" %c", &newSymbol); // Modify a symbol
                modifySymbol(symbolTable, symbolCount, newSymbol);
                break;

            case 6:
                // Free memory for all symbols before exiting
                for (int i = 0; i < symbolCount; i++) {
                    free(symbolTable[i].address);
                }
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6); // Exit loop when user chooses to exit

    return 0;
}
