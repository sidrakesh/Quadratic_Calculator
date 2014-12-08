//Siddharth Rakesh
//11CS30036

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<cmath>
#include<cstdlib>
using namespace std;

//required class from question 1

class Complex
{
   public:
   // CONSTRUCTOR
   // -----------

   // Overloads to
   Complex(double r = 1.0, double i = 1.0) : re_(r), im_(i) {};
   Complex(double);
   Complex();
   // Copy Constructor - needed for efficient parameter passing
   Complex(const Complex&); // Param cannot be changed (const)
   // DESTRUCTOR
   // ----------
   //~Complex(); // No virtual destructor needed
   
   Complex operator-(); // Operand 'this' implicit
   // BASIC I/O using FRIEND FUNCTIONS
   // --------------------------------
   friend ostream& operator<<(ostream&, const Complex&);
   friend istream& operator>>(istream&, Complex&);
   // DYNAMIC MEMORY OPERATORS
   // ------------------------
   void *operator new(size_t s);
   void operator delete(void *ptr) throw();
   // COMPONENT FUNCTIONS
   //--------------------
   double GetReal() { return re_; }
   double GetImg() { return im_; }
   void SetValue(double a,double b);
   private:
   // DATA MEMBERS
   // ------------
   double re_; // The real part
   double im_; // The imaginary part
};

Complex Complex::operator-()
{
   return Complex( (-1.0*re_) , (-1.0*im_) );
}

ostream& operator<<(ostream& os, const Complex& param)
{
    if(param.im_>=0)
    {
        if(param.re_!=0&&param.im_!=0)
            os << param.re_ << " + " << param.im_ << "i";
        else if(param.re_==0&&param.im_!=0)
            os << param.im_ << "i";
        else if(param.im_==0&&param.re_!=0)
            os << param.re_;
        else os <<"0";
    }
    else
    {
        if(param.re_!=0&&param.im_!=0)
            os << param.re_ << " - " << -1*param.im_ << "i";
        else if(param.re_==0&&param.im_!=0)
            os << param.im_ << "i";
        else if(param.im_==0&&param.re_!=0)
            os << param.re_;
        else os <<"0";
    }
    return os;
}

istream& operator>>(istream& is, Complex& param)
{
    string s,sr,sim;
    int i;
   is>>s;

   if(s[0]=='-'&&s[1]=='('&&s[s.length()-1]==')')
   {
      for(i=2;s[i]!='+'&&s[i]!='-'&&s[i]!='i'&&i<s.length()-1;i++)
      sr.push_back(s[i]);

      if(s[i]=='i')
          {
             param.im_ = atof(sr.c_str());

             if(s[2]=='i')
                 param.im_ = 1;
             param.re_ = 0;
          }
      else if(i==s.length()-1)
          {
             param.re_ = atof(sr.c_str());
             param.im_ = 0;
          }
      else
      {
        i++;
        for(;i<s.length()-2;i++)
        sim.push_back(s[i]);

        param.re_ = atof(sr.c_str());
        param.im_ = atof(sim.c_str());
        if(param.im_==0&&s[s.length()-2]=='i'&&s[s.length()-3]=='+')
            param.im_ = 1;
        else if(param.im_==0&&s[s.length()-2]=='i'&&s[s.length()-3]=='-')
            param.im_ = -1;

        param = -(param);
      }
   }
   else
   {
      for(i=0;s[i]!='+'&&s[i]!='-'&&s[i]!='i'&&i<s.length();i++)
      sr.push_back(s[i]);

      if(s[i]=='i')
          {
             param.im_ = atof(sr.c_str());

             if(s[0]=='i')
                param.im_ = 1;

             param.re_ = 0;
          }
      else if(i==s.length())
          {
             param.re_ = atof(sr.c_str());
             param.im_ = 0;
          }

      else
      {
        i++;
        for(;i<s.length()-1;i++)
        sim.push_back(s[i]);

        param.re_ = atof(sr.c_str());
        param.im_ = atof(sim.c_str());

        if(param.im_==0&&s[s.length()-1]=='i'&&s[s.length()-2]=='+')
            param.im_ = 1;
        else if(param.im_==0&&s[s.length()-1]=='i'&&s[s.length()-2]=='-')
            param.im_ = -1;
      }
   }
   return is;
}

void* Complex::operator new(size_t s)
{
   void *storage = malloc(s);
    if(NULL == storage) {
            throw "allocation fail : no free memory";
    }
}

void Complex::SetValue(double a,double b)
{
   re_ = a;
   im_ = b;
}


void Complex::operator delete(void *ptr) throw()
{
   free(ptr);
}

void GetRoots(double a,double b,double c)      //solving function
{
    double real,imag;
    Complex r1(0,0),r2(0,0);
   try{                                //try - catch implementation
       if(b*b-4*a*c<0)
          throw 1;
       else if(b*b-4*a*c==0)
          throw 2;
       
       try{
           if(a==0)
              throw 1;
           
           real = (-1*b+sqrt(b*b-4*a*c))/(2*a);      //quadratic formula
           imag = 0;
           
           r1.SetValue(real,imag);
           
           real = (-1*b-sqrt(b*b-4*a*c))/(2*a);        
           imag = 0;
           
           r2.SetValue(real,imag);
       
       cout<<"Distinct real roots: "<<r1<<" & "<<r2;
       
       }
       catch(int i)
       {
           if(i==1)
           {
            r1.SetValue((-1*c)/b,0);
            cout<<"Only one real root exists : "<<r1;
           }
       }   
   }
   catch(int p)       //catch exception
   {
       if(p==1)     //imaginary roots
       {
        real = (-1*b)/(2*a);
        imag = sqrt(4*a*c-b*b)/(2*a);
           
        r1.SetValue(real,imag);
           
        real = (-1*b)/(2*a);
        imag = (-1)*sqrt(4*a*c-b*b)/(2*a);
           
        r2.SetValue(real,imag);
       
        cout<<"Distinct imaginary roots: "<<r1<<" & "<<r2<<"\n";
       }
       else if(p==2)   //equal roots
       {
        try{
            if(a==0) throw 1;
           
            real = (-1*b)/(2*a);
            r1.SetValue(real,0);
       
            cout<<"\nRepeated roots occur, each being : "<<r1<<"\n";
        }
        catch(int p)
        {
           try{
               if(c==0) throw 'a';
               
               cout<<"\nNo roots exist to this equation\n";
           }
           catch(char q)
           {
               cout<<"\nGiven equation is valid for all real and imaginary values.\n";
           }
        }
       }
   }
}

int main()      //main function
{
   double a,b,c;
   char res;
   do{
   system("CLS");
   cout<<"Welcome to the quadratic equation solver!!\n\n";
   cout<<"Enter a=?";
   cin>>a;
   cout<<"\nEnter b=?";
   cin>>b;
   cout<<"\nEnter c=?";
   cin>>c;
   
   GetRoots(a,b,c);
   
   fflush(stdin);
   
   cout<<"\n\nDo you want to continue?(y/n)...";
   
   res = getch();
   }while(res=='y'||res=='Y');
   return 0;
}

