#include <stdexcept>


namespace ImgClass {
	template <class T>
	RGB<T>::RGB(void)
	{
		_red = 0;
		_green = 0;
		_blue = 0;
	}

	template <class T>
	RGB<T>::RGB(const T& red, const T& green, const T& blue)
	{
		_red = red;
		_green = green;
		_blue = blue;
	}

	template <class T>
	template <class RT>
	RGB<T>::RGB(const RT& value)
	{
		_red = value;
		_green = value;
		_blue = value;
	}


	// Data access
	template <class T>
	T
	RGB<T>::R(void)
	{
		return _red;
	}

	template <class T>
	T
	RGB<T>::G(void)
	{
		return _green;
	}

	template <class T>
	T
	RGB<T>::B(void)
	{
		return _blue;
	}


	// Operators
	template <class T>
	template <class RT>
	RGB<T> &
	RGB<T>::operator=(const RT& value)
	{
		_red = value;
		_green = value;
		_blue = value;
	}

	template <class T>
	template <class RT>
	RGB<T> &
	RGB<T>::operator=(const RGB<RT>& color)
	{
		_red = color._red;
		_green = color._green;
		_blue = color._blue;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator+=(const RGB<T>& color)
	{
		_red += color._red;
		_green += color._green;
		_blue += color._blue;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator+=(const T& value)
	{
		_red += value;
		_green += value;
		_blue += value;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator-=(const RGB<T>& color)
	{
		_red -= color._red;
		_green -= color._green;
		_blue -= color._blue;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator-=(const T& value)
	{
		_red -= value;
		_green -= value;
		_blue -= value;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator*=(const RGB<T>& color)
	{
		_red *= color._red;
		_green *= color._green;
		_blue *= color._blue;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator*=(const T& value)
	{
		_red *= value;
		_green *= value;
		_blue *= value;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator/=(const RGB<T>& color)
	{
		_red /= color._red;
		_green /= color._green;
		_blue /= color._blue;
	}

	template <class T>
	RGB<T> &
	RGB<T>::operator/=(const T& value)
	{
		_red /= value;
		_green /= value;
		_blue /= value;
	}
}


// ----- Global Operators -----

// Arithmetic

template <class Type>
ImgClass::RGB<Type> &
operator+(ImgClass::RGB<Type> color)
{
	return color;
}

template <class Type>
ImgClass::RGB<Type> &
operator-(ImgClass::RGB<Type> color)
{
	color._red = -color._red;
	color._green = -color._green;
	color._blue = -color._blue;
	return color;
}


template <class Type>
ImgClass::RGB<Type> &
operator+(ImgClass::RGB<Type> lcolor, const ImgClass::RGB<Type>& rcolor)
{
	lcolor._red += rcolor._red;
	lcolor._green += rcolor._green;
	lcolor._blue += rcolor._blue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator+(ImgClass::RGB<Type> lcolor, const Type& rvalue)
{
	lcolor._red += rvalue;
	lcolor._green += rvalue;
	lcolor._blue += rvalue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator+(const Type& lvalue, ImgClass::RGB<Type> rcolor)
{
	rcolor._red += lvalue;
	rcolor._green += lvalue;
	rcolor._blue += lvalue;
	return rcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator-(ImgClass::RGB<Type> lcolor, const ImgClass::RGB<Type>& rcolor)
{
	lcolor._red -= rcolor._red;
	lcolor._green -= rcolor._green;
	lcolor._blue -= rcolor._blue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator-(ImgClass::RGB<Type> lcolor, const Type& rvalue)
{
	lcolor._red -= rvalue;
	lcolor._green -= rvalue;
	lcolor._blue -= rvalue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator-(const Type& lvalue, ImgClass::RGB<Type> rcolor)
{
	rcolor._red -= lvalue;
	rcolor._green -= lvalue;
	rcolor._blue -= lvalue;
	return rcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator*(ImgClass::RGB<Type> lcolor, const ImgClass::RGB<Type>& rcolor)
{
	lcolor._red *= rcolor._red;
	lcolor._green *= rcolor._green;
	lcolor._blue *= rcolor._blue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator*(ImgClass::RGB<Type> lcolor, const Type& rvalue)
{
	lcolor._red *= rvalue;
	lcolor._green *= rvalue;
	lcolor._blue *= rvalue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator*(const Type& lvalue, ImgClass::RGB<Type> rcolor)
{
	rcolor._red *= lvalue;
	rcolor._green *= lvalue;
	rcolor._blue *= lvalue;
	return rcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator/(ImgClass::RGB<Type> lcolor, const ImgClass::RGB<Type>& rcolor)
{
	lcolor._red /= rcolor._red;
	lcolor._green /= rcolor._green;
	lcolor._blue /= rcolor._blue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator/(ImgClass::RGB<Type> lcolor, const Type& rvalue)
{
	lcolor._red /= rvalue;
	lcolor._green /= rvalue;
	lcolor._blue /= rvalue;
	return lcolor;
}

template <class Type>
ImgClass::RGB<Type> &
operator/(const Type& lvalue, ImgClass::RGB<Type> rcolor)
{
	rcolor._red = lvalue / rcolor._red;
	rcolor._green = lvalue / rcolor._green;
	rcolor._blue = lvalue / rcolor._blue;
	return rcolor;
}


// Comparator
template <class Type>
bool
operator==(const ImgClass::RGB<Type>& lcolor, const ImgClass::RGB<Type>& rcolor)
{
	if (lcolor._red == rcolor._red
	    && lcolor._green == rcolor._green
	    && lcolor._blue == rcolor._blue) {
		return true;
	} else {
		return false;
	}
}

template <class Type>
bool
operator!=(const ImgClass::RGB<Type>& lcolor, const ImgClass::RGB<Type>& rcolor)
{
	if (lcolor._red != rcolor._red
	    || lcolor._green != rcolor._green
	    || lcolor._blue != rcolor._blue) {
		return true;
	} else {
		return false;
	}
}

