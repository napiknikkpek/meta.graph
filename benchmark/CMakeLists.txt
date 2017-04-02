
include(metabench)

metabench_add_dataset(scc_boost_dataset "scc_boost.cpp.erb" "(1000...12000).step(1000)")
metabench_add_dataset(scc_dataset "scc.cpp.erb" "(1000...12000).step(1000)")

metabench_add_chart(scc_chart DATASETS scc_boost_dataset scc_dataset)
