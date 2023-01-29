#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int stack[1000];
int top = -1;

int isfull() {

    if(top == 50)
        return 1;
    else
        return 0;
}
int isempty() 
{
    if(top == -1)
        return 1;
    else
        return 0;
}
int peek()
{
    return stack[top];
}
int pop() {
    int data;
    if(!isempty()) 
    {
    data = stack[top];
    // stack[top] = '00';
    top = top - 1;   

    return data;
    } 
    else 
    {
        printf("Could not retrieve data, Stack is empty.\n");
    }
}
void push(int data) 
{
    if(!isfull()) 
    {
    top = top + 1;   
    stack[top] = data;
    } else 
    {
    printf("Could not insert data, Stack is full.\n");
    }
}


void solve(char inp[] )
{
    int position = 0;
    for (int i = 0; i< strlen(inp);i++)
    {
        char x = inp[position];
        if (x != ',' &&  x !=' '&& x!= 0)
        {
            if ((int)(x) >= 48 && (int)(x) <= 57)
            {
                int val = 0;
                // while (isdigit(inp[position]))
                while((int)(inp[position]) >= 48 && (int)(inp[position]) <= 57)
                {
                    val = (val*10) + (inp[position]-'0');
                    position++;
                }
                // auto c = val + '0';
                // char v = (char)(val);
                push(val);
                // position--;
            }
            else if(x == '{')
            {
                push(9090);
                position++;
            }
            if (x == '}')
            {
                int i = position;
                int sum = 0;
                while (peek() != 9090)
                {
                    int y = pop();
                    sum += y;
                    i--;
                }
                if (peek() == 9090)
                {
                    int b = pop();
                }
                push(sum);
                printf("%d\n",sum);
                position++;
            }
        }
        // else if(isempty() == 1)
        // {
        //     break;
        // }
        else if(isempty() == 0 && inp[position] == '0')
        {
            push(0);
            position++;
        }
        else{
        position++;}
    }
    
}


int main()
{
    char inp[1000];
    scanf ("%[^\n]%*c", inp);
    solve(inp);
    // printf("%d",'9');
    return 0;
}