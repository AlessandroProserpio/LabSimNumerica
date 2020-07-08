echo "EQUILIBRATING THE SYSTEM"
cp input.liquid input.dat
sed -i '7s#.*#1000#' input.dat
sed -i '8s#.*#1#' input.dat

./restart.sh


echo "RUNNING THE EQUILIBRATED SYSTEM"
./clean.sh
sed -i '7s#.*#100#' input.dat
sed -i '8s#.*#2000#' input.dat


./MolDyn_NVE.exe
