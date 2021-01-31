#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes

/**
 *  \brief Brief Description
 *
 */

namespace Trem::Util
{
  /**
   * \brief Reads a file.
   * @param filePath Path to the file, including its filename.
   * \return Content of the read file.
   */
  std::string readFile(const std::string& filePath);

  /**
   * \brief Extracts the file name from a file path.
   * @param filePath Path to the file, including its filename.
   * \return Name of the file without extension
   */
  std::string fileNameFromFilePath(const std::string& filePath);
}
