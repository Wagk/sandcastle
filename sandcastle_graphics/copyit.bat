::`sandcastle_graphics` depends on `sandcastle`
::@echo off

SET SolutionDir=%~1
SET ProjectDir=%~2
SET ProjectName=%~3
SET Platform=%~4
SET Configuration=%~5

echo Running %ProjectDir%copyit.bat

robocopy /np %SolutionDir%output\sandcastle\%Platform%\%Configuration% %ProjectDir%external\libs\%Platform% sandcastle_%Platform%_%Configuration%.lib sandcastle_%Platform%_%Configuration%.ilk
