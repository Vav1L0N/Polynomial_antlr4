#pragma once
#include"list.h"
#include<string>
#define u_short unsigned short int
const double eps = 1e-10;

class Polynomial
{
public:
	class monom 
	{
	protected:
		u_short pows;
		double coeff;
	public:
		monom(int xPow, int yPow, int zPow, double coeff)
		{
			if (abs(coeff) < eps) 
			{
				this->pows = 0;
				this->coeff = 0;
			}
			else 
			{
				this->pows = u_short(xPow * 100 + yPow * 10 + zPow);
				this->coeff = coeff;
			}
		}

		u_short getPows() const { return pows; }

		double getCoeff() const { return coeff; }

		monom(u_short pows = 0, double coeff = 0) 
		{
			if (abs(coeff) < eps) {
				this->pows = 0;
				this->coeff = 0;
			}
			else 
			{
				this->pows = pows;
				this->coeff = coeff;
			}
		}
		~monom() = default;
		bool isPositive() const 
		{
			if (coeff > 0.0)
				return true;
			return false;
		}
		bool isNull() const 
		{
			if (abs(coeff) < eps)
				return true;
			return false;
		}
		
		bool operator ==(const monom& other) const 
		{
			if (this->pows == other.pows)
				return true;
			return false;
		}

		bool operator !=(const monom& other) const 
		{
			return !(*this == other); 
		}

		bool operator > (const monom& other) const 
		{
			if (this->pows > other.pows)
				return true;
			return false;
		}

		bool operator < (const monom& other) const 
		{
			return !(*this > other);
		}

		monom operator +(const monom& other) const 
		{
			return monom(this->pows, this->coeff + other.coeff);
		}

		monom operator* (const monom& other) const 
		{
			if (((this->pows % 10 + other.pows % 10) > 9) || (((this->pows % 100) / 10) + ((other.pows % 100) / 10) > 9) || ((this->pows / 100 + other.pows / 100) > 9)) 
			{
				throw std::exception("Error, too large power in multiply!");
			}
			return monom(this->pows + other.pows, this->coeff * other.coeff);
		}

		monom operator*(const double val) const 
		{
			return monom(this->pows, this -> coeff * val);
		}

		std::string repr() const 
		{
			std::string res;
			res += std::to_string(coeff);
			if (res[res.size() - 1] == '0')
			{
				for (size_t i = res.size() - 1; res[i] == '0'; i--) 
				{
					res.erase(i, 1);
				}
			}

			if (res[res.size()-1]=='.')
			{
				res.erase(res.size() - 1, 1);
			}

			if ((pows / 100) % 10 != 0) 
			{
				res += "x^" + std::to_string(pows / 100);
			}

			if ((pows / 10) % 10 != 0)
			{
				res += "y^" + std::to_string((pows % 100)/10);
			}

			if (pows  % 10 != 0)
			{
				res += "z^" + std::to_string(pows % 10);
			}

			return res;
		}

		friend std::ostream& operator <<(std::ostream& out, const monom& m)
		{
			out << m.repr();
			return out;
		}
	};

	list<monom> Monoms;
	double StringToDouble(std::string numstr)
	{
		double res = 0.0;

		size_t ePos = numstr.find('e') != std::string::npos ? numstr.find('e') : numstr.size();

		size_t pointPos = numstr.find('.') != std::string::npos ? numstr.find('.') : ePos;

		for (size_t i = 0; i < pointPos; i++)
		{
			size_t num = static_cast<size_t>(numstr[i]) - 48;
			res += static_cast<double>(num * pow(10, numstr.size() - (numstr.size() - pointPos) - i - 1));
		}
		for (size_t i = pointPos + 1, j = 1; i < ePos; i++, j++)
		{
			size_t num = static_cast<size_t>(numstr[i]) - 48;
			res += static_cast<double>(num / pow(10, j));
		}

		size_t i = ePos + 2;

		if (i < numstr.size())
		{
			if (numstr[i - 1] == '-')
			{
				res /= pow(10, StringToDouble(numstr.substr(i, numstr.size())));
			}
			else
			{
				res *= pow(10, StringToDouble(numstr.substr(i, numstr.size())));
			}
		}
		return res;

	}


	void addmonom(const monom& m) 
	{

		if (m.isNull())
		{
			return;
		}
		Monoms.push(m);

	};


