# fcode-tester

Quick and dirty tool to send gcode and fcode commands to farmbot.

## Usage
Create virtual environment:

```
virtualenv --python=python3 --system-site-packages fcode
. ./fcode/bin/activate
pip install -r requirements.txt
```

Change `fcode-tester.py`: adjust the serial port name and run the script. The output of the executed commands is shown in the terminal window.
