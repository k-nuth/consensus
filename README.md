[![Build Status](https://travis-ci.org/bitprim/bitprim-consensus.svg?branch=master)](https://travis-ci.org/bitprim/bitprim-consensus)

# Bitprim Consensus

*Bitcoin consensus library*

## Installation

```sh
$ ./autogen.sh
$ ./configure
$ make
$ sudo make install
$ sudo ldconfig
```

`bitprim-consensus` is now installed in `/usr/local/`.

## Dependencies

This library has no dependencies, although the test cases have a boost dependency.

## Configure Options

There is a dependency on [boost test](http://www.boost.org/doc/libs/1_50_0/libs/test/doc/html/index.html) for `make check` builds (tests). The `--without-tests` option disables test builds and eliminates the boost check during configure.

## Supported Platforms

**Ubuntu** (gcc and clang) and **OSX** (clang) are regularly tested via a [travis build matrix](https://travis-ci.org/libbitcoin/libbitcoin-consensus). There is also a Visual Studio 2013 solution for **Windows** builds (vc12). Unlike other bitprim libraries, consensus does not require a c++11 compiler.

## Language Bindings

Java and python bindings are automatically generated by maintainers using [SWIG](http://www.swig.org). To compile and install these bindings use the `--with-java` and `--with-python` options respectively.

The java option installs the jar file `org.libbitcoin.consensus-${VERSION}.jar`and the library `bitcoin-consensus-jni`. The python option installs the python file `consensus.py` and the library `_bitcoin-consensus`.

# About

This library includes the following 33 files considered to be bitcoin script consensus-critical. These files are identical to those used in version 0.12.0 of bitcoin-core.

```
amount.h
hash.cpp
hash.h
prevector.h
pubkey.cpp
pubkey.h
serialize.h
tinyformat.h
uint256.cpp
uint256.h
utilstrencodings.cpp
utilstrencodings.h
version.h
compat/byteswap.h
compat/endian.h
crypto/common.h
crypto/hmac_sha512.cpp
crypto/hmac_sha512.h
crypto/ripemd160.cpp
crypto/ripemd160.h
crypto/sha1.cpp
crypto/sha1.h
crypto/sha256.cpp
crypto/sha256.h
crypto/sha512.cpp
crypto/sha512.h
primitives/transaction.cpp
primitives/transaction.h
script/interpreter.cpp
script/interpreter.h
script/script.cpp
script/script.h
script/script_error.h
```

# Bitprim Integration

Bitprim natively implements consensus checks that are redundant with `bitprim-consensus`. Bitprim includes a full bitcoin client and server SDK. This includes the full node implementation [bitprim-node](https://github.com/bitprim/bitprim-node), which builds on [bitprim-core](https://github.com/bitprim/bitprim-core) and [bitprim-blockchain](https://github.com/bitprim/bitprim-blockchain).

The `bitprim-blockchain` configuration provides the `--with-consensus` option. This allows the developer to select either `bitprim-core` native or `bitprim-consensus` checks. The option defaults to `yes` so that by default all `bitprim-node` and `bitprim-server` builds use the same consensus checks as a Satoshi node.
