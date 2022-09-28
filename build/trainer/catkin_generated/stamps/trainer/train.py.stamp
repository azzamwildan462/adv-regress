#!/usr/bin/env python
import rospy
import rospkg
from std_msgs.msg import String, Int8, Int16MultiArray
from trainer.msg import LUT

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import random
import math
import matplotlib.pyplot as plt
import csv
import pandas as pd


TRAIN_START = int(1)
TRAIN_STOP = int(0)
INTR_FLAG_START_TRAIN = int(1)
INTR_FLAG_STOP_TRAIN = int(2)
INTR_FLAG_LOAD_DATA = int(3)
INTR_FLAG_GET_LUT = int(4)

PROGRAM_STOP = int(99)
PROGRAM_START = int(1)


class NeuralNet(nn.Module):
    def __init__(self):
        super(NeuralNet, self).__init__()
        self.act_func = nn.Sigmoid()
        self.layer1 = nn.Linear(2, 100)
        self.layer2 = nn.Linear(100, 100)
        self.layer3 = nn.Linear(100, 1)

    def forward(self, x):
        x = self.act_func(self.layer1(x))
        x = self.act_func(self.layer2(x))
        x = self.layer3(x)
        return x


class TrainClass():
    train_flag = None
    data_file_name = None

    prev_train_flag = int(0)
    misc_flag = int(0)

    ws_path = " "

    def cllbck_file_name(self, data):
        self.data_file_name = data.data

    def cllbck_train_flag(self, data):
        self.train_flag = data.data

    def cllbck_misc_flag(self, data):
        self.misc_flag = data.data

    def load_csv(self):
        self.data_file = pd.read_csv(self.data_file_name)
        self.data_x = np.array(
            [self.data_file.values[:, 0], self.data_file.values[:, 1]], dtype=np.float32)
        self.data_y = np.array(
            [self.data_file.values[:, 2]], dtype=np.float32)
        self.data_x = self.data_x.transpose()
        self.data_y = self.data_y.transpose()
        self.data_x = torch.from_numpy(self.data_x)
        self.data_y = torch.from_numpy(self.data_y)
        # print(self.data_x)
        print("Load data success..")

    def tim50hz_cllbck(self, data):
        # Tipe trigger
        if self.misc_flag == INTR_FLAG_LOAD_DATA:
            self.load_csv()

        if self.train_flag == TRAIN_START and self.prev_train_flag == TRAIN_STOP:
            # Set NN Architecture
            self.model = NeuralNet()
            self.mse_loss = nn.MSELoss()
            self.optimizer = optim.Adam(self.model.parameters(), lr=0.0001)
            self.epoch = 0
            print("Setup train success")

        if self.train_flag == TRAIN_STOP and self.prev_train_flag == TRAIN_START:
            # model_buffer = copy.deepcopy(self.model)
            # torch.save(model_buffer, "model_train/temp_model.pth")

            theta_max = 360
            r_maks = 320
            lut = np.empty(r_maks*theta_max, dtype=int)
            input_buffer = np.random.random_sample((2, 2))
            th_iter = 0
            print("Creating a LUT model and saving it...")
            while th_iter < theta_max:
                r_iter = 0
                while r_iter < r_maks:
                    index = th_iter * r_maks + r_iter

                    input_buffer[0, 0] = (th_iter/180) - 1
                    input_buffer[0, 1] = (r_iter/160) - 1
                    input_buffer = torch.from_numpy(
                        np.array(input_buffer, dtype=np.float32))

                    pred = self.model(input_buffer[0, :])
                    r_lap = pred.data * 600 + 600

                    if (r_iter > 80):
                        lut[index] = r_lap
                    else:
                        lut[index] = 0
                    r_iter += 1
                th_iter += 1

            csv_path = self.ws_path + "LUT/lut_nn_r.csv"
            with open(csv_path, 'w', encoding='UTF8') as f:
                writer = csv.writer(f)
                writer.writerow(lut)

            print(("stop -> save"))

        self.prev_train_flag = self.train_flag

        while self.train_flag == TRAIN_START:
            self.optimizer.zero_grad()
            pred = self.model(self.data_x)
            loss = self.mse_loss(pred, self.data_y)
            loss.backward()
            self.optimizer.step()
            if (self.epoch + 1) % 1000 == 0:
                # torch.save(self.model, "model_train/temp_model.pth")
                print("Epoch %d  Loss %f" % (self.epoch + 1, loss.item()))
            if (self.misc_flag == INTR_FLAG_GET_LUT):
                theta_max = 360
                r_maks = 320
                lut = np.empty(r_maks*theta_max, dtype=int)
                input_buffer = np.random.random_sample((2, 2))
                th_iter = 0
                print("Creating a LUT model and saving it...")
                while th_iter < theta_max:
                    r_iter = 0
                    while r_iter < r_maks:
                        index = th_iter * r_maks + r_iter

                        input_buffer[0, 0] = (th_iter/180) - 1
                        input_buffer[0, 1] = (r_iter/160) - 1
                        input_buffer = torch.from_numpy(
                            np.array(input_buffer, dtype=np.float32))

                        pred = self.model(input_buffer[0, :])
                        r_lap = pred.data * 600 + 600

                        if (r_iter > 80):
                            lut[index] = r_lap
                        else:
                            lut[index] = 0
                        r_iter += 1
                    th_iter += 1

                csv_path = self.ws_path + "LUT/lut_nn_r.csv"
                with open(csv_path, 'w', encoding='UTF8') as f:
                    writer = csv.writer(f)
                    writer.writerow(lut)
                msg_lut = LUT()
                msg_lut.data = lut
                self.pub_misc_flag.publish(msg_lut)
            self.epoch += 1
            self.prev_train_flag = TRAIN_START

    def init_ros(self):
        rospack = rospkg.RosPack()
        self.ws_path = rospack.get_path('main') + "/../../"
        rospy.init_node('Trainer', anonymous=True)

        rospy.Subscriber("train_flag", Int8, self.cllbck_train_flag)
        rospy.Subscriber("data_file_name", String, self.cllbck_file_name)
        rospy.Subscriber("misc_flag", Int8, self.cllbck_misc_flag)
        self.pub_misc_flag = rospy.Publisher('LUT_buffer', LUT, queue_size=10)

        self.timer = rospy.Timer(rospy.Duration(0.02), self.tim50hz_cllbck)

        # spin() simply keeps python from exiting until this node is stopped
        rospy.spin()


if __name__ == '__main__':
    train = TrainClass()
    train.init_ros()
