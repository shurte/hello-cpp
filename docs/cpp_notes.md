# Language facilities
## Basics
### Types
```cpp
int 
double
float
char
bool
short
long
signed
unsigned
```
### Pointers, arrays, structures
#### Pointers
```cpp
new 
delete
```
### Expressions & operators
Operators:
- `+, -, *, /, %, +=, -=. *=, /=, %=, ++, --`  
- `==, !=, >, <, >=, <=`
- `!, &&, ||`

Expressions:  
- `if - else if - else`;
- `switch - case - break - default`;  
- `while - do - break - continue`;
- `for - break - continue`;
### Functions
### Namespaces & exceptions
* RAII - Resource Acquisition Is Initialization
* Basic guarantee, strong guarantee and no-throw guarantee
#### Exceptions
```cpp
std::exception
try {
} catch (std::exception& exception) {
}
std::nothrow
```

### Compilation & linkage
&nbsp;

## Abstractions
### Classes definition
```cpp
class
struct
public 
private
const 
mutable
static
```
### Overloading
### Inheritance
### Templates
### Exceptions in classes
### RTTI

&nbsp;

# Standard library
## Input/output  
## Data & algorithms
### Containers
```cpp
#include <vector>
std::vector<int> int_vector;
int_vector.push_back(10);
std::vector<int>::iterator it = int_vector.begin();
int_vector.insert(int_vector.begin(), 23);
int_vector.erase(int_vector.begin() + 1);
```
```cpp
deque
list
map
multimap
multiset
priority_queue
queue
set
stack
```
### Iterators
### Allocators
### Strings
```cpp
std::string str{"Some text."};
str.size();
str[0];
```
### Algorithms
```cpp
#include <algorithm>
```
### Maths

## Concurrency
&nbsp;

# Conferences
### CppCon 2016 
### David Sankel “Building Software Capital: How to write the highest quality code and why"

#### Principle #1 Code Review  
  How does it organized in the company?
#### Principle #2 Standards  
  Are the standards defined in the company?
#### Principle #3 Unit Testing  
#### Principle #4 Contracts  
  It means clear contracts between a user and an application. Not implementation.
#### Principle #5 Good Interfaces - Organization  
  Components / Packages / Package Groups; Naming
#### Principle #6 Innovation  
#### Principle #7 Infrastructure  
  Version control / CI/CD / Build System / Libraries

&nbsp;

# Book "Elements of programming interviews in C++"
### 1 Primitive Types
#### What to know
* types and properties, size, ranges, signedness;
* basic operators with types, including bitwise operators;
* using masks and create them in a machine independent way;
* fast way to clear the lowermost set bit, get the index etc.;
* signedness and its implications to shifting;
* possibility to parallel and reorder operations;
* comparing floating point values;
#### Library
```cpp
#include "limits"
numeric_limits<int>::min();
numeric_limits<float>::max();
numeric_limits<double>::infinity();
```
```cpp
#include <cmath>
abs(-34.3);
fabs(-34.3);
ceil(-34.3);
floor(-34.3);
min(-34.3, z);
max(-34.3, z);
pow(-34.3, z);
log(34.3);
sqrt(225);
```
* convertion from char to int, from string to number and vice versa:
```cpp
to_string(30);
stoi("42");
```
```cpp
#include <random>
std::random_device rd;
std::mt19937 generator(rd);
auto randomDistribution = std::uniform_int_distribution<int>(1, 10);
int randomValue = randomDistribution(generator);
```
```cpp
swap(x, y);
```

### Links

- [C++ Standard](https://isocpp.org/)  
- [C++ Reference](https://en.cppreference.com/w/)  
- [C++ reddit](https://www.reddit.com/r/cpp/)  
- [Leanpub](https://leanpub.com/)  
- [C++ Draft Standard](https://eel.is/c++draft/)  
- [Compiler Explorer](https://compiler-explorer.com/)  
- [C++ Insights](https://cppinsights.io/)  
