import serial
import time
import string
import json

ser_port="/dev/rfcomm1"
ser = serial.Serial(ser_port, 9600)
ser.write(str.encode("Starting the rpi communication...\r\n"))

try:
    f_json={}
    #c=0
    line_len=45
    while True:
        if ser.in_waiting > 0:
            rawserial=ser.readline()
            cookedserial=rawserial.decode("utf-8").strip("\r\n")
            # print(c)
            print("-"*line_len)
            try:
                # Because sensor readings will come through in the format <reading-type>: <reading-value>
                if cookedserial and "|" in cookedserial and ":" in cookedserial:
                    friedserial=cookedserial.split("|")
                    for fried in friedserial:
                        fried=fried.split(":")
                        f_json[fried[0].strip()]=fried[1].strip()
                else:
                    #handle other serial inputs which are not readings from the sensors
                    print(f"Teensy says: {cookedserial}")
            except Exception as e:
                print(e)
                print("There was some error parsing the data, waiting for next message...")
            if f_json and len(f_json):
                print(json.dumps(f_json, indent=4, ensure_ascii=False))
            print("-"*line_len)
            #c+=1
except KeyboardInterrupt:
    print("\nExiting gracefully....")

