#include "factory_impl.hpp"

class Animal {};

class Dog: public Animal {};

class Cat: public Animal {};

class Rabbit: public Animal {};

#define ANIMAL(Func) \
	Func(Dog) \
	Func(Cat) \
	Func(Rabbit)

FACTORY_IMPL(AnimalFactory, Animal, ANIMAL);

//! define type enumeration
//enum AnimalType {
//#define DO_ENUM(e) AT_##e,
//	ANIMAL(DO_ENUM)
//#undef DO_ENUM
//};

//! define string
//char* AnimalDescription [] = {
//#define DO_DESCRIPTION(e) #e,
//	ANIMAL(DO_DESCRIPTION)
//#undef DO_DESCRIPTION
//};

int main(int argc, char* argv)
{
	AnimalFactory af;
	Animal* a= af.create("Dog");
	if (a) delete a;
	return 0;
}