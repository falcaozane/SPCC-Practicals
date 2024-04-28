#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

    char label[100], opcode[100], operand[100], mnemonic[100];
    int locctr = 0;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt","r");
    fp2 = fopen("mot.txt", "r");
    fp3 = fopen("outputzane.txt", "w");
    fp4 = fopen("stzane.txt", "w");

    //START opcode
    fscanf(fp1, "%s %s %s", label, opcode, operand);
    fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);

    //USING opcode
}
