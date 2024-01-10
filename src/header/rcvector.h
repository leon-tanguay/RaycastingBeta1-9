#pragma once
#include <SFML/Graphics.hpp>

namespace rc
{
	template <typename T>
	class RCVector
	{
	public:
		// constructors
		RCVector() : x(0), y(0) {}
		RCVector(T x, T y) : x(x), y(y) {}
		RCVector(sf::Vector2<T> sfV) : x(sfV.x), y(sfV.y) { }

		// vector functions
		float magnitude() const;
		RCVector<T> getPerpendicularVector() const;
		RCVector<float> getUnitVector() const;
		RCVector<T> getPerpendicularUnitVector() const;
		RCVector<T> RCVector<T>::getRotatedVector(const T angle) const;

		// assignment operator
		void operator = (const RCVector<T>& rhs);
		
		// equality operators
		bool operator == (const RCVector<T>& rhs) const;
		bool operator != (const RCVector<T>& rhs) const;

		// unary math operators
		RCVector<T> operator -  ();
		
		// binary math operators with another vector
		RCVector<T>& operator += (const RCVector<T>& rhs);
		RCVector<T>& operator -= (const RCVector<T>& rhs);

		// binary math operators with a scalar value
		RCVector<T>& operator *= (const T scalar);
		RCVector<T>& operator /= (const T scalar);

		//conversion operators (should move sfml one)
		RCVector<float> toFloat() const;
		RCVector<int> toInt() const;
		operator sf::Vector2<T>() { return sf::Vector2<T>{x, y}; };
		
		//members
		T x;
		T y;
	};



	/*************
 	 Implementation
	**************/

	template <typename T>
	float RCVector<T>::magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	template <typename T>
	RCVector<T> RCVector<T>::getPerpendicularVector() const
	{
		return RCVector<T>{-y, x};
	}

	template <typename T>
	RCVector<float> RCVector<T>::getUnitVector() const
	{
		return RCVector<float>{static_cast<float>(x) / magnitude(), static_cast<float>(y) / magnitude()};
	}

	template <typename T>
	RCVector<T> RCVector<T>::getPerpendicularUnitVector() const
	{
		return getUnitVector().getPerpendicularVector();
	}

	template <typename T>
	RCVector<float> RCVector<T>::toFloat() const
	{
		return RCVector<float>(static_cast<float>(x), static_cast<float>(y));
	}

	template <typename T>
	RCVector<int> RCVector<T>::toInt() const
	{
		return RCVector<int>(static_cast<int>(x), static_cast<int>(y));
	}

	template <typename T>
	RCVector<T> RCVector<T>::getRotatedVector(const T angle) const //in degrees
	{
		return RCVector<T>
		{
			static_cast<T>(cos(angle * PI / 180.f) * x - sin(angle * PI / 180.f) * y),
			static_cast<T>(sin(angle * PI / 180.f) * x + cos(angle * PI / 180.f) * y)
		};
	}

	template <typename T>
	void RCVector<T>::operator = (const RCVector<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	//equality operators

	template <typename T>
	bool RCVector<T>::operator == (const RCVector<T>& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}

	template <typename T>
	bool RCVector<T>::operator != (const RCVector<T>& rhs) const
	{
		return (x != rhs.x || y != rhs.y);
	}

	// binary math operators - two vectors

	template <typename T>
	RCVector<T>& RCVector<T>::operator+= (const RCVector<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <typename T>
	RCVector<T>& RCVector<T>::operator-= (const RCVector<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	// binary math operators - vector and scalar


	template <typename T>
	RCVector<T>& RCVector<T>::operator *= (const T scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	template <typename T>
	RCVector<T>& RCVector<T>::operator /= (const T scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	// unary minus
	template <typename T>
	RCVector<T> RCVector<T>::operator-()
	{
		RCVector<T> result{ -lhs.x, -lhs.y };
		return result;
	}

	
	//binary math operators : non member functions

	template <typename T>
	RCVector<T> operator + (RCVector<T> lhs, const RCVector<T>& rhs)
	{
		return lhs += rhs;
	}

	template <typename T>
	RCVector<T> operator - (RCVector<T> lhs, const RCVector<T>& rhs)
	{
		return lhs -= rhs;
	}

	template <typename T>
	RCVector<T> operator * (RCVector<T> lhs, const T rhs)
	{
		return lhs *= rhs;
	}

	template <typename T>
	RCVector<T> operator / (RCVector<T> lhs, const T rhs)
	{
		return lhs /= rhs;
	}

	//defined instantiations

	using Vector2f = rc::RCVector<float>;
	using Vector2i = rc::RCVector<int>;

	//color stuff (should move)

	using Color = sf::Color;
	const Color GREEN = Color::Green;
	const Color BLACK = Color::Black;
}