#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <future>

#define LESSON_16 1
using namespace std;
using namespace std::chrono;


#ifdef LESSON_1
typedef unsigned long long ull ;

/*
 *GLOBAL VARIABLES
 * */

ull OddSum = 0;
ull EvenSum = 0;
 

/*
 *FUNTIONS
 */

void findEven(ull start, ull end){
    for(ull i = start; i <= end; i++){
        if((i & 1) == 0){
            EvenSum+=i;
        }
    }
}

void findOdd(ull start, ull end){
    for(ull i = start; i <= end; i++){
        if((i & 1) == 1){
            OddSum+=i;
        }
    }
}

int main(){

    ull start = 0, end = 1900000000;

    auto startTime = high_resolution_clock::now();

    std::thread t1(findEven,start, end);
    std::thread t2(findOdd,start, end);
    
    t1.join();
    t2.join();
    //findOdd(start,end);
    //findEven(start,end);

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum : " << EvenSum << endl;

    cout<< "Sec:  "<<duration.count()/1000000<< endl;

    return 0;

 
}
#endif


#ifdef LESSON_2

/*
 *TEMA : Tipos de Creacion para hilos(threads) en c++11
 */

/*
 * NOTAS:
 * Si creamos multiples hilos(threads) al mismo tiempo no garantiza cual empezara primero 
 */

/*
 * 1.Apuntador a funcion( Funcion Pointer)
 * La forma mas basica de crear un thread
 */

void fun(int x){
    while(x-- >0){
        cout<<x<<endl;
    }
}

/*
 *3.FUNCTOR FuncionesdeObjetos(FunctionObjects)
 */
class Base{
    public:
        void operator()(int x){
            while(x-- >0){
                cout<<x<<endl;
            }
        }
};

/*
 * 4. Funciones miembro no estaticas(non-static member function)
 */
class BaseA
{
    public:
        void run(int x){
            while(x-- >0){
                cout<<x<<endl;
            }
        }
};


/*
 *5. Funcion miembro estatica(static member function)
 */
class BaseB{
    public:
        static void run(int x){
            while(x-- > 0){
                cout << x << endl;
            }
        }
};

int main(){
    /*
     * 1
     */
    std::thread t1(fun,11);


    /*
     *2. Funciones lambda (lambda funcions)
     */

    std::thread t2([](int x){
            while (x-- >0){
            cout<<x<<endl;
            }
           },12);
    /*
     * 3
     */
    std::thread t3((Base()),13);


    /*
     * 4
     */
    BaseA a;
    std::thread t4(&BaseA::run,&a,14);
  
    /*
     * 5
     */

    std::thread t5(&BaseB::run,15);

   /*
    *Joining threads
    */ 
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();


    return 0;
}
#endif


#ifdef LESSON_3
/*
 *TEMA: Uso the join(), detach() y joinable() en hilos (thread) c++11
 */


/* 
 * Notas de JOIN
 * 0. Una vez que un hilo(thread) es iniciado esperamos por el hilo(thread) se termeine llamando el metodo join() en el objeto thread
 * 1. Dos veces join() resultara en la terminacion del programa
 * 2. Si es necesario debemos checar si el hilo(thread) es joinable antes de usar join.(usiando joinable() function) 
 */


/*
 * Notas de DETACH
 * 0.Esto es usado para separar(detach) los  hilos(threads) creados del hilo padre.
 * 1.Siempre checar antes de separar(detach) un thread es joinable de otra manera puedes terminando haciendo un doble detach , lo
 *resultara en la terminacion del programa.
 * 2.Si has separado(detach) un hilo(thread) y la funcion main esta terminado , la ejecucion del hilo(thread) separado(detach) sera suspendido.
 */

/*
 * NOTAS:
 *Ya sea join() o detach() tendra que ser usado con un objeto thread, de otra manera cualdo el destructor del objeto sa llamado se terminara
 *el progrma. Dentro del destructor checa shi el thread es joinable , si lo es , terminara el programa.
 */


