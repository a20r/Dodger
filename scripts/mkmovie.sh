cmake .
make
rm -rf sandbox/figs/*
bin/test_search > instances/result.json
python tests/roadmap_test.py
cd sandbox/figs; mencoder mf://*.png -mf w=800:h=600:fps=13:type=png -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell -oac copy -o output.avi; cd -;
