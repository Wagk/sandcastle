#include "utility_filesystem.h"

#include <iostream> // for debugging


/*!************************************************************

**************************************************************/
std::vector<std::string> GetFilesfromFolder(const std::string& folderpath)
{
  using namespace std::tr2::sys; //this is some TS stuff

  path folder(folderpath);

  if (is_directory(folder) == true)
  {
    std::vector<std::string> filepaths;

    for (const auto& subpath : directory_iterator(folder))
    {
      if (is_regular_file(subpath.path()) == true)
      {
        filepaths.emplace_back(subpath.path().string());
      }
    }

    return filepaths;
  }
  else
  {
    return std::vector<std::string>();
  }
}

/*!************************************************************

**************************************************************/
std::vector<std::string> GetFoldersfromFolder(const std::string& folderpath)
{
  using namespace std::tr2::sys; //this is some TS stuff

  path folder(folderpath);

  if (is_directory(folder) == true)
  {
    std::vector<std::string> subfolders;

    for (const auto& subpath : directory_iterator(folder))
    {
      if (is_directory(subpath.path()) == true)
      {
        subfolders.emplace_back(subpath.path().string());
      }
    }

    return subfolders;
  }
  else
  {
    return std::vector<std::string>();
  }
}
