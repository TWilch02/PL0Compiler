//Program Authors: Terence Wilchcombe, Sloan Keller
//COP 3402
//December 4th 2022
//HW 1 VM
#include <stdio.h>
#include <string.h>
#include "compiler.h"
int base(int *pas, int BP, int L);
void print_stack(int PC, int BP, int SP, int GP, int *pas, int *bars);
void print_instruction(int PC, instruction IR);
instruction ir;
int pas[ARRAY_SIZE]={0};//Create address space
int bars[ARRAY_SIZE]={0};// array of bars for printing
int ic = 0; // Instruction Counter
int gp = 0; // Global Data Pointer
int dp = 0; // Data Pointer
int bp = 0; // Base Pointer
int pc = 0; // Program Counter
int sp = 0; // Stack Pointer
int halt = 1; // int for loops
char * fp;// file pointer
char *operation; // printer help
void execute (int trace_flag, instruction *code){
 int j = 0;

 for(int i = 0; code[i].op != -1; i++ )
 {
 pas[j] = code[i].op;
 pas[j+1] = code[i].l;
 pas[j+2] = code[i].m;
 j+= 3;
 }

 bp = j;//index
 sp = j - 1;
 pc = 0;
 halt = 1;
 while(halt){
 // fetch cycle
 ir.op = pas[pc];
 ir.l = pas[pc + 1];
 ir.m = pas[pc + 2];
 pc += 3;
 print_instruction(pc,ir);
 print_stack(pc,bp,sp,gp, pas,bars);
 // execute cycle
 switch(ir.op){
 case 1://LIT
 sp ++;
 pas[sp] = ir.m;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 2:// OPR
 switch(ir.m){
 case 0://RTN
 sp = bp -1;
 bp = pas[sp+2];
 pc = pas[sp+3];
 bars[sp+1] = 0;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 1://ADD
 pas[sp-1] = pas[sp-1]+pas[sp];
 sp --;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 2://SUB
 pas[sp-1] = pas[sp-1] - pas[sp];
 sp --;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 3://MUL
 pas[sp-1] = pas[sp-1] * pas[sp];
 sp --;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 4://DIV
 pas[sp-1] = pas[sp-1]/pas[sp];
 sp --;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 5://EQL
 if(pas[sp-1]==pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 6://NEQ
 if(pas[sp-1]!=pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 7://LSS
 if(pas[sp-1]< pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 8://LEQ
 if(pas[sp-1]<= pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 9://GTR
 if(pas[sp-1] > pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 10://GEQ
 if(pas[sp-1]>= pas[sp]){
 pas[sp-1] = 1;
 }else{
 pas[sp-1] = 0;
 }
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 default:
 break;
 }
 break;
 case 3://LOD
 sp++;
 pas[sp]= pas[base(pas,bp,ir.l)+ir.m];
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 4://STO
 pas[base(pas,bp,ir.l)+ir.m]= pas[sp];
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 5://CAL
 pas[sp+1] = base(pas,bp,ir.l);
 pas[sp+2] = bp;
 pas[sp+3]=pc;
 bars[sp+1] = 1;
 bp = sp + 1;
 pc = ir.m;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 6://INC
 sp = sp + ir.m;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 7://JMP
 pc = ir.m;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 8://JPC
 if(pas[sp]==0){
 pc = ir.m;
 }
 sp --;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 9://SYS
 switch(ir.m)
 {
 case 1://WRT
 printf("%d",pas[sp]);
 sp--;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 2://RED
 sp++;
 scanf("%d",&pas[sp]);
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 case 3://HLT
 halt = 0;
 if(trace_flag)
 {
 printf("%d\t%d\t%d\t%d\t",(pc-3)/3,ir.op,ir.l,ir.m);
 print_stack(pc , bp, sp, gp , pas, bars);
 }
 break;
 default :
 break;
 }

 break;
 }
 }
}
int base(int *pas, int BP, int L)
{
 int arb = BP; // arb = activation record base
 while (ir.l > 0) //find base L levels down
 {
 arb = pas[arb];
 ir.l--;
 }
 return arb;
}
void print_stack(int PC, int BP, int SP, int GP, int *pas, int *bars)
{
 int i;
 printf("%d\t%d\t%d\t", PC, BP, SP);
 for (i = BP; i <= SP; i++)
 {
 if (bars[i] == 1)
 printf("| %d ", pas[i]);
 else
 printf("%d ", pas[i]);
 }
 printf("\n");
}
void print_instruction(int PC, instruction IR)
{
 char opname[4];
 switch (IR.op)
 {
 case 1: strcpy(opname, "LIT"); break;
 case 2 :
 switch (IR.m)
 {
 case 0 : strcpy(opname, "RTN"); break;
 case 1 : strcpy(opname, "ADD"); break;
 case 2 : strcpy(opname, "SUB"); break;
 case 3 : strcpy(opname, "MUL"); break;
 case 4 : strcpy(opname, "DIV"); break;
 case 5 : strcpy(opname, "EQL"); break;
 case 6 : strcpy(opname, "NEQ"); break;
 case 7 : strcpy(opname, "LSS"); break;
 case 8 : strcpy(opname, "LEQ"); break;
 case 9 : strcpy(opname, "GTR"); break;
 case 10 : strcpy(opname, "GEQ"); break;
 default : strcpy(opname, "err"); break;
 }
 break;
 case 3 : strcpy(opname, "LOD"); break;
 case 4 : strcpy(opname, "STO"); break;
 case 5 : strcpy(opname, "CAL"); break;
 case 6 : strcpy(opname, "INC"); break;
 case 7 : strcpy(opname, "JMP"); break;
 case 8 : strcpy(opname, "JPC"); break;
 case 9 :
 switch (IR.m)
 {
 case 1 : strcpy(opname, "WRT"); break;
 case 2 : strcpy(opname, "RED"); break;
 case 3 : strcpy(opname, "HLT"); break;
 default : strcpy(opname, "err"); break;
 }
 break;
 default : strcpy(opname, "err"); break;
 }
printf("%d\t%s\t%d\t%d\t", (PC - 3)/3, opname, IR.l, IR.m);
printf("\t");
}