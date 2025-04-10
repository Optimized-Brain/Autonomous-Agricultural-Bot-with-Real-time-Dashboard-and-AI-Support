
# Autonomous Agricultural Bot with Real-time Dashboard and AI Support

A Flask-based web dashboard that uses deep learning to classify plant diseases from uploaded images and provides live updates through charts, weather forecast information, and a real-time webcam feed. This project leverages TensorFlow for model predictions, Flask for the backend server, Chart.js for live sensor data visualization, Leaflet for mapping weather data, and Firebase for real-time data updates.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Working](#working)
- [Usage](#usage)
- [Acknowledgements](#acknowledgements)

## Features

- **Plant Disease Classification:**  
  Upload a leaf image to get an instant prediction of plant health status (Healthy, Powdery, or Rust).

- **Live Dashboard:**  
  - Real-time charts for temperature, humidity, and soil moisture using Chart.js.
  - A live webcam feed for surveillance.
  - Weather forecasts and location mapping using Leaflet and OpenWeatherMap API.

- **Realtime Updates:**  
  - Integrated with Firebase for live data fetching.
  - Dynamic chart updates every few seconds.

- **Modern UI:**  
  Responsive and sophisticated design that adapts to different screen sizes.

## Prerequisites

Ensure that you have the following installed:
- **Python 3.6+**
- **pip** (Python package installer)
- **Virtualenv** (optional but recommended)

## Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/plant-disease-detection-dashboard.git
   cd plant-disease-detection-dashboard
   ```

2. **Create & Activate a Virtual Environment** (optional, but recommended)
   ```bash
   python -m venv venv
   # On Windows:
   venv\Scripts\activate
   # On macOS/Linux:
   source venv/bin/activate
   ```

3. **Install Dependencies**

   ```
   Flask
   tensorflow
   numpy
   opencv-python
   Pillow
   werkzeug
   firebase-admin
   ```

5. **Model File**
   
   Ensure that your trained model (`model.h5`) is placed in the root directory of the project.

6. **Firebase & API Keys Configuration**
   
   Verify that your Firebase configuration details and OpenWeatherMap API key are correctly set in the respective JavaScript and Flask code sections.

## Working


  The Plant Disease Detection Dashboard is a sophisticated web application designed to assist users in identifying plant diseases through image analysis and to provide real-time environmental data. It integrates several technologies to deliver a seamless and informative experience. Here's an in-depth look at its components and functionalities:

**1. Plant Disease Classification**

- **Image Upload and Processing:**
  - Users can upload images of plant leaves via the dashboard's intuitive interface.
  - Upon submission, the image is sent to the server where it's preprocessed to match the input requirements of the predictive model.

- **Deep Learning Model Prediction:**
  - A Convolutional Neural Network (CNN) model, trained using TensorFlow/Keras, analyzes the preprocessed image to classify the plant's condition.
  - The model can identify various categories, such as "Healthy," "Powdery Mildew," or "Rust."
  - The prediction, along with a confidence score, is then displayed to the user.

**2. Live Environmental Data Visualization**

- **Real-time Sensor Data:**
  - The dashboard fetches live data from sensors measuring parameters like temperature, humidity, and soil moisture.
  - This data is stored and retrieved from Firebase, ensuring real-time updates.

- **Dynamic Charting:**
  - Utilizing Chart.js, the application renders dynamic charts that visually represent the sensor data.
  - These charts update at regular intervals, providing users with the latest environmental readings.

**3. Web Surveillance Feature**

- **Live Webcam Feed:**
  - Users have the option to enable their device's webcam to stream live video directly on the dashboard.
  - This feature is particularly useful for monitoring plant conditions in real-time.

**4. Weather Forecast Integration**

- **Geolocation and Mapping:**
  - With user permission, the application accesses the device's geolocation data.
  - Using Leaflet.js, it displays an interactive map centered on the user's location.

- **Weather Data Retrieval:**
  - The dashboard integrates with the OpenWeatherMap API to fetch current weather conditions and forecasts for the user's location.
  - This information aids in understanding external factors that might influence plant health.

**5. Technical Architecture**

- **Backend:**
  - Built with Flask, a lightweight Python web framework, the server handles HTTP requests, processes images, interacts with the predictive model, and serves dynamic content.

- **Frontend:**
  - The user interface is crafted using HTML, CSS, and JavaScript, ensuring a responsive and user-friendly experience.
  - AJAX calls facilitate asynchronous data fetching, enhancing the dashboard's responsiveness.

- **Model Integration:**
  - The TensorFlow/Keras model is loaded into the Flask application at startup, allowing for efficient on-the-fly predictions without reloading the model for each request.

- **Data Storage and Real-time Updates:**
  - Firebase serves as the real-time database, storing sensor data and ensuring that the dashboard reflects the most current information.

**6. User Experience Flow**

- Upon accessing the dashboard, users are presented with real-time environmental data visualizations.
- They can navigate to the "AI Prediction" section to upload a plant leaf image for disease analysis.
- The "Web Surveillance" tab allows users to monitor their plants via a live webcam feed.
- By enabling geolocation, users can view localized weather forecasts and maps in the "Weather Forecast" section.


---

## 🌱 AI-Powered Support

This project utilizes a Convolutional Neural Network (CNN) built from scratch to classify and detect plant diseases from leaf images. The model is trained on a diverse dataset of plant leaves exhibiting various diseases and healthy conditions.

### Technical Overview:
-  Architecture: Custom CNN with multiple convolutional layers, pooling layers, and fully connected dense layers.
-  Input: Pre-processed leaf images resized to uniform dimensions.
-  Feature Extraction: Convolution layers detect edges, textures, color patterns, and disease-specific symptoms.
-  Classification: Softmax output layer classifies images into respective disease categories.
-  Loss Function: Categorical Crossentropy
-  Optimizer: Adam Optimizer
-  Evaluation Metrics: Accuracy, Loss, Precision, Recall
-  Deployment: The trained model is integrated into the web interface for real-time image prediction.

### Workflow:
1. User uploads a leaf image via the web interface.
2. The image is passed to the backend where preprocessing (resizing, normalization) is done.
3. The CNN model predicts the class of disease based on learned features.
4. The prediction result is displayed to the user.

We used [Plant Disease Recognition Dataset — Kaggle](https://www.kaggle.com/datasets/rashikrahmanpritom/plant-disease-recognition-dataset?resource=download)
for plant disease data.


### Technologies Used:
|Component|Technology|
|---------|-----------|
|Model|Custom CNN|
|Framework|TensorFlow / Keras|
|Language|Python|
|Deployment|Flask Backend API|
|Frontend Communication|AJAX Call to /predict Route|



### AI-Powered Chatbot

An AI-driven chatbot was integrated into the Plant Disease Detection website to enhance user interaction and provide automated support. The chatbot was built using Chatbase and leverages OpenAI's GPT-4o mini model for natural language understanding and response generation.


#### Technical Specifications:

- #### AI Model:  
  → OpenAI GPT-4o mini (via Chatbase platform)

- #### Purpose:  
  → Automate user support for:  
  - Plant disease-related queries  
  - Usage guidance for the web app  
  - Troubleshooting assistance  

- #### Integration:  
  - Embedded using Chatbase-provided widget script.
  - API key-based secure communication.
  - Custom-trained on project-specific datasets and FAQs.
  - Response tuning via Chatbase configuration panel.

- #### Functionalities:
  - NLP-based dynamic query handling.
  - Context-aware responses.
  - Fallback message customization.
  - Website-specific knowledge embedding.


#### Advantages:
- Instant query resolution.
- Scalable and easily updatable.
- No manual supervision required.
- 24x7 available assistant for user convenience.

---

## Usage

1. **Run the Flask Application**

   From the project root, run:
   ```bash
   python app.py
   ```

   The server should start with a message similar to:
   ```
   Model loaded. Check http://127.0.0.1:5000/
   ```

2. **Access the Dashboard**

   Open your web browser and navigate to [http://127.0.0.1:5000/](http://127.0.0.1:5000/).

3. **Using the Dashboard**
   - **Home Tab:**  
     View live sensor data charts.
   - **AI Prediction Tab:**  
     Upload a plant leaf image to receive a disease classification prediction.
   - **Web Surveillance Tab:**  
     Enable the webcam to stream live video.
   - **Weather Forecast Tab:**  
     Allow geolocation access to see local weather and map updates.


## Acknowledgements

- [TensorFlow](https://www.tensorflow.org/) for model development.
- [Flask](https://flask.palletsprojects.com/) for the web framework.
- [Chart.js](https://www.chartjs.org/) for real-time charts.
- [Leaflet](https://leafletjs.com/) for interactive maps.
- [Firebase](https://firebase.google.com/) for real-time updates.
- [OpenWeatherMap](https://openweathermap.org/) for weather data.


---
