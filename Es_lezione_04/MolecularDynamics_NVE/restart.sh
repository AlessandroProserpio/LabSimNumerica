echo "Run Molecular Dynamics w/ generation of previous configuration"
./clean.sh
cp config.fcc config.0
sed -i "1s/.*/0/g" input.dat

./MolDyn_NVE.exe

sed -i "1s/.*/1/g" input.dat

for i in {2..7}
do
	echo "Run Molecular Dynamics with old configuration #$i"
	cp old.final old.0
	cp config.final config.0

	./MolDyn_NVE.exe
done

cp old.final old.0
cp config.final config.0
