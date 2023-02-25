# Copyright (c) 2016-2023 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 3.23)

project(kth-consensus VERSION 0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++14 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Implement --use-conan
#------------------------------------------------------------------------------
# option(USE_CONAN "Use Conan Build Tool." OFF)
# option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

# if (NO_CONAN_AT_ALL)
#   set(USE_CONAN OFF)
# endif()

# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)

# Process options.
#==============================================================================

# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)


#TODO(fernando): check Legacy for with_java and with_python parameters
# Implement --with-java and declare WITH_JAVA.
#------------------------------------------------------------------------------
option(WITH_JAVA "Compile the Java bindings." OFF)
if (WITH_JAVA)
  message(FATAL_ERROR "WITH_JAVA not yet implemented")
endif()

# Implement --with-python and declare WITH_PYTHON.
#------------------------------------------------------------------------------
option(WITH_PYTHON "Compile the Python bindings." OFF)
if (WITH_PYTHON)
  message(FATAL_ERROR "WITH_PYTHON not yet implemented")
endif()



set(KTH_PROJECT_VERSION "-" CACHE STRING "Specify the Knuth Project Version.")
# message(${KTH_PROJECT_VERSION})
message( STATUS "Knuth: Compiling version ${KTH_PROJECT_VERSION}")

set(MARCH_ID "" CACHE STRING "Specify the Microarchitecture ID (x86_64|...).")
message( STATUS "Knuth: Compiling for Microarchitecture ID ${MARCH_ID}")

message( STATUS "Knuth: CONAN_CXX_FLAGS ${CONAN_CXX_FLAGS}")
message( STATUS "Knuth: CONAN_C_FLAGS ${CONAN_C_FLAGS}")


set(CURRENCY "BCH" CACHE STRING "Specify the Cryptocurrency (BCH|BTC|LTC).")

if (${CURRENCY} STREQUAL "BCH")
  add_definitions(-DKTH_CURRENCY_BCH)
elseif (${CURRENCY} STREQUAL "BTC")
  add_definitions(-DKTH_CURRENCY_BTC)
elseif (${CURRENCY} STREQUAL "LTC")
  add_definitions(-DKTH_CURRENCY_LTC)
else()
  message(FATAL_ERROR "Invalid Cryptocurrency: ${CURRENCY}")
endif()

message(STATUS "Knuth: Cryptocurrency: ${CURRENCY}")


# Set preprocessor defines.
include(CheckIncludeFile)
include(CheckCXXSymbolExists)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)

include(KnuthTools)



#==============================================================================
# Conditionally define the preprocessor symbol HAVE_DECL_BSWAP_16.
#------------------------------------------------------------------------------
_check_has_decl(byteswap.h HAVE_BYTESWAP_H bswap_16 HAVE_DECL_BSWAP_16)

# Conditionally define the preprocessor symbol HAVE_DECL_BSWAP_32.
#------------------------------------------------------------------------------
_check_has_decl(byteswap.h HAVE_BYTESWAP_H bswap_32 HAVE_DECL_BSWAP_32)

# Conditionally define the preprocessor symbol HAVE_DECL_BSWAP_64.
#------------------------------------------------------------------------------
_check_has_decl(byteswap.h HAVE_BYTESWAP_H bswap_64 HAVE_DECL_BSWAP_64)

# Conditionally define the preprocessor symbol HAVE_DECL_LE16TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H le16toh HAVE_DECL_LE16TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_LE32TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H le32toh HAVE_DECL_LE32TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_LE64TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H le64toh HAVE_DECL_LE64TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE16.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htole16 HAVE_DECL_HTOLE16)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE32.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htole32 HAVE_DECL_HTOLE32)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE64.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htole64 HAVE_DECL_HTOLE64)

