rm -rf $2
mkdir $2
cmake .
make

echo Running search
bin/test_search > $1

echo Running animator
python scripts/run_animator.py $1 $2

echo Creating video
mencoder mf://$2*.png -mf w=800:h=600:fps=11:type=png -ovc lavc \
    -lavcopts vcodec=mpeg4:mbd=2:trell -oac copy -o $3
