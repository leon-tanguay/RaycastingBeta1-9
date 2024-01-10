#pragma once
#include <SFML/Graphics.hpp>
namespace rc
{
	template <typename T>
	class RCVector
	{
	public:

		RCVector() : x(0), y(0)
		{
		}

		RCVector(T x, T y) : x(x), y(y)
		{
		}
		RCVector(sf::Vector2<T> sfV) : x(sfV.x), y(sfV.y)
		{

		}

		float magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		RCVector<T> getPerpendicularVector() const
		{
			return RCVector<T>{-y, x};
		}

		RCVector<float> getUnitVector() const
		{
			return RCVector<float>{static_cast<float>(x) / magnitude(), static_cast<float>(y) / magnitude()};
		}

		RCVector<T> getPerpendicularUnitVector() const
		{
			return getUnitVector().getPerpendicularVector();
		}

		RCVector<float> toFloat() const
		{
			return RCVector<float>(static_cast<float>(x), static_cast<float>(y));
		}
		
		RCVector<int> toInt() const
		{
			return RCVector<int>(static_cast<int>(x), static_cast<float>(y));
		}
		
		void operator = (RCVector<T> const& rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		
		RCVector<T>& operator += (RCVector<T> const& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		
		RCVector<T>& operator -= (RCVector<T> const& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		RCVector<T>& operator *= (const T i)
		{
			x *= i;
			y *= i;
			return *this;
		}

		RCVector<T>& operator /= (const int i)
		{
			x /= i;
			y /= i;
			return *this;
		}

		RCVector<T>& operator /= (const float f)
		{
			x /= f;
			y /= f;
			return *this;
		}
		operator sf::Vector2<T>() { return sf::Vector2<T>{x, y}; };
		T x;
		T y;
	};

	template <typename T>
	RCVector<T> operator + (RCVector<T> const& lhs, RCVector<T> const& rhs)
	{
		return RCVector<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template <typename T>
	RCVector<T> operator - (RCVector<T> const& lhs, RCVector<T> const& rhs)
	{
		return RCVector<T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template <typename T>
	RCVector<T> operator * (RCVector<T> const& lhs, const int i)
	{
		return RCVector<T>(lhs.x * i, lhs.y * i);
	}

	template <typename T>
	RCVector<T> operator * (RCVector<T> const& lhs, const float f)
	{
		return RCVector<T>(lhs.x * f, lhs.y * f);
	}

	template <typename T>
	RCVector<T> operator / (RCVector<T> const& lhs, const int i)
	{
		return RCVector<T>(lhs.x / i, lhs.y / i);
	}

	template <typename T>
	RCVector<T> operator / (RCVector<T> const& lhs, const float f)
	{
		return RCVector<T>(lhs.x / f, lhs.y / f);
	}
	
	template <typename T>
	bool operator == (RCVector<T> const& lhs, RCVector<T> const& rhs)
	{
		return (lhs.x==rhs.x && lhs.y == rhs.x);
	}

	template <typename T>
	bool operator != (RCVector<T> const& lhs, RCVector<T> const& rhs)
	{
		return (lhs.x != rhs.x || lhs.y != rhs.x);
	}
	
	using Vector2f = rc::RCVector<float>;
	using Vector2i = rc::RCVector<int>;
	using Color = sf::Color;
	const Color GREEN = Color::Green;
	const Color BLACK = Color::Black;
}