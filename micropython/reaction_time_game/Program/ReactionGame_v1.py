import machine
import utime
import urandom
import RGB1602
import time
import math

colorR = 64
colorG = 128
colorB = 64
rgb1 = (148,0,110) 
rgb2 = (255,0,255) 
rgb3 = (144,249,15) 
rgb4 = (0,128,60) 
rgb5 = (255,209,0)
rgb6 = (248,248,60)
rgb7 = (80,80,145) 
rgb8 = (255,0,0) 
rgb9 = (0,255,0)

lcd = RGB1602.RGB1602(16,2)
led = machine.Pin(15, machine.Pin.OUT)
left_button = machine.Pin(14, machine.Pin.IN, machine.Pin.PULL_DOWN)
right_button = machine.Pin(16, machine.Pin.IN, machine.Pin.PULL_DOWN)

player2_wins = 0
player1_wins = 0
fastest_button = None

def button_handler(pin):
    global fastest_button
    if not fastest_button:
        fastest_button = pin
        timer_reaction = utime.ticks_diff(utime.ticks_ms(), timer_start)
        if fastest_button is left_button:
            print("Player 1 won the round! \n")
            global player1_wins
            player1_wins += 1
            if timer_reaction < 500:
                print("Wow! Quick reaction time Player 1!: " + str(timer_reaction) + " milliseconds!")
            elif timer_reaction >= 500 and timer_reaction < 700:
                print("Good reaction time Player 1!: " + str(timer_reaction) + " milliseconds!")
            else:
                print("Slow reaction time Player 1!: " + str(timer_reaction) + " milliseconds!")
        elif fastest_button is right_button:
            print("Player 2 won the round! \n")
            global player2_wins
            player2_wins += 1
            if timer_reaction < 500:
                print("Wow! Quick reaction time Player 2!: " + str(timer_reaction) + " milliseconds!")
            elif timer_reaction >= 500 and timer_reaction < 700:
                print("Good reaction time Player 2!: " + str(timer_reaction) + " milliseconds!")
            else:
                print("Slow reaction time Player 2!: " + str(timer_reaction) + " milliseconds!")

while player2_wins < 5 and player1_wins < 5:
    fastest_button = None
    timer_start = utime.ticks_ms()
    left_button.irq(trigger=machine.Pin.IRQ_RISING, handler=button_handler)
    right_button.irq(trigger=machine.Pin.IRQ_RISING, handler=button_handler)
    led.value(0)
    lcd.clear()
    lcd.setCursor(0, 0)
    lcd.printout("Fastest wins!")
    lcd.setCursor(0, 1)
    lcd.printout("P2: " + str(player2_wins) + "    P1: " + str(player1_wins))
    print("GO!")
    utime.sleep(5)
    print("Player 2: " + str(player2_wins) + " ---" + " Player 1: " +str(player1_wins) + "\n")
    print("Ready, set..")
    lcd.clear()
    lcd.setCursor(0, 0)
    lcd.printout("Ready, set...")
    lcd.setCursor(0, 1)
    lcd.printout("P2: " + str(player2_wins) + "    P1: " + str(player1_wins))
    led.value(1)
    utime.sleep(urandom.uniform(2, 13))
    lcd.clear()

if player2_wins == 5:
    lcd.clear()
    lcd.setCursor(0, 0)
    lcd.printout("Player 2 Victory!")
    lcd.setCursor(0, 1)
    lcd.printout("P2: " + str(player2_wins) + "    P1: " + str(player1_wins))
    print("Player 2 wins the overall game with 5 wins!")
else:
    lcd.clear()
    lcd.setCursor(0, 0)
    lcd.printout("P1 Victory!")
    lcd.setCursor(0, 1)
    lcd.printout("P2: " + str(player2_wins) + "    P1: " + str(player1_wins))
    print("Player 1 wins the overall game with 5 wins!")