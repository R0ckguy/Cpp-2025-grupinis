# Cpp-2025-grupinis projektas
- **Projektas:** To-do app
- **Nariai:**
  - **Rokas Sirvydis**
  - **Lukas Zujevas**
  - **Mažvydas Peleckas**
  - **Ugnė Pacevičiūtė**

# Projekto aprašymas
- **Aprašymas:** Programa leidžianti kurti, redaguoti ir trinti užduotis su terminais, pažymėti jas atliktomis, filtruoti/rūšiuoti pagal terminą arba prioritetą.

# Use-case diagrama
![Use-case diagram](https://github.com/user-attachments/assets/6afb3c2a-881c-409b-a68f-a81efa502baf)

# Activity diagrama
![Activity diagram](https://github.com/user-attachments/assets/cf94452c-05cc-424e-b70b-0f15dce367a1)

![Klasių diagrama](https://github.com/user-attachments/assets/0d0bcf77-bed4-4eb5-8d11-9123d47ae9ae)

## Projektavimo šablonai

Šiame projekte taikomi šie projektavimo šablonai:

### Iteratorius (Iterator Pattern)
- **Kur rasti:** `TaskManager.cpp` metodai (`listAll()`, `searchByTitle()`), taip pat pagrindinė duomenų išvedimo vieta (`main.cpp`, ciklas `for (auto& t : list)`).
- **Kaip veikia:** Leidžia patogiai ir saugiai pereiti per užduočių sąrašą, neatsižvelgiant į jų saugojimo būdą.
- **Nauda:** Lankstumas dirbant su duomenų kolekcijomis, aiškesnė programos logika.

### Atsakomybės atskyrimas (Separation of Concerns)
- **Kur rasti:** Klasių struktūroje: `TaskManager` klasė valdo visą užduočių logiką, o `main.cpp` tik valdo vartotojo įvestis.
- **Kaip veikia:** Kiekviena komponentė atsakinga tik už savo funkcionalumą.
- **Nauda:** Lengvesnis kodų keitimas bei palaikymas, aiškesnė architektūra.

## Kaip paleisti projektą

### 🐧 Linux

#### 1. Įdiek priklausomybes (jei neturi):
```bash 
sudo apt install cmake g++ libnlohmann-json-dev
```

#### 2. Sukurk build katalogą:
```bash
mkdir build
cd build
```

#### 3. Sugeneruok projektą:
```bash
cmake ..
```

#### 4. Sukompiliuok:
```bash
make
```

#### 5. Paleisk programą:
```bash
./task_app
```

#### 6. Paleisk testus:
```bash
ctest --verbose
```

### 🪟 Windows (per MSYS2 + CLANG64)

#### 1. Įsidiek [MSYS2](https://www.msys2.org/)

#### 2. Paleisk *MSYS2 CLANG64* terminalą ir įdiek reikalingas programas:

```bash
pacman -Syu
pacman -S cmake clang make mingw-w64-clang-x86_64-nlohmann-json
```

#### 3. Sukurk build katalogą ir sugeneruok projektą:

```bash
cd C:/kelias/iki/projekto
mkdir build
cd build
cmake ..
```

#### 4. Sukompiliuok projektą:

```bash
mingw32-make
```

#### 5. Paleisk programą:

```bash
./task_app.exe
```

#### 6. Paleisk testus:

```bash
ctest --verbose
```
