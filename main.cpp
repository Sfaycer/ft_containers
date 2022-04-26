#include <exception>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "utils.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <fstream>
#include <time.h>
#include <stack>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include <cstring> // for strcmp
#include <stddef.h>
#include <stdlib.h> // for system()

#define _ratio 100
#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
//#define T int
//#define V int

time_t g_start1;
time_t g_end1;
time_t g_start2;
time_t g_end2;

struct  Dummy
{
	std::string str;
	Dummy *operator&() const
	{
		return NULL;
	}
};

class B {
	public:
		char *l;
		int i;
		B():l(nullptr), i(1) {};
		/*
		   B(const B& src) {
		   this->i = src.i;
		   this->l = new char();
		 *this->l = *src.l;
		 }
		 */
		B(const int &ex) {
			this->i = ex;
			this->l = new char('a');
		};
		virtual ~B() {
			delete this->l;
			this->l = nullptr;
		};
};

class A : public B {
	public:
		A():B(){};
		A(const B* ex){
			this->l = new char(*(ex->l));
			this->i = ex->i;
			if (ex->i == -1) throw "n";
		}
		~A() {
			delete this->l;
			this->l = nullptr;
		};
};

template <class I, class G, class C>
void fillMap(std::map<I, G, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}

template <class I, class G, class C>
void fillMap(_map<I, G, C> &mp) {
	mp.insert(_make_pair(16, 3));
	mp.insert(_make_pair(8, 3));
	mp.insert(_make_pair(23, 3));
	mp.insert(_make_pair(7, 3));
	mp.insert(_make_pair(19, 3));
	mp.insert(_make_pair(29, 3));
	mp.insert(_make_pair(41, 3));
	mp.insert(_make_pair(4, 3));
	mp.insert(_make_pair(11, 3));
}

template< typename T >
void	print_container_content(ft::vector<T> &vec, std::string name = "container") {
	std::cout << name << " contains:";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename T >
void	reverse_print_container_content(ft::vector<T> &vec, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (ft::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename T >
void	print_container_content(std::vector<T> &vec, std::string name = "container") {
	std::cout << name << " contains:";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename T >
void	reverse_print_container_content(std::vector<T> &vec, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename K, typename V >
void	mprint_container_content(ft::map<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:";
	for (typename ft::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << it->second;
	std::cout << " $" << std::endl;
}
template< typename K, typename V >
void	mprint_container_content(std::map<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:";
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << it->second;
	std::cout << " $" << std::endl;
}


template< typename k, typename v>
void	compare_keys(ft::map<k, v>& mappie, k compelem = k(), std::string name = "container") {
	typename ft::map<k, v>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename ft::map<k, v>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(it->first, compelem))
			std::cout << it->first << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, it->first))
			std::cout << it->first << " is higher than " << compelem << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem << std::endl;
	}
}
template< typename k, typename v>
void	compare_keys(std::map<k, v>& mappie, k compelem = k(), std::string name = "container") {
	typename std::map<k, v>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename std::map<k, v>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(it->first, compelem))
			std::cout << it->first << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, it->first))
			std::cout << it->first << " is higher than " << compelem << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem << std::endl;
	}
}


template< typename K, typename V>
void	compare_values(ft::map<K, V>& mappie, ft::pair<K, V> compelem = ft::make_pair(K(), V()), std::string name = "container") {
	typename ft::map<K, V>::value_compare vcomp = mappie.value_comp();
	(void)name;
	for (typename ft::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (vcomp(*it, compelem))
			std::cout << it->first << " is lower than " << compelem.first << std::endl;
		else if (vcomp(compelem, *it))
			std::cout << it->first << " is higher than " << compelem.first << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem.first << std::endl;
	}
}
template< typename K, typename V>
void	compare_values(std::map<K, V>& mappie, std::pair<K, V> compelem = std::make_pair(K(), V()), std::string name = "container") {
	typename std::map<K, V>::value_compare vcomp = mappie.value_comp();
	(void)name;
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (vcomp(*it, compelem))
			std::cout << it->first << " is lower than " << compelem.first << std::endl;
		else if (vcomp(compelem, *it))
			std::cout << it->first << " is higher than " << compelem.first << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem.first << std::endl;
	}
}

ft::map<int, std::string>	getstlmap() {
	ft::map<int, std::string> stl;
	stl[10] = "tien";
	stl[7] = "zeven";
	stl[6] = "zes";
	stl[13] = "dertien";
	stl[1] = "een";
	stl[4] = "vier";
	stl[3] = "drie";
	stl[8] = "acht";
	stl[14] = "veertien";
	return stl;
}	
std::map<int, std::string>	mgetstlmap() {
	std::map<int, std::string> stl;
	stl[10] = "tien";
	stl[7] = "zeven";
	stl[6] = "zes";
	stl[13] = "dertien";
	stl[1] = "een";
	stl[4] = "vier";
	stl[3] = "drie";
	stl[8] = "acht";
	stl[14] = "veertien";
	return stl;
}	






