# -------------------------
# Real-time Emotion Detection + Arduino Servo Control
# -------------------------

import cv2, numpy as np, time, serial
from collections import deque
import mediapipe as mp
from hsemotion_onnx.facial_emotions import HSEmotionRecognizer

# -------------------------
# 1. Choose pretrained model
# -------------------------
MODEL_NAME = 'enet_b2_8'
fer = HSEmotionRecognizer(model_name=MODEL_NAME)

# -------------------------
# 2. Initialize MediaPipe face detector
# -------------------------
mp_fd = mp.solutions.face_detection.FaceDetection(
    model_selection=1,
    min_detection_confidence=0.6
)

# -------------------------
# 3. Emotion classes
# -------------------------
CLASSES = ['Anger', 'Contempt', 'Disgust', 'Fear', 'Happiness',
           'Neutral', 'Sadness', 'Surprise']

# -------------------------
# 4. Arduino Serial Setup
# -------------------------
# ⚠️ Change 'COM3' to your Arduino port
# Windows → COMx , Linux/Mac → /dev/ttyUSB0 or /dev/ttyACM0
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # wait for Arduino to reset

# Map emotions to single-character commands
emotion_map = {
    "Happiness": "H",
    "Sadness": "S",
    "Anger": "A",
    "Neutral": "N",
    "Surprise": "U"
}

last_sent = None  # track last emotion sent to Arduino

# -------------------------
# 5. Temporal smoothing buffer
# -------------------------
SMOOTH_N = 8
prob_buf = deque(maxlen=SMOOTH_N)

# -------------------------
# 6. Webcam Setup
# -------------------------
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

print("Press 'q' to quit.")
t0, frames = time.time(), 0

# -------------------------
# 7. Main Loop
# -------------------------
while True:
    ok, frame = cap.read()
    if not ok:
        break

    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = mp_fd.process(rgb)

    if results.detections:
        h, w = frame.shape[:2]

        for det in results.detections:
            bbox = det.location_data.relative_bounding_box
            x1 = max(int(bbox.xmin * w) - 10, 0)
            y1 = max(int(bbox.ymin * h) - 10, 0)
            x2 = min(int((bbox.xmin + bbox.width) * w) + 10, w-1)
            y2 = min(int((bbox.ymin + bbox.height) * h) + 10, h-1)

            face = frame[y1:y2, x1:x2]
            if face.size == 0:
                continue

            # Predict emotions
            emo, probs = fer.predict_emotions(face, logits=False)
            prob_buf.append(probs)
            avg = np.mean(prob_buf, axis=0)

            cls_id = int(np.argmax(avg))
            emotion = CLASSES[cls_id]
            label = f"{emotion} {avg[cls_id]*100:.1f}%"

            # Draw results
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0,255,0), 2)
            cv2.putText(frame, label, (x1, max(25, y1-10)),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0,255,0), 2)

            # -------------------------
            # Send command to Arduino
            # -------------------------
            if emotion in emotion_map:
                if last_sent != emotion:   # only send if changed
                    arduino.write(emotion_map[emotion].encode())
                    last_sent = emotion
                    print(f"Sent to Arduino: {emotion}")

    # Show FPS every 20 frames
    frames += 1
    if frames % 20 == 0:
        fps = frames / (time.time() - t0)
        cv2.putText(frame, f"FPS: {fps:.1f}", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255,255,255), 2)

    cv2.imshow("Realtime Emotion + Arduino Control", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# -------------------------
# 8. Cleanup
# -------------------------
cap.release()
cv2.destroyAllWindows()
arduino.close()
