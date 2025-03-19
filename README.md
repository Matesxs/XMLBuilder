# XML Builder library for C++

## Note

This library is still in development so lot of things may change.

## About XML Builder Library

This library is designed to simplify the process of generating XML documents programmatically. The primary motivation behind creating this library stems from the observation that many existing XML generation tools or libraries can be overly complex, difficult to integrate, or lack flexibility for developers who need a easy-to-use solution.

### Key Motivations:
- **Simplicity**: Many existing XML generators are either too verbose or require extensive setup. This library aims to provide a straightforward and intuitive interface.
- **Header-Only Design**: The library is designed as a single header file, making it easy to integrate into projects without the need for complex build configurations or dependencies.
- **Flexibility**: Whether you're building a small script or integrating XML generation into a larger application, this library provides the tools you need.

### Why Create This Library?

The absence of a simple, lightweight, and header-only solution inspired me to create this XML builder library. My goal was to create simple library for my projects that don't need extensive setup and is ready to use with friendly interface.

## Features

- Single header file
- Use with any build system
- [Documentation](https://matesxs.github.io/XMLBuilder/)

## Limitations

- Use of modern C++ standard C++20
- No XML check, only check done is on repeating attribute names

## Repository structure

- **include** folder contains the library itself, feel free to include it in your project
- **tests** folder contains tests of functionality of the library

## Support

Currently there are no official example, FAQ or anything like that. If you want examples of usage you can refer to tests. In **special_tests.cpp** there is example of real life usage of the library. If you want to explore the library you can go directly to the source code in **include** folder and read through the code. It's documented by doxygen comments and if you find any mistake feel free to report it in issues or create PR yourself. If you are more into web page documentation then there is hosted version of the doxygen documentation on [Documentation](https://matesxs.github.io/XMLBuilder/).
