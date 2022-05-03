#include <functional>
#include <iostream>

struct Foo{
    Foo(int num) : num_(num){}
    void print_add(int i) const {std::cout<<num_+i<<std::endl;}
    int num_;
};

void print_num(int i){
    std::cout<<i<<std::endl;
}

struct PrintNum{
    void operator()(int i)const {
        std::cout<<i<<std::endl;
    }
};

int main(){
    //Store a free function
    //Guardar una funcion libre
 
    std::function<void(int)>f_display = print_num;
    f_display(-9);

    //Store a Lambda
    //Guardar una funcion lambda
    
    std::function<void()> f_display_42 = [](){print_num(42);};
    f_display_42();

    //store the result of call to std::bind
    //Guardar el resultado de la llamada de std::bind

    std::function<void()> f_display_31337 = std::bind(print_num,31337);
    f_display_31337();

  
    //store the call to a member function
    //guarda la llamda a una funcion miembro
    
    std::function<void(const Foo&, int)>f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo,1);
    f_add_display(34459,1);


    //store a call to a data member accesor
    //guarda la llamada de acceso a un miembro data
/*    
    std::function<void(Foo const&)> f_num = &Foo::num_;
    std::cout<<"num_:"<<f_num(foo)<<std::endl;
*/
    //store a call to a member function and object
    //guarda la llamadaa un objeto y la funcion miembro
    
    using std::placeholders::_1;
    std::function<void(int)>f_add_display2 = std::bind(&Foo::print_add,foo,_1);
    f_add_display2(2);

    //store the call to a memeber function and object ptr
    //guarda un apuntador a un objeto y a la funcion miembro
    std::function<void(int)>f_add_display3 = std::bind(&Foo::print_add,&foo,_1);
    f_add_display3(3);

    //store a call to a function object
    //guarda la llmada objeto funcion
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);

    auto factorial = [](int n){
        //store a lambda function to emulate "recursive lambda" aware of extra overhead
        //guardando una funcion lambada para emular la lambda recursiva, estar pendiente de la sobrecomplejidad
        std::function<int(int)>fac= [&](int n){return (n<2)?1:n*fac(n-1);};
        //nota que auto fac = [&](int n){....}," no funcionaria en llamadas recursivas
        return fac(n);
    };
    for (int i{5}; i !=8; ++i){std::cout<<i<<"!="<<factorial(i)<<";"<<std::endl;}
            
    return 0;
}
