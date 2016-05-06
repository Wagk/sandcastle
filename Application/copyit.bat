::We assume that the generic application will need `sandcastle_graphics` and `sandcastle` dlls
::format `call "$(ProjectDir)copyit.bat" "$(SolutionDir)" "$(ProjectDir)" "$(ProjectName)" "$(Platform)" "$(Configuration)"`
::@echo off

SET SolutionDir=%~1
SET ProjectDir=%~2
SET ProjectName=%~3
SET Platform=%~4
SET Configuration=%~5

echo Running %ProjectDir%copyit.bat

::handle sandcastle things
robocopy /np %SolutionDir%output\sandcastle\%Platform%\%Configuration% %ProjectDir%external\libs\%Platform% sandcastle_%Platform%_%Configuration%.lib sandcastle_%Platform%_%Configuration%.ilk
robocopy /np %SolutionDir%output\sandcastle\%Platform%\%Configuration% %SolutionDir%output\%ProjectName%\%Platform%\%Configuration% sandcastle_%Platform%_%Configuration%.dll sandcastle_%Platform%_%Configuration%.exp sandcastle_%Platform%_%Configuration%.pdb

::handle sandcastle_graphics things
robocopy /np %SolutionDir%output\sandcastle_graphics\%Platform%\%Configuration% %ProjectDir%external\libs\%Platform% sandcastle_graphics_%Platform%_%Configuration%.lib sandcastle_graphics_%Platform%_%Configuration%.ilk
robocopy /np %SolutionDir%output\sandcastle_graphics\%Platform%\%Configuration% %SolutionDir%output\%ProjectName%\%Platform%\%Configuration% sandcastle_graphics_%Platform%_%Configuration%.dll sandcastle_graphics_%Platform%_%Configuration%.exp sandcastle_graphics_%Platform%_%Configuration%.pdb