void run(int count){
    while(count-- > 0){
        cout<<"SEB"<<endl;
    }
//    std::this_thread::sleep_for(chrono::seconds(3));
}

int main(){
    std::thread t1(run,10);
    cout<<"main()"<<endl;
//    t1.join();
//    if(t1.joinable()){
//        t1.join();
//    }
    t1.detach();
    cout<<"main() after"<<endl;

    return 0;

}
#endif

#ifdef LESSON_4

/*
 *TEMA: Mutex en C Threading|Porque usar Mutex|Que es una condicion y como resolverlo?|Quee es una seccion critica
 */

/*
 *Mutex: Mutuamente Exclusivo
 */

/*
 *Condicion de carrera (RACE CONDITION)
 *0.Condicion de carrera es cuando dos o mas threads(hilos/procesos) tratande cambiar datos en comun al mismo tiempo.
 *1.Si sucede una condicion de carrera tnemos que protejerle y la region protegida es la seccion critica.
 */


/*
 *MUTEX
 *0.Mutex es usado para evitar condiciones de carrera
 *1.se usa lock(), unlock(), en mutex para eviar condiciones de carerra
 */

int myAmount = 0;
mutex m;

void addMoney(){
    m.lock();
    //Seccion Critica
    ++myAmount;
    m.unlock();
}

int main(){
    thread t1(addMoney);
    thread t2(addMoney);
    
    if(t1.joinable()){
         t1.join();

    }
    if(t2.joinable()){
         t2.join();
    }
    
    cout<<myAmount<<endl;

   return 0;
}
#endif

#ifdef LESSON_5
/*
 *TEMA: sdt::mutex::try_lock() Mutex Intenta bloquear Hilo en c++ .
 */

/*
 * 0. try_lock() Intenta bloquear el Mutex, Regresa inmendiatamnete, Cuando bloquea satisfactoria mente regresa true(verdad) de otra manera false(falso)
 * 1.Si try_lock() no es capaz de bloquear el Mutex(), entonces no lo es hace es por eso que es una llamada no-bloqueante(non-blocking)
 * 2.SI try_lock() es llamada de nuevo por el mismo thread(hilo) que tiene el mutex, el comportamiento sera indefinido.
 * Es una situacion dead_lock(bloqueo de muerte) con un comportamiento indefinido.(Si quieres bloquear el mutex el el mimso hilo mas de una vez usa un recursive_mutex() mutex recursivo.
 */


int counter = 0;
mutex mtx;

void increseTheCounterFor100000Time(){
    for(int i=0;i<100000;++i){
        if(mtx.try_lock()){
            ++counter;
            mtx.unlock();
        }
    }
}

int main(){
    thread t1(increseTheCounterFor100000Time);
    thread t2(increseTheCounterFor100000Time);

    t1.join();
    t2.join();

    cout<<"Counter could increce up to: "<<counter<<endl;

    return 0;
}


#endif


#ifdef LESSON_6
/*
 *std::try_lock() in C++11 Threading
 *1.std::try_lock() intenta bloquear todos los objetos que se puedan bloquear uno a uno en el orden dado.
 *
 *SYNTAX std_trylock(m1,m2,m3,m4,....);
 *
 *2.En exito , la funcion regresa -1 de otra manera regresa el indice del mutex que no se pudo bloquear.
 *3.Si falla, al bloquear alguno de los mutex, desbloqueara todos los mutex bloqueados con anterioridad.
 *4.Si try_lock resulta en una excepcion , desbloquea los elementos bloqueados antes de volver a relanzar.
 *
 */



int X= 0, Y = 0;
std::mutex m1, m2;

void doSomeWorkForSeconds(int seconds){std::this_thread::sleep_for(std::chrono::seconds(seconds));}

void incrementXY( int &XorY, std::mutex &m, const char* desc){
    for(int i = 0; i<5; ++i){
        m.lock();
        ++XorY;
        cout<<dec<<XorY<<'\n';
        m.unlock();
        doSomeWorkForSeconds(1);
    }
}

