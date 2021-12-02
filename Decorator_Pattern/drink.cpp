//Spencer Moore
//smoor114

#include "drink.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

int main()
{
  std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
  char choice;
  std::cin >> choice;
  

  DrinkType type;
  double price;

  if (choice == 'l') //Select Large
  {
    type = DrinkType::large;
    price = 3.00;
  }
  else if (choice == 'm') //Select Medium
  { 
    type = DrinkType::medium; 
    price = 2.00; 
  }
  else //Default to Small
  { 
    type = DrinkType::small; 
    price = 1.00; 
  }
  choice = ' ';

  //Create drink object
  Drink drink(type, price);
 

  while(choice != 'n')
  {
    std::cout << "Would you like to add [s]prinkles, milk [f]oam, or [n]ot? ";

    if(choice == 's')
    {
      SprinkledDrink sd(&drink);
      drink = sd;
    }

    if(choice == 'f')
    {
      MilkFoamDrink mfd(&drink);
      drink = mfd;
    }
    
    std::cin >> choice;
  }
  choice = ' ';

  std::cout << "Can I get your name? ";
  string customerName;
  std::cin >> customerName;
  
  std::cout << std::fixed;
  std::cout << customerName <<  ", your " << drink.getSize() << " coffee with " << drink.getToppings() <<
       " is ready. It will be $" << std::setprecision(2) << drink.getPrice() << ", please." << std::endl;

  return 0;
}
