from PySide6.QtWidgets import QApplication, QWidget, QGridLayout
from incoming_data_widget import IncomingDataWidget

from outgoing_data_widget import OutgoingDataWidget
from metric_widget import MetricWidget
# from outgoing_metric_widget import OutgoingDataMetricWidget
# from incoming_metric_widget import IncomingDataMetricWidget
import sys

app = QApplication(sys.argv)

window = QWidget()

grid_layout = QGridLayout()

grid_layout.addWidget(OutgoingDataWidget(), 0, 0)
grid_layout.addWidget(IncomingDataWidget(), 0, 1)
grid_layout.addWidget(MetricWidget(), 1, 0)
grid_layout.addWidget(MetricWidget(), 1, 1)

window.setLayout(grid_layout)



window.show()
app.exec()
