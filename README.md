# WeActStudio_STM32_BlackPill_2

USB HID with vendor-defined interface project for the WeActStudio BlackPill 2.0 board with STM32F411CEU6 MCU (100MHz, 512K flash, 128K RAM).

This project demonstrates USB HID feature reports, input reports and output reports.
The provided Python script demonstrates reading/writing all 3 types of HID reports using pywinusb library on a Windows machine.

# Python Virtual Environment (optional)

From Powershell, make sure you're running your most recently installed Python:

```
which python
```

Create a virtual environment:

```
python -m venv venv
```

Activate in PowerShell running as admin:

```
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

Regular Powershell:

```
.\venv\Scripts\Activate.ps1
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
