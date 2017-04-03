
include(metabench)

add_compile_options(-fconstexpr-steps=999999999)

metabench_add_dataset(scc_boost_dataset 
  "scc.cpp.erb" "(100000...1000000).step(100000)"
  ENV "{func: \"boost_strongly_connected_components\"}")
metabench_add_dataset(scc_dataset 
  "scc.cpp.erb" "(100000...1000000).step(100000)" 
  ENV "{func: \"strongly_connected_components\"}")

metabench_add_chart(scc_chart DATASETS scc_boost_dataset scc_dataset)
