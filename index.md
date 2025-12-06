---
layout: default
title: e-Puppy — Your Everyday Companion
---

<div style="text-align:center; margin-top:60px; margin-bottom:40px;">
  <h1 style="font-size:3rem; font-weight:600; letter-spacing:1.5px; margin-bottom:10px;">
    e-Puppy
  </h1>
  <div style="font-size:1.4rem; font-weight:300; color:#555;">
    Your Everyday Companion
  </div>
  <div style="margin-top:12px; font-size:1rem; color:#777;">
    Developed by <strong>Team G Square</strong>
  </div>
</div>

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

<div style="border:1px solid #ddd; border-radius:10px; padding:20px; margin-bottom:20px; background:#fafafa;">
  <h3>Yubin</h3>
  <p>
    From the final project, I learned how to program communication protocols and integrate
    multiple modules. I was responsible for IMU programming and system integration.
    While individual modules worked well, integration introduced challenges.
  </p>
  <p>
    Initially, we used an ADC-based microphone on the ATmega, which worked in isolation
    but failed once the ultrasonic sensor, IMU, and buzzer were added.
    After consulting with the TA, we switched to an I2S-based solution using ESP32.
    We later identified blocking delays as the main issue and resolved it using timers.
  </p>
  <p>
    In the future, we plan to improve motion smoothness and revisit voice-recognition
    control using spoken commands.
  </p>
</div>

<div style="border:1px solid #ddd; border-radius:10px; padding:20px; margin-bottom:20px; background:#fafafa;">
  <h3>Haoliang</h3>
  <p>
    I learned how to use a mircophone to detect the voice information using I2S protocol, and leverage it to 
    control the LCD and servo motors. Also, I have known better about the bare metal program. It is kind of overwhelmed 
    when we use it to tackle a lot of tasks. So next time I may use RTOS instead of bare metal. For me, the ultra sonic
    and the LCD works well. I am proud of the voice control, which recognizes the number of claps as orders and the cooperation
    of the four servo motors. I think the walking motion could have been done differently since we could produce another PWM to 
    drive the motors or stick something to the legs to enhance the friction if we have one more day. One obstacle is that it was 
    harder than we thought to use "words" to control the dog. After we tried two ways, we gave it up and chose the claps. But on 
    the Demo day I saw another team had sucessfully implemented the function. I asked them and they told me that they used a 
    voice module which they found in Dektin. So next time we should explore the Detkin carefully. For the next step, I think 
    we can try a different PWM to drive the motors to see if the legs can sucessfully move the body, or enhancing some friction.
  </p>
</div>

<div style="border:1px solid #ddd; border-radius:10px; padding:20px; margin-bottom:20px; background:#fafafa;">
  <h3>Shengge</h3>
  <p>
    From this final program, I have learned much more about the I2C and I2S protocols and gained a comprehensive understanding of how to integrate different modules of code. I was responsible for 3D printing, ESP32 modeling, and the PWM generator. I also learned more about servo motors and how to use Arduino for voice recognition.At the beginning, we planned to use the ATmega328PB for voice recognition through the ADC. However, after integrating the code, we found a significant delay, which prevented us from achieving our goals. Therefore, we decided to use a microphone connected to the ESP32 and performed voice recognition on the ESP32 instead. This greatly reduced the delay in the overall system.One of the challenges we encountered was measuring the size of the servo motors because no dimensional information was provided in the datasheet. As a result, the hole size in our 3D-printed model did not match the servo motor dimensions. We had to use tape to wrap the motor to ensure it remained stable. In the next step, we could design and 3D-print a more realistic leg for our robot dog. We could also create a more suitable frame to eliminate the need for tape and improve overall stability.
  </p>
</div>

## References

LCD library (Lab 4 Pong).
