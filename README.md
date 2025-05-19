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

![Klasių_diagram](https://github.com/user-attachments/assets/0d0bcf77-bed4-4eb5-8d11-9123d47ae9ae)


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


