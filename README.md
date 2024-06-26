# Sign Language Glove Project

## Overview
This project focuses on developing a glove-based system capable of accurately recognizing and interpreting sign language gestures in real-time. The primary aim is to bridge the communication gap between sign language users and non-signers by leveraging advanced sensor technologies and machine learning algorithms.

## Motivation
The Deaf community in Austria, consisting of approximately 8,000-10,000 individuals, faces significant communication barriers. Despite advancements in reducing these barriers, there remains a shortage of sign language interpreters. This project aims to develop a technological solution that facilitates seamless communication for deaf individuals.

## Problem Statement
Current technological solutions often fail to accurately recognize and interpret sign language gestures, leading to misunderstandings. This project aims to develop a comfortable, non-restrictive glove that accurately recognizes and interprets Austrian Sign Language (ÖGS) gestures in real-time.

## Goal
To create a dual-glove system that enhances the recognition and translation of two-handed signs, improving communication for deaf and hard-of-hearing individuals.

## Goals
- **Achieve Real-Time Translation:** Develop a system that captures and interprets gestures performed by the user instantaneously.
- **Implement a Dual-Glove System:** Utilize sensors on both gloves to accurately track movements and positions of both hands.
- **Ensure Comfort and Flexibility:** Design gloves that are comfortable, lightweight, and adjustable to accommodate diverse hand sizes.
- **Integrate Advanced Sensors:** Incorporate flex sensors and an Inertial Measurement Unit (IMU) to capture detailed hand and finger movements.

## Implementation
### Hardware
- **Flex Sensors:** Placed on each finger and the wrist to capture flexion and extension movements.
- **IMU Sensor:** Positioned on the wrist to track hand position in 3D space.
- **Microcontroller:** ESP32 microcontroller interfaces with sensors to process data.

### Software
- **Data Acquisition:** Sensors are calibrated and data is captured using Arduino. Data is stored in text files and preprocessed for machine learning.
- **Machine Learning Model:** A custom neural network model developed in TensorFlow’s Keras API to classify and interpret sign language gestures.

## Results
- **Accuracy:** The model achieved a training accuracy of 92.22% and a test accuracy of 86.67%, indicating good generalization to unseen data.
- **Sign Recognition:** High accuracy in recognizing specific signs such as 'Hallo', 'Baba', 'Bitte', 'Danke', and 'Ich'.

## Future Work
- **Improved Sensors:** Incorporate longer or additional sensors to capture a broader range of finger movements.
- **Enhanced Materials:** Use more durable and form-fitting materials to maintain sensor position and improve data accuracy.
- **Additional Technologies:** Integrate cameras or depth sensors to capture non-manual markers like facial expressions and body movements.
- **User Testing:** Conduct extensive user testing to gather feedback and refine the design.

## Contributors
- **Julia Jackermaier**
- **Martina Adler**
