//Spencer Moore
//smoor114

// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/15/2016

#include <string>
#include <iostream>
#include <vector>
#include <list>
char askToppings();

using std::cout; using std::cin;
using std::string;
enum class DrinkType {small, medium, large};

class Drink{
public:
   Drink(DrinkType type=DrinkType::small, double price=0): type_(type), price_(price){}
   Drink& operator=(const Drink& rhs);
   virtual double getPrice() const { return price_; };
   virtual std::string getToppings() const { return toppings_; };
   virtual std::string getSize() const;
   virtual DrinkType getSize_num() const {return type_;};
   virtual void setType(DrinkType type) {type_ = type; };

private: 
   double price_;
   DrinkType type_;
   string toppings_ = "";
};

//--------------Sprinkled Drink-------------------
class SprinkledDrink: public Drink 
{
public:
  SprinkledDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.50 + wrapped_->getPrice(); } 
  string getToppings() const override { return "Sprinkles " + wrapped_->getToppings(); }

private:
  const Drink *wrapped_;
};

//---------------Milk Foam Drink------------------
class MilkFoamDrink: public Drink {
public:
  MilkFoamDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.40 + wrapped_->getPrice(); } 
  string getToppings() const override { return "Foam " + wrapped_->getToppings(); }

private:
  const Drink *wrapped_;
};


//~~~~~~~~~~~~~~~~~~~~~getToppings~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string Drink::getSize() const
{
  string typeName;

  if (type_ == DrinkType::small)
  	typeName = "small";
  else if (type_ == DrinkType::medium)
  	typeName = "medium";
  else
  	typeName = "large";

  return 
  	typeName;
}

Drink& Drink::operator= (const Drink& rhs) 
{
	cout << std::endl << "LHS SIZE:" << getSize() << std::endl;
	cout << "RHS SIZE:" << rhs.getSize() << std::endl;

	price_ = rhs.getPrice();
	type_ = rhs.getSize_num();
	toppings_ = rhs.getToppings();

	cout << "NEW SIZE:" << getSize() << std::endl;


	return *this;
}