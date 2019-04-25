/*!
 * \file
 * \brief Main header of the libcompress
*/

#include <string>
#include <cstring>

class LibCompress
{
public:
  LibCompress() {};
  ~LibCompress() {};

  /*!
   * \brief Encode raw string with RLE
   * \param[in] input is a string to encode
   * \return The encoded string with RLE algorithm
   */
  std::string rle_encode(std::string &input);

  /*!
   * \brief Decode a string encoded with RLE
   * \param[in] encoded is a encoded string
   * \return The decoded string
   */
  std::string rle_decode(std::string &encoded);

  /*!
   * \brief Encode raw string with LZ77
   * \param[in] input is a string to encode
   * \return The encoded string with LZ77 algorithm
   */
  std::string lz77_encode(std::string &input);

  /*!
   * \brief Decode a string encoded with LZ77
   * \param[in] encoded is a encoded string
   * \return The decoded string
   */
  std::string lz77_decode(std::string &encoded);
};
