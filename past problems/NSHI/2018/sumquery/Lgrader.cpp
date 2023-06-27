#include <iostream>
#include "sumquery.h"

int main() {
	unsigned q;
	std::cin >> q;
	init(q);
	for (unsigned i = 0;i < q;i++) {
		unsigned t;
		unsigned long long x;
		std::cin >> t >> x;
		switch (t) {
			case 1: add_number(x); break;
			case 2: remove_number(x); break;
			case 3: 
				unsigned long long r;
				std::cin >> r;
				std::cout << sum_query(x, r) << "\n"; break;
			default: std::cerr << "ERROR: Invalid query type t = " << t << "\n"; break;
		}
	}
}
