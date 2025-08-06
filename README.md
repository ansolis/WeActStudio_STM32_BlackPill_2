# WeActStudio_STM32_BlackPill_2

Projects for the WeActStudio BlackPill 2.0 board with STM32F411CEU6 MCU (100MHz, 512K flash, 128K RAM)

# Python Virtual Environment

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
