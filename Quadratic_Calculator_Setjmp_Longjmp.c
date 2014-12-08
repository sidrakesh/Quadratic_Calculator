//Siddharth Rakesh
//11CS30036

#include<stdio.h>
#include<setjmp.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

typedef struct tag{   //required data structure
    double real;
    double imag;
}comp;

GetAns(double a,double b,double c)        //function for solving
{
    comp c1,c2;
    double r1,r2;
    jmp_buf buf1;   //jmp_buf variables (used for setjmp - longjmp)
    jmp_buf buf2;
    jmp_buf buf3;
    jmp_buf buf4;

    if(setjmp(buf1)==0)
    {
        if(b*b-4*a*c<=0)   //imaginary / equal roots
            longjmp(buf1,1);
        if(setjmp(buf2)==0)
        {
            if(a==0)
                longjmp(buf2,1);

            r1 = (-1*b+sqrt(b*b-4*a*c))/(2*a);
            r2 = (-1*b-sqrt(b*b-4*a*c))/(2*a);

            printf("\nRoots are : %lf & %lf",r1,r2);
        }
        else
        {
            r1 = (-1*c)/b;      //linear equation
            printf("\nEquation is linear; only one root exists, = %lf",r1);
        }
    }
    else if(setjmp(buf3)==0)
    {
        if(b*b==4*a*c)
            longjmp(buf3,1);
        if(setjmp(buf2)==0)
        {
            if(a==0)
                longjmp(buf2,1);

            c1.real = (-1*b)/(2*a);
            c1.imag = sqrt(4*a*c-b*b)/(2*a);

            c2.real = (-1*b)/(2*a);
            c2.imag = (-1)*sqrt(4*a*c-b*b)/(2*a);

            printf("\nComplex roots to the equation\nRoots are : %lf+%lfi & %lf%lfi",c1.real,c1.imag,c2.real,c2.imag);
        }
        else
        {
            r1 = (-1*c)/b;   //linear equation
            printf("\nEquation is linear; only one root exists, = %lf",r1);
        }
    }
    else
    {
        if(setjmp(buf2)==0)
        {
            if(a==0)
                longjmp(buf2,1);

            r1 = (-1*b)/(2*a);

            printf("\nRepeated roots occur; the roots being : %lf each",r1);
        }
        else
        {
            if(setjmp(buf4)==0)
            {
                if(c!=0)
                   longjmp(buf4,1);
                printf("\nGiven equation has all real numbers as its roots.");  //a=0,b=0,c=0
            }
            else
            {
                printf("\nNo solution exists to this equation.");//a=0,b=0,c!=0
            }
        }
    }
}

int main()   //main
{
    char ans;
    double a,b,c;
    do{
    system("CLS");
    printf("Welcome to the quadratic calulator!!\n\n");
    printf("Enter a=?");
    scanf("%lf",&a);

    printf("\nEnter b=?");
    scanf("%lf",&b);

    printf("\nEnter c=?");
    scanf("%lf",&c);

    GetAns(a,b,c);  //solving function invoked

    fflush(stdin);
    printf("\n\nDo you want to continue?(y/n)");
    ans = getch();
    }while(ans=='y'||ans=='Y');
return 0;
}
