//Name : yaman abu jazar
//ID : 1212199
//Section : 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 100
//declare a stack
typedef struct node* PtrToNode;
typedef PtrToNode Stack;
struct node
{
    int Element;
    PtrToNode next;
};
void DisposeStack(Stack S);
void Push(int X, Stack S);
int Top(Stack S);
int Pop(Stack S);
void MakeEmpty(Stack S);
Stack CreateStack();
int IsEmpty(Stack S);
int IsValid(char S[],int *index);
void prefix(char infix[], char* result);
int evaluatePrefix(char prefix[]);
int isNumber(char x);
int isNumber1(char x[]);
int isOperation(char x);
int isBracket(char x);
int precedence(char x);
void splitStringBySpaces(char* original, char* result);
//main function
int main()
{
    //declare the files we use to read and write the inputs and outputs
    FILE *input,*output;
    char file[] = "input.txt";
    input = fopen(file,"r");
    output = fopen("output.txt","w");
    char equation[SIZE][SIZE] = {};
    char prefixEquation[SIZE][SIZE] = {};
    //read input file.
    int R = fscanf(input,"%s",equation[0]);
    int countOfEquations = 0,count = 97;
    for(int i = 1 ; R != EOF ; i++)
    {
        countOfEquations++;
        R = fscanf(input,"%s",equation[i]);
    }
    int x[countOfEquations];
    char eq[SIZE][SIZE] = {};
    int selection;
    //print the interface of the project.
    printf("Choose one task.\n");
    printf("1-Read the input file.\n");
    printf("2-Check the validity of equations.\n");
    printf("3-Convert valid equations from infix to prefix.\n");
    printf("4-Evaluate the prefix expressions.\n");
    printf("5-Print invalid equations.\n");
    printf("6-Print all equations to the file.\n");
    printf("7-Exit.\n");
    scanf("%d",&selection);
    while(selection != 7)
    {
        //switch statement to determine the task that the user chose it
        switch(selection)
        {
        case 1://Read the input file
            printf("Enter the name of the file.\n");
            scanf("%s",file);
            input = fopen(file,"r");
            R = fscanf(input,"%s",equation[0]);
            countOfEquations = 0;
            for(int i = 1 ; R != EOF ; i++)
            {
                countOfEquations++;
                R = fscanf(input,"%s",equation[i]);
            }
            for(int i = 0 ; i < countOfEquations ; i++)
            {
                printf("%s\n",equation[i]);
            }
            fclose(input);
            break;
        case 2://Check the validity of equations
            for(int i = 0 ; i < countOfEquations ; i++)
            {
                x[i] = IsValid(equation[i],0);
            }
            for(int i = 0 ; i < countOfEquations ; i++)
            {
                switch(x[i])
                {
                case 0:
                    printf("%c. Equation No. %d -> Invalid: Equation starting with operation.\n",(count++),(i+1));
                    break;
                case 1:
                    printf("%c. Equation No. %d -> Valid\n",(count++),(i+1));
                    break;
                case 2:
                    printf("%c. Equation No. %d -> Invalid: ] has no [ \n",(count++),(i+1));
                    break;
                case 3:
                    printf("%c. Equation No. %d -> Invalid: ) has no ( \n",(count++),(i+1));
                    break;
                case 4:
                    printf("%c. Equation No. %d -> Invalid: two operations after each other \n",(count++),(i+1));
                    break;
                case 5:
                    printf("%c. Equation No. %d -> Invalid: operation after open parenthesis without number \n",(count++),(i+1));
                    break;
                case 6:
                    printf("%c. Equation No. %d -> Invalid: close parentheses after operation \n",(count++),(i+1));
                    break;
                case 10:
                    printf("%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                    break;
                case 11:
                    printf("%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                    break;
                case 12:
                    printf("%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                    break;
                case 13:
                    printf("%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                    break;
                case 14:
                    printf("%c. Equation No. %d -> Invalid: [ is not closed \n",(count++),(i+1));
                    break;
                case 15:
                    printf("%c. Equation No. %d -> Invalid: ( is not closed \n",(count++),(i+1));
                    break;
                }
            }
            count = 97;
            break;
        case 3://Convert valid equations from infix to prefix
            for(int i = 0 ; i < countOfEquations ; i++)
            {
                splitStringBySpaces(equation[i],eq[i]);
            }
            for(int i = 0, j = 0, k = 0; i < countOfEquations ; i++)
            {
                if(x[i] == 1)
                {
                    prefix(eq[i],prefixEquation[j]);
                    printf("%c. Equation No. %d -> %s\n",(count++),(++k),prefixEquation[j++]);
                }
            }
            count = 97;
            break;
        case 4://Evaluate the prefix expressions
            for(int i = 0, j = 0, k = 0 ; i < countOfEquations ; i++)
            {
                if(x[i] == 1)
                {
                    printf("%c. Equation No. %d -> %d\n",(count++),(++k),evaluatePrefix(prefixEquation[j++]));
                }
            }
            count = 97;
            break;
        case 5://Print invalid equations
            for(int i = 0, j = 0; i < countOfEquations ; i++)
            {
                if(x[i] != 1)
                {
                    printf("%c. Equation No. %d -> %s\n",(count++),(++j),equation[i]);
                }
            }
            count = 97;
            break;
        case 6://Print all equations to the file
            for(int i = 0, j = 0; i < countOfEquations ; i++)
            {
                fprintf(output,"%c. Equation No. %d -> %s\n",(count++),(i+1),equation[i]);
                if(x[i] == 1)
                {
                    fprintf(output,"Valid:\n");
                    fprintf(output,"PreFix Expression. -> %s\n",prefixEquation[j]);
                    fprintf(output,"The result = %d.\n",evaluatePrefix(prefixEquation[j++]));
                }
                else
                {
                    switch(x[i])
                    {
                    case 0:
                        fprintf(output,"%c. Equation No. %d -> Invalid: Equation starting with operation.\n",(count++),(i+1));
                        break;
                    case 1:
                        fprintf(output,"%c. Equation No. %d -> Valid\n",(count++),(i+1));
                        break;
                    case 2:
                        fprintf(output,"%c. Equation No. %d -> Invalid: ] has no [ \n",(count++),(i+1));
                        break;
                    case 3:
                        fprintf(output,"%c. Equation No. %d -> Invalid: ) has no ( \n",(count++),(i+1));
                        break;
                    case 4:
                        fprintf(output,"%c. Equation No. %d -> Invalid: two operations after each other \n",(count++),(i+1));
                        break;
                    case 5:
                        fprintf(output,"%c. Equation No. %d -> Invalid: operation after open parenthesis without number \n",(count++),(i+1));
                        break;
                    case 6:
                        fprintf(output,"%c. Equation No. %d -> Invalid: close parentheses after operation \n",(count++),(i+1));
                        break;
                    case 10:
                        fprintf(output,"%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                        break;
                    case 11:
                        fprintf(output,"%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                        break;
                    case 12:
                        fprintf(output,"%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                        break;
                    case 13:
                        fprintf(output,"%c. Equation No. %d -> Invalid: There is no operator \n",(count++),(i+1));
                        break;
                    case 14:
                        fprintf(output,"%c. Equation No. %d -> Invalid: [ is not closed \n",(count++),(i+1));
                        break;
                    case 15:
                        fprintf(output,"%c. Equation No. %d -> Invalid: ( is not closed \n",(count++),(i+1));
                        break;
                    }
                }
            }
            printf("\nDone.\n");
            break;
        default:
            printf("Unavailable choice.\n");
            break;

        }
        printf("Choose one task.\n");
        printf("1-Read the input file.\n");
        printf("2-Check the validity of equations.\n");
        printf("3-Convert valid equations from infix to prefix.\n");
        printf("4-Evaluate the prefix expressions.\n");
        printf("5-Print invalid equations.\n");
        printf("6-Print all equations to the file.\n");
        printf("7-Exit.\n");
        scanf("%d",&selection);
    }
    fclose(output);
    printf("\nExiting...\n");
    return 0;
}
//functions to create a stack and do operations on it
void DisposeStack(Stack S)
{
    MakeEmpty(S);
    free(S);
}
//push an element to the stack
void Push(int X, Stack S)
{
    PtrToNode temp;
    temp = ( Stack )malloc( sizeof( struct node ) );
    if( temp == NULL)
        printf("Out of space!");
    else
    {
        temp->Element = X;
        temp->next = S->next;
        S->next = temp;
    }
}
//find the top of the stack
int Top(Stack S)
{
    if(!IsEmpty(S))
        return S->next->Element;
    printf("Empty stack");
    return 0;
}
//return and delete the top of the stack
int Pop(Stack S)
{
    PtrToNode firstCell;
    int x;
    if(IsEmpty(S))
    {
        printf("Empty stack");
        return 0;
    }
    else
    {
        x = S->next->Element;
        firstCell = S->next;
        S->next = S->next->next;
        free(firstCell);
        return x;
    }
}
//make the stack empty
void MakeEmpty(Stack S)
{
    if(S == NULL)
        printf("Out of space!");
    else
        while(!IsEmpty(S))
            Pop(S);
}
//function to create the stack
Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct node));
    if(S == NULL)
        printf("Out of space!");
    S->next = NULL;
    MakeEmpty(S);
    return S;
}
//function to determine if the stack is empty or not
int IsEmpty(Stack S)
{
    return S->next == NULL;
}
//function to determine if the infix expression is valid to find its value or not
int IsValid(char S[],int *index)
{
    int square = 0, bracket = 0;
    if(isOperation(S[0]) && precedence(S[0]) > 0)
        return 0;
    else
    {
        char check;
        for(int i = 0 ; i < strlen(S) ; i++)
        {
            check = S[i];
            if( isBracket(check) )
            {
                if(check == '[')
                    square++;
                else if(check == ']')
                {
                    if(square > 0)
                        square--;
                    else
                        return 2;
                }
                else if(check == '(')
                    bracket++;
                else if(check == ')')
                {
                    if(bracket > 0)
                        bracket--;
                    else
                        return 3;
                }
            }
            else if(isOperation(check))
            {
                if(i != 0 && isOperation(S[i+1]) && precedence(S[i+1]) > 0)
                {
                    return 4;
                }
                else if(i != 0 && (S[i-1] == '[' || S[i-1] == '(') && precedence(S[i]) > 0)
                {
                    return 5;
                }
                else if(i != 0 && (S[i+1] == ']' || S[i+1] == ')'))
                {
                    return 6;
                }
            }
            else if( isNumber(check) )
            {
                if( !isOperation(S[i-1]))
                {
                    if(S[i-1] == ']')
                        return 10;
                    else if(S[i-1] == ')')
                        return 11;
                }
                else if( !isOperation(S[i+1]))
                {
                    if(S[i+1] == '[')
                        return 12;
                    else if(S[i+1] == '(')
                        return 13;
                }
            }
        }
        if(square != 0 )
            return 14;
        if(bracket != 0 )
            return 15;
    }
    return 1;
}
//function to convert from infix expression to prefix expression
void prefix(char infix[], char* result)
{
    Stack pre = CreateStack();
    char temp[strlen(infix)];
    strcpy(temp,infix);
    strrev(temp);
    char *token = strtok(temp," ");
    char check[] = {};
    int counter = 0 ;
    while(token != NULL)
    {
        strcpy(check,token);
        if( isBracket(check[0]) )
        {
            if(check[0] == ']')
            {
                Push(']',pre);
            }
            else if(check[0] == ')')
            {
                Push(')',pre);
            }
            else if(check[0] == '[')
            {
                while(pre->next->Element != ']')
                {
                    if( !isBracket(pre->next->Element))
                    {
                        result[counter++] = Pop(pre);
                        result[counter++] = ' ';
                    }
                    else
                        Pop(pre);
                }
            }
            else if(check[0] == '(')
            {
                while(pre->next->Element != ')')
                {
                    if( !isBracket(pre->next->Element))
                    {
                        result[counter++] = Pop(pre);
                        result[counter++] = ' ';
                    }
                    else
                        Pop(pre);
                }
            }
        }
        if( isNumber1(check) )
        {
            if(strlen(check)>1)
            {
                for(int k = 0 ; k < strlen(check) ; k++)
                {
                    result[counter++] = check[k];
                }
                result[counter++] = ' ';
            }
            else
            {
                result[counter++] = check[0];
                result[counter++] = ' ';
            }
        }
        else if( isOperation(check[0]) )
        {
            if( IsEmpty(pre) )
            {
                Push(check[0],pre);
            }
            else
            {
                check[1] = pre->next->Element;
                if( isBracket(check[1]) )
                {
                    Push(check[0],pre);
                }
                else if( isOperation(check[1]) )
                {
                    if(precedence(pre->next->Element) > precedence(check[0]))
                    {
                        while(isOperation(pre->next->Element) && (precedence(pre->next->Element) > precedence(check[0])))
                        {
                            result[counter++] = Pop(pre);
                            result[counter++] = ' ';
                        }
                        Push(check[0],pre);
                    }
                    else
                        Push(check[0],pre);
                }
            }
        }
        token = strtok(NULL," ");
    }
    while(pre->next != NULL)
    {
        if( !isBracket(pre->next->Element))
        {
            result[counter++] = Pop(pre);
            result[counter++] = ' ';
        }
        else
            Pop(pre);
    }
    int len = strlen(result);
    result[len-1] = '\000'; // Null-terminate the resulting string
    strrev(result);
}
//function to evaluate the prefix expression
int evaluatePrefix(char prefix[])
{
    Stack pre = CreateStack();
    int num1, num2, num =0;
    char temp[strlen(prefix)];
    char check[] = {};
    strcpy(temp,prefix);
    strrev(temp);
    char *token = strtok(temp," ");
    while(token != NULL)
    {
        strcpy(check,token);
        if( isNumber1(check) )
        {
            num = 0;
            if(strlen(check) > 1)
            {
                strrev(check);
                for(int i = 0; i < strlen(check) ; i++)
                {
                    num += ((int)check[i] - '0')*pow(10,(strlen(check)-1-i));
                }
                Push(num,pre);
            }
            else
                Push((int)check[0]-'0',pre);
        }
        else if( isOperation(check[0]) )
        {
            num1 = Pop(pre);
            num2 = Pop(pre);
        }
        switch (check[0])
        {
        case '+':
            Push((num1 + num2),pre);
            break;
        case '-':
            Push((num1 - num2),pre);
            break;
        case '*':
            Push((num1 * num2),pre);
            break;
        case '/':
            if(num2 == 0){
                Push(0, pre);
            }
            else{
                Push((num1 / num2),pre);
            }
            break;
        case '^':
            Push((pow(num1,num2)),pre);
            break;
        }
        token = strtok(NULL," ");
    }
    int result = Top(pre);
    return result;
}
//function to determine if the char is number or not
int isNumber(char x)
{
    for(int i = 0 ; i < 10 ; i++)
    {
        if((int)x-'0' == (i))
            return 1;
    }
    return 0;
}
//function to determine if the char is operator or not
int isOperation(char x)
{
    if(x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
        return 1;
    else
        return 0;
}
//function to determine if the char is parentheses or not
int isBracket(char x)
{
    if(x == '[' || x == '(' || x == ')' || x == ']')
        return 1;
    else
        return 0;
}
//function to determine if the string is number or not
int isNumber1(char x[])
{
    int j;
    int sum = 0;
    int digit[strlen(x)];
    for(j = 0 ; j < strlen(x) ; j++)
    {
        for(int i = 0 ; i < 10 ; i++)
        {
            if((int)x[j]-'0' == (i))
            {
                digit[j] = 1;
                sum += digit[j];
            }
        }
    }
    if(sum == (strlen(x)))
        return 1;
    return 0;
}
//function to determine the precedence of the operations
int precedence(char x)
{
    if(x == '^')
        return 2;
    else if(x == '*' || x == '/')
        return 1;
    else if(x == '+' || x == '-')
        return 0;
    return 0;
}
//function to determine the length of the prefix expression
int sizeofPrefix(char equation[])
{
    int count = 0;
    for(int i = 0 ; i < strlen(equation) ; i++)
    {
        if(isNumber(equation[i]) || isOperation(equation[i]))
            count++;
    }
    return count;
}
//function to add spaces to the strings
void splitStringBySpaces(char* original, char* result)
{
    int length = strlen(original);
    int i, j;


    for (i = 0, j = 0 ; i < length; i++)
    {
        if(isBracket(original[i]))
        {
            result[j] = original[i];
            result[j + 1] = ' '; // Add a space before every character
            j += 2;
        }
        if(isNumber(original[i]))
        {
            if(!isNumber(original[i+1]))
            {
                result[j] = original[i];
                result[j + 1] = ' '; // Add a space before every character
                j += 2;
            }
            else
            {
                result[j] = original[i];
                j++;
            }
        }
        if(isOperation(original[i]))
        {
            if(isBracket(original[i+1]))
            {
                result[j] = original[i];
                result[j + 1] = ' '; // Add a space before every character
                j += 2;
            }
            else if( isOperation(original[i+1]) )
            {
                while(isOperation(original[i+1]))
                {
                    if(original[i] != original[i+1])
                    {
                        result[j] = '-';
                        result[j + 1] = ' '; // Add a space before every character
                        j += 2;
                        i++;
                    }
                    else
                    {
                        result[j] = '+';
                        result[j + 1] = ' '; // Add a space before every character
                        j += 2;
                        i++;
                    }
                }
            }
            else if( (i == 0 || isBracket(original[i-1])) && isNumber(original[i+1]))
            {
                if(original[i-1] == '[' || original[i-1] == '(' )
                {
                    result[j] = original[i];
                    j++;
                }
                else if( i == 0 && isNumber(original[i+1]))
                {
                    result[j] = '0';
                    result[j+1] = ' '; // Add a space before every character
                    result[j+2] = original[i];
                    result[j+3] = ' '; // Add a space before every character
                    j += 4;
                }
                else
                {
                    result[j] = original[i];
                    result[j + 1] = ' '; // Add a space before every character
                    j += 2;
                }
            }
            else
            {
                result[j] = original[i];
                result[j + 1] = ' '; // Add a space before every character
                j += 2;
            }
        }
    }
    result[j] = '\000'; // Null-terminate the resulting string
}
