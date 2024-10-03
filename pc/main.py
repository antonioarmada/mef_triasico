import serial
import time
import yaml
import pyglet
from pyglet.window import Window
from pyglet.image import load

from modules.videoplayer import  VideoPlayer as vp

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

# Create instances of VideoPlayer for different videos
video_player1 = vp('assets/boton_01.mp4',(0,0))  # Adjust the path as needed
video_player2 = vp('assets/boton_02.mp4',(400,0))  # Adjust the path as needed

# Start playing the first video
video_player1.play()
video_player2.play()  # You can play multiple videos simultaneously

@window.event
def on_draw():
    window.clear()
    video_player1.draw()
    video_player2.draw()  # Draw the second video

def update(dt):
    # Read serial data
    if not no_serial:
        if ser.inWaiting() > 0:
            line = ser.readline()
            print(line)


# Run the Pyglet app
pyglet.app.run()