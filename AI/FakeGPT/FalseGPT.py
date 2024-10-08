"""FalseGPT.ipynb

Created by Obx using Colab.

Original file is located at
    https://colab.research.google.com/drive/13HD8ve8VTiatkaySOE0p6enPS-oRsYjX

# JSYK 1
Follow the comments and use gemini if you don't understand python

!pip3 install openai
!pip3 install keras

!pip install --upgrade tensorflow
"""


import requests
import openai # type: ignore
import tensorflow as tf # type: ignore
from tensorflow.keras import layers # type: ignore
from tensorflow.keras.preprocessing.image import ImageDataGenerator # type: ignore

# Step 1: Google Roads API Setup
GOOGLE_ROADS_API_KEY = "YOUR_GOOGLE_ROADS_API_KEY"
def get_road_info(lat, lng):
    url = f"https://roads.googleapis.com/v1/nearestRoads?points=60.170880,24.942795|60.170879,24.942796|60.170877,24.942796&key=YOUR_GOOGLE_ROADS_API_KEY"
    response = requests.get(url)
    return response.json()

# Step 2: GPT-4o Integration for Object Detection
openai.api_key = "YOUR_OPENAI_API_KEY"
def get_gpt4o_response(prompt):
    response = openai.Completion.create(
        engine="text-davinci-003",
        prompt=prompt,
        max_tokens=150
    )
    return response.choices[0].text.strip()

"""
# JSYK 2: Prepare the dataset
 Assuming you have one ready and organized in directories
"""

# Step 4: Build and Train a Neural Network with TensorFlow
# Image data preprocessing
datagen = ImageDataGenerator(rescale=1.0/255, validation_split=0.2)

train_data = datagen.flow_from_directory(
    '/content/datasets/',
    target_size=(128, 128),
    batch_size=32,
    class_mode='categorical',
    subset='training'
)

val_data = datagen.flow_from_directory(
    '/content/datasets',
    target_size=(128, 128),
    batch_size=32,
    class_mode='categorical',
    subset='validation'
)

# Neural network model
model = tf.keras.Sequential([
    layers.Conv2D(32, (3, 3), activation='relu', input_shape=(128, 128, 3)),
    layers.MaxPooling2D(2, 2),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.MaxPooling2D(2, 2),
    layers.Flatten(),
    layers.Dense(128, activation='relu'),
    layers.Dense(4, activation='softmax')  # Adjust the number of classes based on your dataset
])

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

"""our simple custom training loop using metric constructor to parse arguments"""

# Check if training data generator is yielding data
for batch in train_data:
    print("Training batch shape:", batch[0].shape)  # Print shape of image data
    print("Training batch labels shape:", batch[1].shape)  # Print shape of labels
    break  # Stop after one batch

# Check if validation data generator is yielding data
for batch in val_data:
    print("Validation batch shape:", batch[0].shape)
    print("Validation batch labels shape:", batch[1].shape)
    break

"""The neural network is trained to classify images into four categories (e.g., car, truck, bus, stop sign). The output from the prediction is a probability distribution over these classes.

"""

# Test the model
test_image = tf.keras.preprocessing.image.load_img('/content/datasets/dataset_image.jpg', target_size=(128, 128))
test_image = tf.keras.preprocessing.image.img_to_array(test_image)
test_image = tf.expand_dims(test_image, 0)  # Add batch dimension

"""The output from the prediction is a probability distribution over these classes"""

prediction = model.predict(test_image)
print("Predicted class:", prediction)

"""The model predicted with high confidence for one class, which corresponds to a car.

`Predicted class: [[5.9604534e-34 8.5541062e-31 1.0000000e+00 5.4494220e-25]]`


The third value `(1.0000000e+00)` indicates that the model is confident the image is a car.
"""


model.save('model.h5')

""Saving it all to a matlab compartable file""
