from PySide6.QtWidgets import QPushButton, QWidget, QGridLayout, QFileDialog
from progress_bar import ProgressBar90

class OutgoingDataWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.grid_layout = QGridLayout()
        self.setLayout(self.grid_layout)

        self.startButton = QPushButton("Send File")
        self.startButton.clicked.connect(self.select_file)
        
        self.progressBar = ProgressBar90()

        self.grid_layout.addWidget(self.startButton, 0, 0)
        self.grid_layout.addWidget(self.progressBar, 1, 0)



                # This will be changed once we have proper hooks
        self.endButton = QPushButton("End Progress Bar")
        self.endButton.clicked.connect(lambda : self.progressBar.end_progress_bar())
        self.grid_layout.addWidget(self.endButton, 2, 0)


    def select_file(self):
        filename, _ = QFileDialog.getOpenFileName(parent=self, caption="Open File", dir=".", filter="Text Files (*.txt);;All Files (*.*)")
        if filename:
            print(f"{filename}")
            self.progressBar.run_progress_bar(5)