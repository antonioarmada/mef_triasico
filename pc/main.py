import serial
import time
import yaml
import pyglet
from pyglet.window import Window
from pyglet.image import load


# read config.yaml
with open("config.yaml") as f:
    cfg = yaml.load(f, Loader=yaml.FullLoader)

# set serial port settings
no_serial = cfg['no_serial']    
try:
    if no_serial:
        ser = None
    else:
        ser = serial.Serial(cfg['port'], cfg['baudrate'])
except:
    print("Serial port not found")
    no_serial = True

time.sleep(2)

# Create a Pyglet window
window = Window(width=cfg['resolution'][0], height=cfg['resolution'][1])
window.set_fullscreen(cfg['fullscreen'])
window.set_exclusive_mouse(cfg['exclusive_mouse'])

# Load the image
image = load('assets/background.jpg') 
sprite = pyglet.sprite.Sprite(image)

# Scale the sprite to fit the screen
sprite.scale = min(window.width / sprite.width, window.height / sprite.height)

@window.event
def on_draw():
    window.clear()
    sprite.draw()

def update(dt):
    # Read serial data
    if not no_serial:
        if ser.inWaiting() > 0:
            line = ser.readline()
            print(line)

# Schedule the update function
pyglet.clock.schedule_interval(update, 1/60.0)

# Run the Pyglet app
pyglet.app.run()