void consumeXY(){
    int useCount = 5;
    int XplusY = 0;
    while(1){
        int lockResult = std::try_lock(m1,m2);
        if(lockResult == -1){
            if(X!=0 && Y!=0){
                --useCount;
                XplusY+=X+Y;
                X=0;
                Y=0;
                cout<<"XpluY"<<XplusY<<'\n';
               }
            m1.unlock();
            m2.unlock();
            if(useCount == 0 )break;
        }
    }
}

int main(){


    thread t1(incrementXY, std::ref(X), std::ref(m1), "X");
    thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y");
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();


    return 0;
}


#endif


#ifdef LESSON_7
/*
 *TEMA: Mutex temporizado En c++ thrading(std::timed_mutex)
 *Hemos aprendido Mutex, Condiciones de carrera, Secciones criticas en ejemplos pasados
 */

/*
 * Notas:
 * 0. std::timed_mutex es bloqueado hasta que el tiempo especificado haya terminado o el bloqueo sea adquieirdo regresa true si tiene exito
 * 1.Miembros funcion:
 *  a.lock
 *  b.try_lock
 *  c.try_lock_for  ....\estas dos funciones hacen cosas diferentes para el mutex
 *  d.try_lock_until..../
 *  e.unlock
 */


/*
 *Ejemplo: try_lock_until()
 *Espera hasta que
 *En respuesta de bloqueo satisfactoria regresa True, de otra manera False
 */

int myAmount = 0;
std::timed_mutex m;

void increment(int i){
    auto now=std::chrono::steady_clock::now();
    if(m.try_lock_until(now+std::chrono::seconds(2))){
   // if(m.try_lock_for(std::crono::seconds(1))){
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout<<"thread"<<i<<"entered"<<endl;
        m.unlock();
    }else{
        cout<<"Thread"<<i<<"Could not enter"<<endl;
    }
}


int main(){
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();


    cout<<myAmount<<endl;
    return 0;

}


#endif

#ifdef LESSON_8

/*
 *TEMA: Mutex Recursivo en c++(std::recursive_mutex)
 */


/*
 * Notas:
 * 0.es lo mismo que un mutex, pero , el mismo hilo puedo bloquear un mutex multiples veces usando un mutex recursivo
 * 1. si el hilo t1 esta ejecutandose en recursion , t1 puede llamar lock/try _lock cualquier numero de veces y no habra problemas.
 * 2.Si t1 ha adquirido 10 veces lock/try_lock en el mutex, entonces el hilo t1 tendra que desbloquearlo 10 veces de otra manera no habra otro hilo que pueda desbloquearlo.
 * El recursive_mutex lleva cuenta de cuantas veces ha sido bloqueado por lo cual tendras que desbloquearlo ese numero de veces
 * 3. cuantas veces podemos bloquar un mutex recursivo no esta definido pero cuando ese numero es alcansado utliziando lock nos regresara std::system_error y si ustamos usando try_lock nos regresara falso
 */


/*
 * Ultima linea:
 * 0- Es siilar a mutex pero tiene la facilidad extra de que puede ser bloqueado multiples veces en el mismo hilo
 * 1- Si podemos evitar mutex recursivos derbermos hacer lo ya que agrega complejidad al sistema
 * 2. puede ser usado en ciclos .
 *
 */

std::recursive_mutex m1;
int buffer =  0;

void recursion(char c, int loopFor){

    if(loopFor<0){
        return;
    }
    m1.lock();
    cout<<"Locked by thread ID: "<< c << " " <<buffer++<<endl;
    recursion(c,--loopFor);
    m1.unlock();
    cout<<"Unlocked by thread ID: "<<c<<endl;
}

int main(){

    thread t1(recursion, '0', 10);
    thread t2(recursion, '1', 10);

    t1.join();
    t2.join();
 
    return 0;

}

/*
 *Ejemplo 2 usando Ciclos
 */
