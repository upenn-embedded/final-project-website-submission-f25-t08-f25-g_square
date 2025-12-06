---
layout: default
title: e-Puppy — Your Everyday Companion
---

# e-Puppy — Your Everyday Companion
### Developed by Team G Square

A smart robotic puppy with sensing, motion, and interactive features.

---

## Final Project Report


### 1. Video

[Insert final project video here]

* The video must demonstrate your key functionality.
* The video must be 5 minutes or less.
* Ensure your video link is accessible to the teaching team. Unlisted YouTube videos or Google Drive uploads with SEAS account access work well.
* Points will be removed if the audio quality is poor - say, if you filmed your video in a noisy electrical engineering lab.

### 2. Images

[Insert final project images here]

*Include photos of your device from a few angles. If you have a casework, show both the exterior and interior (where the good EE bits are!).*


### 3. System Block Diagram

### 4. Results

*What were your results? Namely, what was the final solution/design to your problem?*

#### 4.1 Software Requirements Specification (SRS) Results

*Based on your quantified system performance, comment on how you achieved or fell short of your expected requirements.*

*Did your requirements change? If so, why? Failing to meet a requirement is acceptable; understanding the reason why is critical!*

*Validate at least two requirements, showing how you tested and your proof of work (videos, images, logic analyzer/oscilloscope captures, etc.).*

| ID     | Description                                                                                               | Validation Outcome                                                                          |
| ------ | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| SRS-01 | The IMU 3-axis acceleration will be measured with 16-bit depth every 100 milliseconds +/-10 milliseconds. | Confirmed, logged output from the MCU is saved to "validation" folder in GitHub repository. |

#### 4.2 Hardware Requirements Specification (HRS) Results

*Based on your quantified system performance, comment on how you achieved or fell short of your expected requirements.*

*Did your requirements change? If so, why? Failing to meet a requirement is acceptable; understanding the reason why is critical!*

*Validate at least two requirements, showing how you tested and your proof of work (videos, images, logic analyzer/oscilloscope captures, etc.).*

| ID     | Description                                                                                                                        | Validation Outcome                                                                                                      |
| ------ | ---------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| HRS-01 | A distance sensor shall be used for obstacle detection. The sensor shall detect obstacles at a maximum distance of at least 10 cm. | Confirmed, sensed obstacles up to 15cm. Video in "validation" folder, shows tape measure and logged output to terminal. |
|        |                                                                                                                                    |                                                                                                                         |

### 5. Conclusion

Reflect on your project. Some questions to address:

* What did you learn from it?
* What went well?
* What accomplishments are you proud of?
* What did you learn/gain from this experience?
* Did you have to change your approach?
* What could have been done differently?
* Did you encounter obstacles that you didn’t anticipate?
* What could be a next step for this project?

Yubin:
From the final project, I learned about how to progamme for a communication protocol. I am responsible for programming for the IMU and integrating all the modules. Finally all functions works well. However there are really some challenges between the integration. At first, we tried to use a microphone connected with the ADC pin of ATmega. It can run normally when we do the test solely. But once we add the ultrasonic sensor, IMU and buzzer, the whole project cannot work. We discuss the problem with TA and decided change the method. We used I2S circuit connected with ESP32. Since ESP32 already has the I2S driver library, it was not tough for us to achieve. After changing the method, the integration still not work. We found that it was mainly because the delay function in our main file. Therefore we chose to use Timer for counting time, which was effective in the end. In the future, we will revised the motion, achieving smooth walking motion. And also I want to try the voice recognition control again, using words to control it, which is our initial goal, but difficult to achieve in a short time.

Haoliang:

Shengge:

## References

LCD library (Lab 4 Pong).