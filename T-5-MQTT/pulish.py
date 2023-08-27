import paho.mqtt.publish as pub
import time

topic="/Week5"

try:
    while True:
        pub.single(topic, "Published message!!", hostname="13.211.158.174")
except KeyboardInterrupt:
    print("\nExiting gracefully...")
