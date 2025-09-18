from PySide6.QtWidgets import QRadioButton, QWidget, QGridLayout
from pyqtgraph import PlotWidget, plot

class DataRadioButton(QRadioButton):
    def __init__(self, label:str, units:str):
        super().__init__()


        self.label = label
        self.units = units
        self.data = 0
        self.update_data(self.data)

    def update_data(self, new_data: float):
        self.data = new_data
        self.setText(f"{self.label} {self.data:.3f} {self.units}")



class MetricWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.grid_layout = QGridLayout()
        self.setLayout(self.grid_layout)

        self.data_radio_2 = DataRadioButton("ThroughRate:", "Mb/s")
        self.data_radio = DataRadioButton("PacketLoss", "Packets/s")
        self.grid_layout.addWidget(self.data_radio, 0, 0)
        self.grid_layout.addWidget(self.data_radio_2, 1, 0)
        self.plot = PlotWidget()
        self.grid_layout.addWidget(self.plot, 0, 1, 2, 1)