::@echo off
::@title bat for git 
E:
cd E:\github\machine-pwm
git add .
git commit -m %date:~0,4%year%date:~5,2%month%date:~8,2%day
git push
pause