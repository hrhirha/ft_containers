#ifndef TYPES_TRAITS_HPP
# define TYPES_TRAITS_HPP

namespace ft
{
	template <bool, class T = void>
		struct enable_if {};
	template <class T>
		struct enable_if<true, T> { typedef T type; };

	template <class T>
		struct is_integral
		{
			static bool value;
			operator T()
			{
				if (typeid(T) == typeid(bool)
					|| typeid(T) == typeid(char)
					|| typeid(T) == typeid(char16_t)
					|| typeid(T) == typeid(char32_t)
					|| typeid(T) == typeid(wchar_t)
					|| typeid(T) == typeid(signed char)
					|| typeid(T) == typeid(short int)
					|| typeid(T) == typeid(int)
					|| typeid(T) == typeid(long int)
					|| typeid(T) == typeid(long long int)
					|| typeid(T) == typeid(unsigned char)
					|| typeid(T) == typeid(unsigned short int)
					|| typeid(T) == typeid(unsigned long int)
					|| typeid(T) == typeid(unsigned long long int))
				{
					value = true;
				}
				else
					value = false;
				return (value);
			}
		};
}

#endif
