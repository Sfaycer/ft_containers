#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
#include "utils.hpp"
#include "map_iterator.hpp"
#include "r_map_iterator.hpp"

namespace ft
{

template <class Key, class T, class Compare = ft::less<Key>,
		 class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	private:
	public:
		typedef Key				key_type;
		typedef Compare			key_compare;
		typedef Alloc			allocator_type;
		typedef T				mapped_type;

		typedef ft::pair<const key_type, mapped_type> value_type;

		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t		size_type;

		typedef Node<Key, T>*	nodePtr;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;

		typedef ft::map_iterator<Key, T>				iterator;
		typedef ft::map_iterator<Key, const T>		const_iterator;
		typedef ft::r_map_iterator<Key, T>			reverse_iterator;
		typedef ft::r_map_iterator<Key, const T>		const_reverse_iterator;

		class value_compare
		{
			friend class map;

			protected:
				key_compare comp;

				value_compare(Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;

				bool operator() (const value_type& x, const value_type& y) const
				{
					return (comp(x.first, y.first));
				}
		};

	private:
		//pseudoElem goes left of min key and right of max key
		//also, depending on Comparator,
		//pseudoElem->left = rightmost key (max with ft::less)
		//pseudoElem->right = leftmost key (min with ft::less)
		//basically needed for iterators or i'm too dumb
		nodePtr					_pseudoElem;

		nodePtr					_root;
		size_type				_size;
		key_compare				_comp;
		allocator_type			_allocPair;
		std::allocator<Node<Key, T> >	_allocNode;

//-------------------------------Constructors-----------------------------

	public: 

		explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
			_size(0), _comp(comp), _allocPair(alloc)
		{
			_pseudoElem = createNode(ft::pair<const key_type, mapped_type>());
			_pseudoElem->height = 0;
			_root = _pseudoElem;
			_pseudoElem->left = _pseudoElem;
			_pseudoElem->right = _pseudoElem;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
			_size(0), _comp(comp), _allocPair(alloc)
		{
			_pseudoElem = createNode(ft::pair<const key_type, mapped_type>());
			_pseudoElem->height = 0;
			_root = _pseudoElem;
			_pseudoElem->left = _pseudoElem;
			_pseudoElem->right = _pseudoElem;

			for (; first != last; first++)
				insert(*first);
		}

		map(map const &src) :
			_size(0), _comp(src._comp), _allocPair(src._allocPair), _allocNode(src._allocNode)
		{
			_pseudoElem = createNode(ft::pair<const key_type, mapped_type>());
			_pseudoElem->height = 0;
			_root = _pseudoElem;
			_pseudoElem->left = _pseudoElem;
			_pseudoElem->right = _pseudoElem;

			for (const_iterator it = src.begin(); it != src.end(); ++it)
			{
				insert(*it);
			}
		}

		~map()
		{
			clear();
			destroyNode(_pseudoElem);
		}

		map & operator=(map const & src)
		{
			map tmp(src);
			swap(tmp);

			return (*this);
		}

//---------------------------------Iterators--------------------------------


		iterator begin() { return iterator(_pseudoElem->right, _pseudoElem); }
		const_iterator begin() const { return const_iterator(_pseudoElem->right, _pseudoElem); }
		iterator end() { return iterator(_pseudoElem, _pseudoElem); }
		const_iterator end() const { return const_iterator(_pseudoElem, _pseudoElem); }

		reverse_iterator rbegin() { return reverse_iterator(_pseudoElem->left, _pseudoElem); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_pseudoElem->left,
				_pseudoElem); }
		reverse_iterator rend() { return reverse_iterator(_pseudoElem, _pseudoElem); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_pseudoElem,
				_pseudoElem); }

//----------------------------------Capacity------------------------------------

		bool empty() const { return (_size == 0); }
		size_type size() const { return (_size); }
		size_type max_size() const { return (_allocNode.max_size()); }

//--------------------------------Element access----------------------------------

