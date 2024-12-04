#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
using namespace std;

#define deb(...) deb_impl(#__VA_ARGS__, __VA_ARGS__)

template <typename T, typename... Args>
void deb_impl(const char *names, T &&arg, Args &&...args) {
    const char *comma = strchr(names, ',');
    cout.write(names, comma ? comma - names : strlen(names)) << " = " << arg;
    if constexpr (sizeof...(args) > 0) {
        cout << ", ";
        deb_impl(comma + 1, std::forward<Args>(args)...);
    } else {
        cout << endl;
    }
}

// Overload for std::pair
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

// Overload for containers
template <typename T_container,
          typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    set<string> str_set = {"apple", "banana", "cherry"};
    map<int, string> num_map = {{1, "one"}, {2, "two"}, {3, "three"}};
    pair<int, string> my_pair = {42, "answer"};

    // Debugging simple and complex data structures
    deb(vec);          // Prints: vec = {1, 2, 3, 4, 5}
    deb(str_set);      // Prints: str_set = {apple, banana, cherry}
    deb(num_map);      // Prints: num_map = {(1, one), (2, two), (3, three)}
    deb(my_pair);      // Prints: my_pair = (42, answer)


    // Debugging multiple variables
    int x = 10, y = 20;
    string greeting = "hello";
    deb(x, y, greeting);  // Prints: x = 10, y = 20, greeting = hello

    return 0;
}