int main()
{
	std::cout << "=====================================================" << std::endl;
	std::cout << "========================VECTOR=======================" << std::endl;
	std::cout << "=====================================================" << std::endl;
	{
		std::cout << "=====STL test=====" << std::endl;
		std::cout << "STD" << std::endl;
		std::vector<int>		wap;
		std::vector<int>	stl;
		for (int i = 0; i < 12; i++)
			stl.push_back(i * 4);
		wap.assign(stl.begin(), stl.end());
		print_container_content(wap, "wap");
		reverse_print_container_content(wap, "wap");
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "FT" << std::endl;
		ft::vector<int>		wap;
		std::vector<int>	stl;
		for (int i = 0; i < 12; i++)
			stl.push_back(i * 4);
		wap.assign(stl.begin(), stl.end());
		print_container_content(wap, "wap");
		reverse_print_container_content(wap, "wap");
	}




	{
		std::cout << "=====Constuctor test=====" << std::endl;
		std::cout << "STD" << std::endl;
		int i = 8;
		std::vector<int> def;
		print_container_content(def, "default constructor");
		std::vector<int>	fill(i, 42);
		for (int i = 0; i < 8; i++)
			fill.push_back( i );
		print_container_content(fill, "fill constructor");
		std::vector<int> range(fill.begin(), fill.end());
		print_container_content(range, "range constructor");
		std::vector<int> copy(range);
		print_container_content(copy, "copy constructor");
		copy = def;
		print_container_content(copy, "assignation operator");
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "FT" << std::endl;
		int i = 8;
		ft::vector<int> def;
		print_container_content(def, "default constructor");
		ft::vector<int>	fill(i, 42);
		for (int i = 0; i < 8; i++)
			fill.push_back( i );
		print_container_content(fill, "fill constructor");
		ft::vector<int> range(fill.begin(), fill.end());
		print_container_content(range, "range constructor");
		ft::vector<int> copy(range);
		print_container_content(copy, "copy constructor");
		copy = def;
		print_container_content(copy, "assignation operator");
	}



	{
		std::cout << "=====Iterators test=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::vector<int> hats;
		for (int i = 0; i < 72; i++)
			hats.push_back(i * 10);
		std::vector<int>::iterator		it = hats.begin();
		std::vector<int>::iterator		ite = hats.end();
		ite--;
		std::vector<int>::iterator test = 5 + it;
		std::cout << "*test = " << *test << std::endl;
		std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
		std::vector<int>::const_iterator	cit = hats.begin();
		std::vector<int>::const_iterator	cite = hats.end();
		cite--;
		std::cout << "*cit = " << *cit << ", *cite = " << *cite << std::endl;
		std::vector<int>::reverse_iterator		rit = hats.rbegin();
		std::vector<int>::reverse_iterator		rite = hats.rend();
		(void)rite;
		std::vector<int>::const_reverse_iterator	crit = hats.rbegin();
		std::vector<int>::const_reverse_iterator	crite = hats.rend();
		std::cout << "regular iterators:" << std::endl;
		std::cout << "reg: operator==(): " << std::boolalpha << (it == cit) << ", " << (cit == it) << std::endl;
		std::cout << "reg: operator!=(): " << std::boolalpha << (it != cite) << ", " << (cite != it) << std::endl;
		std::cout << "reg: operator<(): " << std::boolalpha << (it < cite) << ", " << (cite < it) << std::endl;
		std::cout << "reg: operator<=(): " << std::boolalpha << (it <= cite) << ", " << (cite <= it) << std::endl;
		std::cout << "reg: operator>(): " << std::boolalpha << (it > cite) << ", " << (cite > it) << std::endl;
		std::cout << "reg: operator>=(): " << std::boolalpha << (it >= cite) << ", " << (cite >= it) << std::endl;
		ite = it;
		std::cout << "*it++ gives: " << *it++ << ", it now is " << *it << std::endl;
		std::cout << "*++it gives: " << *++it << ", it now is " << *it << std::endl;
		std::cout << "*rit++ gives: " << *rit++ << ", it now is " << *rit << std::endl;
		std::cout << "*++rit gives: " << *++rit << ", it now is " << *rit << std::endl;
		std::cout << "*it-- gives: " << *it-- << ", it now is " << *it << std::endl;
		std::cout << "*--it gives: " << *--it << ", it now is " << *it << std::endl;
		std::cout << "*rit-- gives: " << *rit-- << ", it now is " << *rit << std::endl;
		std::cout << "*--rit gives: " << *--rit << ", it now is " << *rit << std::endl;
		std::cout << "reverse iterators:" << std::endl;
		std::cout << "reverse: operator==(): " << std::boolalpha << (rit == crit) << ", " << (crit == rit) << std::endl;
		std::cout << "reverse: operator!=(): " << std::boolalpha << (rit != crite) << ", " << (crite != rit) << std::endl;
		std::cout << "reverse: operator<(): " << std::boolalpha << (rit < crite) << ", " << (crite < rit) << std::endl;
		std::cout << "reverse: operator<=(): " << std::boolalpha << (rit <= crite) << ", " << (crite <= rit) << std::endl;
		std::cout << "reverse: operator>(): " << std::boolalpha << (rit > crite) << ", " << (crite > rit) << std::endl;
		std::cout << "reverse: operator>=(): " << std::boolalpha << (rit >= crite) << ", " << (crite >= rit) << std::endl;
		std::cout << "dereference operator on iterators: " << it[2] << ", " << cit[3] << ", " << rit[4] << ", " << crit[5] << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;
		ft::vector<int> hats;
		for (int i = 0; i < 72; i++)
			hats.push_back(i * 10);
		ft::vector<int>::iterator		it = hats.begin();
		ft::vector<int>::iterator		ite = hats.end();
		ite--;
		ft::vector<int>::iterator test = 5 + it;
		std::cout << "*test = " << *test << std::endl;
		std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
		ft::vector<int>::const_iterator	cit = hats.begin();
		ft::vector<int>::const_iterator	cite = hats.end();
		cite--;
		std::cout << "*cit = " << *cit << ", *cite = " << *cite << std::endl;
		ft::vector<int>::reverse_iterator		rit = hats.rbegin();
		ft::vector<int>::reverse_iterator		rite = hats.rend();
		(void)rite;
		ft::vector<int>::const_reverse_iterator	crit = hats.rbegin();
		ft::vector<int>::const_reverse_iterator	crite = hats.rend();
		std::cout << "regular iterators:" << std::endl;
		std::cout << "reg: operator==(): " << std::boolalpha << (it == cit) << ", " << (cit == it) << std::endl;
		std::cout << "reg: operator!=(): " << std::boolalpha << (it != cite) << ", " << (cite != it) << std::endl;
		std::cout << "reg: operator<(): " << std::boolalpha << (it < cite) << ", " << (cite < it) << std::endl;
		std::cout << "reg: operator<=(): " << std::boolalpha << (it <= cite) << ", " << (cite <= it) << std::endl;
		std::cout << "reg: operator>(): " << std::boolalpha << (it > cite) << ", " << (cite > it) << std::endl;
		std::cout << "reg: operator>=(): " << std::boolalpha << (it >= cite) << ", " << (cite >= it) << std::endl;
		ite = it;
		std::cout << "*it++ gives: " << *it++ << ", it now is " << *it << std::endl;
		std::cout << "*++it gives: " << *++it << ", it now is " << *it << std::endl;
		std::cout << "*rit++ gives: " << *rit++ << ", it now is " << *rit << std::endl;
		std::cout << "*++rit gives: " << *++rit << ", it now is " << *rit << std::endl;
		std::cout << "*it-- gives: " << *it-- << ", it now is " << *it << std::endl;
		std::cout << "*--it gives: " << *--it << ", it now is " << *it << std::endl;
		std::cout << "*rit-- gives: " << *rit-- << ", it now is " << *rit << std::endl;
		std::cout << "*--rit gives: " << *--rit << ", it now is " << *rit << std::endl;
		std::cout << "reverse iterators:" << std::endl;
		std::cout << "reverse: operator==(): " << std::boolalpha << (rit == crit) << ", " << (crit == rit) << std::endl;
		std::cout << "reverse: operator!=(): " << std::boolalpha << (rit != crite) << ", " << (crite != rit) << std::endl;
		std::cout << "reverse: operator<(): " << std::boolalpha << (rit < crite) << ", " << (crite < rit) << std::endl;
		std::cout << "reverse: operator<=(): " << std::boolalpha << (rit <= crite) << ", " << (crite <= rit) << std::endl;
		std::cout << "reverse: operator>(): " << std::boolalpha << (rit > crite) << ", " << (crite > rit) << std::endl;
		std::cout << "reverse: operator>=(): " << std::boolalpha << (rit >= crite) << ", " << (crite >= rit) << std::endl;
		std::cout << "dereference operator on iterators: " << it[2] << ", " << cit[3] << ", " << rit[4] << ", " << crit[5] << std::endl;
	}



	{
		std::cout << "=====Capacity test=====" << std::endl;
		std::cout << "STD" << std::endl;
		std::vector<int>	papajohns;

		std::cout << "papajohns.empty(): " << std::boolalpha<< papajohns.empty() << std::endl;
		for (int i = 0; i < 10; ++i)
			papajohns.push_back(i);
		std::cout << "papajohns.size(): " << papajohns.size() << std::endl;
		std::cout << "papajohns.max_size(): " << papajohns.max_size() << std::endl;
		std::cout << "papajohns.capacacity(): " << papajohns.capacity() << std::endl;
		std::cout << "papajohns.empty(): " << std::boolalpha << papajohns.empty() << std::endl;

	}
	std::cout << "--------------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::vector<int>	papajohns;
		std::cout << "papajohns.empty(): " << std::boolalpha<< papajohns.empty() << std::endl;
		for (int i = 0; i < 10; ++i)
			papajohns.push_back(i);
		std::cout << "papajohns.size(): " << papajohns.size() << std::endl;
		std::cout << "papajohns.max_size(): " << papajohns.max_size() << std::endl;
		std::cout << "papajohns.capacacity(): " << papajohns.capacity() << std::endl;
		std::cout << "papajohns.empty(): " << std::boolalpha << papajohns.empty() << std::endl;

	}



	{
		std::cout << "=====Element access test=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::vector<int> kokkita;

		for (int i = 0; i < 10; ++i)
			kokkita.push_back(-3 * i);

		const std::vector<int> constkita(kokkita);
		std::cout << "kokkita[3]: " << kokkita[3] << ", constkita[4]: " << constkita[4] << std::endl;
		try {
			std::cout << "the [] operator does not check if the input value is inbounds of the array" << std::endl;
			std::cout << "the function .at() does check and throws an exception if it is out of bounds, here I'll show you:" << std::endl;
			std::cout << "kokkita.at(13): " << kokkita.at(13) << std::endl;
		}
		catch (std::out_of_range& e) {
			std::cout << "See? it threw an exception" << std::endl;
			// I didnt print e.what(), because diff will see it as different (and wrong) sadface
		}
		std::cout << "kokkita.front() = " << kokkita.front() << ", constkita.front() = " << constkita.front() << std::endl;
		std::cout << "kokkita.back() = " << kokkita.back() << ", constkita.back() = " << constkita.back() << std::endl;
		// std::cout << "kokkita[" << 812039 << "]: " << kokkita[812039] << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::vector<int> kokkita;

		for (int i = 0; i < 10; ++i)
			kokkita.push_back(-3 * i);

		const ft::vector<int> constkita(kokkita);
		std::cout << "kokkita[3]: " << kokkita[3] << ", constkita[4]: " << constkita[4] << std::endl;
		try {
			std::cout << "the [] operator does not check if the input value is inbounds of the array" << std::endl;
			std::cout << "the function .at() does check and throws an exception if it is out of bounds, here I'll show you:" << std::endl;
			std::cout << "kokkita.at(13): " << kokkita.at(13) << std::endl;
		}
		catch (std::out_of_range& e) {
			std::cout << "See? it threw an exception" << std::endl;
			// I didnt print e.what(), because diff will see it as different (and wrong) sadface
		}
		std::cout << "kokkita.front() = " << kokkita.front() << ", constkita.front() = " << constkita.front() << std::endl;
		std::cout << "kokkita.back() = " << kokkita.back() << ", constkita.back() = " << constkita.back() << std::endl;
		// std::cout << "kokkita[" << 812039 << "]: " << kokkita[812039] << std::endl;
	}








	{
		std::cout << "=====Modifiers test=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::vector<int>	tocopy;
		for (int i = 0; i < 14; ++i)
			tocopy.push_back(14 * i);
		std::vector<int> wap;
		wap.assign(5, 69);
		print_container_content(wap, "after the first assign, wapwap");
		wap.assign(tocopy.begin(), tocopy.end());
		print_container_content(wap, "and after the second, wapwap");
		while (!(tocopy.empty()))
			tocopy.pop_back();
		print_container_content(wap, "wap");
		std::vector<int>::iterator it = wap.begin() + 2;
		std::cout << "*it = " << *it << std::endl;
		wap.insert(it, 2, 800);
		it = wap.insert(wap.begin() + 1, 9999);
		std::cout << "returned iterator from insert gives " << *it << std::endl;
		tocopy.insert(tocopy.begin(), wap.begin(), wap.end() - 5);
		print_container_content(wap, "after insert, wap");

		it = tocopy.erase(tocopy.begin());
		std::cout << "erasing returns iterator to " << *it << std::endl;
		print_container_content(tocopy, "after insert and erasing, tocopy");
		it = tocopy.erase(tocopy.begin(), tocopy.begin() + 6);
		std::cout << "erasing returns iterator to " << *it << std::endl;

		print_container_content(tocopy, "after insert and erasing, tocopy");

	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::vector<int>	tocopy;
		for (int i = 0; i < 14; ++i)
			tocopy.push_back(14 * i);
		ft::vector<int> wap;
		wap.assign(5, 69);
		print_container_content(wap, "after the first assign, wapwap");
		wap.assign(tocopy.begin(), tocopy.end());
		print_container_content(wap, "and after the second, wapwap");
		while (!(tocopy.empty()))
			tocopy.pop_back();
		print_container_content(wap, "wap");
		ft::vector<int>::iterator it = wap.begin() + 2;
		std::cout << "*it = " << *it << std::endl;
		wap.insert(it, 2, 800);
		it = wap.insert(wap.begin() + 1, 9999);
		std::cout << "returned iterator from insert gives " << *it << std::endl;
		tocopy.insert(tocopy.begin(), wap.begin(), wap.end() - 5);
		print_container_content(wap, "after insert, wap");

		it = tocopy.erase(tocopy.begin());
		std::cout << "erasing returns iterator to " << *it << std::endl;
		print_container_content(tocopy, "after insert and erasing, tocopy");
		it = tocopy.erase(tocopy.begin(), tocopy.begin() + 6);
		std::cout << "erasing returns iterator to " << *it << std::endl;

		print_container_content(tocopy, "after insert and erasing, tocopy");

	}





	{
		std::cout << "=====Relational operators test=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::vector<int>	a;
		std::vector<int>	b;
		for (int i = 0; i < 8; i++) {
			a.push_back(i);
			b.push_back(i);
		}
		std::cout << "this one should return 1: " << (a == b) << ", and this one 0: " << (a != b) << std::endl;
		std::cout << (a < b) << " " << (b < a) << " " << (a <= b) << " " << (b <= a) << std::endl;
		a.push_back(0);
		b.push_back(5);
		std::cout << "now vice versa, should return 0: " << (a == b) << ", and this one 1: " << (a != b) << std::endl;
		std::cout << (a < b) << " " << (b < a) << " " << (a <= b) << " " << (b <= a) << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::vector<int>	a;
		ft::vector<int>	b;
		for (int i = 0; i < 8; i++) {
			a.push_back(i);
			b.push_back(i);
		}
		std::cout << "this one should return 1: " << (a == b) << ", and this one 0: " << (a != b) << std::endl;
		std::cout << (a < b) << " " << (b < a) << " " << (a <= b) << " " << (b <= a) << std::endl;
		a.push_back(0);
		b.push_back(5);
		std::cout << "now vice versa, should return 0: " << (a == b) << ", and this one 1: " << (a != b) << std::endl;
		std::cout << (a < b) << " " << (b < a) << " " << (a <= b) << " " << (b <= a) << std::endl;
	}



	std::cout << "=====================================================" << std::endl;
	std::cout << "========================STACK========================" << std::endl;
	std::cout << "=====================================================" << std::endl;

	{
		{
			std::cout << "STD" << std::endl;
			std::stack<int> MyStack;
			std::cout << MyStack.empty() << std::endl;
			std::cout << MyStack.size() << std::endl;
		}
		std::cout << std::endl;
		{
			std::stack<int> MyStack;
			std::cout << MyStack.empty() << std::endl;
			MyStack.push(88);
			std::cout << MyStack.top() << std::endl;
			MyStack.push(44);
			std::cout << MyStack.top() << std::endl;
			std::cout << MyStack.size() << std::endl;
			MyStack.pop();
			std::cout << MyStack.size() << std::endl;
			std::cout << MyStack.top() << std::endl;
			MyStack.pop();
			std::cout << MyStack.size() << std::endl;
		}
		{
			std::stack<int> MyStack1;
			std::stack<int> MyStack2;

			MyStack1.push(100);
			MyStack1.push(44);

			MyStack2.push(100);
			MyStack2.push(44);

			if (MyStack1 == MyStack2)
				std::cout << "MyStack1 is equal to MyStack2" << std::endl;
			if (MyStack1 < MyStack2)
				std::cout << "MyStack1 is smaller than MyStack2" << std::endl;
			if (MyStack1 <= MyStack2)
				std::cout << "MyStack1 is smaller than or equal to MyStack2" << std::endl;
			if (MyStack1 > MyStack2)
				std::cout << "MyStack1 is larger than MyStack2" << std::endl;
			if (MyStack1 >= MyStack2)
				std::cout << "MyStack1 is larger than or equal to MyStack2" << std::endl;
		}
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;
		{
			ft::stack<int> MyStack;
			std::cout << MyStack.empty() << std::endl;
			std::cout << MyStack.size() << std::endl;
		}
		std::cout << std::endl;
		{
			ft::stack<int> MyStack;
			std::cout << MyStack.empty() << std::endl;
			MyStack.push(88);
			std::cout << MyStack.top() << std::endl;
			MyStack.push(44);
			std::cout << MyStack.top() << std::endl;
			std::cout << MyStack.size() << std::endl;
			MyStack.pop();
			std::cout << MyStack.size() << std::endl;
			std::cout << MyStack.top() << std::endl;
			MyStack.pop();
			std::cout << MyStack.size() << std::endl;
		}
		{
			ft::stack<int> MyStack1;
			ft::stack<int> MyStack2;

			MyStack1.push(100);
			MyStack1.push(44);

			MyStack2.push(100);
			MyStack2.push(44);

			if (MyStack1 == MyStack2)
				std::cout << "MyStack1 is equal to MyStack2" << std::endl;
			if (MyStack1 < MyStack2)
				std::cout << "MyStack1 is smaller than MyStack2" << std::endl;
			if (MyStack1 <= MyStack2)
				std::cout << "MyStack1 is smaller than or equal to MyStack2" << std::endl;
			if (MyStack1 > MyStack2)
				std::cout << "MyStack1 is larger than MyStack2" << std::endl;
			if (MyStack1 >= MyStack2)
				std::cout << "MyStack1 is larger than or equal to MyStack2" << std::endl;
		}
	}


	std::cout << "=====================================================" << std::endl;
	std::cout << "=========================MAP=========================" << std::endl;
	std::cout << "=====================================================" << std::endl;

	{
		std::cout << "=====Constructors and destructors=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string>	mappie;
		mappie.insert(std::make_pair(0, "nul"));
		mappie.insert(std::make_pair(1, "een"));
		mappie.insert(std::make_pair(1, "een-1"));
		mappie.insert(std::make_pair(1, "een-2"));
		mappie.insert(std::make_pair(-1, "min een"));
		mappie.insert(std::make_pair(5, "vijf"));

		mprint_container_content(mappie, "mappie");
		std::map<int, std::string> wappie(mappie);
		wappie.insert(std::make_pair(8, "acht"));
		wappie.insert(std::make_pair(7, "zeven"));
		wappie.insert(std::make_pair(7, "zeven-1"));
		mprint_container_content(wappie, "wappie");
		std::map<int, std::string>::iterator it = wappie.begin();
		for (int i = 0; i < 4; i++)
			++it;
		std::map<int, std::string>	range2(wappie.begin(), it);
		mprint_container_content(range2, "range2");
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string>	mappie;
		mappie.insert(ft::make_pair(0, "nul"));
		mappie.insert(ft::make_pair(1, "een"));
		mappie.insert(ft::make_pair(1, "een-1"));
		mappie.insert(ft::make_pair(1, "een-2"));
		mappie.insert(ft::make_pair(-1, "min een"));
		mappie.insert(ft::make_pair(5, "vijf"));

		mprint_container_content(mappie, "mappie");
		ft::map<int, std::string> wappie(mappie);
		wappie.insert(ft::make_pair(8, "acht"));
		wappie.insert(ft::make_pair(7, "zeven"));
		wappie.insert(ft::make_pair(7, "zeven-1"));
		mprint_container_content(wappie, "wappie");
		ft::map<int, std::string>::iterator it = wappie.begin();
		for (int i = 0; i < 4; i++)
			++it;
		ft::map<int, std::string>	range2(wappie.begin(), it);
		mprint_container_content(range2, "range2");
	}




	{
		std::cout << "=====Iterators=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string>	stl = mgetstlmap();
		std::map<int, std::string>	peer;

		// testing if the container is empty
		if (peer.begin() == peer.end())
			std::cout << "begin is the same as end" << std::endl;
		else std::cout << "begin is NOTTTT the same as end" << std::endl;
		peer.insert(stl.begin(), stl.end());

		std::map<int, std::string>::iterator					it = peer.begin();
		std::map<int, std::string>::reverse_iterator			rit = peer.rbegin();
		std::map<int, std::string>::const_reverse_iterator	crit(rit);				// Just testing if you can convert a regular iterator to a const one
		std::map<int, std::string>::const_iterator 			cit(it);				// Just testing if you can convert a regular iterator to a const one
		std::cout << "it gives: " << it->first << " ===> " << it->second << std::endl;
		std::cout << "cit gives: " << cit->first << " ===> " << cit->second << std::endl;
		std::cout << "rit gives: " << rit->first << " ===> " << rit->second << std::endl;
		std::cout << "crit gives: " << crit->first << " ===> " << crit->second << std::endl;

		// Testing if equal operators work
		if (it == cit)
			std::cout << "equal operator work on regular iterators " << it->first << " and " << cit->first << std::endl;
		if (rit == crit)
			std::cout << "equal operator work on reverse iterators " << rit->first << " and " << crit->first << std::endl;
		++it;
		it++;
		--it;
		it--;
		if (it != peer.end() && cit != peer.end())
			std::cout << "UNequal operator work on regular iterators " << (*it).first << " and " << (*cit).first << std::endl;
		if (rit != peer.rend() && crit != peer.rend())
			std::cout << "UNequal operator work on reverse iterators " << (*rit).first << " and " << (*crit).first << std::endl;
		it->second = "NIEUW";
		//	it->first = 8;
		mprint_container_content(peer);
		std::pair<int, std::string> ret = *it++;
		std::cout << "ret: " << ret.first << " => " << ret.second << std::endl;
		std::cout << " it: " << it->first << " => " << it->second << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string>	stl = getstlmap();
		ft::map<int, std::string>	peer;

		// testing if the container is empty
		if (peer.begin() == peer.end())
			std::cout << "begin is the same as end" << std::endl;
		else std::cout << "begin is NOTTTT the same as end" << std::endl;
		peer.insert(stl.begin(), stl.end());

		ft::map<int, std::string>::iterator					it = peer.begin();
		ft::map<int, std::string>::reverse_iterator			rit = peer.rbegin();
		ft::map<int, std::string>::const_reverse_iterator	crit(rit);				// Just testing if you can convert a regular iterator to a const one
		ft::map<int, std::string>::const_iterator 			cit(it);				// Just testing if you can convert a regular iterator to a const one
		std::cout << "it gives: " << it->first << " ===> " << it->second << std::endl;
		std::cout << "cit gives: " << cit->first << " ===> " << cit->second << std::endl;
		std::cout << "rit gives: " << rit->first << " ===> " << rit->second << std::endl;
		std::cout << "crit gives: " << crit->first << " ===> " << crit->second << std::endl;

		// Testing if equal operators work
		if (it == cit)
			std::cout << "equal operator work on regular iterators " << it->first << " and " << cit->first << std::endl;
		if (rit == crit)
			std::cout << "equal operator work on reverse iterators " << rit->first << " and " << crit->first << std::endl;
		++it;
		it++;
		--it;
		it--;
		if (it != peer.end() && cit != peer.end())
			std::cout << "UNequal operator work on regular iterators " << (*it).first << " and " << (*cit).first << std::endl;
		if (rit != peer.rend() && crit != peer.rend())
			std::cout << "UNequal operator work on reverse iterators " << (*rit).first << " and " << (*crit).first << std::endl;
		it->second = "NIEUW";
		//	it->first = 8;
		mprint_container_content(peer);
		ft::pair<int, std::string> ret = *it++;
		std::cout << "ret: " << ret.first << " => " << ret.second << std::endl;
		std::cout << " it: " << it->first << " => " << it->second << std::endl;
	}




	{
		std::cout << "=====Capacity=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string>	stl = mgetstlmap();
		std::map<int, std::string>	mymap(stl.begin(), stl.end());
		std::cout << std::boolalpha << "mymap.empty() returns " << mymap.empty() << std::endl;
		std::cout << "mymap.size() returns " << mymap.size() << std::endl;
		// std::cout << "mymap.max_size() returns " << mymap.max_size() << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string>	stl = getstlmap();
		ft::map<int, std::string>	mymap(stl.begin(), stl.end());
		std::cout << std::boolalpha << "mymap.empty() returns " << mymap.empty() << std::endl;
		std::cout << "mymap.size() returns " << mymap.size() << std::endl;
		// std::cout << "mymap.max_size() returns " << mymap.max_size() << std::endl;
	}



	{
		std::cout << "=====Element access=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string> in = mgetstlmap();
		mprint_container_content(in);
		try {
			std::cout << "in.at(6) gives: " << in.at(6) << std::endl;
			std::cout << "in.at(5) gives: " << in.at(5) << std::endl;
		}
		catch (std::out_of_range& e) {
			std::cout << "exception thrown" << std::endl;
			// std::cerr << e.what() << std::endl;
		}
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string> in = getstlmap();
		mprint_container_content(in);
		try {
			std::cout << "in.at(6) gives: " << in.at(6) << std::endl;
			std::cout << "in.at(5) gives: " << in.at(5) << std::endl;
		}
		catch (std::out_of_range& e) {
			std::cout << "exception thrown" << std::endl;
			// std::cerr << e.what() << std::endl;
		}
	}



	{
		std::cout << "=====Modifiers=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string> mymap = mgetstlmap();
		mymap.insert(std::make_pair(12, "twaalf"));
		mymap.insert(std::make_pair(12, "twaalf"));
		mymap.insert(mymap.find(7), std::make_pair(2, "negen"));
		//	 mymap.printBT();

		mymap.erase(1);
		mymap.erase(13);
		// //	 mymap.printBT();
		mymap.erase(mymap.find(4));
		mymap.erase(7);
		for (std::map<int, std::string>::iterator it = mymap.begin(); it != mymap.end(); it++) {
			std::cout << "it: " << it->first << " ==> " << it->second << std::endl;
		}
		std::map<int, std::string> emptymap;
		emptymap.swap(mymap);
		mprint_container_content(mymap);
		mprint_container_content(emptymap);
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string> mymap = getstlmap();
		mymap.insert(ft::make_pair(12, "twaalf"));
		mymap.insert(ft::make_pair(12, "twaalf"));
		mymap.insert(mymap.find(7), ft::make_pair(2, "negen"));
		//	 mymap.printBT();

		mymap.erase(1);
		mymap.erase(13);
		// //	 mymap.printBT();
		mymap.erase(mymap.find(4));
		mymap.erase(7);
		for (ft::map<int, std::string>::iterator it = mymap.begin(); it != mymap.end(); it++) {
			std::cout << "it: " << it->first << " ==> " << it->second << std::endl;
		}
		ft::map<int, std::string> emptymap;
		emptymap.swap(mymap);
		mprint_container_content(mymap);
		mprint_container_content(emptymap);
	}





	{
		std::cout << "=====Operations=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string> mymap = mgetstlmap();
		mprint_container_content(mymap);
		std::map<int, std::string>::iterator it = mymap.find(4);
		if (it == mymap.end())
			std::cout << "element not found!" << std::endl;
		else std::cout << it->first << " => " << it->second << std::endl;
		std::cout << "i have " << mymap.count(1) << " elements with key = 1" << std::endl;
		std::cout << "i have " << mymap.count(2) << " elements with key = 2" << std::endl;
		std::cout << "i have " << mymap.count(3) << " elements with key = 3" << std::endl;

		it = mymap.lower_bound(6);
		std::cout << "lower bound of 6 returns: " << it->first << std::endl;
		it = mymap.upper_bound(6);
		std::cout << "upper bound of 6 returns: " << it->first << std::endl;
		it = mymap.upper_bound(14);
		if (it != mymap.end())
			std::cout << "upper bound of 14 returns: " << it->first << std::endl;
		std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> peer \
			= mymap.equal_range(10);
		std::cout << "mymap.equal_range(10) gives a range from " << peer.first->first << " to " << peer.second->first << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string> mymap = getstlmap();
		mprint_container_content(mymap);
		ft::map<int, std::string>::iterator it = mymap.find(4);
		if (it == mymap.end())
			std::cout << "element not found!" << std::endl;
		else std::cout << it->first << " => " << it->second << std::endl;
		std::cout << "i have " << mymap.count(1) << " elements with key = 1" << std::endl;
		std::cout << "i have " << mymap.count(2) << " elements with key = 2" << std::endl;
		std::cout << "i have " << mymap.count(3) << " elements with key = 3" << std::endl;

		it = mymap.lower_bound(6);
		std::cout << "lower bound of 6 returns: " << it->first << std::endl;
		it = mymap.upper_bound(6);
		std::cout << "upper bound of 6 returns: " << it->first << std::endl;
		it = mymap.upper_bound(14);
		if (it != mymap.end())
			std::cout << "upper bound of 14 returns: " << it->first << std::endl;
		ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> peer \
			= mymap.equal_range(10);
		std::cout << "mymap.equal_range(10) gives a range from " << peer.first->first << " to " << peer.second->first << std::endl;
	}



	{
		std::cout << "=====Observers=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, int>	mymap;
		std::map<int, int>	othermap;
		for (size_t i = 0; i < 20; i++) {
			mymap[i * 2] = i * 4;
			othermap[i * 3] = i * 6;
		}
		compare_keys(mymap, 18);
		compare_keys(othermap, 29);
		compare_values(mymap, std::make_pair(18, 45));
		compare_values(othermap, std::make_pair(29, 76));
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, int>	mymap;
		ft::map<int, int>	othermap;
		for (size_t i = 0; i < 20; i++) {
			mymap[i * 2] = i * 4;
			othermap[i * 3] = i * 6;
		}
		compare_keys(mymap, 18);
		compare_keys(othermap, 29);
		compare_values(mymap, ft::make_pair(18, 45));
		compare_values(othermap, ft::make_pair(29, 76));
	}






	{
		std::cout << "=====Telly=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(10, 353));
			MyMap.insert(std::make_pair(100, 4543));
			MyMap.insert(std::make_pair(1000, 34534));
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> Range;
			Range.insert(std::make_pair(10, 99));
			Range.insert(std::make_pair(100, 999));
			Range.insert(std::make_pair(1000, 9999));
			std::map<int, int> MyMap(Range.begin(), Range.end());
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> Range;
			Range.insert(std::make_pair(1, 80));
			Range.insert(std::make_pair(-10, 57758));
			Range.insert(std::make_pair(89, 34));
			std::cout << "distance: " << std::distance(Range.begin(), Range.end()) << std::endl;
			std::map<int, int> MyMap(Range.begin(), Range.end());
			std::cout << "haha" << std::endl;
			std::map<int, int>::iterator it = --MyMap.end();
			std::cout << "it: " << it->first << " => " << it->second << std::endl;
			std::map<int, int>::iterator result = MyMap.insert(it, std::make_pair(-666, 33333));
			std::cout << result->first << " => " << result->second << std::endl;
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << "for:\t" << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(-10, 57758));
			MyMap.insert(std::make_pair(89, 34));
			std::map<int, int>::iterator result = MyMap.find(89);
			std::cout << result->first << " => " << result->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(-10, 57758));
			MyMap.insert(std::make_pair(89, 34));
			std::cout << (MyMap.lower_bound(2))->first << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(-10, 57758));
			MyMap.insert(std::make_pair(89, 34));
			std::cout << (MyMap.lower_bound(88))->first << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(-10, 57758));
			MyMap.insert(std::make_pair(89, 34));
			std::cout << (MyMap.equal_range(-5)).first->first << " --- " << (MyMap.equal_range(2)).second->first << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(100, 34));
			std::cout << MyMap[10] << std::endl;
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(100, 34));
			MyMap[10] = 99;
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(100, 34));
			MyMap[1000] = 99;
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}

		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.erase(MyMap.begin());
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(100, 34));
			MyMap.erase(MyMap.begin());
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(100, 34));
			MyMap.erase(10);
			for (std::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		{
			std::map<int, int> MyMap1;
			MyMap1.insert(std::make_pair(10, 57758));
			MyMap1.insert(std::make_pair(1, 80));
			MyMap1.insert(std::make_pair(100, 34));


			std::map<int, int> MyMap2;
			MyMap2.insert(std::make_pair(10, 57758));
			MyMap2.insert(std::make_pair(1, 80));
			MyMap2.insert(std::make_pair(100, 34));

			if (MyMap1 == MyMap2)
				std::cout << "MyMap1 is equal to MyMap2" << std::endl;
			if (MyMap1 < MyMap2)
				std::cout << "MyMap1 is smaller than MyMap2" << std::endl;
			if (MyMap1 <= MyMap2)
				std::cout << "MyMap1 is smaller than or equal to MyMap2" << std::endl;
			if (MyMap1 > MyMap2)
				std::cout << "MyMap1 is larger than MyMap2" << std::endl;
			if (MyMap1 >= MyMap2)
				std::cout << "MyMap1 is larger than or equal to MyMap2" << std::endl;
			MyMap1.swap(MyMap2);
			if (MyMap1 < MyMap2)
				std::cout << "MyMap1 is smaller than MyMap2" << std::endl;
			if (MyMap1 <= MyMap2)
				std::cout << "MyMap1 is smaller than or equal to MyMap2" << std::endl;
			if (MyMap1 > MyMap2)
				std::cout << "MyMap1 is larger than MyMap2" << std::endl;
			if (MyMap1 >= MyMap2)
				std::cout << "MyMap1 is larger than or equal to MyMap2" << std::endl;
		}
		{
			std::map<int, int> MyMap;
			MyMap.insert(std::make_pair(10, 57758));
			MyMap.insert(std::make_pair(1, 80));
			MyMap.insert(std::make_pair(100, 34));

			for (std::map<int, int>::reverse_iterator rit = MyMap.rbegin(); rit != MyMap.rend(); rit++)
				std::cout << rit->first << " => " << rit->second << std::endl;

			for (std::map<int, int>::reverse_iterator rit = MyMap.rbegin(); rit != MyMap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << std::endl;
		}
	}
	std::cout << "---------------" << std::endl;
	{
		std::cout << "FT" << std::endl;
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(10, 353));
			MyMap.insert(ft::make_pair(100, 4543));
			MyMap.insert(ft::make_pair(1000, 34534));
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> Range;
			Range.insert(ft::make_pair(10, 99));
			Range.insert(ft::make_pair(100, 999));
			Range.insert(ft::make_pair(1000, 9999));
			ft::map<int, int> MyMap(Range.begin(), Range.end());
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> Range;
			Range.insert(ft::make_pair(1, 80));
			Range.insert(ft::make_pair(-10, 57758));
			Range.insert(ft::make_pair(89, 34));
			std::cout << "distance: " << std::distance(Range.begin(), Range.end()) << std::endl;
			ft::map<int, int> MyMap(Range.begin(), Range.end());
			std::cout << "haha" << std::endl;
			ft::map<int, int>::iterator it = --MyMap.end();
			std::cout << "it: " << it->first << " => " << it->second << std::endl;
			ft::map<int, int>::iterator result = MyMap.insert(it, ft::make_pair(-666, 33333));
			std::cout << result->first << " => " << result->second << std::endl;
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << "for:\t" << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(-10, 57758));
			MyMap.insert(ft::make_pair(89, 34));
			ft::map<int, int>::iterator result = MyMap.find(89);
			std::cout << result->first << " => " << result->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(-10, 57758));
			MyMap.insert(ft::make_pair(89, 34));
			std::cout << (MyMap.lower_bound(2))->first << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(-10, 57758));
			MyMap.insert(ft::make_pair(89, 34));
			std::cout << (MyMap.lower_bound(88))->first << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(-10, 57758));
			MyMap.insert(ft::make_pair(89, 34));
			std::cout << (MyMap.equal_range(-5)).first->first << " --- " << (MyMap.equal_range(2)).second->first << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(100, 34));
			std::cout << MyMap[10] << std::endl;
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(100, 34));
			MyMap[10] = 99;
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(100, 34));
			MyMap[1000] = 99;
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}

		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.erase(MyMap.begin());
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(100, 34));
			MyMap.erase(MyMap.begin());
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << std::endl;
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(100, 34));
			MyMap.erase(10);
			for (ft::map<int, int>::iterator it = MyMap.begin(); it != MyMap.end(); it++)
				std::cout << it->first << " => " << it->second << std::endl;
		}
		{
			ft::map<int, int> MyMap1;
			MyMap1.insert(ft::make_pair(10, 57758));
			MyMap1.insert(ft::make_pair(1, 80));
			MyMap1.insert(ft::make_pair(100, 34));


			ft::map<int, int> MyMap2;
			MyMap2.insert(ft::make_pair(10, 57758));
			MyMap2.insert(ft::make_pair(1, 80));
			MyMap2.insert(ft::make_pair(100, 34));

			if (MyMap1 == MyMap2)
				std::cout << "MyMap1 is equal to MyMap2" << std::endl;
			if (MyMap1 < MyMap2)
				std::cout << "MyMap1 is smaller than MyMap2" << std::endl;
			if (MyMap1 <= MyMap2)
				std::cout << "MyMap1 is smaller than or equal to MyMap2" << std::endl;
			if (MyMap1 > MyMap2)
				std::cout << "MyMap1 is larger than MyMap2" << std::endl;
			if (MyMap1 >= MyMap2)
				std::cout << "MyMap1 is larger than or equal to MyMap2" << std::endl;
			MyMap1.swap(MyMap2);
			if (MyMap1 < MyMap2)
				std::cout << "MyMap1 is smaller than MyMap2" << std::endl;
			if (MyMap1 <= MyMap2)
				std::cout << "MyMap1 is smaller than or equal to MyMap2" << std::endl;
			if (MyMap1 > MyMap2)
				std::cout << "MyMap1 is larger than MyMap2" << std::endl;
			if (MyMap1 >= MyMap2)
				std::cout << "MyMap1 is larger than or equal to MyMap2" << std::endl;
		}
		{
			ft::map<int, int> MyMap;
			MyMap.insert(ft::make_pair(10, 57758));
			MyMap.insert(ft::make_pair(1, 80));
			MyMap.insert(ft::make_pair(100, 34));

			for (ft::map<int, int>::reverse_iterator rit = MyMap.rbegin(); rit != MyMap.rend(); rit++)
				std::cout << rit->first << " => " << rit->second << std::endl;

			for (ft::map<int, int>::reverse_iterator rit = MyMap.rbegin(); rit != MyMap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << std::endl;
		}
	}




	{
		std::cout << "=====Conversion of iterators=====" << std::endl;
		std::cout << "STD" << std::endl;

		std::map<int, std::string> hats = mgetstlmap();
		std::map<int, std::string>::iterator it = hats.begin();
		std::map<int, std::string>::const_iterator cit = it;
		(void)cit;
	}
	std::cout << "----------------" << std::endl;
	{
		std::cout << "FT" << std::endl;

		ft::map<int, std::string> hats = getstlmap();
		ft::map<int, std::string>::iterator it = hats.begin();
		ft::map<int, std::string>::const_iterator cit = it;
		(void)cit;
	}

}
