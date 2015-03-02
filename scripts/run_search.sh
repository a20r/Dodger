
cmake .
make -j8 -l8

bash scripts/mkmovie.sh $1 $2 $3 $4
python scripts/run_drawer.py $1$4.json
