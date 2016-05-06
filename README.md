# Sandcastle
Public repository for the Sandcastle Engine

# Checklists
### When creating a new project (within the solution)

- In project properties:
	- Under `General` configuration properties:
		- Set `Output Directory` to `$(SolutionDir)output\$(ProjectName)\$(Platform)\$(Configuration)\`
		- Set `Intermediate Directory` to `$(SolutionDir)artifacts\$(ProjectName)\$(Platform)\$(Configuration)\`
		- Set `Target Name` to `$(ProjectName)_$(Platform)_$(Configuration)`
- If the project is a `.dll` project:
	- Under `C/C++` settings, under `Preprocessor`
		- **Add under `Preprocessor Definitions` the define `SANDCASTLE_DLL`**
	- Under `VC++ Directories`:
		- Add under `Include Directories` the path `$(SolutionDir)sandcastle\`
		- **Use `export_macros.h` for your API concerns**
		
### When adding a 3rd party library
The conventions are:
	- All include files should be found under `$(ProjectDir)\external\`
	- All static libs should be found under `$(ProjectDir)\external\libs\`
		- 32-bit machines should place their libs in `$(ProjectDir)\external\libs\32bit`
		- 64-bit machines should place their libs in `$(ProjectDir)\external\libs\64bit`
		
# Useful Macros
(These are generally used for Visual Assist, but we can refer to it as a useful guideline)
(They are, of course, open to change in the future.)

#### `.h`, `.inl` Files

```
/*!************************************************************
	Created	:	$DATE$
	Intent	:		

	Usage	:
		```
		
		```
	Note	:
		
**************************************************************/
#ifndef $FILE_BASE_LOWER$_$FILE_EXT_LOWER$__
#define $FILE_BASE_LOWER$_$FILE_EXT_LOWER$__

$body$$end$

#endif //$FILE_BASE_LOWER$_$FILE_EXT_LOWER$__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
```

#### Function

- Implementation commentary
```
/*!************************************************************

**************************************************************/
$SymbolType$ $SymbolContext$($ParameterList$) $MethodQualifier$
{
	$end$$MethodBody$
}
```
- Documentation commentary
```
/*!************************************************************
	FullName :	$SymbolContext$
	Returns  :	$SymbolType$
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
```

#### `.cpp` Files

```
/*!************************************************************
	Created	:	$DATE$
	Note	:
		
**************************************************************/
#include "$FILE_BASE$.h"

$body$$end$

/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
```