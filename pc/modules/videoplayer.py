import pyglet
import imageio
import numpy as np  # Import numpy to flip the image

class VideoPlayer:
    def __init__(self, video_path, position=(0, 0)):
        # Initialize the video reader
        self.reader = imageio.get_reader(video_path)
        self.position_x, self.position_y = position
        self.n_frames = self.reader.get_length()  # Total number of frames
        self.fps = self.reader.get_meta_data()['fps']  # Frames per second
        self.current_frame_index = 0
        self.visible = False
   
        # Load the first frame and flip it vertically
        self.first_frame = self.reader.get_data(self.current_frame_index)
        self.first_frame = np.flipud(self.first_frame)  # Flip the frame vertically
        height, width, _ = self.first_frame.shape
        self.texture = pyglet.image.ImageData(width, height, 'RGB', self.first_frame.tobytes())
        
    def play(self):
        self.visible = True
        pyglet.clock.schedule_interval(self.update, 1 / self.fps)  # Schedule updates

    def restart(self):
        self.visible = True
        self.current_frame_index = 0
        pyglet.clock.schedule_interval(self.update, 1 / self.fps)

    def update(self, dt):
        self.current_frame_index += 1
        
        if self.current_frame_index < self.n_frames:
            try:
                # Read the next frame from the video
                frame = self.reader.get_data(self.current_frame_index)
                # Flip the frame vertically
                frame = np.flipud(frame)
                # Update the texture with the new frame data
                height, width, _ = frame.shape
                self.texture = pyglet.image.ImageData(width, height, 'RGB', frame.tobytes())
            except IndexError:
                self.end_video()
        else:
            self.end_video()
    
    def end_video(self):
        print(f"End of video reached for {self}")
        pyglet.clock.unschedule(self.update)
        self.visible = False

    def draw(self):
        if self.visible:
            self.texture.blit(self.position_x, self.position_y)