		mapped_type &operator[](const key_type &k)
		{
			nodePtr tmp = searchNode(_root, k);

			if (tmp)
				return (tmp->content.second);

			value_type val = ft::pair<const key_type, mapped_type>(k, mapped_type());
			insert(val);
			return (searchNode(_root, k)->content.second);
		}

		T& at(const Key& key)
		{
			nodePtr tmp = searchNode(_root, key);

			if (tmp)
				return (tmp->content.second);
			else
				throw std::out_of_range("map");
		}

		const T& at(const Key& key) const
		{
			nodePtr tmp = searchNode(_root, key);

			if (tmp)
				return (tmp->content.second);
			else
				throw std::out_of_range("map");
		}

//----------------------------------Modifiers------------------------------------

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			nodePtr tmp = searchNode(_root, val.first);
			if (tmp)
				return (ft::pair<iterator, bool>(iterator(tmp, _pseudoElem), false));

			_size++;
			_root = insertNode(_root, val);
			tmp = searchNode(_root, val.first);
			return (ft::pair<iterator, bool>(iterator(tmp, _pseudoElem), true));
		}
	
		iterator insert(iterator position, const value_type& val)
		{
			nodePtr tmp = searchNode(_root, val.first);
			if (tmp)
				return (iterator(tmp, _pseudoElem));

			(void)position;
			_size++;
			_root = insertNode(_root, val);
			tmp = searchNode(_root, val.first);
			return (iterator(tmp, _pseudoElem));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase (iterator position)
		{
			_root = deleteNode(_root, position.getNode()->content);
			_size--;
		}

		size_type erase (const key_type& k)
		{
			nodePtr tmp = searchNode(_root, k);
			size_type deleted = 0;
			if (tmp)
			{
				_root = deleteNode(_root, tmp->content);
				deleted = 1;
			}
			_size -= deleted;
			return (deleted);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp(first);
				first++;
				erase(tmp);
			}
		}

		void swap (map& x)
		{
			swap(_root, x._root);
			swap(_pseudoElem, x._pseudoElem);
			swap(_size, x._size);
			swap(_comp, x._comp);
			swap(_allocPair, x._allocPair);
			swap(_allocNode, x._allocNode);
		}

		void clear()
		{
			erase(begin(), end());
		}

//---------------------------------Observers------------------------------

		key_compare key_comp() const { return (_comp); }
		value_compare value_comp() const { return (value_compare(_comp)); }

