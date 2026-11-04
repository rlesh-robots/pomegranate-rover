import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from std_msgs.msg import String

class MyTalker(Node):

    def __init__(self):
        super().__init__("my_talker")
        self.i = 0
        self.pub = self.create_publisher(String, 'my_chatter', 10)
        self.timer = self.create_timer(1, self.timercall)

    def timercall(self):
        msg = String()
        self.i += 1
        msg.data = f'Published {self.i} times'
        self.get_logger().info(f'publishing {self.i}')
        self.pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)

    node = MyTalker()

    try:
        rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()

if __name__ == '__main__':
    main()