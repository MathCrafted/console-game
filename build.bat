@echo off
setlocal

rem INIT
set source="*.cpp"
set output="game.exe"

rem COMPILE
if exist %output% del %output%
g++ -Wall -o .\builds\%output% .\src\%source% 2>log.txt

rem RUN THE GAME
if %errorlevel%==0 (
    cls
    .\%output%
)