import serial
import time

from tkinter import *
import threading
from queue import Queue, Empty

request_queue = Queue()
cmd_queue = Queue()

p = {
"P0": "UNKOWN",
"P2": "PARAM_CONFIG_OK",
"P3": "PARAM_USE_EEPROM",
"P4": "PARAM_E_STOP_ON_MOV_ERR",
"P5": "PARAM_MOV_NR_RETRY",
"P11": "MOVEMENT_TIMEOUT_X",
"P12": "MOVEMENT_TIMEOUT_Y",
"P13": "MOVEMENT_TIMEOUT_Z",
"P15": "MOVEMENT_KEEP_ACTIVE_X",
"P16": "MOVEMENT_KEEP_ACTIVE_Y",
"P17": "MOVEMENT_KEEP_ACTIVE_Z",
"P18": "MOVEMENT_HOME_AT_BOOT_X",
"P19": "MOVEMENT_HOME_AT_BOOT_Y",
"P20": "MOVEMENT_HOME_AT_BOOT_Z",
"P21": "MOVEMENT_INVERT_ENDPOINTS_X",
"P22": "MOVEMENT_INVERT_ENDPOINTS_Y",
"P23": "MOVEMENT_INVERT_ENDPOINTS_Z",
"P25": "MOVEMENT_ENABLE_ENDPOINTS_X",
"P26": "MOVEMENT_ENABLE_ENDPOINTS_Y",
"P27": "MOVEMENT_ENABLE_ENDPOINTS_Z",
"P31": "MOVEMENT_INVERT_MOTOR_X",
"P32": "MOVEMENT_INVERT_MOTOR_Y",
"P33": "MOVEMENT_INVERT_MOTOR_Z",
"P36": "MOVEMENT_SECONDARY_MOTOR_X",
"P37": "MOVEMENT_SECONDARY_MOTOR_INVERT_X",
"P41": "MOVEMENT_STEPS_ACC_DEC_X",
"P42": "MOVEMENT_STEPS_ACC_DEC_Y",
"P43": "MOVEMENT_STEPS_ACC_DEC_Z",
"P45": "MOVEMENT_STOP_AT_HOME_X",
"P46": "MOVEMENT_STOP_AT_HOME_Y",
"P47": "MOVEMENT_STOP_AT_HOME_Z",
"P51": "MOVEMENT_HOME_UP_X",
"P52": "MOVEMENT_HOME_UP_Y",
"P53": "MOVEMENT_HOME_UP_Z",
"P55": "MOVEMENT_STEP_PER_MM_X",
"P56": "MOVEMENT_STEP_PER_MM_Y",
"P57": "MOVEMENT_STEP_PER_MM_Z",
"P61": "MOVEMENT_MIN_SPD_X",
"P62": "MOVEMENT_MIN_SPD_Y",
"P63": "MOVEMENT_MIN_SPD_Z",
"P65": "MOVEMENT_HOME_SPD_X",
"P66": "MOVEMENT_HOME_SPD_Y",
"P67": "MOVEMENT_HOME_SPD_Z",
"P71": "MOVEMENT_MAX_SPD_X",
"P72": "MOVEMENT_MAX_SPD_Y",
"P73": "MOVEMENT_MAX_SPD_Z",
"P101": "ENCODER_ENABLED_X",
"P102": "ENCODER_ENABLED_Y",
"P103": "ENCODER_ENABLED_Z",
"P105": "ENCODER_TYPE_X",
"P106": "ENCODER_TYPE_Y",
"P107": "ENCODER_TYPE_Z",
"P111": "ENCODER_MISSED_STEPS_MAX_X",
"P112": "ENCODER_MISSED_STEPS_MAX_Y",
"P113": "ENCODER_MISSED_STEPS_MAX_Z",
"P115": "ENCODER_SCALING_X",
"P116": "ENCODER_SCALING_Y",
"P117": "ENCODER_SCALING_Z",
"P121": "ENCODER_MISSED_STEPS_DECAY_X",
"P122": "ENCODER_MISSED_STEPS_DECAY_Y",
"P123": "ENCODER_MISSED_STEPS_DECAY_Z",
"P125": "ENCODER_USE_FOR_POS_X",
"P126": "ENCODER_USE_FOR_POS_Y",
"P127": "ENCODER_USE_FOR_POS_Z",
"P131": "ENCODER_INVERT_X",
"P132": "ENCODER_INVERT_Y",
"P133": "ENCODER_INVERT_Z",
"P141": "MOVEMENT_AXIS_NR_STEPS_X",
"P142": "MOVEMENT_AXIS_NR_STEPS_Y",
"P143": "MOVEMENT_AXIS_NR_STEPS_Z",
"P145": "MOVEMENT_STOP_AT_MAX_X",
"P146": "MOVEMENT_STOP_AT_MAX_Y",
"P147": "MOVEMENT_STOP_AT_MAX_Z",
"P201": "PIN_GUARD_1_PIN_NR",
"P202": "PIN_GUARD_1_TIME_OUT",
"P203": "PIN_GUARD_1_ACTIVE_STATE",
"P205": "PIN_GUARD_2_PIN_NR",
"P206": "PIN_GUARD_2_TIME_OUT",
"P207": "PIN_GUARD_2_ACTIVE_STATE",
"P211": "PIN_GUARD_3_PIN_NR",
"P212": "PIN_GUARD_3_TIME_OUT",
"P213": "PIN_GUARD_3_ACTIVE_STATE",
"P215": "PIN_GUARD_4_PIN_NR",
"P216": "PIN_GUARD_4_TIME_OUT",
"P217": "PIN_GUARD_4_ACTIVE_STATE",
"P221": "PIN_GUARD_5_PIN_NR",
"P222": "PIN_GUARD_5_TIME_OUT",
"P223": "PIN_GUARD_5_ACTIVE_STATE"
}

