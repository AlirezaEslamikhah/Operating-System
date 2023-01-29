#include <stdio.h>
int position = 0;
int jam();
int taghsim();
int condition();



int condition(char inp[])
{
  int n = 0;
  if(inp[position] == '('){
    position++;
    n = jam(inp);
    if(inp[position] == ')')
    {
      position++;
      return n;
    }
  }else{
    while('0' <= inp[position] && inp[position] <= '9'){
      n = n*10 + (inp[position] - '0');
      position++;
    }
  }
  return n;
}

int taghsim(char inp[]){
  int first,second;
  int temp = 0;
  first = condition(inp);
  for(int i= 0;i <50 ;i++){
    // if(inp[position] == '*'){
    //   position++;
    //   second = condition(inp);
    //   first *= second; 
    // }else if(inp[position] == '/'){
    //   position++;
    //   second = condition(inp);
    //   first /= second;
    if (inp[position] == '*' || inp[position] == '/')
    {
        if (inp[position] == '*')
      {
        // first += second;
        temp = 0; 
      }
      else if(inp[position] == '/')
      {
        // first -= second;
        temp = 1;
      }

      position++;
      second = condition(inp);
      first = (temp)? first / second : first * second;
      
    }
    
    else{
      return first;
    }
  }
}

int jam(char inp[]){
  int first,second;
  first = taghsim(inp);
  int j = 0;
  int temp = 0;
  // for(int i = 0;i < 50;i++)
  while(j<50)
  {
    // if(inp[position] == '+'){
    //   position++;
    //   second = taghsim(inp);
    //   first += second; 
    //   temp = 1;
    // }
    // if(inp[position] == '-')
    // {
    //   position++;
    //   second = taghsim(inp);
    //   first -= second;
    //   temp= 2;
    // }
    if (inp[position] == '+' || inp[position] == '-')
    {
      if (inp[position] == '+')
      {
        // first += second;
        temp = 0; 
      }
      else if(inp[position] == '-')
      {
        // first -= second;
        temp = 1;
      }

      position++;
      second = taghsim(inp);
      first = (temp)? first - second : first + second;
      
      
    }
    
    if(inp[position] != '+' && inp[position]!='-')
    {
      // if (temp == 1)
      // {
      //   first += second;
      // }
      // if (temp ==2 )
      // {
      //   first -= second;
      // }
      return first;
    }
    j++;
  }
  
}

int main(){
  char num;
  scanf("%s",num);
  int final[4];
  for (int i = 0; i < 5; i++)
  {
      char inp[90];
      scanf("%s",inp);
      final[i] = jam(inp);
      position = 0;
  }
  position = 0;
  final[0]+= 2;
  int tmp;
  if (final[1] > final[0])
  {
    tmp = final[0];
    final[0] = final[1];
    final[1] = tmp;  
  }
  
  // tmp = final[0];
  // final[0] = final[1];
  // final[1] = tmp;  
  for (int j = 0; j < 4; j++)
  {
    printf("%d ",final[j]); 
  }
 
  return 0;
  }
