#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <stdint.h>

struct SymbolEntry{
    char symbol;
    void *address;
    char type[40];
};

void insertSymbol(struct SymbolEntry symbolTable[],int *symbolCount,char newSymbol){
    //duplicates
    for(int i=0;i<*symbolCount;i++){
        if(symbolTable[i].symbol == newSymbol){
            printf("Duplicate\n");
            return;
        }
    }

    // allocate memory
    symbolTable[*symbolCount].address = malloc(sizeof(int));
    if(symbolTable[*symbolCount].address == NULL){
        printf("Address allocation failed\n");
        return;
    }

    // determine type 
    if(isalpha(newSymbol)){
        strcpy(symbolTable[*symbolCount].type,"identifier");
    }else{
        strcpy(symbolTable[*symbolCount].type,"operator");
    }

    symbolTable[*symbolCount].symbol = newSymbol;
    (*symbolCount)++;
}

void deleteSymbol(struct SymbolEntry symbolTable[], int *symbolCount, char symbolToDelete){
    int foundIndex = -1;
    // search the symbol index
    for (int i = 0; i < *symbolCount; i++)
    {
        if(symbolTable[i].symbol == symbolToDelete){
            foundIndex = i;
            break;
        }
    }

    if (foundIndex==-1)
    {
        printf("Symbol not found\n");
    }

    free(symbolTable[foundIndex].address);

    for(int i=foundIndex;i<*symbolCount;i++){
        symbolTable[i]=symbolTable[i+1];
    }
    (*symbolCount)--;
}

void displayTable(const struct SymbolEntry symbolTable[], int symbolCount){
    printf("\nSymbol Table\n");
    printf("Symbol \t Address \t\t Type\n");
    for(int i=0;i<symbolCount;i++){
        printf("%c \t %p \t %s\n", symbolTable[i].symbol, symbolTable[i].address, symbolTable[i].type);
    }
}

void searchAndDisplay(const struct SymbolEntry symbolTable[], int *symbolCount, char symbolToSearch){
    int foundIndex = -1;
    for(int i=0;i<*symbolCount;i++){
        if(symbolTable[i].symbol == symbolToSearch){
            foundIndex=i;
            break;
        }
    }

    if (foundIndex==-1)
    {
        printf("Symbol not found\n");
    }else{
        printf("\nSymbol Information\n");
        printf("Symbol: %c\n", symbolTable[foundIndex].symbol);
        printf("Address: %p\n", symbolTable[foundIndex].address);
        printf("Type: %s\n", symbolTable[foundIndex].type);
    }    
}

int main(){
    struct SymbolEntry symbolTable[50];
    int symbolCount=0;
    int choice;
    char newSymbol;
    do
    {
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

        switch(choice)
        {
        case 1:
            printf("Enter the symbol to be inserted: ");
            scanf(" %c",&newSymbol);
            insertSymbol(symbolTable,&symbolCount,newSymbol);
            break;
        case 2:
            displayTable(symbolTable, symbolCount);
            break;
        case 3:
            printf("Enter the symbol to be deleted: ");
            scanf(" %c",&newSymbol);
            deleteSymbol(symbolTable,&symbolCount,newSymbol);
            break;
        case 4:
            printf("Enter the symbol to search for: ");
            scanf(" %c",&newSymbol);
            searchAndDisplay(symbolTable,&symbolCount,newSymbol);
            break;
        
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice!=6);
    
    return 0;
}