#include "libcompress.h"

/* ~~~ RLE ALGORITHM ~~~ */

std::string LibCompress::rle_encode(std::string &input)
{
  std::string result;
  int count = 0;

  for (auto it = input.begin(); it != input.end(); ++it)
  {
    // Check if char matches rules
    if (!(isalpha(*it) || *it == ' ' || *it == '\n')) {
      result = "Only ASCII alphabetical chars is allowed";
      return result;
    }

    count = 1;
    while (*it == *(it + 1)) {
      ++count;
      ++it;
    }
    if (count != 1) result += std::to_string(count);
    result.push_back(*it);
  }

  return result;
}

/* -------------------------------------------------------- */

std::string LibCompress::rle_decode(std::string &encoded)
{
  std::string result;

  for (auto it = encoded.begin(); it != encoded.end(); ++it)
  {
    if (isdigit(*it)) {
      std::string count;
      while (isdigit(*it))
      {
        count += *it;
        ++it;
      }

      int count_int = stoi(count);
      for (int i = 0; i < count_int; ++i)
      {
        result.push_back(*it);
      }

      continue;
    }

    result.push_back(*it);
  }

  return result;
}

/* ~~~ LZ77 ALGORITHM ~~~ */

std::string LibCompress::lz77_encode(std::string &input)
{
  std::string result, window, suffix;

  for (auto it = input.begin(); it != input.end(); ++it)
  {
    // Check if char matches rules
    if (!(isalpha(*it) || *it == ' ' || *it == '\n')) {
      result = "Only ASCII alphabetical chars is allowed";
      return result;
    }

    if ((window + suffix).find(suffix + *it) == std::string::npos) {
      if (suffix.empty()) {
        result += *it;
        window += *it;
      } else {
        int lookback = window.length() - (window + suffix).find(suffix);
        result += std::to_string(lookback) + "," + std::to_string(suffix.length()) + ";";
        window += suffix;
        suffix = "";
        --it;
      }
    } else {
      suffix += *it;
    }
  }

  if (suffix != "") {
    int lookback = window.length() - (window + suffix).find(suffix);
    result += std::to_string(lookback) + "," + std::to_string(suffix.length()) + ";";
  }

  return result;
}

/* -------------------------------------------------------- */

std::string LibCompress::lz77_decode(std::string &encoded)
{
  std::string result;

  for (auto it = encoded.begin(); it != encoded.end(); ++it)
  {
    if (isdigit(*it)) {
      std::string offset, length;
      int offset_int, length_int;

      // Getting offset
      while (isdigit(*it)) {
        offset += *it;
        ++it;
      }

      ++it; // Skip "," char

      // Getting length
      while (isdigit(*it)) {
        length += *it;
        ++it;
      }

      // Converting raw string numbers to integers
      offset_int = stoi(offset);
      length_int = stoi(length);

      // Getting starting point
      int start_point = result.length() - offset_int;

      for (int i = start_point; i < start_point + length_int; ++i)
      {
        result += result[i];
      }
    } else {
      result += *it;
    }
  }

  return result;
}
