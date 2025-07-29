# WeActStudio_STM32_BlackPill_2

Projects for the WeActStudio BlackPill 2.0 board with STM32F411CEU6 MCU (100MHz, 512K flash, 128K RAM)

# Python Virtual Environment

Activate in PowerShell running as admin:

```
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

Regular Powershell:

```
.\.venv\bin\Activate.ps1
```

Install pywinusb:

```
python -m pip install pywinusb
OR
python -m pip install -r requirements.txt
```

Run Python script:

```
python .\test_hid.py
```
