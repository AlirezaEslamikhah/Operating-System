#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
int N = 1000;
int v_top = -1;
int o_top = -1;
char v_stack[1000];
char o_stack[1000];
char inp[100];

void v_push(char x)
{
    if(v_top == N-1)
        return;
    else{
        v_top+=1;
        v_stack[v_top] = x;
    }
}
char v_pop(){
        int x = v_stack[v_top];
        v_top-=1;
        return x;
    }
    return -1;
}
bool v_topp()
{
    if(v_top == -1)
        return;
    else{
        int x = v_stack[v_top];
        // v_top-=1;
        return x;
    }
    return -1;
}
bool v_isEmpty()
{
    if(v_top == -1)
    {
        return true;
    }
    return false;
}
bool v_isFull()
{
    if(v_top == N-1){
        return true;
    }
    return false;
}
void o_push(char x)
{
    if(o_top == N-1)
        return;
    else{
        o_top+=1;
        o_stack[o_top] = x;
    }
}
char o_pop(){
    if(o_top == -1)
        return;
    else{
        int x = o_stack[o_top];
        o_top-=1;
        return x;
    }
    return -1;
}
bool o_topp()
{
    if(o_top == -1)
        return;
    else{
        int x = o_stack[o_top];
        // o_top-=1;
        return x;
    }
    return -1;
}
bool o_isEmpty()
{
    if(o_top == -1)
    {
        return true;
    }
    return false;
}
bool o_isFull()
{
    if(o_top == N-1){
        return true;
    }
    return false;
}
bool cond(int i , int l ,char t)
{
    if (i<l && isdigit(t))
    {
        return true;
    }
    
}
int app(int a, int b, char op){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}
int pre(char op){
	if(op == '+'||op == '-')
	return 1;
	if(op == '*'||op == '/')
	return 2;
	return 0;
}
int solve(char inp[])
{
    for (int i = 0; i < sizeof(inp); i++)
    {
        if (inp[i] == '(')
        {
            o_push(inp[i]);
        }
        else if(inp[i] == ')')
        {
            if (o_isempty() && o_topp())
            {
                auto v2 = v_topp();
                v_pop();
                auto v1 = v_topp();
                v_pop();
                auto op = o_topp();
                o_pop();
                v_push(app(v1,v2,op));
            }
            if (!o_isempty())
            {
                o_pop();
            }   
        }
        else if(isdigit(inp[i]))
        {
            int v = 0;
            while (cond(i,sizeof(inp),inp[i]))
            {
                v = (v*10) + (inp[i] - '0');
                i++;
            }
            v_push(v);
            i--;
        }
        else 
        {
            while (!o_isempty() && pre(o_topp()>=pre(inp[i])))
            {
                auto v2 = v_topp();
                v_pop();
                auto v1 = v_topp();
                v_pop();
                auto op = o_topp();
                o_pop();
                v_push(app(v1,v2,op));
            }
            if(inp[i] == '-' && o_topp() == '(')
			{
				i++;
				if(isdigit(inp[i]))
				{
					int val = 0;	
					while(cond(i,sizeof(inp),inp[i]))
					{
						val = (val*10) + (inp[i]-'0');
						i++;
					}		
					v_push(val * -1);			
					i--;
				}
			}
            else
            {
				o_push(inp[i]);
			}
            
        }
        
    }
    //  while(!o_isempty()){
	// 	int val2 = v_topp();
	// 	v_pop();
				
	// 	int val1 = v_topp();
	// 	v_pop();
				
	// 	char op = o_topp();
	// 	o_pop();
				
	// 	v_push(app(val1, val2, op));
	// }	
	return v_topp();
        
}

int main()
{
    scanf("%s",inp);
    printf("%d\n",solve(inp));
    return 0;
}