//----------------------------------Operations----------------------------

		iterator find (const key_type& k)
		{
			nodePtr tmp = searchNode(_root, k);
			if (tmp)
				return (iterator(tmp, _pseudoElem));
			return (end());
		}

		const_iterator find (const key_type& k) const
		{
			nodePtr tmp = searchNode(_root, k);
			if (tmp)
				return (const_iterator(tmp, _pseudoElem));
			return (end());
		}

		size_type count (const key_type& k) const
		{
			nodePtr tmp = searchNode(_root, k);
			if (tmp)
				return (1);
			return (0);
		}

		iterator lower_bound(const key_type& k)
		{
			iterator it = begin();
			for (; it != end(); it++)
				if (!_comp(it->first, k))
					break;
			return (it);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			const_iterator it = begin();
			for (; it != end(); it++)
				if (!_comp(it->first, k))
					break;
			return (it);
		}

		iterator upper_bound(const key_type& k)
		{
			iterator it = begin();
			for (; it != end(); it++)
				if (_comp(k, it->first))
					break;
			return (it);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			const_iterator it = begin();
			for (; it != end(); it++)
				if (_comp(k, it->first))
					break;
			return (it);
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{
			iterator low = lower_bound(k);
			iterator up = upper_bound(k);
			return (ft::pair<iterator, iterator>(low, up));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			const_iterator low = lower_bound(k);
			const_iterator up = upper_bound(k);
			return (ft::pair<const_iterator, const_iterator>(low, up));
		}

		friend bool operator==(const map& lhs, const map& rhs)
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

		friend bool operator<(const map& lhs, const map& rhs)
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

		friend bool operator!=(const map& lhs, const map& rhs) {return !(lhs == rhs); }
		friend bool operator>(const map& lhs, const map& rhs) {return (rhs < lhs); }
		friend bool operator<=(const map& lhs, const map& rhs) {return !(rhs < lhs); }
		friend bool operator>=(const map& lhs, const map& rhs) {return !(lhs < rhs); }

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
	private:

		void print()
		{
			printTree(_root, "", true);
		}

		template <typename S>
		void swap(S& a, S& b)
		{
			S tmp = a;
			a = b;
			b = tmp;
		}

		// Calculate height
		int height(nodePtr N) const
		{
			if (N == NULL)
				return 0;
			return N->height;
		}

		int max(int a, int b) const
		{
			return (a > b) ? a : b;
		}

		// New node creation
		nodePtr createNode(const value_type& pair)
		{
			nodePtr node = _allocNode.allocate(1);
			_allocPair.construct(&node->content, pair);
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->height = 1;
			return (node);
		}

		//Destroy node and it's contents
		void destroyNode(nodePtr node)
		{
			_allocPair.destroy(&node->content);
			_allocNode.deallocate(node, 1);
		}

		// Rotate right
		nodePtr rightRotate(nodePtr y)
		{
			nodePtr x = y->left;
			nodePtr T2 = x->right;
			x->right = y;
			y->left = T2;

			x->parent = y->parent;
			y->parent = x;
			if (T2)
				T2->parent = y;

			y->height = 1 + max(height(y->left), height(y->right));
			x->height = 1 + max(height(x->left), height(x->right));
			return x;
		}

		// Rotate left
		nodePtr leftRotate(nodePtr x)
		{
			nodePtr y = x->right;
			nodePtr T2 = y->left;
			y->left = x;
			x->right = T2;

			y->parent = x->parent;
			x->parent = y;
			if (T2)
				T2->parent = x;

			x->height = 1 + max(height(x->left), height(x->right));
			y->height = 1 + max(height(y->left), height(y->right));
			return y;
		}

		// Get the balance factor of each node
		int getBalanceFactor(nodePtr N) const
		{
			if (N == NULL)
				return 0;
			return height(N->left) - height(N->right);
		}

		// Insert a node
		// pseudoElem should
		nodePtr insertNode(nodePtr node, const value_type& pair)
		{
			// Find the correct postion and insert the node
			if (node == NULL)
				return (createNode(pair));
			else if (node == _pseudoElem)
			{
				nodePtr tmp = createNode(pair);
				//corner case, when map is empty
				if (_root == _pseudoElem)
				{
					_root = tmp;
					_root->left = _pseudoElem;
					_root->right = _pseudoElem;
					_pseudoElem->left = _root;
					_pseudoElem->right = _root;

					return (_root);
				}

				//connect pseudoElem to min or max value
				if (_comp(tmp->content.first, _pseudoElem->right->content.first))
				{
					_pseudoElem->right = tmp;
					tmp->left = _pseudoElem;
				}
				else if (_comp(_pseudoElem->left->content.first, tmp->content.first))
				{
					_pseudoElem->left = tmp;
					tmp->right = _pseudoElem;
				}
				return (tmp);
			}
			if (_comp(pair.first, node->content.first))
			{
				node->left = insertNode(node->left, pair);
				node->left->parent = node;
			}
			else if (_comp(node->content.first, pair.first))
			{
				node->right = insertNode(node->right, pair);
				node->right->parent = node;
			}
			else
				return node;

			// Update the balance factor of each node and
			// balance the tree
			node->height = 1 + max(height(node->left), height(node->right));
			int balanceFactor = getBalanceFactor(node);
			if (balanceFactor > 1)
			{
				if (_comp(pair.first, node->left->content.first))
					return rightRotate(node);
				else if (_comp(node->left->content.first, pair.first))
				{
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			if (balanceFactor < -1)
			{
				if (_comp(node->right->content.first, pair.first))
					return leftRotate(node);
				else if (_comp(pair.first, node->right->content.first))
				{
					node->right = rightRotate(node->right);
					return leftRotate(node);
				}
			}
			return node;
		}

		// Node with minimum value
		nodePtr nodeWithMimumValue(nodePtr node) const
		{
			nodePtr current = node;
			while (current->left != NULL)
				current = current->left;
			return current;
		}


		// Delete a node
		nodePtr deleteNode(nodePtr root, const value_type& pair) {
			// Find the node and delete it
			if (root == NULL)
				return root;
			if (pair.first == root->content.first)
			{
				if ((root->left == NULL) || (root->right == NULL)
					|| (root->left == _pseudoElem) || (root->right == _pseudoElem)
				   )
				{
					nodePtr temp;
					if (root->left && root->left != _pseudoElem)
						temp = root->left;
					else if (root->right && root->right != _pseudoElem)
						temp = root->right;
					else
						temp = NULL;


					if (temp == NULL)
					{
						temp = root;

						//case of true root being deleted while it's the only node
						if (root->left == _pseudoElem && root->right == _pseudoElem)
						{
							root = _pseudoElem;
							_pseudoElem->left = _pseudoElem;
							_pseudoElem->right = _pseudoElem;
						}
						else if (root->left == _pseudoElem)
						{
							_pseudoElem->right = root->parent;
							root = _pseudoElem;
						}
						else if (root->right == _pseudoElem)
						{
							_pseudoElem->left = root->parent;
							root = _pseudoElem;
						}
						else
							root = NULL;

						destroyNode(temp);
					}
					else
					{
						temp->parent = root->parent;

						//case of true root being deleted with only 1 node connected to it
						if (root->left == _pseudoElem)
							temp->left = _pseudoElem;
						if (root->right == _pseudoElem)
							temp->right = _pseudoElem;

						if (temp->parent)
						{
							if (temp->parent->left == root)
								temp->parent->left = temp;
							else if (temp->parent->right == root)
								temp->parent->right = temp;
						}
						nodePtr temp_root = root;
						root = temp;

						//retaging parent and _pseudoElem back on
						if (root->left && root->left != _pseudoElem)
							root->left->parent = root;
						else if (root->left == _pseudoElem)
							_pseudoElem->right = root;
						if (root->right && root->right != _pseudoElem)
							root->right->parent = root;
						else if (root->right == _pseudoElem)
							_pseudoElem->left = root;

						destroyNode(temp_root);
					}
				}
				else
				{
					nodePtr temp = nodeWithMimumValue(root->right);

					//root->content = temp->content;
					_allocPair.destroy(&root->content);
					_allocPair.construct(&root->content, temp->content);

					root->right = deleteNode(root->right, temp->content);
					if (root->right)
						root->right->parent = root;
				}
			}
			else if (_comp(pair.first, root->content.first))
			{
				root->left = deleteNode(root->left, pair);
				if (root->left)
					root->left->parent = root;
			}
			else if (_comp(root->content.first, pair.first))
			{
				root->right = deleteNode(root->right, pair);
				if (root->right)
					root->right->parent = root;
			}

			if (root == NULL || root == _pseudoElem)
				return root;

			// Update the balance factor of each node and
			// balance the tree
			root->height = 1 + max(height(root->left),
					height(root->right));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1) {
				if (getBalanceFactor(root->left) >= 0) {
					return rightRotate(root);
				} else {
					root->left = leftRotate(root->left);
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1) {
				if (getBalanceFactor(root->right) <= 0) {
					return leftRotate(root);
				} else {
					root->right = rightRotate(root->right);
					return leftRotate(root);
				}
			}
			return root;
		}

		//search for node
		nodePtr searchNode(nodePtr root, key_type key) const
		{
			if (root == NULL || root == _pseudoElem)
				return (0);

			if (root->content.first == key)
				return (root);

			if (_comp(key, root->content.first))
				return (searchNode(root->left, key));
			else if (_comp(root->content.first, key))
				return (searchNode(root->right, key));

			return (0);
		}

		// Print the tree
		void printTree(nodePtr root, std::string indent, bool last) {
			if (root != nullptr && root != _pseudoElem) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}
				std::cout << root->content.first << std::endl;
				printTree(root->left, indent, false);
				printTree(root->right, indent, true);
			}
		}


};

}
#endif /* MAP_HPP */

