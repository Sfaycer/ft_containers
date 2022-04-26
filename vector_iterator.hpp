#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include "utils.hpp"

namespace ft
{
	template <typename T>
	class vector_iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

		private:
			pointer m_ptr;

		public:
//---------------------------Coplien form---------------------------
			vector_iterator(pointer ptr = 0){m_ptr = ptr;}
			vector_iterator(const vector_iterator<typename ft::remove_const<T>::type >& src)
			{
				m_ptr = src.getPtr();
			}
			~vector_iterator(void){}
			vector_iterator & operator=(vector_iterator<typename ft::remove_const<T>::type > const & src)
			{
				m_ptr = src.getPtr();
				return (*this);
			}

//-------------------------Operator overloads------------------------
			reference operator*() const {return *m_ptr;}
			pointer operator->() {return m_ptr;}
			const pointer operator->() const {return m_ptr;}

//--------------------------------------------------------------

			//prefix increment
			vector_iterator& operator++()
			{
				++m_ptr;
				return (*this);
			}
			//postfix increment
			vector_iterator operator++(int)
			{
				vector_iterator old = *this;
				operator++();
				return (old);
			}

			//prefix decrement
			vector_iterator& operator--()
			{
				--m_ptr;
				return (*this);
			}
			//postfix decrement
			vector_iterator operator--(int)
			{
				vector_iterator old = *this;
				operator--();
				return (old);
			}

//-------------------------------------------------------------

			//Increment by value
			vector_iterator& operator+=(const difference_type& movement)
			{
				m_ptr += movement;
				return (*this);
			}
			//Decrement by value
			vector_iterator& operator-=(const difference_type& movement)
			{
				m_ptr -= movement;
				return (*this);
			}

			//Adding value without changing member variable
			vector_iterator operator+(const difference_type& movement) const
			{
				vector_iterator it = *this;
				it += movement;
				return (it);
			}
			//Substracting value without changing member variable
			vector_iterator operator-(const difference_type& movement) const
			{
				vector_iterator it = *this;
				it -= movement;
				return (it);
			}

//-----------------------------------------------------------

			//Comparisons
			bool operator==(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr == src.getPtr());}
			bool operator==(const vector_iterator<const T>& src) const {return (m_ptr == src.getPtr());}

			bool operator!=(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr != src.getPtr());}
			bool operator!=(const vector_iterator<const T>& src) const {return (m_ptr != src.getPtr());}

			bool operator<(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr < src.getPtr());}
			bool operator<(const vector_iterator<const T>& src) const {return (m_ptr < src.getPtr());}

			bool operator>(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr > src.getPtr());}
			bool operator>(const vector_iterator<const T>& src) const {return (m_ptr > src.getPtr());}

			bool operator<=(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr <= src.getPtr());}
			bool operator<=(const vector_iterator<const T>& src) const {return (m_ptr <= src.getPtr());}

			bool operator>=(const vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr >= src.getPtr());}
			bool operator>=(const vector_iterator<const T>& src) const {return (m_ptr >= src.getPtr());}

			reference operator[](const difference_type& movement) const
			{
				pointer tmp = m_ptr;
				tmp += movement;
				return (*tmp);
			}

			difference_type operator-(const vector_iterator &src) {return (m_ptr - src.m_ptr);}

			friend vector_iterator operator+(int nb, const vector_iterator& it)
			{
				vector_iterator newIt(it);
				return (newIt += nb);
			}

			friend vector_iterator operator-(int nb, const vector_iterator& it)
			{
				vector_iterator newIt(it);
				return (newIt -= nb);
			}


			pointer getPtr() const {return m_ptr;}
	};

}

#endif /* VECTOR_ITERATOR_HPP */

