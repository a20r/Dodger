
cmake .
make -j8 -l8 $1

echo Running search
bin/$1 > sandbox/searches/$1.json

echo Running visualization
# rosbag record -a --output-name=sandbox/bags/$1.bag &
# bagpid=$!
python scripts/run_ros_animator.py sandbox/searches/$1.json
# kill -9 $bagpid
