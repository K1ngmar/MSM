#include "MSM/Utility/UniqueTuple.hpp" 

#include <criterion/criterion.h>

void suitesetup(void)
{
}

void suiteteardown(void)
{
}

TestSuite(UniqueTupleTestGroup, .init=suitesetup, .fini=suiteteardown);

Test(UniqueTupleTestGroup, TypeIsNotDuplicateInParameterPack)
{
	cr_expect(TypeIsDuplicateInParameterPack<int, float, char, bool>::value == false);

	cr_expect(TypeIsDuplicateInParameterPack<int>::value == false);

	cr_expect(TypeIsDuplicateInParameterPack<int, double>::value == false);
}

Test(UniqueTupleTestGroup, TypeIsDuplicateInParameterPack)
{
	cr_expect(TypeIsDuplicateInParameterPack<int, int>::value == true);

	cr_expect(TypeIsDuplicateInParameterPack<int, float, int>::value == true);

	cr_expect(TypeIsDuplicateInParameterPack<double, float, double, int>::value == true);
}

Test(UniqueTupleTestGroup, UniqueTupleFromTypes)
{
	cr_expect(std::is_same_v<
		MSM::Utility::UniqueTuple<int, float, int, char, char, bool>,
		std::tuple<float, int, char, bool>
	>);
}

Test(UniqueTupleTestGroup, UniqueTupleFromTuple)
{
	cr_expect(std::is_same_v<
		MSM::Utility::UniqueTupleFromTuple<std::tuple<int, float, int, char, char, bool>>,
		std::tuple<float, int, char, bool>
	>);
}

