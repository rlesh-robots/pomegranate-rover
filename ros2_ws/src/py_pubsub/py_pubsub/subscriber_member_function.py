import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from std_msgs.msg import String

class MyListener(Node):
    def __init__(self):
        super().__init__('my_listener')
        self.sub = self.create_subscription(String, 'my_chatter', self.subscriber_callback, 10)
        self.get_logger().info(f'began subscription to "{self.sub.topic}"')

    def subscriber_callback(self, msg):
        self.get_logger().info(f'i heard: "{msg.data}"')

def main(args=None):
    rclpy.init(args=args)

    node = MyListener()
    try:
        rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()

if __name__ == '__main__':
    main()