/*
int main(){
   
    for(int i=0; i<5; i++){
        m1.lock();
        std::cout "locked" <<i <<endl;
    }

    
    for(int i=0; i<5; i++){
        m1.unlock();
        std::cout "unlocked" <<i<<endl;
    }

    return 0;
}
*/

#endif

#ifdef LESSON_9
/*
 *TEMA: lock_guard in C++ (std::lock_guard<mutex> lock(m1))
 */

/*
 * Notas:
 * 0. Es un wrapper muy ligero para adquirir el mutex en alcances de la funcion donde es llamado
 * 1. Este adquiere el bloqueo del mutex en el momento que creas el objeto lock_guard
 * 2. Automaticamete remueve el bloqueo cuando queda fuera de alcance
 * 3. No puedes desblquear explicitamnete el lock_guard
 * 4. No puedes copiar el lock_guard
 */

std::mutex m1;
int buffer = 0;

void task(const char * threadNumber, int loopFor){
    std::lock_guard<mutex> lock(m1);
    for(int i=0; i<loopFor; ++i){
        buffer++;
        cout<< threadNumber<<buffer<<endl;
    }
}
int main(){
    thread t1(task,"T0",10);
    thread t2(task,"T1",10);

    t1.join();
    t2.join();

    return 0;
}
#endif

#ifdef LESSON_10 

/*
 * TEMA: unique_lock en C++ (std::unique_lock<mutex> lock(m1))
 */


/*
 * Notas:
 * 1. La clase unique_lock es un wrapper de aquisicion unica de un mutex
 * 2. te permite:
 *      a) Poder tener diferentes estrategias de bloqueo
 *      b) Intentos limitaos por tiempo de bloqueo(try_lock_for. try_lock_until=
 *      c) bloqueo recursivo
 *      d) tranfercia de dueño del bloqueo(moverlo no copiarlo)
 *      e) Variables de condicion
 */


/*
 * Estrategias de bloqueo
 * TYPE              EFFECTS
 * 1. defer_lock     No adquiere la propiedad del mutex
 * 2. try_to_locl    trata de adquirir la propiedad del mutex sin bloquear
 * 3. adopt_lock     asume que el hilo llamado tiene la propiedad del mutex
 */


std::mutex m1 ;
int buffer = 0;

/*
void task(const char * threadNumber, int loopFor){
    std::unique_lock<mutex> lock(m1);//destructor will unlock the mutex
    for(int i=0; i<loopFor; ++i){
        buffer++;
        cout<< threadNumber<<buffer<<endl;
    }
}
int main(){
    thread t1(task,"T0",10);
    thread t2(task,"T1",10);

    t1.join();
    t2.join();

    return 0;
}
*/

//Ejemplo 2
void task(const char * threadNumber, int loopFor){
    std::unique_lock<mutex> lock(m1,std::defer_lock);//No se bloqueara el mutex, porque se uso defer_lock
    lock.lock();//Entonces tendremos que bloquearlo explicitamente cuando queramos q se bloquee el mutex
    for(int i=0; i<loopFor; ++i){
        buffer++;
        cout<< threadNumber<<buffer<<endl;
    }
    //no es necesario desbloquear el mutex , serea desbloqueado por el destructor de unique lock

}
int main(){
    thread t1(task,"T0",10);
    thread t2(task,"T1",10);

    t1.join();
    t2.join();

    return 0;
}
#endif


#ifdef LESSON_11

/*
 * TEMA Condition Variable(Variables de Condicion) en c++ Threading
 */

/*
 * Punto Importante: CV son usados para dos propositos
 * A. Notificar otros threads
 * B. Esperar por algunas condiciones
 */

