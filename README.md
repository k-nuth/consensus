# Bitprim Consensus

*Bitcoin consensus library*

| **master(linux/osx)** | **conan-build-win(linux/osx)**   | **master(windows)**   | **conan-build-win(windows)** |
|:------:|:-:|:-:|:-:|
| [![Build Status](https://travis-ci.org/bitprim/bitprim-consensus.svg)](https://travis-ci.org/bitprim/bitprim-consensus)       | [![Build StatusB](https://travis-ci.org/bitprim/bitprim-consensus.svg?branch=conan-build-win)](https://travis-ci.org/bitprim/bitprim-consensus?branch=conan-build-win)  | [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-consensus?svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-consensus)  | [![Appveyor StatusB](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-consensus?branch=conan-build-win&svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-consensus?branch=conan-build-win)  |

## Installation
Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core) beforehand according to its respective build instructions.

```
$ git clone https://github.com/bitprim/bitprim-consensus.git
$ cd bitprim-consensus
$ mkdir build
$ cd build
$ cmake .. -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11"
$ make -j2
$ sudo make install
```

`bitprim-consensus` is now installed in `/usr/local/`.

# About

This library includes the following 33 files considered to be bitcoin script consensus-critical. These files are identical to those used in version 0.13.2 of bitcoin-core.

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
