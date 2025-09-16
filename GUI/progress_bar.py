from PySide6.QtWidgets import QProgressBar
from PySide6.QtCore import QTimer

FAKE_MAX_PROGRESS = 0.9
UPDATE_MILLISECOND = 100

class ProgressBar90(QProgressBar):
    def __init__(self):
        super().__init__()
        self.setMinimum(0)
        self.setMaximum(UPDATE_MILLISECOND)
        self.max_progress = 1
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_progress_bar)

    def run_progress_bar(self, max:int):
        self.max_progress = max * 1000 
        self.setMaximum(self.max_progress * UPDATE_MILLISECOND )
        self.current_progress = 0
        self.setValue(0)
        #Milleseconds
        self.timer.start(UPDATE_MILLISECOND)

    #Change this once we have actual hooks, so that it reads how much data we've actually gotten instead
    def update_progress_bar(self):
        self.current_progress += 1 * UPDATE_MILLISECOND
        self.setValue(FAKE_MAX_PROGRESS * self.current_progress * UPDATE_MILLISECOND)
        # print(self.value())
        # print(f'{self.current_progress}/{self.max_progress}')
        if(self.current_progress >= self.max_progress):
            self.timer.stop()


    def end_progress_bar(self):
        self.setValue(self.max_progress * UPDATE_MILLISECOND)
        self.timer.stop()