#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <memory>
#include "vector_iterator.hpp"
#include "r_vector_iterator.hpp"
#include "utils.hpp"

/////////////////////////////////////
namespace ft
{

	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;

			typedef ft::vector_iterator<T> iterator;
			typedef ft::vector_iterator<const T> const_iterator;
			typedef ft::r_vector_iterator<T> reverse_iterator;
			typedef ft::r_vector_iterator<const T> const_reverse_iterator;

		private:
			allocator_type _alloc;
			pointer array;
			size_type _size;
			size_type _capacity;
		public:
//------------------------Constructors------------------------------------
			//Default
			explicit vector(const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _size(0), _capacity(0)
			{
				array = _alloc.allocate(_capacity);
			}
			//Fill, vector size of n and value initialize to val
			explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _size(n), _capacity(n)
			{
				array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(array + i, val);
			}
			//Range, size is range between to iterators, copy values of range to new elements
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
				_alloc(alloc), _size(0)
			{
				_capacity = _size;
				array = _alloc.allocate(0);

				while (first != last)
				{
					push_back(*first);
					first++;
				}

				pointer tmp = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, array[i]);
				this->~vector();
				_capacity = _size;
				array = tmp;
			}
			//Copy
			vector(const vector& x) :
				_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				array = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; i++)
					_alloc.construct(array + i, x.array[i]);
			}
			//Destructor
			~vector(void)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(array + i);
				_alloc.deallocate(array, _capacity);
			}
			//Assignment constructor
			vector & operator=(vector const & src)
			{
				vector tmp(src);
				swap(tmp);
				return (*this);
			}

//----------------------------Iterators------------------------------

			iterator begin() { return iterator(array); }
			const_iterator begin() const { return const_iterator(array); }
			iterator end() { return iterator(array + _size); }
			const_iterator end() const { return const_iterator(array + _size); }

			reverse_iterator rbegin() { return reverse_iterator(array + _size - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(array + _size - 1); }
			reverse_iterator rend() { return reverse_iterator(array - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(array - 1); }

//----------------------------Capacity-----------------------------

			size_type size() const { return _size; }
			size_type max_size() const { return _alloc.max_size(); }

			void resize (size_type n, value_type val = value_type())
			{
				/*
				if (n > _capacity)
					reserve(n);
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
				*/
				if (n < _size)
					while (n < _size)
						pop_back();
				else
					while (n > _size)
						push_back(val);
			}

			size_type capacity() const { return _capacity; }
			bool empty() const { return _size == 0; }

			void reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				if (n > _capacity)
				{
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(tmp + i, array[i]);
					this->~vector();
					_capacity = n;
					array = tmp;
				}
			}

//--------------------------Element Access-------------------------

			//[]
			reference operator[](size_type n) { return array[n]; }
			const_reference operator[](size_type n) const { return array[n]; }

			//at reference, same as above but with exception throw
			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (array[n]);
			}
			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (array[n]);
			}

			//first element
			reference front() { return array[0]; }
			const_reference front() const { return array[0]; }

			//last element
			reference back() { return array[_size - 1]; }
			const_reference back() const { return array[_size - 1]; }

			//data
			pointer data() { return (array); }
			const pointer data() const { return (array); }

