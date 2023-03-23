from machine import Pin,SPI
import time
import framebuf
from umqtt.simple import MQTTClient


# minimal library code for the OLED module

class OLED_1inch3(framebuf.FrameBuffer):
    def __init__(self): 
        self.width = 128
        self.height = 64
        
        self.cs = Pin(CS,Pin.OUT)
        self.rst = Pin(RST,Pin.OUT)
        
        self.cs(1)
        self.spi = SPI(1)
        self.spi = SPI(1,2000_000)
        self.spi = SPI(1,20000_000,polarity=0, phase=0,sck=Pin(SCK),mosi=Pin(MOSI),miso=None)
        self.dc = Pin(DC,Pin.OUT)
        self.dc(1)
        self.buffer = bytearray(self.height * self.width // 8)
        super().__init__(self.buffer, self.width, self.height, framebuf.MONO_HMSB)
        self.init_display()
        
        self.white =   0xffff
        self.balck =   0x0000
        
    def write_cmd(self, cmd):
        self.cs(1)
        self.dc(0)
        self.cs(0)
        self.spi.write(bytearray([cmd]))
        self.cs(1)

    def write_data(self, buf):
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(bytearray([buf]))
        self.cs(1)

    def init_display(self):
        """Initialize dispaly"""  
        self.rst(1)
        time.sleep(0.001)
        self.rst(0)
        time.sleep(0.01)
        self.rst(1)
        
        self.write_cmd(0xAE) #turn off OLED display

        self.write_cmd(0x00)   #set lower column address
        self.write_cmd(0x10)   #set higher column address 

        self.write_cmd(0xB0)   #set page address 
      
        self.write_cmd(0xdc)    #et display start line 
        self.write_cmd(0x00) 
        self.write_cmd(0x81)    #contract control 
        self.write_cmd(0x6f)    #128
        self.write_cmd(0x21)    # Set Memory addressing mode (0x20/0x21) #
    
        self.write_cmd(0xa0)    #set segment remap 
        self.write_cmd(0xc0)    #Com scan direction
        self.write_cmd(0xa4)   #Disable Entire Display On (0xA4/0xA5) 

        self.write_cmd(0xa6)    #normal / reverse
        self.write_cmd(0xa8)    #multiplex ratio 
        self.write_cmd(0x3f)    #duty = 1/64
  
        self.write_cmd(0xd3)    #set display offset 
        self.write_cmd(0x60)

        self.write_cmd(0xd5)    #set osc division 
        self.write_cmd(0x41)
    
        self.write_cmd(0xd9)    #set pre-charge period
        self.write_cmd(0x22)   

        self.write_cmd(0xdb)    #set vcomh 
        self.write_cmd(0x35)  
    
        self.write_cmd(0xad)    #set charge pump enable 
        self.write_cmd(0x8a)    #Set DC-DC enable (a=0:disable; a=1:enable)
        self.write_cmd(0XAF)
    def show(self):
        self.write_cmd(0xb0)
        for page in range(0,64):
            self.column = 63 - page              
            self.write_cmd(0x00 + (self.column & 0x0f))
            self.write_cmd(0x10 + (self.column >> 4))
            for num in range(0,16):
                self.write_data(self.buffer[page*16+num])

# end of library code

# OLED pins
DC = 8
RST = 12
MOSI = 11
SCK = 10
CS = 9

# pin definitions
OLED = OLED_1inch3()
sensor_pir = machine.Pin(28, machine.Pin.IN, machine.Pin.PULL_DOWN)
led_onboard = machine.Pin(25, machine.Pin.OUT)
buzzer_pin = machine.Pin(18, machine.Pin.OUT)
key0 = Pin(15, Pin.IN, Pin.PULL_UP)
key1 = Pin(17, Pin.IN, Pin.PULL_UP)

# wifi definitions
WIFI_SSID = 'DNA-XXX-XXX-XXX'
WIFI_PASSWORD = 'XXXX****'
MQTT_BROKER = '----------'
MQTT_PORT = 1883
MQTT_USER = 'ssaul'
MQTT_PASSWORD = 'XXXX****'
MQTT_TOPIC = b'PIR Sensor Active Alarm'

# making the connection to the wifi network
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(WIFI_SSID, WIFI_PASSWORD)


# global variables to control the program and communicate between interrupts and events
data = 'OFF'
intro = True
alarm = False
debug = False
sensor_on = False
interrupt_triggered = False 
led_onboard.value(0)

def pir_handler(pin):
    if sensor_on == True:
        global interrupt_triggered, debug, alarm
        interrupt_triggered = True
        alarm = True
        if alarm:
            if interrupt_triggered and debug == False:
                print("ALARM - 15S")
                led_onboard.value(1)
                client.publish(MQTT_TOPIC, b'ALARM TRIGGERED!')
                buzzer_pin.on()
                time.sleep(15)
                buzzer_pin.off()
            elif interrupt_triggered and debug:
                print("ALARM -- DEBUG")
                led_onboard.value(1)
                client.publish(MQTT_TOPIC, b'ALARM TEST!')
                buzzer_pin.on()
                time.sleep(0.6)
                buzzer_pin.off()
            else:
                led_onboard.value(0)
                buzzer_pin.off()
    
sensor_pir.irq(trigger=machine.Pin.IRQ_RISING, handler=pir_handler)

if __name__ == '__main__':
    client = MQTTClient("PIR OLED", MQTT_BROKER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD)
    client.connect()
    # Dragon Baby
    OLED.text("q q q q q ", 33, 30)
    OLED.text("= = = = = ", 33, 32)
    OLED.text("- - - - - ", 34, 33)
    OLED.text("/ / / / / ", 35, 31)
    # Dragon Eyes
    OLED.text("Loading...", 35, 3)
    # Nose
    OLED.text("PIR Sensor", 25, 20)
    OLED.text("Alarm Screen", 20, 40)
    # Display on the OLED
    OLED.show()
    for i in range(3):
        OLED.fill_rect(109, 3, 5, 9, 0)
        OLED.show()
        time.sleep(0.3)
        OLED.fill_rect(99, 3, 5, 9, 0)
        OLED.show()
        time.sleep(0.3)
        OLED.show()
        time.sleep(0.3)
        OLED.fill_rect(92, 3, 5, 9, 0)
        OLED.text("Loading...", 35, 3)
        OLED.show()
        time.sleep(0.3)
    OLED.fill_rect(0,0,128, 90,1)
    OLED.text("q q q q q ", 33, 30, 0)
    OLED.text("= = = = = ", 33, 32, 0)
    OLED.text("- - - - - ", 34, 33, 0)
    OLED.text("/ / / / / ", 35, 31, 0)
    OLED.text("PIR Inactive", 12, 20, 0)
    OLED.text("Please Stand By", 8, 40, 0)
    OLED.show()
    for i in range(3):
        OLED.fill_rect(112, 3, 5, 9, 1)
        OLED.show()
        time.sleep(0.3)
        OLED.fill_rect(105, 3, 5, 9, 1)
        OLED.show()
        time.sleep(0.3)
        OLED.show()
        time.sleep(0.3)
        OLED.fill_rect(97, 3, 5, 9, 1)
        OLED.text("Loading...", 32, 3, 0)
        OLED.show()
        time.sleep(0.3)
    time.sleep(1)
    OLED.fill_rect(0,0,128, 90, 0)
    OLED.text("q q q q q q", 16, 50, 1)
    OLED.text("= = = = = =", 16, 52, 1)
    OLED.text("- - - - - -", 17, 53, 1)
    OLED.text("/ / / / / /", 18, 51, 1)
    OLED.text("PIR Inactive", 2, 4, 1)
    OLED.text("Run", 2, 23, 1)
    OLED.text("Settings", 2, 36, 1)
    OLED.show()
    # Beginning of the program
    while(1):
        while not wifi.isconnected():
            time.sleep(1)
            print('Connected to WiFi:', wifi.ifconfig())
        if key0.value() == 0:
            OLED.fill_rect(0,0,128, 90, 0)
            OLED.text("q q q q q q", 16, 50, 1)
            OLED.text("= = = = = =", 16, 52, 1)
            OLED.text("- - - - - -", 17, 53, 1)
            OLED.text("/ / / / / /", 18, 51, 1)
            OLED.text("PIR Active", 2, 4, 1)
            OLED.text("Run <", 2, 23, 1)
            OLED.text("Settings", 2, 36, 1)
            OLED.show()
            if key0.value() == 0:
                OLED.fill_rect(0,0,128, 90, 0)
                OLED.text("q q q q q q", 16, 50, 1)
                OLED.text("= = = = = =", 16, 52, 1)
                OLED.text("- - - - - -", 17, 53, 1)
                OLED.text("/ / / / / /", 18, 51, 1)
                OLED.text("PIR Active", 2, 4, 1)
                OLED.text("Running... <", 2, 23, 1)
                OLED.text("Settings", 2, 36, 1)
                time.sleep(10)
                sensor_on = True
                OLED.show()
        else:
            OLED.show()
        if key1.value() == 0:
            led_onboard.value(0)
            sensor_on = False
            OLED.fill_rect(0,0,128, 90, 0)
            OLED.text("q q q q q q", 16, 50, 1)
            OLED.text("= = = = = =", 16, 52, 1)
            OLED.text("- - - - - -", 17, 53, 1)
            OLED.text("/ / / / / /", 18, 51, 1)
            OLED.text("PIR Inactive", 2, 4, 1)
            OLED.text("Run", 2, 23, 1)
            OLED.text("Settings <", 2, 36, 1)
            OLED.show()
            if key1.value() == 0:
                while True:
                    OLED.fill_rect(0,0,128, 90, 0)
                    OLED.text("q q q q q q", 16, 50, 1)
                    OLED.text("= = = = = =", 16, 52, 1)
                    OLED.text("- - - - - -", 17, 53, 1)
                    OLED.text("/ / / / / /", 18, 51, 1)
                    OLED.text("PIR Inactive", 2, 4, 1)
                    OLED.text("Settings:", 1, 23, 1)
                    OLED.text("DEBUG: " + str(data), 2, 36, 1)
                    OLED.show()
                    print(debug)
                    alarm = False
                    if key1.value() == 0 and debug == True:
                        OLED.fill_rect(0,0,128, 90, 0)
                        OLED.text("q q q q q q", 16, 50, 1)
                        OLED.text("= = = = = =", 16, 52, 1)
                        OLED.text("- - - - - -", 17, 53, 1)
                        OLED.text("/ / / / / /", 18, 51, 1)
                        OLED.text("PIR Inactive", 2, 4, 1)
                        OLED.text("Settings:", 1, 23, 1)
                        OLED.text("DEBUG: OFF <", 2, 36, 1)
                        print("Debug off, buzzer uptime limited to 15s")
                        data = 'OFF <'
                        debug = False
                        OLED.show()
                    if key1.value() == 0 and debug == False:
                        OLED.fill_rect(0,0,128, 90, 0)
                        OLED.text("q q q q q q", 16, 50, 1)
                        OLED.text("= = = = = =", 16, 52, 1)
                        OLED.text("- - - - - -", 17, 53, 1)
                        OLED.text("/ / / / / /", 18, 51, 1)
                        OLED.text("PIR Inactive", 2, 4, 1)
                        OLED.text("Settings:", 1, 23, 1)
                        OLED.text("DEBUG: ON <", 2, 36, 1)
                        print("Debug on, buzzer uptime limited to 6ms")
                        data = 'ON <'
                        debug = True
                        OLED.show()
                    if key0.value() == 0:
                        break
                    
