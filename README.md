# Interactive Robotic Head

An interactive robotic head that combines real-time facial emotion recognition, Arduino-based servo control, voice interaction, Gemini AI, and emotion-based music playback.

## Features

- **Real-Time Face Detection:** Detects faces from a webcam using MediaPipe.
- **Emotion Recognition:** Recognizes facial expressions using HSEmotion and DeepFace.
- **Robotic Facial Expressions:** Controls servo motors to display happy, sad, neutral, angry, and surprised expressions.
- **Voice Assistant:** Supports speech recognition and text-to-speech responses.
- **Gemini AI Integration:** Responds to user queries through conversational AI.
- **Emotion-Based Music:** Plays music according to the detected emotion.
- **Facial Landmark Visualization:** Uses MediaPipe Face Mesh to detect and visualize facial landmarks.

## Tech Stack

- **Programming Languages:** Python, Arduino C++
- **Computer Vision:** OpenCV, MediaPipe
- **Emotion Recognition:** HSEmotion, DeepFace
- **AI:** Google Gemini
- **Speech Processing:** SpeechRecognition, pyttsx3
- **Audio Playback:** Pygame
- **Hardware Control:** Arduino, Servo motors

## Hardware Configuration

The robotic head uses six servo motors connected to the Arduino.

| Facial Component | Arduino Pin |
|---|---:|
| Left Eye | 9 |
| Right Eye | 10 |
| Left Cheek | 11 |
| Right Cheek | 12 |
| Upper Jaw | 13 |
| Lower Jaw | 6 |

**Serial Communication:** 9600 baud

### Supported Arduino Commands

| Command | Expression |
|---|---|
| `H` | Happy |
| `S` | Sad |
| `N` | Neutral |
| `A` | Angry |
| `U` | Surprise |

## Project Structure

| File | Description |
|---|---|
| `Arduino.ino` | Controls the robotic head's servos and facial expressions. |
| `emotion.py` | Performs webcam-based facial emotion recognition using DeepFace. |
| `facecapture.py` | Detects faces and visualizes facial landmarks using MediaPipe Face Mesh. |
| `interaction.py` | Implements voice interaction and Gemini AI responses. |
| `songs.py` | Plays music based on a user-selected mood. |
| `test.py` | Integrates emotion recognition, voice interaction, Gemini AI, and mood-based music playback. |

*Note: These Python files represent separate components and prototypes; their features are not automatically integrated into a single application.*

## Installation

Install the required Python packages:

```bash
pip install opencv-python numpy mediapipe hsemotion-onnx deepface matplotlib pygame SpeechRecognition pyttsx3 python-dotenv google-genai pyserial
```

Install only the dependencies required by the component you intend to run.

## Configuration

1. Upload `Arduino.ino` to the Arduino using the Arduino IDE.
2. Connect the servo motors according to the hardware configuration.
3. Update the webcam index, serial port, and music-folder paths in the relevant Python files.
4. Configure the Gemini API key in a `.env` file:

```dotenv
GEMINI_API_KEY=your_api_key_here
```

Load the key using `load_dotenv()` and `os.getenv("GEMINI_API_KEY")`.

**Security:** Never commit API keys or `.env` files to GitHub. Revoke or rotate any API key previously exposed in source code.

## Running the Project

Run the individual Python components as required:

```bash
python emotion.py
python facecapture.py
python interaction.py
python songs.py
python test.py
```

## Future Improvements

- Integrate emotion recognition directly with Arduino servo control in the main assistant.
- Add talking and singing.
- Improve transitions between facial expressions.
- Enhance emotion classification and expression mapping.
- Optimize real-time performance and hardware synchronization.
 
