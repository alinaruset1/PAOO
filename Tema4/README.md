# Proiect Effective C++ - Tema: Flota Spațială

Acest proiect implementează următoarele reguli din *Effective C++* (Scott Meyers):

* **Item 4:** `NavaSpatiala` și `Motor` utilizează liste de inițializare în constructori pentru a evita asignarea târzie.
* **Item 5:** `BazaSpatiala` demonstrează cum compilatorul generează automat constructorul default, copy constructorul și copy assignment operatorul.
* **Item 6:** `ReactorNuclear` interzice explicit copierea și asignarea folosind `= delete` (astfel încât un reactor să rămână unicat).

## Build
```bash
mkdir build
cd build
cmake ..
make
./aplicatie_spatiu
```
