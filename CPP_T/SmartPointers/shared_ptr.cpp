#include <iostream>
#include <memory>
using namespace std;

class Rectangle{
    int lenght;
    int breadth;

    public:
    Rectangle(int l, int b){
        lenght = l;
        breadth = b;
    }
    int area(){
        return lenght *breadth;
    }
};

int main(){
    shared_ptr<Rectangle> P1(new Rectangle(10,5));
    cout<<P1->area()<<endl; //Print 50

    shared_ptr<Rectangle> P2;
    P2=P1;

    cout<<P2->area()<<endl; //Print 50
    cout<<P1->area()<<endl; //Print 50

    cout<<P1.use_count()<<endl;

    return 0;

}