# Conditionally define the preprocessor symbol HAVE_DECL_BE16TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H be16toh HAVE_DECL_BE16TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_BE32TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H be32toh HAVE_DECL_BE32TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_BE64TOH.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H be64toh HAVE_DECL_BE64TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE16.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htobe16 HAVE_DECL_HTOBE16)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE32.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htobe32 HAVE_DECL_HTOBE32)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE64.
#------------------------------------------------------------------------------
_check_has_decl(endian.h HAVE_ENDIAN_H htobe64 HAVE_DECL_HTOBE64)

# Conditionally define the preprocessor symbol HAVE_DECL_LE16TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H le16toh HAVE_DECL_LE16TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_LE32TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H le32toh HAVE_DECL_LE32TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_LE64TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H le64toh HAVE_DECL_LE64TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE16.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htole16 HAVE_DECL_HTOLE16)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE32.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htole32 HAVE_DECL_HTOLE32)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOLE64.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htole64 HAVE_DECL_HTOLE64)

# Conditionally define the preprocessor symbol HAVE_DECL_BE16TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H be16toh HAVE_DECL_BE16TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_BE32TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H be32toh HAVE_DECL_BE32TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_BE64TOH.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H be64toh HAVE_DECL_BE64TOH)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE16.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htobe16 HAVE_DECL_HTOBE16)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE32.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htobe32 HAVE_DECL_HTOBE32)

# Conditionally define the preprocessor symbol HAVE_DECL_HTOBE64.
#------------------------------------------------------------------------------
_check_has_decl(sys/endian.h HAVE_SYS_ENDIAN_H htobe64 HAVE_DECL_HTOBE64)

# Conan infrastructure.
#==============================================================================
# Only if enabled
#------------------------------------------------------------------------------

# if(EXISTS ${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
#     include(${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
# else()
#     message( STATUS "knuthbuildinfo doent exists")
# endif()


# Check dependencies.
#==============================================================================
#------------------------------------------------------------------------------
# if (NO_CONAN_AT_ALL)
#   # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
#   #------------------------------------------------------------------------------
#   if (NOT ENABLE_SHARED)
#     set(Boost_USE_STATIC_LIBS ON)
#   endif()

#   if (MSVC)
#     find_package(
#       Boost 1.56.0 REQUIRED
#       COMPONENTS atomic chrono date_time filesystem iostreams locale program_options regex system thread unit_test_framework
#     )
#   else()
#     find_package(
#       Boost 1.56.0 REQUIRED
#       COMPONENTS chrono date_time filesystem iostreams locale program_options regex system thread unit_test_framework
#     )
#   endif()
# endif()


# message("FER-USE_CONAN")
# message(${USE_CONAN})

# if (NOT USE_CONAN)
#   # Require kth-domain of at least version 0 and output ${kth_domain_CPPFLAGS/LIBS/PKG}.
#   #------------------------------------------------------------------------------
#   if (NOT TARGET kth-domain)
#     find_package(kth-domain 0 REQUIRED)
#   endif()

#   # Require secp256k1 of at least version 0 and output ${secp256k1_CPPFLAGS/LIBS/PKG}.
#   #------------------------------------------------------------------------------
#   if (NOT TARGET secp256k1)
#     find_package(secp256k1 0 REQUIRED)
#   endif()
# endif (NOT USE_CONAN)

find_package(secp256k1 REQUIRED)

# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)


# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Target Windows Vista. Enabled in msvc only.
#------------------------------------------------------------------------------
if (MSVC)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

