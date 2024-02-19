# README

## 生成指南

左程云老师用的是 java，但是我自己主要用的是 C++，
C++ 需要手动管理内存，那么在 fedora 下，如何检测内存是否泄露呢？

```cxx
[parallels@fedora day2]$ clang++ -fsanitize=address p4.cxx
[parallels@fedora day2]$ ./a.out
这是2来到的时候
这是1来到的时候
A B
C D E F G H
I
J
K L M
[parallels@fedora day2]$ clang++ -fsanitize=address p4.cxx
[parallels@fedora day2]$ ./a.out
这是2来到的时候
这是1来到的时候
A B
C D E F G H
I
J
K L M

=================================================================
==477242==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 40 byte(s) in 1 object(s) allocated from:
    #0 0x5060c8 in operator new(unsigned long) (/media/psf/Home/DOCs/cpp/algorithm/day2/a.out+0x5060c8) (BuildId: 3760465b4e44fb33f95a6138e44bd0d62bea14e8)
    #1 0x5096f8 in MessageBox::receive(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (/media/psf/Home/DOCs/cpp/algorithm/day2/a.out+0x5096f8) (BuildId: 3760465b4e44fb33f95a6138e44bd0d62bea14e8)
    #2 0x508c94 in main (/media/psf/Home/DOCs/cpp/algorithm/day2/a.out+0x508c94) (BuildId: 3760465b4e44fb33f95a6138e44bd0d62bea14e8)
    #3 0xffffb57a73c4 in __libc_start_call_main (/lib64/libc.so.6+0x273c4) (BuildId: d2e45a840f9c68ef93f1f9d0377eaf36068504eb)
    #4 0xffffb57a749c in __libc_start_main@GLIBC_2.17 (/lib64/libc.so.6+0x2749c) (BuildId: d2e45a840f9c68ef93f1f9d0377eaf36068504eb)
    #5 0x428cac in _start (/media/psf/Home/DOCs/cpp/algorithm/day2/a.out+0x428cac) (BuildId: 3760465b4e44fb33f95a6138e44bd0d62bea14e8)

Direct leak of 40 byte(s) in 1 object(s) allocated from:
    #0 0x5060c8 in operator new(unsigned long) (/media/psf/Home/DOCs/cpp/algorithm/day2/a.out+0x5060c8) (BuildId: 3760465b4e44fb33f95a6138e44bd0d62bea14e8)
    #1 0x5096f8 in MessageBox::receive(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (/media/psf/Home/DOCs/cpp/

	...
SUMMARY: AddressSanitizer: 520 byte(s) leaked in 13 allocation(s).
[parallels@fedora day2]$
```
