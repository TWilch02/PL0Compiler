//Program Authors: Terence Wilchcombe, Sloan Killer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "compiler.h"
//all four functions
void PsuedoMain();
void NumberConverter();
void SymbolConverter();
void IdentifierConverter();
lexeme *lex_analyze(int list_flag, char *in);
int ErrorFlag = 0, counter_list = 0 ;
int LFlag;
int x = 0;
token_type temp;
int ErrorType;
int counter_list;
lexeme *list;
int working = 0;
int Error_IdSize = 1, Error_NumLen = 2, Error_IdStart = 3, Error_Symbol = 4,
Error_NullMain = 5;
char *holder, *buffer;

lexeme *lex_analyze(int list_flag, char *input)
{
 // Allocate memory for holder and token
 holder = input;
 buffer = (char *)calloc(ARRAY_SIZE, sizeof(char));
 list = (lexeme *)calloc(ARRAY_SIZE, sizeof(lexeme));
 LFlag = list_flag;
 PsuedoMain();
 if (ErrorFlag == 1)
 {
 list = NULL;
 }
 return list;
}
void PsuedoMain(){
 if (LFlag == 1){
 printf("Lexeme List:\n");
 printf("lexeme\t\ttokentype\n");
 }
 x = 0;
 //Makes sure that the code parses until null terminator is detected in holder string
 while (holder[x] != '\0'){
 //Make ErrorType default for now
 ErrorType = working;
 //Checks if the index is a whitespace character
 if (isspace(holder[x])){
 x++;
 continue;
 }
 //Code checks for comments
 else if (holder[x] == '#'){
 while (holder[x] != '\n' && holder[x] != '\0'){
 x++;
 }
 continue;
 }
 //Checks if the index is a number
 else if (isdigit(holder[x])){
 //Calls function to turn number into a token
 NumberConverter();
 }
 //Checks if the index is an identifier
 else if (isalpha(holder[x])){
 //Calls function to turn identifier into a token
 IdentifierConverter();
 }
 else{
 //Calls function to turn symbol into a token
 SymbolConverter();
 }
 //Checks if there is an error anywhere
 if (ErrorType != working){
 printf("Lexical Analyzer Error: ");
 //Print statment for number length error
 if (ErrorType == Error_NumLen){
 printf("maximum number length is 5\n");
 }
 //Print statement for ID length error
 else if (ErrorType == Error_IdSize){
 printf("maximum identifier length is 11\n");
 }
 //Print statement for error called when Identifier starts with number
 else if (ErrorType == Error_IdStart){
 printf("identifiers cannot begin with digits\n");
 }
 //Print statement for Null or Main error
 else if (ErrorType == Error_NullMain){
 printf("identifiers cannot be named 'null' or 'main'\n");
 }
 //Print statment for invalid symbol
 else{
 printf("invalid symbol\n");
 }
 ErrorFlag = 1;
 }
 else{
 //Prints the actual lexeme table
 printf("%s\t%d\n", buffer, temp);
 list[counter_list].type = temp;
 //Assigns ID name to identifier token
 if (temp == identifier){
 strcpy(list[counter_list].identifier_name, buffer);
 }
 //Assigns number to number token
 else if (temp == number){
 list[counter_list].number_value = atoi(buffer);
 }
 counter_list++;
 }
 }
}
//Function made to convert a number into a token
void NumberConverter(){
 int y = 0;
 int MarkerX = 0;
 //Runs while loop for while index is a number
 while (isdigit(holder[x])){
 buffer[y++] = holder[x];
 x++;
 }
 //Throws error for is number length is greater than 5
 if (y > 5){
 ErrorFlag = 1;
 ErrorType = Error_NumLen;
 }
 //Continues through for num len error
 while (isalnum(holder[x])){
 MarkerX = 1;
 buffer[y++] = holder[x];
 x++;
 }
 //Marks ID starting with digit error
 if (MarkerX){
 if (ErrorType == working){
 ErrorFlag = 1;
 ErrorType = Error_IdStart;
 }
 }
 else{
 temp = number;
 }
 buffer[y] = '\0';
}
//Function for converting symbol to token
void SymbolConverter(){
 //Local vars
 int y = 0;
 buffer[y++] = holder[x];
 //Checks for '+'
 if (holder[x] == '+'){
 temp = plus;
 }
 //Checks for '-'
 else if (holder[x] == '-'){
 temp = minus;
 }
 //Checks for '*'
 else if (holder[x] == '*'){
 temp = times;
 }
 //Checks for '/'
 else if (holder[x] == '/'){
 temp = division;
 }
 //Checks for '.'
 else if (holder[x] == '.'){
 temp = period;
 }
 //Checks for ';'
 else if (holder[x] == ';'){
 temp = semicolon;
 }
 //Checks for '{'
 else if (holder[x] == '{'){
 temp = left_curly_brace;
 }
 else if (holder[x] == '}'){
 temp = right_curly_brace;
 }
 else if (holder[x] == '('){
 temp = left_parenthesis;
 }
 else if (holder[x] == ')'){
 temp = right_parenthesis;
 }
 else if (holder[x] == ':'){
 if (holder[x + 1] == '='){
 x++;
 buffer[y++] = holder[x];
 temp = assignment_symbol;
 }
 else{
 // needs a identifier
 ErrorType = Error_Symbol;
 }
 }
 else if (holder[x] == '='){
 if (holder[x + 1] == '='){
 x++;
 buffer[y++] = holder[x];
 temp = equal_to;
 }
 else{
 ErrorFlag = 1;
 // missing something
 ErrorType = Error_Symbol;
 }
 }
 else if (holder[x] == '<'){
 if (holder[x + 1] == '>'){
 x++;
 buffer[y++] = holder[x];
 temp = not_equal_to;
 }
 else if (holder[x + 1] == '='){
 x++;
 buffer[y++] = holder[x];
 temp = less_than_or_equal_to;
 }
 else{
 temp = less_than;
 }
 }
 else if (holder[x] == '>'){
 if (holder[x + 1] == '='){
 x++;
 buffer[y++] = holder[x];
 temp = greater_than_or_equal_to;
 }
 else{
 temp = greater_than;
 }
 }
 else{
 ErrorFlag = 1;
 // cannot be found
 ErrorType = Error_Symbol;
 }
 buffer[y] = '\0';
 x++;
}
// Converts Identifier into token
void IdentifierConverter(){
 int y = 0;
 while (isalnum(holder[x])){
 buffer[y++] = holder[x];
 x++;
 }
 buffer[y] = '\0';
if (strcmp(buffer, "const") == 0){
 temp= keyword_const;
}
else if (strcmp(buffer, "var") == 0){
 temp= keyword_var;
}
else if (strcmp(buffer, "procedure") == 0){
 temp= keyword_procedure;
}
else if (strcmp(buffer, "call") == 0){
 temp= keyword_call;
}
else if (strcmp(buffer, "begin") == 0){
 temp= keyword_begin;
}
else if (strcmp(buffer, "end") == 0){
 temp= keyword_end;
}
else if (strcmp(buffer, "if") == 0){
 temp= keyword_if;
}
else if (strcmp(buffer, "then") == 0){
 temp= keyword_then;
}
else if (strcmp(buffer, "else") == 0){
 temp= keyword_else;
}
else if (strcmp(buffer, "while") == 0){
 temp= keyword_while;
}
else if (strcmp(buffer, "do") == 0){
 temp= keyword_do;
}
else if (strcmp(buffer, "read") == 0){
 temp= keyword_read;
}
else if (strcmp(buffer, "write") == 0){
 temp= keyword_write;
}
else if (strcmp(buffer, "def") == 0){
 temp= keyword_def;
}
else if (strcmp(buffer, "null") == 0 || strcmp(buffer, "main") == 0){
 ErrorFlag = 1;
 ErrorType = Error_NullMain;
 }
 else if (y > 11)
 {
 ErrorFlag = 1;
 ErrorType = Error_IdSize;
 }
 else
 {
 temp = identifier;
 }
}