#
# Copyright (c) 2017-2018 Bitprim Inc.
#
# This file is part of Bitprim.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.4)

# bitprim-consensus
#==============================================================================
project(bitprim-consensus
  VERSION 0
  LANGUAGES CXX C)
  # VERSION 0.11.0


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++11 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Implement --use-conan
#------------------------------------------------------------------------------
option(USE_CONAN "Use Conan Build Tool." OFF)
option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

if (NO_CONAN_AT_ALL)
  set(USE_CONAN OFF)
endif()

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


#TODO(fernando): check libbitcoin for with_java and with_python parameters
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



set(BITPRIM_PROJECT_VERSION "-" CACHE STRING "Specify the Bitprim Project Version.")
# message(${BITPRIM_PROJECT_VERSION})


set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Cryptocurrency (x86_64|...).")
message( STATUS "Bitprim: Compiling for ${MICROARCHITECTURE}")
# add_definitions(-DBITPRIM_MICROARCHITECTURE=${MICROARCHITECTURE})
# add_definitions(-DBITPRIM_MICROARCHITECTURE_STR="${MICROARCHITECTURE}")


set(CURRENCY "BCH" CACHE STRING "Specify the Cryptocurrency (BCH|BTC|LTC).")

if (${CURRENCY} STREQUAL "BCH")
  add_definitions(-DBITPRIM_CURRENCY_BCH)
elseif (${CURRENCY} STREQUAL "BTC")
  add_definitions(-DBITPRIM_CURRENCY_BTC)
elseif (${CURRENCY} STREQUAL "LTC")
  add_definitions(-DBITPRIM_CURRENCY_LTC)
else()
  message(FATAL_ERROR "Invalid Cryptocurrency: ${CURRENCY}")
endif()

message(STATUS "Bitprim: Cryptocurrency: ${CURRENCY}")


# Set preprocessor defines.
include(CheckIncludeFile)
include(CheckCXXSymbolExists)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)

include(BitprimTools)



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

if(EXISTS ${CMAKE_SOURCE_DIR}/ci_utils/cmake/bitprimbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/ci_utils/cmake/bitprimbuildinfo.cmake)
else()
    message( STATUS "bitprimbuildinfo doent exists")
endif()


# Check dependencies.
#==============================================================================
#------------------------------------------------------------------------------
if (NO_CONAN_AT_ALL)
  # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
  #------------------------------------------------------------------------------
  if (NOT ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  if (MSVC)
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS atomic chrono date_time filesystem iostreams locale log log_setup program_options regex system thread unit_test_framework
    )
  else()
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS chrono date_time filesystem iostreams locale log program_options regex system thread unit_test_framework
    )
  endif()
endif()


# message("FER-USE_CONAN")
# message(${USE_CONAN})

if (NOT USE_CONAN)
#   message("Entro!!!")
  # Require bitprim-core of at least version 0 and output ${bitprim_core_CPPFLAGS/LIBS/PKG}.
  #------------------------------------------------------------------------------
  if (NOT TARGET bitprim-core)
    find_package(bitprim-core 0 REQUIRED)
  endif()

  # Require secp256k1 of at least version 0 and output ${secp256k1_CPPFLAGS/LIBS/PKG}.
  #------------------------------------------------------------------------------
  if (NOT TARGET secp256k1)
    find_package(secp256k1 0 REQUIRED)
  endif()
endif (NOT USE_CONAN)


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

  add_library(bitprim-consensus-clone OBJECT
    src/clone-abc/amount.h
    src/clone-abc/amount.cpp
    src/clone-abc/hash.cpp
    src/clone-abc/hash.h
    src/clone-abc/prevector.h
    src/clone-abc/pubkey.cpp
    src/clone-abc/pubkey.h
    src/clone-abc/serialize.h
    src/clone-abc/tinyformat.h
    src/clone-abc/uint256.cpp
    src/clone-abc/uint256.h
    src/clone-abc/utilstrencodings.cpp
    src/clone-abc/utilstrencodings.h
    src/clone-abc/version.h
    src/clone-abc/compat/byteswap.h
    src/clone-abc/compat/endian.h
    src/clone-abc/crypto/common.h
    src/clone-abc/crypto/hmac_sha512.cpp
    src/clone-abc/crypto/hmac_sha512.h
    src/clone-abc/crypto/ripemd160.cpp
    src/clone-abc/crypto/ripemd160.h
    src/clone-abc/crypto/sha1.cpp
    src/clone-abc/crypto/sha1.h
    src/clone-abc/crypto/sha256.cpp
    src/clone-abc/crypto/sha256.h
    src/clone-abc/crypto/sha512.cpp
    src/clone-abc/crypto/sha512.h
    src/clone-abc/primitives/transaction.cpp
    src/clone-abc/primitives/transaction.h
    src/clone-abc/script/interpreter.cpp
    src/clone-abc/script/interpreter.h
    src/clone-abc/script/script.cpp
    src/clone-abc/script/script.h
    src/clone-abc/script/script_error.h
  )

