import paho.mqtt.client as mqtt

# topic="IFN649"
topic="/Week5"

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT")
    print("Connection result: " + str(rc))

    client.subscribe(topic)

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))

client = mqtt.Client()
client.on_connect=on_connect
client.on_message=on_message

client.connect("13.211.158.174", 1883, 60)

client.loop_forever()
