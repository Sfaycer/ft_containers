#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iostream>
#include <iterator>
#include <string>
#include "utils.hpp"

namespace ft
{
	template <class Key, class T>
	class map_iterator
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			typedef std::bidirectional_iterator_tag iterator_category;
			typedef ft::pair<const Key, typename ft::remove_const<T>::type>& reference;
			typedef ft::pair<const Key, typename ft::remove_const<T>::type>* pointer;
			typedef Node<Key, typename ft::remove_const<T>::type>* nodePtr;

		private:
			nodePtr _node;
			nodePtr _pseudoElem;

		public:
//------------------------------Constructors--------------------------------------
			
			//Default
			map_iterator(nodePtr node = 0, nodePtr pseudoElem = 0) :
				_node(node), _pseudoElem(pseudoElem) {}

			//Copy
			map_iterator(const map_iterator<Key, typename ft::remove_const<T>::type> &src)
			{
				_node = src.getNode();
				_pseudoElem = src.getPseudoElem();
			}

			//Destructor
			~map_iterator() {}

			//Assignment
			map_iterator & operator=(const map_iterator<Key, typename ft::remove_const<T>::type> &src)
			{
				_node = src.getNode();
				_pseudoElem = src.getPseudoElem();
				return (*this);
			}

//----------------------------------Operators-----------------------------------------

			reference operator*() const { return (_node->content); }
			pointer operator->() const { return (&_node->content); }

			map_iterator &operator++()
			{
				if (_node == _pseudoElem)
				{
					_node = _pseudoElem->right;
					return (*this);
				}

				if (_node->right)
				{
					_node = _node->right;
					if (_node == _pseudoElem)
						return (*this);
					while (_node->left)
						_node = _node->left;
				}
				else
				{
					while (_node->parent && _node == _node->parent->right)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}

			map_iterator &operator--()
			{
				if (_node == _pseudoElem)
				{
					_node = _pseudoElem->left;
					return (*this);
				}

				if (_node->left)
				{
					_node = _node->left;
					if (_node == _pseudoElem)
						return (*this);
					while (_node->right)
						_node = _node->right;
				}
				else
				{
					while (_node->parent && _node == _node->parent->left)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			map_iterator operator--(int)
			{
				map_iterator tmp(*this);
				--(*this);
				return (tmp);
			}


			bool operator==(const map_iterator<Key, typename ft::remove_const<T>::type> &it) const { return (it.getNode() == _node); }
			bool operator==(const map_iterator<Key, const T> &it) const { return (it.getNode() == _node); }
			bool operator!=(const map_iterator<Key, typename ft::remove_const<T>::type> &it) const { return (it.getNode() != _node); }
			bool operator!=(const map_iterator<Key, const T> &it) const { return (it.getNode() != _node); }

//------------------------------Getters-------------------------------
			nodePtr getNode() const { return _node; }
			nodePtr getPseudoElem() const { return _pseudoElem; }

		private:
			nodePtr findMinNode(nodePtr node)
			{
				if (node && node != _pseudoElem && node->left && node->left != _pseudoElem)
					return (findMinNode(node->left));
				return (node);
			}

			nodePtr findMaxNode(nodePtr node)
			{
				if (node && node != _pseudoElem && node->right && node->right != _pseudoElem)
					return (findMaxNode(node->right));
				return (node);
			}
	};

}
#endif /* MAP_ITERATOR_HPP */