else()
#message("clone BTC")

  add_library(bitprim-consensus-clone OBJECT
    src/clone-legacy/amount.h
    src/clone-legacy/hash.cpp
    src/clone-legacy/hash.h
    src/clone-legacy/prevector.h
    src/clone-legacy/pubkey.cpp
    src/clone-legacy/pubkey.h
    src/clone-legacy/serialize.h
    src/clone-legacy/tinyformat.h
    src/clone-legacy/uint256.cpp
    src/clone-legacy/uint256.h
    src/clone-legacy/utilstrencodings.cpp
    src/clone-legacy/utilstrencodings.h
    src/clone-legacy/version.h
    src/clone-legacy/compat/byteswap.h
    src/clone-legacy/compat/endian.h
    src/clone-legacy/crypto/common.h
    src/clone-legacy/crypto/hmac_sha512.cpp
    src/clone-legacy/crypto/hmac_sha512.h
    src/clone-legacy/crypto/ripemd160.cpp
    src/clone-legacy/crypto/ripemd160.h
    src/clone-legacy/crypto/sha1.cpp
    src/clone-legacy/crypto/sha1.h
    src/clone-legacy/crypto/sha256.cpp
    src/clone-legacy/crypto/sha256.h
    src/clone-legacy/crypto/sha512.cpp
    src/clone-legacy/crypto/sha512.h
    src/clone-legacy/primitives/transaction.cpp
    src/clone-legacy/primitives/transaction.h
    src/clone-legacy/script/interpreter.cpp
    src/clone-legacy/script/interpreter.h
    src/clone-legacy/script/script.cpp
    src/clone-legacy/script/script.h
    src/clone-legacy/script/script_error.h
  )
endif()


if (ENABLE_POSITION_INDEPENDENT_CODE)
  set_property(TARGET bitprim-consensus-clone PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)
  
  


if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 2")
  target_include_directories(bitprim-consensus-clone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-abc)
else()
#message("clone BTC 2")
  target_include_directories(bitprim-consensus-clone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-legacy)
endif()

target_compile_definitions(bitprim-consensus-clone PUBLIC -DBITPRIM_PROJECT_VERSION="\\"${BITPRIM_PROJECT_VERSION}\\"") #TODO(fernando): manage with Conan????
  

if (NOT USE_CONAN)
  target_compile_definitions(bitprim-consensus-clone PRIVATE
  $<TARGET_PROPERTY:secp256k1,INTERFACE_COMPILE_DEFINITIONS>)

  target_include_directories(bitprim-consensus-clone PRIVATE
  $<TARGET_PROPERTY:secp256k1,INTERFACE_INCLUDE_DIRECTORIES>)
endif()

if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 3")

  _group_sources(bitprim-consensus-clone "${CMAKE_CURRENT_SOURCE_DIR}/src/clone-abc")
else()
#message("clone BTC 3")

_group_sources(bitprim-consensus-clone "${CMAKE_CURRENT_SOURCE_DIR}/src/clone-legacy")
endif()



# src/bitprim-consensus.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

add_library(bitprim-consensus ${MODE}
  src/consensus/consensus.cpp
  src/consensus/consensus.hpp
  $<TARGET_OBJECTS:bitprim-consensus-clone>
)

if (ENABLE_POSITION_INDEPENDENT_CODE)
  set_property(TARGET bitprim-consensus PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)
  
  
target_include_directories(bitprim-consensus PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_definitions(bitprim-consensus PUBLIC -DBITPRIM_PROJECT_VERSION="\\"${BITPRIM_PROJECT_VERSION}\\"") #TODO(fernando): manage with Conan????


if (NOT ENABLE_SHARED)
  target_compile_definitions(bitprim-consensus PUBLIC -DBCK_STATIC)
endif()




if (${CURRENCY} STREQUAL "BCH")
#message("clone BCH 4")

  target_include_directories(bitprim-consensus PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-abc)
else()
#message("clone BTC 4")

  target_include_directories(bitprim-consensus PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-legacy)
endif()


if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(bitprim-consensus PUBLIC ${CONAN_LIBS})
else()
  target_link_libraries(bitprim-consensus secp256k1 bitprim-core)
endif()


# if (USE_CONAN)
  if (MINGW)
    target_link_libraries(bitprim-consensus PUBLIC ws2_32 wsock32) #TODO(fernando): manage with Conan
  endif()
# endif()

_group_sources(bitprim-consensus "${CMAKE_CURRENT_LIST_DIR}")

# Tests
#==============================================================================

if (WITH_TESTS)
  enable_testing()
endif()

# local: test/bitprim_consensus_test
#------------------------------------------------------------------------------
if (WITH_TESTS)
 
  add_executable(bitprim_consensus_test
    # test/consensus__script_error_to_verify_result.cpp
    test/consensus__script_verify.cpp
    # test/consensus__verify_flags_to_script_flags.cpp
    test/main.cpp
    test/script.hpp)
 
 

  if (${CURRENCY} STREQUAL "BCH")
  #message("clone BCH 5")

    target_include_directories(bitprim_consensus_test PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-abc)
  else()
  #message("clone BTC 5")
    target_include_directories(bitprim_consensus_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clone-legacy)
  endif()
  

  target_link_libraries(bitprim_consensus_test PUBLIC bitprim-consensus)
 
  _group_sources(bitprim_consensus_test "${CMAKE_CURRENT_LIST_DIR}/test")

  _add_tests(bitprim_consensus_test
    #consensus__script_error_to_verify_result
    consensus__script_verify
    #consensus__verify_flags_to_script_flags
          )


endif()


# Install
#==============================================================================
# install(TARGETS bitprim-consensus bitprim-consensus-requester bitprim-consensus-replier
install(TARGETS bitprim-consensus 
  EXPORT bitprim-consensus
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

set(_bitprim_headers
  # include_bitcoin_HEADERS =
  bitcoin/consensus.hpp
  # include_bitcoin_consensus_HEADERS =
  bitcoin/consensus/define.hpp
  bitcoin/consensus/export.hpp
  bitcoin/consensus/version.hpp)
foreach (_header ${_bitprim_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT bitprim-consensus
  FILE "${CMAKE_CURRENT_BINARY_DIR}/bitprim-consensusTargets.cmake")
export(PACKAGE bitprim-consensus)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT bitprim-consensus
  FILE bitprim-consensusTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(bitprim-consensusConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-consensusConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-consensusConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-consensusConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-consensusConfigVersion.cmake"
  DESTINATION ${_config_package_location})
