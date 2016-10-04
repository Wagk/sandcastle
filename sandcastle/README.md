# ON `.DLL`'s

- Define a `*_EXPORTS` macro under `Preprocessor Definitions`
- Under `Linker->Input->Additional Dependencies` add your library
	- Note that your library won't be created until you export at least one symbol
- Make sure your dll is in the same build folder as your exe