/*
 * 1. CV permite a threads(hilos) en ejecucion esperar alguna condicion cuando alguna condicion es alcanzada el thread en espera es notificado usando
 *         a. notify_one();
 *         b. notify_all();
 *
 * 2. Necestias un mitex para usar CV
 * 3. Si algun thread quiere esperar para una condicion tendra que hacer una de estas cosas:
 *         a. Adquirir el bloqueo del mutex usando std::unique_lock<std::mutex> lock(m);
 *         b. Executar wait, wait_for, or wait_until, estas operaciones de espera automaticamente liberan el mutex y suspende automaticamente la ejecucion del hilo
 *         c. Cuando la CV es notificada , el hilo es despertado , y el mutex automaticamente readquirido
 *         Entonces el thread tendra que checar la condicion y regresar a la espera si el despertar era inesperado
 */

/*
 * Notas:
 * 1. CV son usados para sincronizar uno mas threads
 * 2. El mejor caso de uso de las CV es el problmea Producer/Consumer(productor/consumidor)
 */

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money){
    std::lock_guard<mutex> lg(m);
    balance+=money;
    cout<<" Amount of money Current Balance:"<<balance<<endl;
    cv.notify_one();
}

void withdrowMoney(int money){
    std::unique_lock<mutex> ul(m);
    cv.wait(ul,[]{return (balance!=0)? true : false;});
    if(balance >= money){
        balance-=money;
        cout<<"Amount deducted: "<<money <<endl;
    }else{
        cout<<"Amount cant be deducted, current balance is less that requested"<<endl;
    }
    cout<<"Current Balance is"<<balance<<endl;
}

int main(){
    std::thread t1(withdrowMoney,500);
    std::thread t2(addMoney,500);
    t1.join();
    t2.join();

    return 0;
}
#endif

#ifdef LESSON_12

/*
 *EJEMPLO DE SITUACION DE DEAD LOCK (BLOQUE DE MUERTE)
 */ 
std::mutex m1;
std::mutex m2;

void thread1(){
    m1.lock();
    std::this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    cout<<"Seccion critica de thread1"<<endl;
    m1.unlock();
    m2.unlock();
}

