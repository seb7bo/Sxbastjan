#include <iostream>
#include <string>

using namespace std;

/**
 * @brief The Mediator intreface declares a method used by components to notify the
 * mediator about various events. The mediator may react to these events and pass the 
 * execution to other components.
 */

/**
 * @brief ESP - La interfaz del medidado declara un metodo usado por otros componentes para
 * notificar al medidador de varios eventos. El mediador reacionara a estos eventos y pasara
 * la ejecucion a otros componentes.
 */

class BaseComponent;
class Mediator{
    public:
    virtual void Notify(BaseComponent *sender, string event ) const = 0;
};

/**
 * @brief The Base Component provides the basic funcionality of storing a mediator´s
 * instance inside component object.
 */

/**
 * @brief ESP El componente base provee la funcionalidad basica de guardar una instancia
 * del mediador dentro del obejeto componente.
 */

class BaseComponent {
 protected:
  Mediator *mediator_;

 public:
  BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {
  }
  void set_mediator(Mediator *mediator) {
    this->mediator_ = mediator;
  }
};
/**
 * @brief Concrete components implement various funcionality. They don´t depend on 
 * other components. They also don´t depend on any concrete mediator classes.
 */

/**
 * @brief Componentes concretos implementan varias funcionalidades.Ellos no dependedn en
 * otros componentes. Ellos tampoco dependen de ninguna clase concreta mediadora.
 */

class Component1 : public BaseComponent{
    public:
    void DoA(){
        cout<<"Componente 1 does A.\n";
        this->mediator_->Notify(this,"A");
    }
    void DoB(){
        cout<<"Componente 1 does B.\n";
        this->mediator_->Notify(this,"B");
    }
};


class Component2 : public BaseComponent{
    public:
    void DoC(){
        cout<<"Componente 2 does C.\n";
        this->mediator_->Notify(this,"C");
    }
    void DoD(){
        cout<<"Componente 2 does D.\n";
        this->mediator_->Notify(this,"D");
    }
};

/**
 * @brief Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */

/**
 * @brief Mediadores concretos implementan un comportamibeto coperativo cordinando varios
 * componentes.
 */

class ConcreteMediator : public Mediator {
 private:
  Component1 *component1_;
  Component2 *component2_;

 public:
    ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }
    void Notify(BaseComponent *sender, string event) const override {
        if (event == "A") {
            cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D") {
            cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

/**
 * @brief The Client Code 
 * 
 */

void ClientCode() {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A.\n";
    c1->DoA();
    cout << "\n";
    cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main(){
    ClientCode();
    return 0;
}