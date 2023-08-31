import paho.mqtt.publish as mqtt_publisher

TEENSY_1_CONTROLLER_TOPIC="controller/teensy/1"
MQTT_BROKER_HOST="0.0.0.0" #Change this to the EC2 MQTT broker instance url accordingly

try:
    while True:
        _user_command=input("Input your command(enter q for quitting): ")
        if _user_command.lower()  == 'q':
            print("Exiting ...")
            exit(1)
        mqtt_publisher.single(TEENSY_1_CONTROLLER_TOPIC, _user_command, hostname=MQTT_BROKER_HOST)
        print("Command published successfully!!")
except KeyboardInterrupt:
    print("\nExiting gracefully....")
    exit(1)