//-----------------------------Modifiers------------------------------

			
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				clear();
				insert (begin(), first, last);
			}
			void assign (size_type n, const value_type& val)
			{
				value_type valx = val;
				clear();
				insert(begin(), n, valx);
			}
			
			//Push back
			void push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					reserve(!_capacity? 1 : _capacity * 2);
				_alloc.construct(array + _size, val);
				_size++;
			}

			//Pop back
			void pop_back()
			{
				if (_size)
					_alloc.destroy(array + (_size - 1));
				_size--;
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type offset = size() == 0 ? 0 : position - begin();
				insert(position, 1, val);
				return (begin() + offset);
			}
			void insert(iterator position, size_type n, const value_type& val)
			{
				value_type valx  = val;
				size_type c = capacity();
				if (n == 0)
					;
				else if (max_size() - size() < n)
					throw std::length_error("vector");
				else if (c < size() + n)
				{
					c = max_size() - c < c ? 0 : c * 2;
					if (c < size() + n)
						c = size() + n;
					pointer s = _alloc.allocate(c);
					pointer q;
					try {
						q = uCopy(begin(), position, s);
						q = uFill(q, n, valx);
						uCopy(position, end(), q);
					} catch (...) {
						destroy (s, q);
						_alloc.deallocate(s, c);
						throw;
					}
					destroy(begin().getPtr(), end().getPtr());
					_alloc.deallocate(array, _capacity);
					_capacity = c;
					_size = _size + n;
					array = s;
				}
				else if ((size_type) (end() - position) < n)
				{
					uCopy(position, end(), position.getPtr() + n);
					try {
						uFill(end().getPtr(), n - (end() - position), valx);
					} catch (...) {
						destroy(position.getPtr() + n, end().getPtr() + n);
						throw;
					}
					_size += n;
					std::fill(position, end() - n, valx);
				}
				else
				{
					iterator tmpEnd = end();
					pointer last = uCopy(tmpEnd - n, tmpEnd, end().getPtr());
					_size = last - array;
					std::copy_backward(position, tmpEnd - n, tmpEnd);
					std::fill(position, position + n, valx);
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				//Insert(position, first, last, ft::iter_cat(first));
				Insert(position, first, last, typename InputIterator::iterator_category());
			}


			//Erase, removes elements, moving right elements to the left
			iterator erase(iterator position)
			{
				return (erase(position, position + 1));
			}
			iterator erase(iterator first, iterator last)
			{
				if (first != last)
				{
					pointer s = std::copy(last, end(), first.getPtr());
					destroy(s, end().getPtr());
					_size = s - array;
				}
				return (first);
			}

			//Swap member function
			void swap(vector& x)
			{
				swap(_alloc, x._alloc);
				swap(array, x.array);
				swap(_size, x._size);
				swap(_capacity, x._capacity);
			}

			//clear
			void clear()
			{
				while (_size)
					pop_back();
			}

//---------------------------Allocator-------------------------

			allocator_type get_allocator() const { return (_alloc); }

//-----------------------Non-member function overloads------------------

			friend bool operator==(const vector& lhs, const vector& rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);

				ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
				while (it.first != lhs.end())
				{
					if (*(it.first) != *(it.second))
						return (false);
					it.first++;
					it.second++;
				}
				return (true);
			}

			friend bool operator<(const vector& lhs, const vector& rhs)
			{
				ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
				while ((it.first != lhs.end()) && (it.second != rhs.end()))
				{
					if (*(it.first) < *(it.second))
						return (true);
					it.first++;
					it.second++;
				}
				return (lhs.size() < rhs.size());
			}

			friend bool operator!=(const vector& lhs, const vector& rhs) {return !(lhs == rhs); }
			friend bool operator>(const vector& lhs, const vector& rhs) {return (rhs < lhs); }
			friend bool operator<=(const vector& lhs, const vector& rhs) {return !(rhs < lhs); }
			friend bool operator>=(const vector& lhs, const vector& rhs) {return !(lhs < rhs); }

			friend void swap (vector& x, vector& y) { x.swap(y);}

		private:
			template <typename S>
			void swap(S &x, S &y)
			{
				S tmp = x;
				x = y;
				y = tmp;
			}

			void destroy(pointer first, pointer last)
			{
				for (; first != last; first++)
					_alloc.destroy(first);
			}

			template <class InputIterator>
			pointer uCopy(InputIterator first, InputIterator last, pointer q)
			{
				pointer qs = q;
				try {
					for (; first != last; ++q, ++first)
						_alloc.construct(q, *first);
				} catch (...) {
					destroy(qs, q);
					throw;
				}
				return (q);
			}

			pointer uFill(pointer q, size_type n, const T &x)
			{
				pointer qs = q;
				try {
					for (; 0 < n; --n, ++q)
						_alloc.construct(q, x);
				} catch (...) {
					destroy(qs, q);
					throw;
				}
				return (q);
			}

			template <class InputIterator>
			void Insert(iterator position, InputIterator first, InputIterator last,
					std::input_iterator_tag)
			{
				for (; first != last; ++first, ++position)
					position = insert(position, *first);
			}
			template <class InputIterator>
			void Insert(iterator position, InputIterator first, InputIterator last,
					std::forward_iterator_tag)
			{
				size_type m = std::distance(first, last);
				size_type n = capacity();
				if (m == 0)
					;
				else if (max_size() - size() < m)
					throw std::length_error("vector");
				else if (n < size() + m)
				{
					n = max_size() - n < n ? 0 : n * 2;
					if (n < size() + m)
						n = size() + m;
					pointer s = _alloc.allocate(n);
					pointer q;
					try {
						q = uCopy(begin(), position, s);
						q = uCopy(first, last, q);
						uCopy(position, end(), q);
					} catch (...) {
						destroy(s, q);
						_alloc.deallocate(s, n);
						throw;
					}
					destroy(array, array + _size);
					_alloc.deallocate(array, _capacity);
					_capacity = n;
					_size = _size + m;
					array = s;
				}
				else if ((size_type) (end() - position) < m)
				{
					uCopy(position, end(), position.getPtr() + m);
					InputIterator mid = first;
					std::advance(mid, end() - position);
					try {
						uCopy(mid, last, end().getPtr());
					} catch (...) {
						destroy (position.getPtr() + m, end().getPtr() + m);
						throw;
					}
					_size += m;
					std::copy(first, mid, position);
				}
				else if (0 < m)
				{
					iterator tmpEnd = end();
					pointer l = uCopy(tmpEnd - m, tmpEnd, end().getPtr());
					_size = l - array;
					std::copy_backward(position, tmpEnd - m, tmpEnd);
					std::copy(first, last, position);
				}
			}
	};

}

#endif /* VECTOR_HPP */

