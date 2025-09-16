from PySide6.QtWidgets import QWidget, QVBoxLayout, QPushButton, QLineEdit
from PySide6.QtGui import QIntValidator
from PySide6.QtCore import QTimer

from progress_bar import ProgressBar90



class IncomingDataWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.box_layout = QVBoxLayout()
        self.setLayout(self.box_layout)

        self.progressBar = ProgressBar90()



        self.number = QLineEdit()
        self.number.setText('5')
        self.number.setValidator(QIntValidator(0, 100, self.number))

        # This will be changed once we have proper hooks
        self.startButton = QPushButton("Receieve File")
        self.startButton.clicked.connect(self.run_progress_bar)

        self.box_layout.addWidget(self.number)
        self.box_layout.addWidget(self.startButton)
        self.box_layout.addWidget(self.progressBar)

                # This will be changed once we have proper hooks
        self.endButton = QPushButton("End Progress Bar")
        self.endButton.clicked.connect(lambda : self.progressBar.end_progress_bar())
        self.box_layout.addWidget(self.endButton)



    def run_progress_bar(self):
        self.progressBar.run_progress_bar(int(self.number.text()))




