
# Autonomous Agricultural Bot with Real-time Dashboard and AI Support

A Flask-based web dashboard that uses deep learning to classify plant diseases from uploaded images and provides live updates through charts, weather forecast information, and a real-time webcam feed. This project leverages TensorFlow for model predictions, Flask for the backend server, Chart.js for live sensor data visualization, Leaflet for mapping weather data, and Firebase for real-time data updates.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
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

   Install the required Python packages using pip (make sure you have a `requirements.txt` file; if not, you can create one based on the packages mentioned in the repository).
   ```bash
   pip install -r requirements.txt
   ```
   A sample `requirements.txt` might include:
   ```
   Flask
   tensorflow
   numpy
   opencv-python
   Pillow
   werkzeug
   firebase-admin
   ```

4. **Model File**
   
   Ensure that your trained model (`model.h5`) is placed in the root directory of the project.

5. **Firebase & API Keys Configuration**
   
   Verify that your Firebase configuration details and OpenWeatherMap API key are correctly set in the respective JavaScript and Flask code sections.

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
