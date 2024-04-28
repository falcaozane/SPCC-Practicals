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
    fscanf(fp1,"%s %s %s",label,opcode,operand);
    fprintf(fp3,"%d %s %s %s\n",locctr,label,opcode,operand);

    while (strcmp(opcode,"END")!=0)
    {
        if (str(opcode,"DC")==0 || str(opcode,"DS")==0)  
        {
            fprintf(fp4,"%s %d\n",label,locctr);
            fprintf(fp3,"%d %s %s %s\n",locctr,label,opcode,operand);
            locctr+=4;
        }
        else
        {
            fscanf(fp2,"%s",mnemonic);
            fprintf(fp3,"%d %s %s %s",locctr,label,opcode,operand);
            while (strcmp(mnemonic,"end")!=0)
            {
                if (strcmp(opcode,mnemonic)==0)
                {
                    locctr+=4;
                    break;
                }
                fscanf(fp2,"%s",mnemonic); 
            }
            rewind(fp2);
        }
        fscanf(fp1,"%s %s %s %s",label,opcode,operand);
    }

    fprintf(fp3,"%d %s %s %s",locctr,label,opcode,operand);
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
