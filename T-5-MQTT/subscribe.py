import paho.mqtt.client as mqtt

topic="/Week5"

def on_connect(client, userdata, flags, rc):
    print("Established connection to MQTT!!")
    print("Conn Res: " + str(rc))

    client.subscribe(topic)

def on_message(client, userdata, msg):
    print(msg.topic, " ", msg.payload))

client=mqtt.Client()
client.on_connect=on_connect
client.on_message=on_message

client.Connect("13.211.158.174")

client.loop_forever()
