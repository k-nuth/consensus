# Bitprim Consensus <a target="_blank" href="http://semver.org">![Version][badge.version]</a> <a target="_blank" href="https://travis-ci.org/bitprim/bitprim-consensus">![Travis status][badge.Travis]</a> <a target="_blank" href="https://ci.appveyor.com/project/bitprim/bitprim-consensus">![Appveyor status][badge.Appveyor]</a> <a target="_blank" href="https://gitter.im/bitprim/Lobby">![Gitter Chat][badge.Gitter]</a>

> Cryptocurrencies consensus library


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

This library includes the following 33 files considered to be bitcoin script consensus-critical. These files are identical to those used in version 0.15.0 of bitcoin core.

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


<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-consensus?svg=true&branch=dev
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/bitprim/bitprim-consensus.svg?branch=master
[badge.version]: https://badge.fury.io/gh/bitprim%2Fbitprim-consensus.svg

