import os
import numpy as np
import tensorflow as tf
from tensorflow.keras.preprocessing.image import load_img, img_to_array
from tensorflow.keras.models import load_model
from flask import Flask, request, render_template, jsonify
from werkzeug.utils import secure_filename

app = Flask(__name__)

# Set up upload folder configuration
UPLOAD_FOLDER = os.path.join(os.getcwd(), 'uploads')
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

# Load the model
model = load_model('model.h5')
print('Model loaded. Check http://127.0.0.1:5000/')

# Map model predictions to labels
labels = {0: 'Healthy', 1: 'Powdery', 2: 'Rust'}

def get_result(image_path):
    """Preprocess the image and obtain prediction from the model."""
    img = load_img(image_path, target_size=(225, 225))
    x = img_to_array(img)
    x = x.astype('float32') / 255.0
    x = np.expand_dims(x, axis=0)
    predictions = model.predict(x)[0]
    return predictions

@app.route('/')
def dashboard():
    # Render the template. Ensure that Agrobot_weatherFeature.html exists in the templates folder.
    return render_template('Agrobot_weatherFeature.html')

@app.route('/predict', methods=['POST'])
def predict():
    # Check for the file in the request
    if 'file' not in request.files:
        return jsonify({'error': 'No file part in the request'}), 400
    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No file selected for uploading'}), 400

    # Secure the filename and save it in the configured UPLOAD_FOLDER
    filename = secure_filename(file.filename)
    file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    file.save(file_path)

    # Get predictions and map to a label
    predictions = get_result(file_path)
    predicted_label = labels[np.argmax(predictions)]

    # Optionally, you can delete the file after prediction:
    # os.remove(file_path)

    # Return the prediction result as JSON
    return jsonify({'prediction': predicted_label})

if __name__ == '__main__':
    # Run the Flask application in debug mode
    app.run(debug=True)
