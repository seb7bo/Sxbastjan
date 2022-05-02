#include <iostream>
#include <string>
#include <vector>
/*
*It makes sense to use the Builder pattern only when your product are quite
*complex and require extensive configuration.
*
*Unlike in other creational patterns, different concrete builders can produce
*unrelated products, In other words, results of various builders may not
*always follow the same interface.
*/

class Product1{
	public:
	std::vector<std::string> parts_;
	void ListParts()const{
		std::cout <<"Product parts:";
		for(size_t i=0; parts_.size();i++){
			if(parts_[i]==parts_.back()){
				std::cout<<parts_[i];
			}else{
				std::cout<<parts_[i]<<", ";
			}
		}
		std::cout<<"\n\n";
	}
};

/*
*The Builder Interface specifies methods for creating the different parts of 
*the Product Objects.
*/

class Builder{
	public:
	virtual ~Builder(){}
	virtual void ProducePartA() const = 0;
	virtual void ProducePartB() const = 0;
	virtual void ProducePartC() const = 0;
};

/*
*The Concrete Builder classes follow the Builder interface and provide 
*Specific Implementations of the building steps. Your program may have several 
*variations of Builders, implemented differently.
*/
class ConcreteBuilder1: public Builder{
	private:
	Product1* product;
	
	/**
	*A fresh builder instance should contain a black product objetc, which is 
	*used in further assambly.
	*/
	public:
	ConcreteBuilder1(){
		this->Reset();
	}
	~ConcreteBuilder1(){
		delete product;
	}
	void Reset(){
		this->product = new Product1();
	}
	/*
	*All productions steps work with the same product instance.
	*/
	
	void ProducePartA() const override{
		this->product->parts_.push_back("PartA1");
	}
	void ProducePartB() const override{
		this->product->parts_.push_back("PartA2");
	}
	void ProducePartC() const override{
		this->product->parts_.push_back("PartA3");
	}
	
	/*
	*Concrete Builders are supposed to provide their own methos for 
	*retreiving results. That´s because types of builders may create
	*entirely different products that don´t follow the same interface.
	*Therefore, such methods cannot be declared in the base Builder interface.
	*
	*Usually, after returning the end result to the client, a builder isntace
	*is expected tp be readu to start producing another product. That´s why 
	*it is usal practice to call the reset method at the end of the
	*get product method body.However, this behaviour is not madaotry , and 
	*you can make your builders wit for an explicit reset call from
	*client code before disposing of the previous result.
	*/
	/*
	*Please be careful here with the memory ownership. once you call 
	*GetProduct the user of this function is responsable to release this
	*memory. Here could be a better option to use smart pointers to avoid
	*memory leaks.
	*/
	
	Product1* GetProduct(){
		Product1* result =this->product;
		this->Reset();
		return result;
	}
};
/*
*The Director is only responsible for executing the building steps ina a
*particular sequence. It is helpful when producing products accoridng to a 
*specific order or configuration. Strictly speaking, the Director class is 
*optional, since the client can control builders directly.
*/

class Director{
	/**
	*@var Builder
	*/
	private :
	Builder* builder;
	/*
	*The director works woth any builder instance that the client code passes
	*to it. This way, the client code may alter the final type of the newly 
	*assamebled product.
	*/
	
	public:
	
	void set_builder(Builder* builder){
		this->builder=builder;
	}
	/**
	*The Director can construct several product variations using the same
	*buiding steps.
	*/
	
	void BuildMinimalViableProduct(){
		this->builder->ProducePartA();
	}
	
	void BuildFullFeaturedProduct(){
		this->builder->ProducePartA();
		this->builder->ProducePartB();
		this->builder->ProducePartC();
	}
};

/*
*The client code creates a builder object, passes it to the director and then 
*initiates the constructio process. The end result is retrived form the
*builder object.
*/
/*
*I ised raw pointers for simplicity however you may prefer to use 
*smart pointers here.
*/
void ClientCode(Director& director){
	ConcreteBuilder1 *builder = new ConcreteBuilder1();
	director.set_builder(builder);
	std::cout<<"Standard basic product:\n";
	director.BuildMinimalViableProduct();
	
	Product1* p=  builder->GetProduct();
	p->ListParts();
	delete p;
	
	std::cout <<"Stander full feautured product:\n";
	director.BuildFullFeaturedProduct();
	p= builder->GetProduct();
	p->ListParts();
	delete p;
	
	//Remeber, the Builder pattern can be used without a Director class.
	std::cout<<"Custom product:\n";
	builder->ProducePartA();
	builder->ProducePartC();
	p=builder->GetProduct();
	p->ListParts();
	delete p;
	
	delete builder;

}

int main(){
	Director* director = new Director();
	ClientCode(*director);
	delete director;
	return 0;
}