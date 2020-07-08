echo "Simulating Ising 1D model for T \in [0.5, 2] with steps of \Delta T = 0.1"

if [ -f ene.dat ]; then 
	rm ene.dat
fi

if [ -f heatcap.dat ]; then 
	rm heatcap.dat
fi

if [ -f magn.dat ]; then 
	rm magn.dat
fi

if [ -f msusc.dat ]; then 
	rm msusc.dat
fi


for temp in $(seq 0.5 0.1 2.0)
do
	sed -i "1s/.*/$temp/g" input.dat
	sed -i "s/\([0-9]\),/\1./g" input.dat
	./clean.sh
	./Monte_Carlo_ISING_1D.exe
	tail -1 output.ene.0 | awk -v var="$temp" '{print var, $3, $4}' >> ene.dat
	sed -i "s/\([0-9]\),/\1./g" ene.dat
	tail -1 output.heatcap.0 | awk -v var="$temp" '{print var, $3, $4}' >> heatcap.dat
	sed -i "s/\([0-9]\),/\1./g" heatcap.dat
	tail -1 output.magn.0 | awk -v var="$temp" '{print var, $3, $4}' >> magn.dat
	sed -i "s/\([0-9]\),/\1./g" magn.dat
	tail -1 output.msusc.0 | awk -v var="$temp" '{print var, $3, $4}' >> msusc.dat
	sed -i "s/\([0-9]\),/\1./g" msusc.dat
done
