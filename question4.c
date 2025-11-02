#include <stdio.h>
void displaymenu();
void push(int stack[], int *top, int maxsize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main()
 {
    int stack[100];     
    int top = -1;        
    int maxsize = 100;  
    int ch;
    printf(" STACK IMPLEMENTATION USING ARRAYS\n");
    
    do 
	{
        displaymenu();
        printf("enter your choice: ");
        scanf("%d", &ch);
        
        switch(ch) 
		{
            case 1:
                push(stack, &top, maxsize);
                break;
                
            case 2:
                pop(stack, &top);
                break;
                
            case 3:
                peek(stack, top);
                break;
                
            case 4:
                display(stack, top);
                break;
                
            case 5:
                printf("exiting program...\n");
                break;
                
            default:
                printf("invalid choice! please select 1-5.\n");
        }
        
    } 
	while(ch != 5);
}
void displaymenu() 
{
    printf("STACK MENU\n");
    printf("1. PUSH (insert element)\n");
    printf("2. POP (remove top element)\n");
    printf("3. PEEK (view top element)\n");
    printf("4. DISPLAY (show all elements)\n");
    printf("5. EXIT\n");
}
void push(int stack[], int *top, int maxsize) 
{
    printf("PUSH oPERTAION!\n");
    if(*top >= maxsize - 1) 
	{
        printf("error: STACK OVERFLOW!\n");
        printf("cannot push, stack is full.\n");
        return;
    }
    
    int value;
    printf("enter value to push: ");
    scanf("%d", &value);
    (*top)++;
    stack[*top] = value;
    
    printf("success: %d pushed onto stack.\n", value);
    printf("current top index: %d\n", *top);
}
void pop(int stack[], int *top) 
{
    printf("POP OPERATION\n");
    if(*top == -1)
	 {
        printf("error: STACK UNDERFLOW!\n");
        printf("cannot pop, stack is empty.\n");
        return;
    }
    
    int poppedvalue = stack[*top];
    (*top)--;
    
    printf("success: %d popped from stack.\n", poppedvalue);
    printf("current top index: %d\n", *top);
}
void peek(int stack[], int top)
 {
    printf("\n=== PEEK OPERATION ===\n");
    
    if(top == -1)
	 {
        printf("error: stack is empty!\n");
        printf("no element to peek.\n");
        return;
    }
    
    printf("top element: %d\n", stack[top]);
    printf("top index: %d\n", top);
}
void display(int stack[], int top) 
{
    printf("STACK DISPLAY \n");
    if(top == -1) {
        printf("stack is empty!\n");
        return;
}
    printf("stack elements (top to bottom):\n");
    int i;
    for(i = top; i >= 0; i--) 
	{
        if(i == top) {
            printf("TOP----- [%d] = %d\n", i, stack[i]);
        } else {
            printf("         [%d] = %d\n", i, stack[i]);
        }
    }
    printf("total elements: %d\n", top + 1);
}