void thread2(){
    m2.lock();
    std::this_thread::sleep_for(chrono::seconds(1));
    m1.lock();

    cout<<"Seccion critica de thread2"<<endl;
    m1.unlock();
    m2.unlock();
}
int main(){
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
#endif


#ifdef LESSON_13

/*
 * TEMA: Thread o procesos Syncronizacion
 */

/*
 * Nota: solo usaremos threads para este ejemplo
 */

/*
 * Puntos:
 * 1. Thread o un processo se sincronizan para acceder a la seccion critica
 * 2. La seccion critica es una o una conleccion de instrucciones de programa a la cual solo un thread o proceso
 * puede acceder en un tiempo determindado
 */
mutex m1;
int balance = 0;


void addMoney(int var){
    m1.lock();
    balance+=var;
    cout<<"El balance es :"<<balance<<endl;
    m1.unlock();
}

int main(){

    thread t1(addMoney,100);
    thread t2(addMoney,200);

    t1.join();
    t2.join();

    return 0;
}

#endif 

#ifdef LESSON_14

/*
 * Tema: std::lock() en C++
 */

/*
 * Se usa para bloquear multiples mutex en el mimso momento
 */

/*
 * Importante:
 * Syntaxis-> std::lock(m1,m2,m3,m4);
 * 1.Todos los argumentos son bloqueados a traves de una sequencia de llamadas a lock(), o unlok() o try_lock()
 * 2.El orden de bloqueo no esta definido(tratara de bloquear el mutex dado en cualquier orden asegurando que no
 * exista el deadlock()
 * 3.Es una llamada de bloqueo
 */

/*
 * Ejemplo:0 -->no deadlock
 *  thread 1            thread 2
 *  std::lock(m1,m2)    std::lock(m1,m2)
 */

/*
 * Ejemplo:1 -->no deadlock
 *  thread 1            thread 2
 *  std::lock(m1,m2)    std::lock(m2,m1)
 */

/*
 * Ejemplo:2 -->no deadlock
 *  thread 1                  thread 2
 *  std::lock(m1,m2,m3,m4)    std::lock(m3,m4)
 *                            std::lock(m1,m2)
 */
 
/*
 * Ejemplo:3 -->Si lo de abajo puede crear un deadlock
 *  thread 1                  thread 2
 *  std::lock(m1,m2)    std::lock(m3,m4)
 *  std::lock(m3,m4)    std::lock(m1,m2)
 */

std::mutex m1,m2;

void task_a(){
    while(1){
        std::lock(m1,m2);
        //m1.lock();
        //m2.lock();
        std::cout<<"task a"<<std::endl;
        m1.unlock();
        m2.unlock();
    }
}

void task_b(){
    while(1){
        std::lock(m1,m2);
        //m1.lock();
        //m2.lock();
        std::cout<<"task a"<<std::endl;
        m1.unlock();
        m2.unlock();
    }
}

int main(){
    std::thread t1(task_a);
    std::thread t2(task_b);

    t1.join();
    t2.join();

    return 0;

}
#endif
 
#ifdef LESSON_15

/*
 * TEMA std::future y std::promise en threading
 */

/*
 * Notas:
 * 1. std::promise
 *      a.Usado para establecer valores y excepciones
 *
 * 2. std::future
 *      a. Usado para tener los valores de promise
 *      b. pregunta a promise si el valor esta disponivle
 *      c. espera a promise
 */

typedef unsigned long long ull ;

void findOdd(std::promise<ull>&& OddSumPromise,ull start, ull end){
    ull OddSum = 0;
    for(ull i = start; i <= end; i++){
        if((i & 1) == 1){
            OddSum+=i;
        }
    }
    OddSumPromise.set_value(OddSum);
}

int main(){

    ull start = 0, end = 1900000000;

    std::promise<ull> OddSum;
    std::future<ull> OddFuture = OddSum.get_future();
    
    cout<<"thread Created!!"<<endl;
    std::thread t1(findOdd,std::move(OddSum),start, end);

    cout<<"Wait for Result"<<endl;

    cout<<"OddSum :"<<OddFuture.get()<<endl;
    
    cout<<"Completed"<<endl;
    
    t1.join();
    return 0;

 
}


#endif

#ifdef LESSON_16

/*
 * TEMA: syd::async
 */

/*
 * Notas:
 * 1. Corre una funcion asyncronamente, (potencialmente en un nuevo thread) y regresa a std::future que contiene el resultado
 * 2. Hay tres politicas de lanzamiento para crear una tarea:
 *      a. std::launch::async
 *      b. std::launch::deffered
 *      c. std::launch::async|std::launch::deffered
 *
 *  Como funciona.
 *  1. Crea un thread automaticamente(o selecciona uno de thrad pool interno) y un obejto promise para nosotros.
 *  2. Pasa std::promise a la funcion thread y regresa el objecto std::future asociado
 *  3. Cuando nuestro funcion argumento exista en ese momento se pasa el valor al objeto promise,
 *  entonces evenutalmente el valor de retorno estara disponible en el objeto std::future
 *
 *
 * Otras Notas:
 * 1.Podemos mandar functors y funciones lambda como callbacks a std::async funcionara igual.
 */

typedef unsigned long long ull ;

ull findOdd(ull start, ull end){
    ull OddSum = 0;
    cout<<"Thread ID"<<std::this_thread::get_id()<<endl;
    for(ull i = start; i <= end; i++){
        if((i & 1) == 1){
            OddSum+=i;
        }
    }
    return OddSum;
}

int main(){

    ull start = 0, end = 1900000000;
  
    cout<<"Thread ID"<<std::this_thread::get_id()<<endl;

    cout<<"thread Created if policy is std::launch::async!!"<<endl;
  
    //std::future<ull> OddSum = std::async(std::launch::deferred,findOdd,start,end);
    std::future<ull> OddSum = std::async(std::launch::async,findOdd,start,end);
 
    cout<<"Wait for Result"<<endl;

    cout<<"OddSum :"<<OddSum.get()<<endl;
    
    cout<<"Completed"<<endl;
    
    return 0;

 
}

#endif
