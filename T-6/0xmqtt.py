import serial
import time
import string
import json
import paho.mqtt.publish as mqtt_publish
import paho.mqtt.client as mqtt_client
from enum import Enum


ser_port="/dev/rfcomm0"
ser = serial.Serial(ser_port, 9600)
ser.write(str.encode("Starting the rpi communication...\r\n"))


class MQTT_CONSTANTS(Enum):
    AWS_HOST="3.27.119.140"
    AWS_PORT="1883"
    TOPIC_DHT_TEENSY_1="dht/teensy/1"
    TOPIC_TEENSY_1_CONTROLLER="controller/teensy/1"
 

def on_connect(client, userdata, flags, rc):
    print("Established connection to MQTT!!")
    client.subscribe(MQTT_CONSTANTS.TOPIC_TEENSY_1_CONTROLLER.value)

def on_message(client, userdata, msg):
    print(msg.topic, " ", msg.payload)
    ser.write(str.encode(str(msg.payload)[2:-1]))

client=mqtt_client.Client()
   
try:
    line_len=45
    client.on_connect=on_connect
    client.on_message=on_message
    client.connect(MQTT_CONSTANTS.AWS_HOST.value)
    client.loop_start()
    while True:
        if ser.in_waiting > 0:
            try:
                rawserial=ser.readline()
                cookedserial=rawserial.decode("utf-8").strip("\r\n")
                print(cookedserial)
                print("-"*line_len)
                print(f"Teensy says: {cookedserial}")
                if(cookedserial.lstrip().startswith('{') and cookedserial.rstrip().endswith('}')):
                    #print("Attempting to Deserialize JSON...")
                    servedserial=json.dumps(cookedserial, indent=4, ensure_ascii=False)
                    #print(servedserial)
                    mqtt_publish.single(
                        MQTT_CONSTANTS.TOPIC_DHT_TEENSY_1.value, 
                        servedserial,
                        hostname=MQTT_CONSTANTS.AWS_HOST.value
                    )
            except Exception as e:
                print(e)
                print("There was some error parsing some data, waiting for next message...")
            print("-"*line_len)
except KeyboardInterrupt:
    client.loop_stop()
    print("\nExiting gracefully....")


