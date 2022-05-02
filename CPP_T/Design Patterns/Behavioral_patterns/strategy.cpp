#include <vector>
#include <string>
#include <iostream>
#include <algoritm>
using namespace std;

class Strategy{
    public:
    virtual ~Strategy(){}
    virtual string DoAlgorithm(const vector<string> &data) const = 0;
};

class Context{
    private :
    Strategy *strategy_;

    public:
    Context(Strategy *strategy = nullptr): strategy_(strategy){}
    ~Context(){
        delete this->strategy_;
    }

    void set_strategy(Strategy *strategy){
        delete this->strategy_;
        this->strategy_=strategy;
    }

    void DoSomeBusinessLogic() const{
        cout<<"Context: Sorting dtata using the strategy(not sure how it will do it\n";
        string result = this->strategy_->DoAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
        cout<<result<<endl;
    }
};
class ConcreteStrategyA : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string> &data) const override
    {
        std::string result;
        std::for_each(std::begin(data), std::end(data), [&result](const std::string &letter) {
            result += letter;
        });
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string DoAlgorithm(const std::vector<std::string> &data) const override
    {
        std::string result;
        std::for_each(std::begin(data), std::end(data), [&result](const std::string &letter) {
            result += letter;
        });
        std::sort(std::begin(result), std::end(result));
        for (int i = 0; i < result.size() / 2; i++)
        {
            std::swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};
void ClientCode(){
        Context *context = new Context(new ConcreteStrategyA);
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context->DoSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context->set_strategy(new ConcreteStrategyB);
    context->DoSomeBusinessLogic();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}