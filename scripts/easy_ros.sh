
cmake .
make -j8 -l8 $1

echo Running search
bin/$1 > sandbox/searches/$1.json

echo Running visualization
python scripts/run_ros_animator.py sandbox/searches/$1.json
