import serial
import time
import yaml
import pyglet
import sys
from pyglet.window import Window, key
from pyglet.image import load
from pyglet import text
from pyglet.clock import schedule_interval

import threading
import queue

from modules.videoplayer import  VideoPlayer as vp
from modules.logview import LogView


# read config.yaml
with open("config.yaml") as f:
    cfg = yaml.load(f, Loader=yaml.FullLoader)

# Create a LogView instance   
log_view = LogView(position=(cfg['logview_position'][0],cfg['logview_position'][1]), visible=True, color=cfg['logview_color'], num_lines=cfg['logview_lines'])

# set serial port settings
no_serial = cfg['no_serial']  
try:
    if no_serial:
        ser = None
        log_view.add_log_line("Serial skipped: no_serial=True")
    else:
        ser = serial.Serial(cfg['port'], cfg['baudrate'])
        ser.reset_input_buffer()
        log_view.add_log_line("OK: Serial port opened")
except:
    print(f"Serial port error: {sys.exc_info()[1]}")
    log_view.add_log_line(f"Serial port error! {sys.exc_info()[1]}")
    no_serial = True
time.sleep(2)

#Create a queue for serial data
serial_queue = queue.Queue()

# Thread function for reading serial data
def read_serial():
    print("Serial reading thread started")
    while True:
        if ser and ser.in_waiting:
            try:
                line = ser.readline().decode('utf-8').strip()
                serial_queue.put(line)
            except serial.SerialException as e:
                print(f"Serial error: {e}")
        time.sleep(1)  # Increase sleep time for less frequent checks

# Start the serial reading thread
if not no_serial:
    serial_thread = threading.Thread(target=read_serial, daemon=True)
    serial_thread.start()
    print("Thread started")

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
    log_view.add_log_line("key pressed: " + str(symbol))
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
        log_view.draw()

def update(dt):
    while not serial_queue.empty():
        line = serial_queue.get()
        try:
            # Parse the serial data
            data = int(line)
            video_id = data // 100  # Get the first digit
            action = data % 10      # Get the last digit
            
            # Map video ID to video player
            video_player = video_players.get(getattr(key, f"_{video_id}"))
            
            if video_player and action == 2:
                video_player.restart()
                video_player.visible = True
                log_view.add_log_line(f"Playing video {video_id}")
            else:
                log_view.add_log_line(f"Invalid video ID or action: {data}")
        except ValueError:
            log_view.add_log_line(f"Invalid serial data format: {line}")
        
        print(f"Processed serial data: {line}")
        log_view.add_log_line(f"Serial: {line}")

schedule_interval(update, 1/30.0)  # Call update 30 times per second

schedule_interval(update, 1/30.0)  # Call update 30 times per second

# Run the Pyglet app
pyglet.app.run()