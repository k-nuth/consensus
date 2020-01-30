# Knuth Consensus <a target="_blank" href="http://semver.org">![Version][badge.version]</a> <a target="_blank" href="https://travis-ci.org/k-nuth/consensus">![Travis status][badge.Travis]</a> <a target="_blank" href="https://ci.appveyor.com/project/k-nuth/consensus">![Appveyor status][badge.Appveyor]</a> <a target="_blank" href="https://gitter.im/k-nuth/Lobby">![Gitter Chat][badge.Gitter]</a>

> Cryptocurrencies consensus library


## Installation
Make sure you have installed [domain](https://github.com/k-nuth/domain) beforehand according to its respective build instructions.

```
$ git clone https://github.com/k-nuth/consensus.git
$ cd consensus
$ mkdir build
$ cd build
$ cmake .. -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11"
$ make -j2
$ sudo make install
```

`consensus` is now installed in `/usr/local/`.

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

# Knuth Integration

Knuth natively implements consensus checks that are redundant with `consensus`. Knuth includes a full bitcoin client and server SDK. This includes the full node implementation [node](https://github.com/k-nuth/node), which builds on [domain](https://github.com/k-nuth/domain) and [blockchain](https://github.com/k-nuth/blockchain).

The `blockchain` configuration provides the `--with-consensus` option. This allows the developer to select either `domain` native or `consensus` checks. The option defaults to `yes` so that by default all `node` and `server` builds use the same consensus checks as a Satoshi node.


<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/github/k-nuth/consensus?svg=true&branch=dev
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/k-nuth/consensus.svg?branch=master
[badge.version]: https://badge.fury.io/gh/k-nuth%2Fconsensus.svg

