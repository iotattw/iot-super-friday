# MQTT Broker

This workshop requires an MQTT Broker to be set up.

## Making it visible

Subscribe to all topics, show each incoming message with time, topic and message.
```bash
mosquitto_sub -h localhost -t '#' -v | while IFS= read -r line; do echo $line | sed -E "s/([^ ]*) (.*)/`printf "\033[39m"``date +"%T"` `printf "\033[36m"`\1\: `printf "\033[30m"`\2/"; done;
```