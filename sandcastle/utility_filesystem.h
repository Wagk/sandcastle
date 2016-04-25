/*!************************************************************
	Created:	2016/02/26
	Intent:		
			
	Note:
			After a bajillion man-hours in importing half of boost,
      We finally get a portable filesystem thing.

      This shit better be encapsulated super-good. I don't ever
      want to fuck with build configs like this for a good year
      or so
**************************************************************/
#ifndef util_filesys_h__
#define util_filesys_h__

//#include <boost/filesystem.hpp>

#include <filesystem> //microsoft edition

#include <vector>
#include <string>

/*!************************************************************
	FullName :	GetFilesfromFolder
	Returns  :	std::vector<std::string>
	Parameter:	const std::string & folder
	Brief    :		
			returns all the files within this folder.
      Does not return files within subfolders.
      
      Note that this returns the *filepaths* of the files, not just the name
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
std::vector<std::string> GetFilesfromFolder(const std::string& folder);

/*!************************************************************
	FullName :	GetFoldersfromFolder
	Returns  :	std::vector<std::string>
	Parameter:	const std::string & folder
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
std::vector<std::string> GetFoldersfromFolder(const std::string& folder);

#endif // util_filesys_h__
/*!************************************************************
	Todo:
			
**************************************************************/


