##############################################################
#   @file       :   Hand_Tracking_MQTT.py                    #
#   @brief      :   Enables camera to recognize hands,       #
#                   interpret gestures, and control          #
#                   smart car via MQTT.                      #
#   @auther     :   Ziad Mohammed Fathi Mohammed.            #
##############################################################
# ---------------- imports section Start ---------------- #
import cv2
import mediapipe as mp
import paho.mqtt.client as mqtt
import time
# ---------------- imports section End ---------------- #

# ---------------- MQTT Configuration Start ---------------- #
MQTT_BROKER = "192.168.100.25"
MQTT_PORT = 1883

# MQTT Topics
TOPIC_STOP = "/smart_car/control/stop"
TOPIC_FORWARD = "/smart_car/control/forward"
TOPIC_BACKWARD = "/smart_car/control/backward"
TOPIC_RIGHT = "/smart_car/control/right"
TOPIC_LEFT = "/smart_car/control/left"

ALL_TOPICS = [TOPIC_STOP, TOPIC_FORWARD, TOPIC_BACKWARD, TOPIC_RIGHT, TOPIC_LEFT]
# ---------------- MQTT Configuration End ---------------- #

# ---------------- MQTT Functions Start ---------------- #
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker successfully!")
    else:
        print(f"Failed to connect, return code {rc}")

def on_publish(client, userdata, mid):
    print(f"Message published: {mid}")

# Initialize MQTT Client
mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_publish = on_publish

try:
    mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
    mqtt_client.loop_start()
    print("MQTT Client started")
except Exception as e:
    print(f"Error connecting to MQTT: {e}")
# ---------------- MQTT Functions End ---------------- #

# ---------------- Hand Control Function Start ---------------- #
def send_car_command(finger_count):
    """Send command based on finger count and reset other topics to 0"""
    
    # Map finger count to topic
    finger_map = {
        0: TOPIC_STOP,
        1: TOPIC_LEFT,
        2: TOPIC_RIGHT,
        3: TOPIC_BACKWARD,
        4: TOPIC_FORWARD,
        5: TOPIC_STOP
    }
    
    active_topic = finger_map.get(finger_count, None)
    
    if active_topic:
        # Send 1 to active topic
        mqtt_client.publish(active_topic, "1")
        print(f"Fingers: {finger_count} -> Sent '1' to {active_topic}")
        
        # Send 0 to all other topics
        for topic in ALL_TOPICS:
            if topic != active_topic:
                mqtt_client.publish(topic, "0")
        
        time.sleep(0.1)  # Small delay to prevent flooding
# ---------------- Hand Control Function End ---------------- #

# ---------------- initialization variables section Start ---------------- #
cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils
tipIds = [4, 8, 12, 16, 20]

previous_finger_count = -1  # Track previous state to avoid repeated sends
# ---------------- initialization variables section End ---------------- #

# ---------------- Main Program section Start ---------------- #
print("Starting Hand Tracking MQTT Controller...")
print("Press 'x' to exit")

while True:
    stat, frame = cap.read()
    frame = cv2.flip(frame, 1)
    img_RGB = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    res = hands.process(img_RGB)
    lmList = []
    
    if res.multi_hand_landmarks:
        for handLms in res.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                _high, _width, _cm = frame.shape
                cx, cy = int(lm.x * _width), int(lm.y * _high)
                lmList.append([id, cx, cy])
                mpDraw.draw_landmarks(frame, handLms, mpHands.HAND_CONNECTIONS)
                
                if id == 8:
                    cv2.circle(frame, (cx, cy), 20, (0, 255, 0), cv2.FILLED)
        
        if len(lmList) == 21:
            fingers = []
            
            # Thumb
            if lmList[tipIds[0]][1] < lmList[tipIds[0] - 2][1]:
                fingers.append(1)
            else:
                fingers.append(0)
            
            # Other fingers
            for tip in range(1, 5):
                if lmList[tipIds[tip]][2] < lmList[tipIds[tip] - 2][2]:
                    fingers.append(1)
                else:
                    fingers.append(0)
            
            totalFingers = fingers.count(1)
            
            # Send MQTT command only if finger count changed
            if totalFingers != previous_finger_count:
                send_car_command(totalFingers)
                previous_finger_count = totalFingers
            
            # Display finger count and command on frame
            command_text = {
                0: "STOP", 1: "LEFT", 2: "RIGHT", 
                3: "BACKWARD", 4: "FORWARD", 5: "STOP"
            }
            
            cv2.putText(frame, f'{totalFingers} Fingers', (40, 80), 
                       cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 5)
            cv2.putText(frame, f'CMD: {command_text[totalFingers]}', (40, 150), 
                       cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 255, 0), 4)
# ---------------- Main Program section End ---------------- #

# ---------------- Show Data Start ---------------- #
    cv2.imshow('Hand Tracker - MQTT Car Control', frame)
    
    if cv2.waitKey(5) & 0xff == ord("x"):
        break
# ---------------- Show Data End ---------------- #

# ---------------- Cleanup Start ---------------- #
cap.release()
cv2.destroyAllWindows()
mqtt_client.loop_stop()
mqtt_client.disconnect()
print("Program terminated")
# ---------------- Cleanup End ---------------- #
