from PySide6.QtWidgets import QRadioButton, QWidget, QGridLayout


class MetricWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.grid_layout = QGridLayout()
        self.setLayout(self.grid_layout)