#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			container_type _ctnr;

		public:
//---------------------------------Constructors----------------------------
			explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) {}
			stack(const stack& src) : _ctnr(src._ctnr) {}
			~stack(){}
			stack & operator=(stack const & src)
			{
				stack tmp(src);
				swap(_ctnr, tmp._ctnr);
				return (*this);
			}

//--------------------------------Member functions--------------------------

			//empty, true if container empty
			bool empty() const { return _ctnr.empty(); }

			//size, returns size of container
			size_type size() const { return _ctnr.size(); }

			//top, reference to top element (last element)
			value_type& top() { return _ctnr.back(); }
			const value_type& top() const { return _ctnr.back(); }

			//push, puts element to end(top) of container
			void push(const value_type& val) { _ctnr.push_back(val); }

			//pop, removes last(top) element of container
			void pop() { _ctnr.pop_back(); }

//---------------------------Non-member function overloads-----------------

			friend bool operator==(const stack& lhs, const stack& rhs) { return lhs._ctnr == rhs._ctnr; }
			friend bool operator!=(const stack& lhs, const stack& rhs) { return lhs._ctnr != rhs._ctnr; }
			friend bool operator<(const stack& lhs, const stack& rhs) { return lhs._ctnr < rhs._ctnr; }
			friend bool operator<=(const stack& lhs, const stack& rhs) { return lhs._ctnr <= rhs._ctnr; }
			friend bool operator>(const stack& lhs, const stack& rhs) { return lhs._ctnr > rhs._ctnr; }
			friend bool operator>=(const stack& lhs, const stack& rhs) { return lhs._ctnr >= rhs._ctnr; }

		private:

			template <typename S>
			void swap(S& a, S& b)
			{
				S tmp(a);
				a = b;
				b = tmp;
			}

	};

}
#endif /* STACK_HPP */

