C:\Factory\Tools\RDMD.exe /RC out

SET RAWKEY=a77b425599ab8f74dc2cf69fc214ae24

C:\Factory\SubTools\makeCluster.exe Picture.txt     out\Picture.dat     %RAWKEY% 110000000
C:\Factory\SubTools\makeCluster.exe Music.txt       out\Music.dat       %RAWKEY% 120000000
C:\Factory\SubTools\makeCluster.exe SoundEffect.txt out\SoundEffect.dat %RAWKEY% 130000000
C:\Factory\SubTools\makeCluster.exe Etcetera.txt    out\Etcetera.dat    %RAWKEY% 140000000

COPY /B Shoot\Release\Shoot.exe out\Shoot.exe
C:\Factory\Tools\xcp.exe doc out
ren out\Manual.txt ƒ}ƒjƒ…ƒAƒ‹.txt

C:\Factory\SubTools\zip.exe /G out Shooting
C:\Factory\Tools\summd5.exe /M out

PAUSE
