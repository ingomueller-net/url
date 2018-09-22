// Copyright 2018 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef SKYR_UNICODE_HPP
#define SKYR_UNICODE_HPP

#include <string>
#include <string_view>
#include <system_error>
#include <skyr/expected.hpp>

namespace skyr {
/// Enumerates Unicode errors
enum class unicode_errc {
  /// Overflow
  overflow,
  /// Invalid lead code point
  invalid_lead,
  /// Illegal byte sequence
  illegal_byte_sequence,
  /// Invalid code point
  invalid_code_point,
};

/// Creates a `std::error_code` given a `skyr::unicode_errc` value
/// \param error A Unicode error
/// \returns A `std::error_code` object
std::error_code make_error_code(unicode_errc error);

/// Thrown when there is a Unicode encoding or decoding error
class unicode_error : public std::runtime_error {
 public:
  /// Constructor
  /// \param error An error code value
  explicit unicode_error(std::error_code error) noexcept
      : runtime_error("Unicode error")
      , error_(std::move(error)) {}

  /// \returns An error code
  std::error_code error() const noexcept {
    return error_;
  }

 private:

  std::error_code error_;

};

/// Converts a `std::string` (assuming UTF-8) string to UTF-16
/// \param input A UTF-8 string
/// \returns A UTF-16 `std::wstring` or an error on failure
expected<std::wstring, std::error_code> wstring_from_bytes(
    std::string_view input);

/// Converts a `std::u16string` string to UTF-8
///
/// \param input A UTF-16 string
/// \returns A UTF-8 `std::string` or an error on failure
expected<std::string, std::error_code> wstring_to_bytes(
    std::wstring_view input);

/// Converts a `std::string` (assuming UTF-8) string to UTF-16
///
/// \param input A UTF-8 string
/// \returns A UTF-16 `std::u16string` or an error on failure
expected<std::u16string, std::error_code> utf16_from_bytes(
    std::string_view input);

/// Converts a `std::u16string` string to UTF-8
///
/// \param input A UTF-16 string
/// \returns A UTF-8 `std::string` or an error on failure
expected<std::string, std::error_code> utf16_to_bytes(
    std::u16string_view input);

/// Converts a `std::string` (assuming UTF-8) string to UTF-32
///
/// \param input A UTF-8 string
/// \returns A UTF-32 `std::u32string` or an error on failure
expected<std::u32string, std::error_code> utf32_from_bytes(
    std::string_view input);

/// Converts a `std::u32string` string to UTF-8
///
/// \param input A UTF-32 string
/// \returns A UTF-8 `std::string` or an error on failure
expected<std::string, std::error_code> utf32_to_bytes(
    std::u32string_view input);
}  // namespace skyr

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
namespace std {
template <>
struct is_error_code_enum<skyr::unicode_errc> : true_type {};
}  // namespace std
#endif  // !defined(DOXYGEN_SHOULD_SKIP_THIS)

#endif //SKYR_UNICODE_HPP
