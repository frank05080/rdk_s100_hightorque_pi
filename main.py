import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
import numpy as np
from datetime import datetime
import os
import sys
sys.path.append("/root/model_task-s100/build")
import libmodel_task

class Float32MultiArraySaver(Node):
    def __init__(self):
        super().__init__('float32_multiarray_saver')
        self.subscription = self.create_subscription(
            Float32MultiArray,
            '/input_data_topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.pub = self.create_publisher(Float32MultiArray, '/inf_res', 10)

        self.inf = libmodel_task.ModelTask()
        self.inf.ModelInit("~/gaoqin/policy.hbm")

    def listener_callback(self, msg: Float32MultiArray):
        data = np.array(msg.data, dtype=np.float32).reshape(1,-1)
        print(data.shape)
        res = self.inf.ModelInfer([data])[0]
        print("after")
        print(res)

        output_msg = Float32MultiArray()
        output_msg.data = res
        self.pub.publish(output_msg)


def main(args=None):
    rclpy.init(args=args)
    node = Float32MultiArraySaver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Shutting down node...')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