class UIThread(threading.Thread):
    def run(this):
        global root
        root = Tk()

        endstoplabel = Label(root, text="R81")
        r82label = Label(root, text="R82")
        r84label = Label(root, text="R84")
        r85label = Label(root, text="R85")
        def send_cmd(msg):
            cmd_queue.put(msg)
        def timertick():
            try:
                msg, args, kwargs = request_queue.get_nowait()
            except Empty:
                pass
            else:
                data = msg.split(" ")
                #print(data)
                printit = True
                if data[0] == "R81":
                    endstoplabel.config(text=msg)
                    printit = False
                if data[0] == "R82":
                    r82label.config(text=msg)
                    printit = False
                if data[0] == "R84":
                    r84label.config(text=msg)
                    printit = False
                if data[0] == "R85":
                    r85label.config(text=msg)
                    printit = False
                if data[0] == "R21":
                    print(p[data[1]] + " " + msg)
                    printit = False
                if data[0] == "R00":
                    printit = False
                if printit:
                    print(msg)
            root.after(10, timertick)
        def btnclick():
            send_cmd(e1.get())
        w = Label(root, text="Send Farmbot commands")
        w.pack()
        e1 = Entry(root)
        e1.pack()
        button = Button(root, text='Send', width=30, command=btnclick)
        button.pack()
        endstoplabel.pack()
        r82label.pack()
        r84label.pack()
        r85label.pack()
        timertick()

        root.mainloop()


t = UIThread()
t.start()

def submit_to_tkinter(msg, *args, **kwargs):
    request_queue.put((msg, args, kwargs))

ser =  serial.Serial('/dev/ttyACM3', 115200, timeout=0.5)
while True:
    line = ser.readline()
    if len(line) > 0:
        s = line.decode('utf-8').strip()
        submit_to_tkinter(s)
    else:
        try:
            msg = cmd_queue.get_nowait()
        except Empty:
            pass
        else:
            ser.write((msg+"\r\n").encode('utf-8'))
