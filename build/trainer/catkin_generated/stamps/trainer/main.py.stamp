from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit, QFileDialog, QLabel
from PyQt5.QtGui import QPainter
from PyQt5.QtCore import QRect

import sys
from threading import *
import signal
import multiprocessing

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import random
import math
import matplotlib.pyplot as plt
import csv
import pandas as pd

import rospy
from std_msgs.msg import Int8, String
import rospkg


TRAIN_START = int(1)
TRAIN_STOP = int(0)
INTR_FLAG_START_TRAIN = int(1)
INTR_FLAG_STOP_TRAIN = int(2)
INTR_FLAG_LOAD_DATA = int(3)
INTR_FLAG_GET_LUT = int(4)


PROGRAM_STOP = int(99)
PROGRAM_START = int(1)

pub_misc_flag = rospy.Publisher('misc_flag', Int8, queue_size=10)
pub_train_flag = rospy.Publisher('train_flag', Int8, queue_size=10)
pub_data_file_name = rospy.Publisher('data_file_name', String, queue_size=10)
rospy.init_node('GUI', anonymous=True)
rate = rospy.Rate(50)  # 50hz


class Ui_MainWindow(object):

    interrupt_flag = None
    data_file = None
    status_program = None
    train_flag = 0
    data_file_name = "qwe"
    misc_flag = 0

    def GUI_transmit(self):
        # while not rospy.is_shutdown():
        while self.status_program == PROGRAM_START:
            # rospy.loginfo(self.train_flag)
            # rospy.loginfo(self.data_file_name)
            pub_data_file_name.publish(self.data_file_name)
            pub_train_flag.publish(self.train_flag)
            pub_misc_flag.publish(self.misc_flag)
            self.misc_flag = 0
            rate.sleep()

    def terminate(self, *args):
        self.status_program = PROGRAM_STOP
        exit()

    def __init__(self):
        super().__init__()
        signal.signal(signal.SIGINT, self.terminate)
        self.interrupt_flag = 0
        self.status_program = PROGRAM_START
        self.ros_thread = Thread(target=self.GUI_transmit)
        self.ros_thread.start()

    def setupUi(self, MainWindow):
        MainWindow.resize(506, 312)
        self.centralwidget = QtWidgets.QWidget(MainWindow)

        # Stop training button
        self.StopButton = QtWidgets.QPushButton(self.centralwidget)
        self.StopButton.setGeometry(QtCore.QRect(300, 150, 93, 28))
        self.StopButton.clicked.connect(self.stop_btn_action)
        self.StopButton.setEnabled(False)

        # Start training button
        self.StartButton = QtWidgets.QPushButton(self.centralwidget)
        self.StartButton.setGeometry(QtCore.QRect(100, 150, 93, 28))
        self.StartButton.clicked.connect(self.start_btn_action)
        self.StartButton.setEnabled(False)

        # Load file data
        self.LoadButton = QtWidgets.QPushButton(self.centralwidget)
        self.LoadButton.setGeometry(QtCore.QRect(100, 50, 93, 28))
        self.LoadButton.clicked.connect(self.load_data_btn_action)

        # Get current LUT
        self.GetLUTButton = QtWidgets.QPushButton(self.centralwidget)
        self.GetLUTButton.setGeometry(QtCore.QRect(300, 50, 93, 28))
        self.GetLUTButton.clicked.connect(self.get_lut_btn_action)
        self.GetLUTButton.setEnabled(False)

        # Quit button
        # self.QuitButton = QtWidgets.QPushButton(self.centralwidget)
        # self.QuitButton.setGeometry(QtCore.QRect(200, 250, 93, 28))
        # self.QuitButton.clicked.connect(self.quit_btn_action)

        MainWindow.setCentralWidget(self.centralwidget)
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.StopButton.setText(_translate("MainWindow", "Stop"))
        self.StartButton.setText(_translate("MainWindow", "Start"))
        self.LoadButton.setText(_translate("MainWindow", "Load data"))
        self.GetLUTButton.setText(_translate("MainWindow", "Get LUT"))
        # self.QuitButton.setText(_translate("MainWindow", "Quit"))

    def openFileNameDialog(self):
        rospack = rospkg.RosPack()
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        self.data_file_name, _ = QFileDialog.getOpenFileName(
            None, "Pilih file data", rospack.get_path('trainer') + "/../../", "All Files (*);;Data file (*.csv)", options=options)
        if self.data_file_name:
            print(self.data_file_name)
            return True
        return False

    def stop_btn_action(self):
        self.interrupt_flag = INTR_FLAG_STOP_TRAIN
        self.train_flag = int(TRAIN_STOP)
        self.GetLUTButton.setEnabled(False)

    def start_btn_action(self):
        self.interrupt_flag = INTR_FLAG_START_TRAIN
        self.train_flag = int(TRAIN_START)
        self.GetLUTButton.setEnabled(True)

    def load_data_btn_action(self):
        if (self.openFileNameDialog() == True):
            self.StopButton.setEnabled(True)
            self.StartButton.setEnabled(True)
            self.misc_flag = INTR_FLAG_LOAD_DATA

    def get_lut_btn_action(self):
        self.misc_flag = INTR_FLAG_GET_LUT

    def quit_btn_action(self):
        self.status_program = PROGRAM_STOP
        self.ros_thread.join()
        exit()

    def load_csv(self):
        self.data_file = pd.read_csv(self.data_file_name)
        self.StopButton.setEnabled(True)
        self.StartButton.setEnabled(True)
        print("Load data success")


if __name__ == "__main__":

    app = QtWidgets.QApplication(sys.argv)

    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()

    sys.exit(app.exec_())
