
#include <string>
#include <iostream>
#include <tuple>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <any>

struct None
{};

template<class A, class B, class C>
struct Row
{
    using Type = std::string;
    using State = A;
    using Event = B;
    using Guard = C;
};

template<class A, class C>
struct Row<A, None, C>
{
    using Type = int;
    using State = A;
    using Event = None;
    using Guard = C;
};

template<class A>
struct Row<A, None, None>
{
    using Type = float;
    using State = A;
    using Event = None;
    using Guard = None;
};

template<class A, class B>
struct Row<A, B, None>
{
    using Type = size_t;
    using State = A;
    using Event = B;
    using Guard = None;
};


template<typename ...Rows>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Rows>()...));

template<class ...Rows>
struct TransitionTable
{
	template<class State, class Event>
	struct GetPossibleTransitions
	{
		using possibleTransitions = tuple_cat_t<
			typename std::conditional<
				std::is_same_v<typename Rows::State, State> && std::is_same_v<typename Rows::Event, Event>,
				std::tuple<Rows>,
				std::tuple<>
			>::type...
		>;
	};

};

template<class ...Rows>
void PrintRows(std::tuple<Rows...> transitionTable)
{
    ((
        std::cout << typeid(typename Rows::State).name() << ", " <<
                     typeid(typename Rows::Event).name() << ", " <<
                     typeid(typename Rows::Guard).name() << std::endl
    ), ...);
}

struct Base
{
	virtual void GetType()
	{}
};

struct Derived1 : public Base
{
	void GetType() override
	{}
};

struct Derived2 : public Base
{
	void GetType() override
	{}
};

void PrintType(Derived1* a)
{
	std::cout << typeid(a).name() << std::endl;
}

int main()
{
    using transitionTable = TransitionTable<
        Row<int, float, char>,
        Row<int, float, None>,
        Row<float, int, None>,
        Row<float, None, None>
    >;

	transitionTable::GetPossibleTransitions<int, float>::possibleTransitions transitions;
	PrintRows(transitions);

	Base* a = new Derived1();
	Base* b = new Derived2();

	PrintType(a);
	PrintType(b);
	// PrintType(&Derived2::GetType);

    return 0;
}
