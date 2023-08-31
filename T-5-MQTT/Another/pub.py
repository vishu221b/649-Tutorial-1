import paho.mqtt.publish as pub
import time

topic="IFN649"

try:
    while True:
        pub.single(topic, "Message published", hostname="54.206.96.180")
except KeyboardInterrupt:
    print("\nExiting gracefully....")
