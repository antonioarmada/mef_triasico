import serial
import time
import yaml
import pyglet
from pyglet.window import Window, key
from pyglet.image import load
from pyglet import text


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

mouse_debug_label = None
if cfg['debug']:
    mouse_debug_label = text.Label('Mouse: (0, 0)', font_name='Arial', font_size=14,
                             x=10, y=window.height - 10, anchor_y='top')

# Create instances of VideoPlayer for different videos
video_player1 = vp('assets/station_01.mp4',(cfg['position_1'][0],cfg['position_2'][1]))
video_player2 = vp('assets/station_02.mp4',(cfg['position_2'][0],cfg['position_2'][1]))
video_player3 = vp('assets/station_03.mp4',(cfg['position_3'][0],cfg['position_3'][1]))
video_player4 = vp('assets/station_04.mp4',(cfg['position_4'][0],cfg['position_4'][1]))
video_player5 = vp('assets/station_05.mp4',(cfg['position_5'][0],cfg['position_5'][1]))
video_player6 = vp('assets/station_06.mp4',(cfg['position_6'][0],cfg['position_6'][1]))

# Create a dictionary to map number keys to video players
video_players = {
    key._1: video_player1,
    key._2: video_player2,
    key._3: video_player3,
    key._4: video_player4,
    key._5: video_player5,
    key._6: video_player6
}

@window.event
def on_mouse_motion(x, y, dx, dy):
    if cfg['debug']:
        mouse_debug_label.text = f'Mouse: ({x}, {y})'

@window.event
def on_key_press(symbol, modifiers):
    print(f"Key pressed: {symbol}")
    if symbol in video_players:
        # Play the selected video
        selected_player = video_players[symbol]
        selected_player.restart()
        selected_player.visible = True

@window.event
def on_draw():
    window.clear()
    for player in video_players.values():
        player.draw()
    if cfg['debug']:
        mouse_debug_label.draw()

def update(dt):
    # Read serial data
    if not no_serial:
        if ser.inWaiting() > 0:
            line = ser.readline()
            print(line)


# Run the Pyglet app
pyglet.app.run()