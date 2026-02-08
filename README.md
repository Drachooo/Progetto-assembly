# Pianificatore di Attività Produttive (Assembly AT&T)

**Autori:** Matteo Drago (VR500241), Marco Broccolato (VR501013)
**Corso:** Architettura degli Elaboratori
**Anno Accademico:** 2023/2024
**Università:** Università di Verona

---

## 📋 Descrizione del Progetto

Questo progetto consiste in un software sviluppato in **Assembly (sintassi AT&T)** per la pianificazione ottimizzata delle attività di un sistema produttivo.
Il sistema simula una linea di produzione che può gestire un prodotto alla volta, allocando "slot temporali" per minimizzare le penalità dovute ai ritardi di consegna.

Il software legge un file di ordini, permette all'utente di scegliere tra due algoritmi di scheduling (**EDF** o **HPF**) e calcola l'ordine di esecuzione ottimale e le eventuali penalità monetarie accumulate.

### ⚙️ Caratteristiche del Prodotto
Ogni prodotto è definito da 4 valori interi:
1.  **Identificativo (ID):** Codice univoco (1-127).
2.  **Durata:** Slot temporali necessari alla produzione (1-10).
3.  **Scadenza:** Tempo massimo entro cui completare il prodotto (1-100).
4.  **Priorità:** Valore (1-5) che indica sia l'importanza che il costo della penalità per unità di tempo di ritardo.

---

## 🧠 Algoritmi Implementati

Il programma implementa due algoritmi di ordinamento basati sulla logica *Selection Sort* che operano direttamente sullo stack:

### 1. EDF (Earliest Deadline First)
Pianifica per primi i prodotti con la **scadenza più vicina**.
* *Tie-break:* In caso di parità di scadenza, viene data precedenza al prodotto con **priorità più alta**.

### 2. HPF (Highest Priority First)
Pianifica per primi i prodotti con la **priorità più alta**.
* *Tie-break:* In caso di parità di priorità, viene data precedenza al prodotto con la **scadenza più vicina**.

---

## 🛠️ Struttura del Progetto

Il codice sorgente è modulare e suddiviso nei seguenti file `.s`:

* `pianificatore.s`: Main del programma, gestisce il flusso principale e l'I/O su file.
* `intestazione.s`: Stampa l'interfaccia utente e il menu di scelta.
* `nome.s`: Gestisce la lettura del file di input, il parsing (string to int), il controllo dei range e il caricamento nello stack.
* `edf.s`: Implementazione dell'algoritmo di ordinamento Earliest Deadline First.
* `hpf.s`: Implementazione dell'algoritmo di ordinamento Highest Priority First.
* `printOutput.s`: Gestisce la stampa dei risultati formattati su terminale.
* `printOutputFile.s`: Gestisce la scrittura dei risultati su file di output (se richiesto).

---

## 🚀 Istruzioni per l'Uso

### Compilazione
Per compilare il progetto, utilizzare `gcc` linkando tutti i file sorgente. Eseguire il seguente comando nella directory del progetto:

```bash
gcc -m32 -o pianificatore pianificatore.s intestazione.s nome.s edf.s hpf.s printOutput.s printOutputFile.s
```

*(Nota: Il flag `-m32` è necessario per la compatibilità con architetture a 32 bit).*

### Esecuzione
Il software deve essere lanciato da riga di comando specificando il file degli ordini come argomento:

```bash
./pianificatore <percorso_file_ordini>
```

**Esempio:**
```bash
./pianificatore Ordini.txt
```

### Formato File di Input
Il file deve contenere un prodotto per riga (massimo 10 ordini), con i valori separati da virgole nel formato: `ID,Durata,Scadenza,Priorità`.

Esempio `Ordini.txt`:
```text
4,10,12,4
12,7,32,1
```

---

## 💡 Esempi di Esecuzione

Di seguito viene mostrato un esempio pratico di pianificazione con due ordini, per evidenziare le differenze tra gli algoritmi EDF e HPF.

### Dati di Input
Supponiamo di avere un file contenente i seguenti due prodotti:
* **Prodotto 4:** Durata 10, Scadenza 12, Priorità 4.
* **Prodotto 12:** Durata 7, Scadenza 32, Priorità 5.

### Caso 1: Algoritmo EDF (Earliest Deadline First)
L'algoritmo sceglie il **Prodotto 4** per primo (scadenza 12 < 32).

**Output:**
```text
Pianificazione EDF:
4:0        <-- ID 4 inizia al tempo 0
12:10      <-- ID 12 inizia al tempo 10
Conclusione: 17
Penalty: 0
```
*Analisi:* Entrambi i prodotti finiscono entro la loro scadenza. Nessuna penalità.

### Caso 2: Algoritmo HPF (Highest Priority First)
L'algoritmo sceglie il **Prodotto 12** per primo (priorità 5 > 4).

**Output:**
```text
Pianificazione HPF:
12:0       <-- ID 12 inizia al tempo 0
4:7        <-- ID 4 inizia al tempo 7
Conclusione: 17
Penalty: 20
```
*Analisi:* Il Prodotto 4 termina al tempo 17 (scadenza 12). Ritardo di 5 unità. Penalità: 5 * 4 = 20.

---

## 📂 File di Test Inclusi
Nella repository sono presenti diversi file per testare i casi limite:
* `EDF.txt`: Penalità zero con EDF, maggiore di zero con HPF.
* `None.txt`: Penalità presente con entrambi gli algoritmi.
* `Both.txt`: Penalità zero con entrambi gli algoritmi.
* `Error.txt`: File malformato per testare la gestione errori (valori fuori range).
