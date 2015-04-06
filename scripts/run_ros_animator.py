

import rospy
import agent
import model
import path
import stpoint

import json
import sys
import time
# import math

from visualization_msgs.msg import Marker
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped


duration = 30


def print_usage():
    print "Usage:\n\tpython scripts/run_ros_animator.py"\
        + "[search json file name]"


def run():
    rospy.init_node("dodger_animator", anonymous=False)
    pub = rospy.Publisher(
        "visualization_marker", Marker, queue_size=1000)

    path_pub = rospy.Publisher(
        "dodger_path", Path, queue_size=1000)

    try:
        search_file = sys.argv[1]
        with open(search_file) as f:
            result = json.loads(f.read())
            agents = list()
            for ag in result["agents"]:
                try:
                    model_x = model.models[ag["x"]["type"]](*ag["x"]["params"])
                    model_y = model.models[ag["y"]["type"]](*ag["y"]["params"])
                    agents.append(agent.Agent(model_x, model_y))
                except TypeError:
                    agents.append(path.make(list()))
                    for p in ag:
                        agents[-1].append(stpoint.make(p["x"], p["y"], p["t"]))

            b_path = path.make(list())
            for st_p in result["path"]:
                b_path.append(stpoint.make(st_p["x"], st_p["y"], st_p["t"]))

            delta_t = 0.01
            t = 0
            while t < b_path[-1].t and not rospy.is_shutdown():
                stp, j = b_path(t, True)
                draw_path(b_path[:j + 1], path_pub)
                draw_stp_base(stp, pub, -1)
                draw_stp_base(b_path[-1], pub, -2, r=0, b=0, g=1, a=0.4)
                draw_stp_base(b_path[0], pub, -3, r=1, b=0, g=0, a=0.4)
                for i, ag in enumerate(agents):
                    draw_stp_base(ag(t), pub, i, bad_guy=True)
                t += delta_t
                time.sleep(5 * delta_t)
                # time.sleep(5)

    except IndexError:
        print_usage()


def draw_path(pth, pub):
    if not rospy.is_shutdown():
        ros_path = Path()
        ros_path.header.frame_id = "/my_frame"
        for i, stp in enumerate(pth):
            ps = PoseStamped()
            ps.header.frame_id = "/my_frame"
            ps.header.seq = i
            ps.pose.position.x = stp.x
            ps.pose.position.y = stp.y
            ros_path.poses.append(ps)

        pub.publish(ros_path)


def draw_stp_base(stp, pub, id_num, bad_guy=False, r=False, b=False,
                  g=False, a=False):
    if not rospy.is_shutdown():
        marker = Marker()
        marker.header.frame_id = "/my_frame"
        marker.lifetime = rospy.Duration(duration)
        marker.type = marker.MESH_RESOURCE

        if not bad_guy:
            marker.mesh_resource = "package://hector_quadrotor_description/"\
                + "meshes/quadrotor/quadrotor_base.dae"
        else:
            marker.mesh_resource = "package://pr2_description/meshes/"\
                + "base_v0/base.dae"

        marker.action = marker.ADD
        marker.scale.x = 0.3
        marker.scale.y = 0.3
        marker.scale.z = 0.3

        if r is False and g is False and b is False and a is False:
            marker.mesh_use_embedded_materials = True
        else:
            marker.color.r = r
            marker.color.g = g
            marker.color.b = b
            marker.color.a = a

        marker.pose.position.x = stp.x
        marker.pose.position.y = stp.y

        if bad_guy:
            marker.pose.position.z = 0
        else:
            marker.pose.position.z = 0.1

        marker.id = id_num
        pub.publish(marker)


if __name__ == "__main__":
    run()