#------------------------------------------------------------------------------
if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH")

  add_library(kth-consensus-clone OBJECT
    src/bch-rules/amount.h
    src/bch-rules/amount.cpp
    src/bch-rules/coins.cpp
    src/bch-rules/hash.cpp
    src/bch-rules/hash.h
    src/bch-rules/prevector.h
    src/bch-rules/pubkey.cpp
    src/bch-rules/pubkey.h
    src/bch-rules/feerate.cpp
    src/bch-rules/feerate.h
    src/bch-rules/serialize.h
    src/bch-rules/tinyformat.h
    src/bch-rules/uint256.cpp
    src/bch-rules/uint256.h
    src/bch-rules/version.h
    src/bch-rules/compat/byteswap.h
    src/bch-rules/compat/endian.h
    src/bch-rules/crypto/common.h
    src/bch-rules/crypto/hmac_sha512.cpp
    src/bch-rules/crypto/hmac_sha512.h
    src/bch-rules/crypto/ripemd160.cpp
    src/bch-rules/crypto/ripemd160.h
    src/bch-rules/crypto/sha1.cpp
    src/bch-rules/crypto/sha1.h
    src/bch-rules/crypto/sha256.cpp
    src/bch-rules/crypto/sha256.h
    src/bch-rules/crypto/sha512.cpp
    src/bch-rules/crypto/sha512.h
    src/bch-rules/crypto/siphash.h

    src/bch-rules/primitives/token.h
    src/bch-rules/primitives/token.cpp

    src/bch-rules/primitives/transaction.cpp
    src/bch-rules/primitives/transaction.h
    src/bch-rules/primitives/txid.h

    src/bch-rules/script/bitfield.cpp
    src/bch-rules/script/bitfield.h
    src/bch-rules/script/interpreter.cpp
    src/bch-rules/script/interpreter.h
    src/bch-rules/script/script.cpp
    src/bch-rules/script/script.h
    src/bch-rules/script/script_flags.h
    src/bch-rules/script/script_error.h
    src/bch-rules/script/script_execution_context.cpp
    src/bch-rules/script/sigencoding.h
    src/bch-rules/script/sigencoding.cpp
    src/bch-rules/util/strencodings.cpp
    src/bch-rules/util/strencodings.h
    src/bch-rules/util/string.cpp
    src/bch-rules/util/string.h
  )

else()
#message("clone BTC")

  add_library(kth-consensus-clone OBJECT
    src/btc-rules/amount.h
    src/btc-rules/hash.cpp
    src/btc-rules/hash.h
    src/btc-rules/prevector.h
    src/btc-rules/pubkey.cpp
    src/btc-rules/pubkey.h
    src/btc-rules/serialize.h
    src/btc-rules/tinyformat.h
    src/btc-rules/uint256.cpp
    src/btc-rules/uint256.h
    src/btc-rules/version.h
    src/btc-rules/compat/byteswap.h
    src/btc-rules/compat/endian.h
    src/btc-rules/crypto/common.h
    src/btc-rules/crypto/hmac_sha512.cpp
    src/btc-rules/crypto/hmac_sha512.h
    src/btc-rules/crypto/ripemd160.cpp
    src/btc-rules/crypto/ripemd160.h
    src/btc-rules/crypto/sha1.cpp
    src/btc-rules/crypto/sha1.h
    src/btc-rules/crypto/sha256.cpp
    src/btc-rules/crypto/sha256.h
    src/btc-rules/crypto/sha512.cpp
    src/btc-rules/crypto/sha512.h
    src/btc-rules/primitives/transaction.cpp
    src/btc-rules/primitives/transaction.h
    src/btc-rules/script/interpreter.cpp
    src/btc-rules/script/interpreter.h
    src/btc-rules/script/script.cpp
    src/btc-rules/script/script.h
    src/btc-rules/script/script_error.h
    src/btc-rules/util/strencodings.cpp
    src/btc-rules/util/strencodings.h
  )
endif()


if (ENABLE_POSITION_INDEPENDENT_CODE)
  set_property(TARGET kth-consensus-clone PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)




if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 2")
  target_include_directories(kth-consensus-clone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/bch-rules)
else()
#message("clone BTC 2")
  target_include_directories(kth-consensus-clone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/btc-rules)
endif()

