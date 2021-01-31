#include <trpch.h>
#include "file.h"

namespace Trem::Util
{  
  std::string readFile(const std::string& filePath)
  {
    std::ifstream inFile(filePath, std::ios::in | std::ios::binary);
    TR_ASSERT(inFile, "File " + filePath + " could not be opened!")
    std::string fileContent; 
    if (inFile)
    {
      inFile.seekg(0, std::ios::end);
		  size_t size = inFile.tellg();
      fileContent.resize(size);
      inFile.seekg(0, std::ios::beg);
      inFile.read(&fileContent[0], size);
    }

    return fileContent;
  }

  std::string fileNameFromFilePath(const std::string& filePath)
  {
    //find last slash
    std::size_t lsPos = filePath.find_last_of("/\\");
    //find position of the file extension
    std::size_t extPos = filePath.find(".", lsPos + 1);
    //determine length of file name, if not extension was found us size of the string
    std::size_t nameLen = (extPos == std::string::npos) ? filePath.size() - lsPos  : extPos - lsPos;
    //we do not want to get the '.' so we subtract 1 from the determined length
    std::string name = filePath.substr(lsPos + 1, nameLen - 1);

    return name;
  }

}
