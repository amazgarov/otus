#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "print_ip.h"

using namespace std;

int main()
{
	cout << "char(-1) -> ";
	print_ip(char(-1));
	cout << endl;

	cout << "short(0) -> ";
	print_ip(short(0));
	cout << endl;

	cout << "int(2130706433) -> ";
	print_ip(int(2130706433));
	cout << endl;

	cout << "long(8875824491850138409) -> ";
	print_ip(long(8875824491850138409));
	cout << endl;

	cout << "std::string{\"Some IP string: 207.46.170\"} -> ";
	print_ip(string{"Some IP string: 207.46.170"});
	cout << endl;

	cout << "std::vector{209,85,231,104,57,23} -> ";
	vector<int> ip_as_vector{209, 85, 231, 104, 57, 23};
	print_ip(ip_as_vector);
	cout << endl;

	cout << "std::list{66,220,149,25} -> ";
	list<int> ip_as_list{66, 220, 149, 25};
	print_ip(ip_as_list);
	cout << endl;

	cout << "std::tuple<int, int, int>{66,220,149} -> ";
	tuple<int, int, int> ip_as_tuple{66, 220, 149};
	print_ip(ip_as_tuple);
	cout << endl;

	// this call throws error
	cout << "std::tuple<int, int, long>{66,220,149} -> ";
	tuple<int, int, long> ip_as_tuple_heterogeneous{66, 220, 149L};
	print_ip(ip_as_tuple_heterogeneous);
	cout << endl;

	return 0;
}