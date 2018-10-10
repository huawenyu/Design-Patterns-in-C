#include<stdio.h>
int main()
{ int a,b,e,n;
  printf("enter no of rows of diamond");
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {  b=n;
     for(int j=1;j<=2*n-1;++j)
    { if(j<=n-i||j>=n+i)
     { printf("* ");
	 }
	else
	  {
	    if(j>n)
	    {a=e+1;
	    e=a;
		 }
		else
		{
		
		e=b;
		b=b-1;
		a=e;
	}
	  printf("%d ",a);
      }
	}
  printf("\n");
  }
  for(int i=1;i<n;i++) 
   {   b=n;
  for(int j=1;j<=2*n-1;j++)
     { if(j<=i||j>=2*n-i)
        printf("* ");
        else
        { if(j>n)
          { a=e+1;
          e=a;
		            }
	      else
		  { e=b;
		  b=b-1;
		  a=e;
			  }	
		printf("%d ",a);
		
		}
	 }
  printf("\n");
  }
return 0;	
}
