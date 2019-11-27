empty_binary="__empty__binary__"
empty_main=".test_empty.c"
supp_file=".my_supp.supp"
gcc -o $empty_binary $empty_main
valgrind --leak-check=full --gen-suppressions=all "./${empty_binary}" 2>&1 | perl .supp_getter.perl > $supp_file
rm $empty_binary
rm -rf "${empty_binary}.dSYM"
