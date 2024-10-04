import pyglet
from pyglet import text
from datetime import datetime

class LogView:
    def __init__(self, position=(0, 0), visible=False, color=(255, 255, 255, 255), num_lines=10):
        self.position_x, self.position_y = position
        self.log_text = ""
        self.log_label = text.Label(self.log_text, font_name='Arial', font_size=14,
                                    x=self.position_x, y=self.position_y, anchor_y='top',
                                    multiline=True, width=400)  # Added width for multiline text
        self.log_label.color = color  # White color
        self.visible = visible
        self.log_lines = []
        self.max_lines = num_lines

    def add_log_line(self, line):
        timestamp = datetime.now().strftime("%H:%M:%S")
        formatted_line = f"[{timestamp}] {line}"
        self.log_lines.insert(0, formatted_line)  # Insert new line at the beginning
        self.log_lines = self.log_lines[:self.max_lines]  # Keep only the last 10 lines
        
        # Format the text with bold for the newest line
        formatted_text = [f"{self.log_lines[0]}"]
        formatted_text.extend(self.log_lines[1:])
        
        self.log_text = '\n'.join(formatted_text)
        self.log_label.text = self.log_text

    def draw(self):
        if self.visible:
            self.log_label.draw()
