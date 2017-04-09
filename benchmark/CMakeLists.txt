
include(metabench)

add_compile_options(-fconstexpr-steps=999999999)

metabench_add_dataset(scc_boost_dataset 
  "scc.cpp.erb" "(100000...1000000).step(100000)"
  ENV "{func: \"boost_strongly_connected_components\"}")
metabench_add_dataset(scc_dataset 
  "scc.cpp.erb" "(100000...1000000).step(100000)" 
  ENV "{func: \"strongly_connected_components\"}")

metabench_add_chart(scc_chart DATASETS scc_boost_dataset scc_dataset)

metabench_add_dataset(insert_sort "sort.cpp.erb" "(0..5000).step(500)")

metabench_add_chart(sort_chart DATASETS insert_sort)

metabench_add_dataset(prim_dataset "prim.cpp.erb" "(100000...1000000).step(100000)")

metabench_add_chart(prim_chart DATASETS prim_dataset)
