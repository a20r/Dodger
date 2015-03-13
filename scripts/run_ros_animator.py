

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
from std_msgs.msg import ColorRGBA


duration = 10


def print_usage():
    print "Usage:\n\tpython scripts/run_ros_animator.py"\
        + "[search json file name]"


def run():
    rospy.init_node("dodger_animator", anonymous=False)
    pub = rospy.Publisher(
        "visualization_marker", Marker, queue_size=1000)
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
                stp = b_path(t)
                stp.z = 0.1
                draw_stp_base(stp, pub, -1)
                for i, ag in enumerate(agents):
                    draw_stp_base(ag(t), pub, i, True)
                t += delta_t
                time.sleep(5 * delta_t)

    except IndexError:
        print_usage()


def draw_stp_base(stp, pub, id_num, bad_guy=False):
    if not rospy.is_shutdown():
        marker = Marker()
        marker.header.frame_id = "/my_frame"
        marker.lifetime = rospy.Duration(duration)
        marker.type = marker.MESH_RESOURCE

        if not bad_guy:
            marker.mesh_resource = "package://hector_quadrotor_description/"\
                + "meshes/quadrotor/quadrotor_base.dae"
        else:
            marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae"

        marker.action = marker.ADD
        marker.scale.x = 0.3
        marker.scale.y = 0.3
        marker.scale.z = 0.3
        marker.mesh_use_embedded_materials = True

        marker.pose.orientation.w = 0
        marker.pose.orientation.x = 0
        marker.pose.orientation.y = 0
        marker.pose.orientation.z = 0

        marker.pose.position.x = stp.x
        marker.pose.position.y = stp.y
        marker.pose.position.z = stp.z
        marker.id = id_num
        pub.publish(marker)


if __name__ == "__main__":
    run()
