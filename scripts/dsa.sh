#!/bin/sh
folderpath="/mnt/server/nishimoto/text"
outputpath="/mnt/server/nishimoto/output/dsa"

filearr=( "fib41" "rs.13" "tm29" "dblp.xml.00001.1" "dblp.xml.00001.2" "dblp.xml.0001.1" "dblp.xml.0001.2" "sources.001.2" 
"dna.001.1" "proteins.001.1" "english.001.2" "einstein.de.txt" "einstein.en.txt" "world_leaders" "influenza" "kernel" "cere" "coreutils" "Escherichia_Coli" "para")

for file in ${filearr[@]}; do
	echo "DSA : ${file}"
    nohup /usr/bin/time -f "# lazy ${file}, %e sec, %M KB" ~/list_order_maintenance/build/dsa.out -i ${folderpath}/${file} -o ${outputpath}/${file}.dsa -c u8 >> ~/output.txt 2>> ~/error.log
done