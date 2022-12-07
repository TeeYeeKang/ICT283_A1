#include <iostream>
#include "Vector.h"
#include "Date.h"
#include <fstream>

using namespace std;

bool testIntvec(Vector<int> &vec);
void testDatevec(Vector<Date> &vec);

int main()
{
    Vector<int> intvec;
    Vector<Date> datevec;

    if(testIntvec(intvec)!= true)
    {
        cout<<"\nnot working"<<endl;
    }
    else
    {
        cout<<"\nIts working"<<endl;
    }


    cout<<"----------------------------------------"<<'\n';

    testDatevec(datevec);

    cout<<"----------------------------------------"<<'\n';
    cout<<"Test for deep copy"<<endl;
    Vector<int> newVector;
    newVector.Copy(intvec);
    //newVector = intvec;
    newVector.Display();

    return 0;
}

bool testIntvec(Vector<int> &vec)
{
    cout<<"Test for int vector\n"<<endl;

    for(int idx=1; idx<20; idx++)
    {
        vec.PushBack(idx);
    }

    if(vec.Get(0) != 0)
    {
        vec.Display();

        //remove item
        int num1, num2;
        vec.PopBack(num1);
        vec.PopBack(num2);

        cout<<'\n';
        cout<<"The deleted numbers are "<< num1 << " and " << num2 <<endl;
        cout<<"After pop\n"<<endl;

        cout << "Test for the Get() operator" << endl;
        for(int i=0; i<vec.GetCounter(); i++)
        {
            cout<<vec.Get(i)<< " ";
        }

        cout<<'\n';
        cout<<"\nTest for get function"<<endl;
        cout<<vec.Get(2)<<endl; //test for get function
        cout<<"\nTest for get size function: "<<vec.GetVecSize()<<endl;

        return true;
    }
    else
    {
        return false;
    }

}

void testDatevec(Vector<Date> &vec)
{
    cout<<"Test for Date type vector\n"<<endl;

    Date d1(3, 1, 1999);
    Date d2(3, 2, 1999);
    Date d3(3, 3, 1999);
    Date d4(3, 4, 1999);
    Date d5(3, 5, 1999);

    vec.PushBack(d1);
    vec.PushBack(d2);
    vec.PushBack(d3);
    vec.PushBack(d4);
    vec.PushBack(d5);


    vec.Display();

    cout<<'\n';
    cout<<"After pop\n"<<endl;

    Date removeDate1, removeDate2;

    vec.PopBack(removeDate1);
    vec.PopBack(removeDate2);

    vec.Display();
}
