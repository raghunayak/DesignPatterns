/*
 * (c) 2015 Raghavendra Nayak, All Rights Reserved.
 * www.openguru.com/
 */

#include <iostream>
#include <string>

// Pizza is the abstract base for all concrete Pizza implementations
class Pizza {
    std::string name;
    float price;
public:
    Pizza(const std::string& name, const float price)
        : name(name), price(price) {
    }
    virtual ~Pizza() {
    }

    virtual float getPrice() {
        return price;
    }
    virtual std::string getName() {
        return name;
    }
    virtual void bake() = 0;
};

// CheesePizza is a type of Pizza
class CheesePizza : public Pizza {
public:
    CheesePizza()
        : Pizza("Cheese", 100) {
    }
    ~CheesePizza() {
    }

    void bake() {
        std::cout << "Baking " << getName() << " Pizza." << std::endl;
    }
};

// MexicanPizza is a type of Pizza
class MexicanPizza : public Pizza {
public:
    MexicanPizza()
        : Pizza("Mexican", 200) {
    }
    ~MexicanPizza() {
    }

    void bake() {
        std::cout << "Baking " << getName() << " Pizza." << std::endl;
    }
};

// Below class is a decorator or wrapper for Pizza
class PizzaToppings : public Pizza {
    // Here we store the reference
    Pizza& pizza;
public:
    // Constructor
    PizzaToppings(const std::string& toppingName, const float price, Pizza& pizza)
        : Pizza(toppingName, price), pizza(pizza) {
    }
    virtual ~PizzaToppings() {
    }

    // Call our wrapper object's functions
    virtual float getPrice() {
        return pizza.getPrice();
    }
    virtual std::string getName() {
        return pizza.getName();
    }
    virtual void bake() {
        pizza.bake();
    }
};

class ExtraCheeseTopping : public PizzaToppings {
    void addExtraCheeseToPizza() {
        std::cout << "Added extra cheese to the pizza: ["
            << PizzaToppings::getName() << "]." << std::endl;
    }
public:
    ExtraCheeseTopping(Pizza& pizza)
        : PizzaToppings("ExtraCheeseTopping", 10, pizza) {
    }
    ~ExtraCheeseTopping() {
    }

    virtual float getPrice() {
        return Pizza::getPrice()+ PizzaToppings::getPrice();
    }
    virtual std::string getName() {
        return Pizza::getName();
    }

    // Call our wrapper object's function
    virtual void bake() {
        addExtraCheeseToPizza();
        PizzaToppings::bake();
    }
};

class BroccoliTopping : public PizzaToppings {
    void addBroccoliToPizza() {
        std::cout << "Added Broccoli to the pizza: ["
            << PizzaToppings::getName() << "]." << std::endl;
    }
public:
    BroccoliTopping(Pizza& pizza)
        : PizzaToppings("BroccoliTopping", 15, pizza) {
    }
    ~BroccoliTopping() {
    }

    virtual float getPrice() {
        return Pizza::getPrice() + PizzaToppings::getPrice();
    }
    virtual std::string getName() {
        return Pizza::getName();
    }

    // Call our wrapper object's function
    virtual void bake() {
        addBroccoliToPizza();
        PizzaToppings::bake();
    }
};

int main(int argc, char **argv)
{
    // Create MexicanPizza
    Pizza &pizza = MexicanPizza();

    // Add ExtraCheeseTopping
    ExtraCheeseTopping mexicanPizzaWithExtraCheeseTopping(pizza);

    // Now bake
    mexicanPizzaWithExtraCheeseTopping.bake();

    std::cout << "Total price: " 
        << mexicanPizzaWithExtraCheeseTopping.getPrice() << std::endl;

    return 0;
}