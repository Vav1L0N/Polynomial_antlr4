#include"Polynomial.h"
#include"gtest.h"

TEST(Polynomial, can_create_empty_polinom)
{
	ASSERT_NO_THROW(Polynomial());
}

TEST(Polynomial, empty_polinom_equal_to_zero)
{
	ASSERT_NO_THROW(Polynomial().isNull(), true);
}

TEST(Polynomial, can_create_polinom)
{
	string in("2.3x^5y^3z^4+4.5x^4y^2z^1");
	ASSERT_NO_THROW(Polynomial(in));
}

TEST(Polynomial, polinom_stored_correctly)
{
	string in("6.43x^5y^3z^4+6.3x^4y^2z^1");
	Polynomial pol(in);
	EXPECT_EQ(in, pol.repr());
}

TEST(Polynomial, polinom_stored_correctly_with_0)
{
	string in("6.43x^5y^3z^4+6.3x^4y^2z^1+0");
	string exp("6.43x^5y^3z^4+6.3x^4y^2z^1");
	Polynomial pol(in);
	EXPECT_EQ(exp, pol.repr());
}

TEST(Polynomial, polinom_stored_sorted)
{
	string in("5.4x^3y^3z^4+1.3x^4y^2z^1");
	string exp("1.3x^4y^2z^1+5.4x^3y^3z^4");
	Polynomial pol(in);
	EXPECT_EQ(exp, pol.repr());
}

TEST(Polynomial, can_multiply_polinom_by_const)
{
	string in("3x^8y^1z^3+x^7y^4");
	string exp("6x^8y^1z^3+2x^7y^4");
	Polynomial pol(in);
	Polynomial res = pol * 2;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_multiply_polinom_by_zero)
{
	string in("3x^8y^1z^3+x^7y^4");
	string exp("0");
	Polynomial pol(in);
	Polynomial res = pol * 0;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_add_polinoms)
{
	string in("5x^2y^3z^2+2x^2y^2");
	Polynomial pol(in);
	string in1("4x^2y^2+3.14");
	Polynomial pol1(in1);
	string exp("5x^2y^3z^2+6x^2y^2+3.14");
	Polynomial res = pol + pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_add_polinoms_with_bringing_similar)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polynomial pol(in);
	string in1("-x^2y^2+3.14");
	Polynomial pol1(in1);
	string exp("5x^2y^3z^2+3.14");
	Polynomial res = pol + pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_sub_polinoms)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polynomial pol(in);
	string in1("4x^2y^2+3.14");
	Polynomial pol1(in1);
	string exp("5x^2y^3z^2-3x^2y^2-3.14");
	Polynomial res = pol - pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_sub_equal_polinoms)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polynomial pol(in);
	string in1("5x^2y^3z^2+x^2y^2");
	Polynomial pol1(in1);
	string exp("0");
	Polynomial res = pol - pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_mul_polinoms)
{
	string in("x+y");
	Polynomial pol(in);
	string in1("x-y");
	Polynomial pol1(in1);
	string exp("1x^2-1y^2");
	Polynomial res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(Polynomial, can_mul_polinoms_with_bringing_similar)
{
	string in("x+y");
	Polynomial pol(in);
	string in1("x+y");
	Polynomial pol1(in1);
	string exp("1x^2+2x^1y^1+1y^2");
	Polynomial res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}


TEST(Polynomial, cant_mul_polinoms_power_overflou)
{
	string in("x^5+y");
	Polynomial pol(in);
	string in1("x^5-y");
	Polynomial pol1(in1);
	ASSERT_ANY_THROW(pol * pol1);
}