# target_compile_definitions(kth-consensus-clone PUBLIC -DKTH_PROJECT_VERSION="\\"${KTH_PROJECT_VERSION}\\"") #TODO(fernando): manage with Conan????
target_compile_definitions(kth-consensus-clone PUBLIC -DKTH_PROJECT_VERSION="${KTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????


# if (NOT USE_CONAN)
  target_compile_definitions(kth-consensus-clone PRIVATE $<TARGET_PROPERTY:secp256k1,INTERFACE_COMPILE_DEFINITIONS>)
  target_include_directories(kth-consensus-clone PRIVATE $<TARGET_PROPERTY:secp256k1,INTERFACE_INCLUDE_DIRECTORIES>)
# endif()

if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 3")

  _group_sources(kth-consensus-clone "${CMAKE_CURRENT_SOURCE_DIR}/src/bch-rules")
else()
#message("clone BTC 3")

_group_sources(kth-consensus-clone "${CMAKE_CURRENT_SOURCE_DIR}/src/btc-rules")
endif()



# src/kth-consensus.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

add_library(kth-consensus ${MODE}
  src/consensus/consensus.cpp
  src/consensus/consensus.hpp
  $<TARGET_OBJECTS:kth-consensus-clone>
)

if (ENABLE_POSITION_INDEPENDENT_CODE)
  set_property(TARGET kth-consensus PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)


target_include_directories(kth-consensus PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# target_compile_definitions(kth-consensus PUBLIC -DKTH_PROJECT_VERSION="\\"${KTH_PROJECT_VERSION}\\"") #TODO(fernando): manage with Conan????
target_compile_definitions(kth-consensus PUBLIC -DKTH_PROJECT_VERSION="${KTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????


if (NOT ENABLE_SHARED)
  target_compile_definitions(kth-consensus PUBLIC -DBCK_STATIC)
endif()




if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 4")

  target_include_directories(kth-consensus PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bch-rules)
else()
#message("clone BTC 4")

  target_include_directories(kth-consensus PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_SOURCE_DIR}/src/btc-rules)
endif()


# if (NOT NO_CONAN_AT_ALL)
#   # target_link_libraries(kth-consensus PUBLIC ${CONAN_LIBS})
# else()
#   target_link_libraries(kth-consensus secp256k1 kth-domain)
# endif()
target_link_libraries(kth-consensus secp256k1)

# if (USE_CONAN)
  if (MINGW)
    target_link_libraries(kth-consensus PUBLIC ws2_32 wsock32) #TODO(fernando): manage with Conan
  endif()
# endif()

_group_sources(kth-consensus "${CMAKE_CURRENT_LIST_DIR}")

# Tests
#==============================================================================
if (WITH_TESTS)
  enable_testing()
  find_package(Catch2 3 REQUIRED)

  add_executable(kth_consensus_test
    test/consensus__script_error_to_verify_result.cpp
    test/consensus__script_verify.cpp
    test/consensus__verify_flags_to_script_flags.cpp
    test/main.cpp
    test/script.hpp)

  if (${CURRENCY} STREQUAL "BCH")
    target_include_directories(kth_consensus_test PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_SOURCE_DIR}/src/bch-rules)
  else()
    target_include_directories(kth_consensus_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/btc-rules)
  endif()

  target_include_directories(kth_consensus_test PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>)
  target_link_libraries(kth_consensus_test PUBLIC kth-consensus)
  target_link_libraries(kth_consensus_test PRIVATE Catch2::Catch2WithMain)

  _group_sources(kth_consensus_test "${CMAKE_CURRENT_LIST_DIR}/test")

  include(CTest)
  include(Catch)
  catch_discover_tests(kth_consensus_test)
endif()


# Install
#==============================================================================
install(TARGETS kth-consensus
  EXPORT kth-consensus
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

set(_kth_headers
  # include_bitcoin_HEADERS =
  kth/consensus.hpp
  # include_bitcoin_consensus_HEADERS =
  kth/consensus/define.hpp
  kth/consensus/export.hpp
  kth/consensus/version.hpp)
foreach (_header ${_kth_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT kth-consensus
  FILE "${CMAKE_CURRENT_BINARY_DIR}/kth-consensusTargets.cmake")
export(PACKAGE kth-consensus)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT kth-consensus
  FILE kth-consensusTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(kth-consensusConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/kth-consensusConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/kth-consensusConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kth-consensusConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/kth-consensusConfigVersion.cmake"
  DESTINATION ${_config_package_location})
