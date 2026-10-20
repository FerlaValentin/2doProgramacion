@ECHO OFF

del *.obj *.o *.pdb *.ilk *.exe

REM clang++ Debug
REM clang++ -g -D_DEBUG -D_MT -D_DLL -DDEBUG -DLLVM_USE_CRT_DEBUG=MDd -Wall -I ..\include -I ..\deps\esat\include -c ..\src\*.cc 
REM clang++ -g -L ..\deps\esat\bin\win_x64 -lESAT_d -lopengl32 -lgdi32 -luser32 -lshell32 -lmsvcrtd -lvcruntimed -lucrtd -o test_d.exe *.o -nodefaultlibs 

REM clang++ Release

REM clang++ -O2 -D_MT -D_DLL -DNDEBUG -D_NDEBUG -DLLVM_USE_CRT_DEBUG=MD -Wall -I ..\include -I ..\deps\esat\include -c ..\src\*.cc 
REM clang++ -O2 -L ..\deps\esat\bin\win_x64 -lESAT -lopengl32 -lgdi32 -luser32 -lshell32 -lmsvcrt -lvcruntime -lucrt -o test.exe *.o -nodefaultlibs 

REM clang-cl Debug

clang-cl /nologo /Zi /W4 /GR- /EHs /MDd -I..\include -I..\deps\esat\include /c ..\src\*.cc
clang-cl /nologo /Zi /W4 /MDd /Fetest_d.exe *.obj ..\deps\esat\bin\win_x64\ESAT_d.lib opengl32.lib user32.lib gdi32.lib shell32.lib /link /IGNORE:4099

