#ifndef R_VECTOR_ITERATOR_HPP
#define R_VECTOR_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include "vector_iterator.hpp"

namespace ft
{
	template <typename T>
	class r_vector_iterator
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
			r_vector_iterator(pointer ptr = 0){m_ptr = ptr;}
			r_vector_iterator(const r_vector_iterator<typename ft::remove_const<T>::type >& src)
			{
				m_ptr = src.getPtr();
			}
			explicit r_vector_iterator(const vector_iterator<typename ft::remove_const<T>::type >& src)
			{
				m_ptr = src.getPtr() - 1;
			}
			~r_vector_iterator(void){}
			r_vector_iterator & operator=(r_vector_iterator<typename ft::remove_const<T>::type > const & src)
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
			r_vector_iterator& operator++()
			{
				--m_ptr;
				return (*this);
			}
			//postfix increment
			r_vector_iterator operator++(int)
			{
				r_vector_iterator old = *this;
				operator++();
				return (old);
			}

			//prefix decrement
			r_vector_iterator& operator--()
			{
				++m_ptr;
				return (*this);
			}
			//postfix decrement
			r_vector_iterator operator--(int)
			{
				r_vector_iterator old = *this;
				operator--();
				return (old);
			}

//-------------------------------------------------------------

			//Increment by value
			r_vector_iterator& operator+=(const difference_type& movement)
			{
				m_ptr -= movement;
				return (*this);
			}
			//Decrement by value
			r_vector_iterator& operator-=(const difference_type& movement)
			{
				m_ptr += movement;
				return (*this);
			}

			//Adding value without changing member variable
			r_vector_iterator operator+(const difference_type& movement) const
			{
				r_vector_iterator it = *this;
				it += movement;
				return (it);
			}
			//Substracting value without changing member variable
			r_vector_iterator operator-(const difference_type& movement) const
			{
				r_vector_iterator it = *this;
				it -= movement;
				return (it);
			}

//-----------------------------------------------------------

			//Comparisons
			bool operator==(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr == src.getPtr());}
			bool operator==(const r_vector_iterator<const T>& src) const {return (m_ptr == src.getPtr());}

			bool operator!=(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr != src.getPtr());}
			bool operator!=(const r_vector_iterator<const T>& src) const {return (m_ptr != src.getPtr());}

			bool operator<(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr > src.getPtr());}
			bool operator<(const r_vector_iterator<const T>& src) const {return (m_ptr > src.getPtr());}

			bool operator>(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr < src.getPtr());}
			bool operator>(const r_vector_iterator<const T>& src) const {return (m_ptr < src.getPtr());}

			bool operator<=(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr >= src.getPtr());}
			bool operator<=(const r_vector_iterator<const T>& src) const {return (m_ptr >= src.getPtr());}

			bool operator>=(const r_vector_iterator<typename ft::remove_const<T>::type >& src) const {return (m_ptr <= src.getPtr());}
			bool operator>=(const r_vector_iterator<const T>& src) const {return (m_ptr <= src.getPtr());}

			reference operator[](const difference_type& movement) const
			{
				pointer tmp = m_ptr;
				tmp -= movement;
				return (*tmp);
			}

			difference_type operator-(const r_vector_iterator &src) {return (src.m_ptr - m_ptr);}


			friend r_vector_iterator operator+(int nb, const r_vector_iterator& it)
			{
				r_vector_iterator newIt(it);
				return (newIt += nb);
			}

			friend r_vector_iterator operator-(int nb, const r_vector_iterator& it)
			{
				r_vector_iterator newIt(it);
				return (newIt -= nb);
			}

			pointer getPtr() const {return m_ptr;}
	};

}

#endif /* R_VECTOR_ITERATOR_HPP */

