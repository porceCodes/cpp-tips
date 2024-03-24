# Q. Does it automatically zero-initialized?

## No
```
struct A { int x; };
struct B { int x; B() = default; };
A a;
B b;
```

## Yes
```
struct A { int x; };
struct B { int x; B() = default; };
A a{}; auto a = A(); auto a = A{};
B b{}; auto b = B(); auto b = B{};
```

## Compiler
```
> clang++ --version
Apple clang version 15.0.0 (clang-1500.3.9.4)
Target: arm64-apple-darwin23.4.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

## Standard library
```
> grep " _LIBCPP_VERSION " $(xcrun --show-sdk-path)/usr/include/c++/v1/__config | grep -v "LLVM" | cut -f5 -d' '
170006
```

## How to run, and a sample results
```
> clang++ --std=c++20 init.cc; ./a.out
[counts] a1:10000 a2:-- a3:0 a4:0 a5:0
[counts] b1:10000 b2:-- b3:0 b4:0 b5:0
```


## References
* [Stack overflow QnA](https://stackoverflow.com/questions/2417065/does-the-default-constructor-initialize-built-in-types)
* [r/programming](https://www.reddit.com/r/programming/comments/akn5jx/initialization_in_c_is_seriously_bonkers/)
* [P2723R1 for C++26](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2723r1.html), blocked by [P2795 R4](https://github.com/cplusplus/papers/issues/1460) as of Mar 24 2024
* ISO/IEC 14882:2020(E) Section 9.4.1.8
```
8 To value-initialize an object of type T means:
—
(8.1) if T is a (possibly cv-qualified) class type (Clause 11), then
—
(8.1.1) if T has either no default constructor (11.4.5.2) or a default constructor that is user-provided or
deleted, then the object is default-initialized;
—
(8.1.2) otherwise, the object is zero-initialized and the semantic constraints for default-initialization are
checked, and if T has a non-trivial default constructor, the object is default-initialized;
—
(8.2) if T is an array type, then each element is value-initialized;
—
(8.3) otherwise, the object is zero-initialized.
9 A program that calls for default-initialization or value-initialization of an entity of reference type is ill-formed.
10 [Note 4: For every object of static storage duration, static initialization (6.9.3.2) is performed at program startup
before any other initialization takes place. In some cases, additional initialization is done later. —end note]
11 An object whose initializer is an empty set of parentheses, i.e., (), shall be value-initialized.
[Note 5: Since () is not permitted by the syntax for initializer,
X a();
is not the declaration of an object of class X, but the declaration of a function taking no argument and returning an X.
The form () is permitted in certain other initialization contexts (7.6.2.8, 7.6.1.4, 11.10.3). —end note]
```
