echo off
setlocal
for %%f in (%*) do (
  echo %%f|find "=" >nul:
  if errorlevel 1 goto DoCmd
  set %%f
  shift
)
:DoCmd
%1 %2 %3 %4 %5 %6 %7 %8 %9
endlocal
