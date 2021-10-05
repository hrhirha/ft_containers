#ifndef TYPES_TRAITS_HPP
# define TYPES_TRAITS_HPP

namespace ft
{
	template <bool, class T = void>
		struct enable_if {};
	template <class T>
		struct enable_if<true, T> { typedef T type; };

	template <bool B>
		struct bool_type { static const bool value = B; };

	typedef bool_type<true> true_type;
	typedef bool_type<false> false_type;

	template <class T>
		struct is_integral : false_type {};
	template <>
		struct is_integral<bool> : true_type {};
	template <>
		struct is_integral<char> : true_type {};
	template <>
		struct is_integral<char16_t> : true_type {};
	template <>
		struct is_integral<char32_t> : true_type {};
	template <>
		struct is_integral<wchar_t> : true_type {};
	template <>
		struct is_integral<signed char> : true_type {};
	template <>
		struct is_integral<short int> : true_type {};
	template <>
		struct is_integral<int> : true_type {};
	template <>
		struct is_integral<long int> : true_type {};
	template <>
		struct is_integral<long long int> : true_type {};
	template <>
		struct is_integral<unsigned char> : true_type {};
	template <>
		struct is_integral<unsigned short int> : true_type {};
	template <>
		struct is_integral<unsigned int> : true_type {};
	template <>
		struct is_integral<unsigned long int> : true_type {};
	template <>
		struct is_integral<unsigned long long int> : true_type {};
}

#endif
