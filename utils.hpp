#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <iterator>

namespace ft
{
	//enable_if, defines a type if true
	template <bool B> struct enable_if {};
	template <> struct enable_if<true> {typedef int type; };

	//is_integral, true if it is integral type
	template <typename T>
	struct is_integral : std::false_type { static const bool value = false; };
	template <> struct is_integral<bool> : std::true_type { static const bool value = true; };
	template <> struct is_integral<char> : std::true_type {static const bool value = true; } ;
	template <> struct is_integral<short> : std::true_type {static const bool value = true; };
	template <> struct is_integral<int> : std::true_type {static const bool value = true; };
	template <> struct is_integral<long> : std::true_type {static const bool value = true; };
	template <> struct is_integral<signed char> : std::true_type {static const bool value = true; };
//	template <> struct is_integral<long long> : std::true_type {static const bool value = true; };
	template <> struct is_integral<unsigned char> : std::true_type {static const bool value = true; };
	template <> struct is_integral<unsigned short> : std::true_type {static const bool value = true; };
	template <> struct is_integral<unsigned int> : std::true_type {static const bool value = true; };
	template <> struct is_integral<unsigned long> : std::true_type {static const bool value = true; };
//	template <> struct is_integral<unsigned long long> : std::true_type {static const bool value = true; };
	template <> struct is_integral<wchar_t> : std::true_type {static const bool value = true; };
	template <> struct is_integral<char16_t> : std::true_type {static const bool value = true; };
	template <> struct is_integral<char32_t> : std::true_type {static const bool value = true; };

	template <class T> struct remove_const          { typedef T type; };
	template <class T> struct remove_const<const T> { typedef T type; };

	//pair
	template <class T1, class T2>
	class pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;
			first_type first;
			second_type second;

			//default
			pair() : first(), second() {};
			//copy
			template <class U, class V>
			pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
			//init
			pair(const first_type& a, const second_type& b) : first(a), second(b) {};
			
			~pair() {};

			pair& operator=(const pair& pr)
			{
				first = pr.first;
				second = pr.second;

				return (*this);
			}


			friend bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{
				return lhs.first == rhs.first && lhs.second == rhs.second;
			}

			friend bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{ return !(lhs==rhs); }

			friend bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{
				return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
			}

			friend bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{ return !(rhs<lhs); }

			friend bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{ return rhs<lhs; }

			friend bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
			{ return !(lhs<rhs); }
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	//less
	template <class T>
	struct less
	{
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator() (const T &x, const T &y) const { return (x < y); }
	};

	template <class Key, class T>
	struct Node
	{
		ft::pair<const Key, T> content;
		Node * parent;
		Node * left;
		Node * right;
		int height;
	};


	template <class It>
	struct iterator_traits
	{
		typedef typename It::iterator_category iterator_category;
		typedef typename It::value_type value_type;
		typedef typename It::distance_type distance_type;
		typedef typename It::pointer pointer;
		typedef typename It::reference reference;
	};
	template <class T>
	struct iterator_traits<T *>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t distance_type;
		typedef T* pointer;
		typedef T& reference;
	};
	
}
#endif /* UTILS_HPP */