	void parser(std::string input)
	{
		std::string validVars("xyz");

		for (size_t i = 0; i < input.size();)
		{
			std::string substr;
			double coeff = 1.0;
			int pows[3] = { 0,0,0 };
			if (input[i] == '-' || input[i] == '+')
			{
				if (input[i] == '-')
				{
					coeff = -1.0;
				}
				i++;
			}
			if (input[i] >= '0' && input[i] <= '9')
			{
				while (input[i] >= '0' && input[i] <= '9')
				{
					substr.push_back(input[i]);
					i++;
				}
				if (input[i] == '.')
				{
					substr.push_back(input[i]);
					i++;
					while (input[i] >= '0' && input[i] <= '9')
					{
						substr.push_back(input[i]);
						i++;
					}
				}
				if (input[i] == 'e')
				{
					substr.push_back(input[i]);
					i++;
					if (input[i] == '+' || input[i] == '-')
					{
						substr.push_back(input[i]);
						i++;
					}
					while (input[i] >= '0' && input[i] <= '9')
					{
						substr.push_back(input[i]);
						i++;
					}
				}
				coeff *= StringToDouble(substr);
			}
			if (validVars.find(input[i]) != std::string::npos)
			{
				while (validVars.find(input[i]) != std::string::npos)
				{
					if (input[i + 1] != '^')
					{
						pows[validVars.find(input[i])] = 1;
						i++;
						continue;
					}
					pows[validVars.find(input[i])] = input[i + 2] - 48;
					i += 3;
				}
			}
			addmonom(monom(pows[0], pows[1], pows[2], coeff));
		}
	
	}
	

	list<monom>::iterator listbegin() const 
	{
		return Monoms.begin();
	}

	list<monom>::iterator listend() const 
	{
		return Monoms.end();
	}

	Polynomial() {};
	Polynomial(std::string input)
	{
		parser(input);
	}

	Polynomial(const list<monom>& monoms) {
		for (const auto& m : monoms)
			Monoms.push(m);
	}

	~Polynomial() = default;


	bool isNull() const
	{
		if (Monoms.isEmpty())
		{
			return true;
		}
		return false;
	}

	std::string repr() const
	{
		if (isNull())
		{
			return std::to_string(0);
		}
		std::string res;
		bool isFirst = true;
		for (auto& i : Monoms)
		{
			if (i.isPositive() && !isFirst)
			{
				res += "+";
			}
			res += i.repr();
			isFirst = false;
		}
		return res;
	}

	Polynomial operator + (const Polynomial& other) const
	{
		Polynomial res;
		auto cur = this->listbegin();
		auto oth = other.listbegin();
		while (cur != this->listend() && oth != other.listend())
		{
			if ((*cur) == (*oth))
			{
				monom resSum = (*cur) + (*oth);
				cur++;
				oth++;
				if (resSum.isNull())
				{
					continue;
				}
				res.addmonom(resSum);
			}
			else if ((*cur) > (*oth))
			{
				res.addmonom((*cur));
				cur++;
			}
			else
			{
				res.addmonom((*oth));
				oth++;
			}
		}
		while (cur != this->listend())
		{
			res.addmonom((*cur));
			cur++;
		}
		while (oth != other.listend())
		{
			res.addmonom((*oth));
			oth++;
		}
		return res;


	}

	Polynomial operator - (const Polynomial& other) const
	{
		Polynomial res;
		res = *this + other * (-1.0);
		return res;
	}

	Polynomial operator * (const Polynomial& other) const
	{
		Polynomial res;
		auto cur = this->listbegin();
		auto oth = other.listbegin();
		while (cur != this->listend())
		{
			Polynomial tmp;
			while (oth != this->listend())
			{
				tmp.addmonom((*cur) * (*oth));
				oth++;
			}
			res = res + tmp;
			oth = other.listbegin();
			cur++;
		}
		return res;
	}

	Polynomial operator * (const double val) const
	{
		Polynomial res;
		auto cur = this->listbegin();
		while (cur != this->listend())
		{
			res.addmonom((*cur) * val);
			cur++;
		}
		return res;
	}

	friend std::ostream& operator <<(std::ostream& out, const Polynomial& p)
	{
		out << p.repr();
		return out;
	}
	friend std::istream& operator >>(std::istream& in, Polynomial& m)
	{
		std::string input;
		in >> input;
		m.parser(input);
		return in;
	}

	double Polynomial::evaluate(double x, double y, double z) const {
		double result = 0.0;
		for (const auto& monom : Monoms) {
			double monomValue = monom.getCoeff(); 
			monomValue *= pow(x, monom.getPows() / 100); 
			monomValue *= pow(y, (monom.getPows() % 100) / 10); 
			monomValue *= pow(z, monom.getPows() % 10); 
			result += monomValue;
		}
		return result;
	}

};