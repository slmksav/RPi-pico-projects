# MicroPython
Projects using MicroPython. Meant to be more than just tutorial copies, trying to apply my own sensors and functionalities et cetera. 
- Reaction time game with real-time results and calculations displayed on LCD
- Physically manageable PIR alarm through an OLED screen that sends information remotely over MQTT protocol

# PIR alarm IoT device
![image](https://user-images.githubusercontent.com/87731856/227073030-18f3108e-ef5e-43f5-b7a6-62d084360c2e.png)
![image](https://user-images.githubusercontent.com/87731856/227072958-64792add-cfce-425e-8a06-38eb5afa3c89.png)
*pre-casing photos*
# Reaction Game

Made with the Pico and MicroPython using: LCD1602, 1 LED, 1 330Ω resistor, two capped tactile buttons. Two players compete for the best reaction time and gain one score each round. Once a player hits five scores, the game ends. In addition, the game will calculate the average reaction based on last five reactions (all reactions are stored in an array), and display it on the LCD and terminal.

![image](https://user-images.githubusercontent.com/87731856/217179677-cc887c50-ea92-4b42-9f22-196381f6eaad.png)
*prints on the bootshell*
![image](https://user-images.githubusercontent.com/87731856/217180184-f67d563e-2eb4-4059-9400-73d95b61e869.png)
*on the left side Player 2 controller (green button), and right side Player 1 controller (red)*
![image](https://user-images.githubusercontent.com/87731856/217179739-0e0ea30c-f2a7-47fc-add9-ff3800f41042.png)
*once the LED turns off, the round is won by the player who presses their button first from that moment*
![image](https://user-images.githubusercontent.com/87731856/217179861-f2f2673a-023a-47de-b43f-ba6000db7ea0.png) 
*prints when the game ends*
![image](https://user-images.githubusercontent.com/87731856/217891107-f5e19b13-69c7-4797-b40a-a70191bce40d.png) 
*and calculation of average reaction times*
![image](https://user-images.githubusercontent.com/87731856/217180328-de646231-6430-4a98-bc42-a7ed0c53aaf9.png)
*victory screen on the LCD and scores of both players on display*
![image](https://user-images.githubusercontent.com/87731856/217895031-88c8585e-3828-490c-905d-32eff490368d.png)
*lastly, it will begin a new game after showing the average reaction times on the LCD*
