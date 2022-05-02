#include <iostream>
#include <string>
/*
*The product interface declares the operations that all concrete products must 
*implement.
*/

/*
*La interfaz del producto declara las operaciones que todos  los productos completos tienen que
*implementar.
*/
class Product{
	public:
	virtual ~Product(){}
	virtual std::string Operation() const = 0;
};

/*
*Concrete Products provide various implementations of the Product interface.
*/
/*
*Productos Concretos proveen varias implementaciones de la interfaz del producto.
*/

class ConcreteProduct1 : public Product{
	public:
	std::string Operation() const override{
		return "{Result of the ConcreteProduct1}";
	}
};
class ConcreteProduct2 : public Product{
	public:
	std::string Operation() const override{
		return "{Result of the ConcreteProduct2}";
	}
};
/*
*The Creator class declares the factory method that is supposed to return an 
*object of a Product class. The Creator´s subclasses ussually provide the 
*implementation of this method.
*/
/*
*La clase Creador declara el metodo de fabrica(factory) el cual supone  que regresara
*un objeto de una clase de Producto. Las subclases del creador usualmente proveen la
*implementacion de este metodo.
*/
class Creator{
	/*
	*Note that the Creator may also provide some default implementation of the factory method.
	*/
	/*
	*Nota el Creador debe proceer alguna implementacion por defecto del metodo fabrica(factory).
	*/
	public:
	virtual ~Creator(){};
	virtual Product* FactoryMethod() const = 0;
	/*
	*Also note that, despite its name, the Creator´s primary resposability is 
	*not creating products. Usually , it contains some core business logic that 
	*relies on Product objects, returned by the factory method. Subclasses can 
	*indirectly  change that business logic by overriding the factory method and
	*returning a different type of product from it.
	*/
	/*
	*Nota: a pesar de su nombre, la responsabilidad primaria del creador no es
	*crear los productos. Usualmente, contiene alguna logica base que recae en los
	*objetos producto, regresados por el metodo de fabrica(factory). Las subclasses 
	*pueden indictamente cambiar esta logica base sobre escribiendo el metodo de fabrica y
	*regresando un producto diferente.
	*/
	
	std::string SomeOperation() const{
		//Call the factory method to create a Product object.
		//Llama el metodo de fabrica para crear un producto diferente.
		Product* product = this->FactoryMethod();
		//Now use the product
		//Usa el producto.
		std::string result = "Creator: The same creator´s code has jut worked with "+ product->Operation();
		delete product;
		return result;
	}
};

/*
*Concrete creators override the factory method in order to change the
*resulting product´s type.
*/
/*
*Los creadores concretos sobreescriben el medo de la fabrica con el objectivo de 
*cambiar el tipo de producto.
*/
class ConcreteCreator1 : public Creator{
	/*
	*Note that the signature of the method stills uses the abstract product type,
	*even though the concrete product is actually returned from the method. This
	*way the Creator can stay independent of the concrete product classes.
	*/
	/*
	*Nota la firma del metodo aun usa el tipo de producto abstracto,
	*a pesar de que el producto concreto es regresado por el metodo.De esta manera
	*el creador es independiente de la calse de producto concreto.
	*/
	public:
	Product * FactoryMethod() const override{
		return new ConcreteProduct1();
	}
};
class ConcreteCreator2 : public Creator{
	public:
	Product * FactoryMethod() const override{
		return new ConcreteProduct2();
	}
};

/*
*The client code works with an instance of a concrete creator, albeit through 
*its base interface, As long as the client keeps working with the creator via
*the base interface, you can pass it any creator´s subclass.
*/
/*
*El codifo del cliente trabaja con una instacia del creador concreto, aunque a traves de  
*la intefaz de la base, mientras el cliente siga trabajando con creado a traves 
*de la interfaz de la base, tu puedes pasar cualquier subclase del creador.
*/
void ClientCode(const Creator& creator){
	//...
	std::cout<<"Client:I'm not aware of the creator's class, but it still wokrs.\n"
			<<creator.SomeOperation()<<std::endl;
	//...
}
/*
*The Application picks a creator's type depending on the configuration or
*environment.
*/
/*
*La aplicacion escoje un tipo de creador dependiendo de la configuracion
*del ambiente.
*/
int main(){
	std::cout <<"App: Launched with the ConcreteCreator1.\n";
	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	std::cout<<std::endl;
	std::cout << "App: Launched with the ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);

	delete creator;
	delete creator2;
	return 0;
}